// Fill out your copyright notice in the Description page of Project Settings.


#include "Manix/BouncingBall/ManixBouncingBlock.h"
#include "Components/CapsuleComponent.h"
#include "Components/WidgetComponent.h"
#include "Manix/ManixInteractWidget.h"
#include "Materials/Material.h"

AManixBouncingBlock::AManixBouncingBlock()
{
	PrimaryActorTick.bCanEverTick = false;

	Root = CreateDefaultSubobject<USceneComponent>(FName(TEXT("Root")));
	SetRootComponent(Root);
	
	for (int32 index = 0; index < BouncingBlockQuantity; ++index)
	{
		UStaticMeshComponent* StaticMesh = CreateDefaultSubobject<UStaticMeshComponent>(FName(FString::Printf(TEXT("BouncingBlock_%d"), index)));
		BouncingBlocks.Add(StaticMesh, false);
		BouncingBlock.Add(StaticMesh);
		StaticMesh->AttachTo(Root);
	}

	MainBouncingComponent = CreateDefaultSubobject<UStaticMeshComponent>(FName(FString(TEXT("MainBouncingComponent"))));
	MainBouncingComponent->AttachTo(Root);

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
	InteractWidget->ToggleInteractVisibility(false);
}

void AManixBouncingBlock::OnHit(UPrimitiveComponent* HitComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, FVector NormalImpulse, const FHitResult& Hit)
{
	//Hit
//zmiana na kazdym materai³u SetMaterial(0, MaterialMarked);
	GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::Yellow, TEXT("Your"));
}


