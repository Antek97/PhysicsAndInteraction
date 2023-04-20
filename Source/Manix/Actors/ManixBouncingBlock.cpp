// Fill out your copyright notice in the Description page of Project Settings.


#include "Manix/Actors/ManixBouncingBlock.h"
#include "Components/CapsuleComponent.h"
#include "Components/WidgetComponent.h"
#include "Components/PrimitiveComponent.h"
#include "Components/WidgetComponent.h"
#include "Kismet/GameplayStatics.h"
#include "Kismet/KismetMathLibrary.h"
#include "Manix/ManixCharacter.h"
#include "Manix/Widgets/ManixInteractWidget.h"
#include "Materials/Material.h"

AManixBouncingBlock::AManixBouncingBlock()
{
	PrimaryActorTick.bCanEverTick = false;

	Root = CreateDefaultSubobject<USceneComponent>(FName(TEXT("Root")));
	SetRootComponent(Root);
	
	for (int32 index = 0; index < BouncingBlockQuantity; ++index)
	{
		UStaticMeshComponent* StaticMesh = CreateDefaultSubobject<UStaticMeshComponent>(FName(FString::Printf(TEXT("BouncingBlock_%d"), index)));
		BouncingBlock.Add(StaticMesh);
		BouncingBlockMaterials.Add(DefaultMaterial);
		StaticMesh->SetupAttachment(Root);
	}

	MainBouncingComponent = CreateDefaultSubobject<UStaticMeshComponent>(FName(FString(TEXT("MainBouncingComponent"))));
	MainBouncingComponent->SetupAttachment(Root);

	TrackingComponent = CreateDefaultSubobject<UStaticMeshComponent>(FName(FString(TEXT("TrackingComponent"))));
	TrackingComponent->SetupAttachment(Root);

	WidgetComponent = CreateDefaultSubobject<UWidgetComponent>(FName(TEXT("Widget")));
	WidgetComponent->SetupAttachment(MainBouncingComponent);

	TriggerCapsule = CreateDefaultSubobject<UCapsuleComponent>(TEXT("TriggerCapsule"));
	TriggerCapsule->InitCapsuleSize(200.f, 200.f);
	TriggerCapsule->SetCollisionProfileName(TEXT("Trigger"));
	TriggerCapsule->SetupAttachment(MainBouncingComponent);

	MainBouncingComponent->OnComponentHit.AddDynamic(this, &AManixBouncingBlock::OnHit);
}

void AManixBouncingBlock::BeginPlay()
{
	Super::BeginPlay();

	ACharacter* MyCharacter = UGameplayStatics::GetPlayerCharacter(this, 0);

	PlayerCharacter = Cast<AManixCharacter>(MyCharacter);
	GetWorld()->GetTimerManager().SetTimer(HandleTimer, this, &AManixBouncingBlock::Tracking, 0.1f, true);
}

void AManixBouncingBlock::Tracking()
{
	if(PlayerCharacter != nullptr)
	{
		FVector PlayerLocation = PlayerCharacter->GetActorLocation();
		FVector TrackingComponentLocation = TrackingComponent->GetComponentLocation();

		FRotator TargetRotation = UKismetMathLibrary::FindLookAtRotation(PlayerLocation, TrackingComponentLocation);
		TrackingComponent->SetWorldRotation(TargetRotation);
	}
}

void AManixBouncingBlock::NotifyActorBeginOverlap(AActor* OtherActor)
{
	if (InteractWidget == nullptr)
	{
		InteractWidget = Cast<UManixInteractWidget>(WidgetComponent->GetWidget());
	}

	if (InteractWidget)
	{
		InteractWidget->UpdateInteractText(TextWidget);
		InteractWidget->ToggleInteractVisibility(true);
	}
}

void AManixBouncingBlock::NotifyActorEndOverlap(AActor* OtherActor)
{
	if (InteractWidget)
	{
		InteractWidget->ToggleInteractVisibility(false);
	}
}

void AManixBouncingBlock::OnHit(UPrimitiveComponent* HitComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, FVector NormalImpulse, const FHitResult& Hit)
{
	if (bIsFirstHit)
	{
		bIsFirstHit = false;

		for (size_t index = 0; index < BouncingBlock.Num(); index++)
		{
			if (BouncingBlock[index] != nullptr)
			{
				UStaticMeshComponent* BlockMesh = BouncingBlock[index];
				UMaterial* BlockMaterial = BouncingBlockMaterials[index];
				BlockMesh->SetMaterial(0, BlockMaterial);
			}
		}
		MainBouncingComponent->SetMaterial(0, DefaultMaterial);
	}
}


