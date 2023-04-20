// Fill out your copyright notice in the Description page of Project Settings.


#include "Manix/BouncingBall/ManixBouncingBlock.h"
#include "Components/CapsuleComponent.h"
#include "Components/WidgetComponent.h"
#include "Components/PrimitiveComponent.h"
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
		BouncingBlock.Add(StaticMesh);
		BouncingBlockMaterials.Add(DefaultMaterial);
		StaticMesh->SetupAttachment(Root);
	}

	MainBouncingComponent = CreateDefaultSubobject<UStaticMeshComponent>(FName(FString(TEXT("MainBouncingComponent"))));
	MainBouncingComponent->SetupAttachment(Root);

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


