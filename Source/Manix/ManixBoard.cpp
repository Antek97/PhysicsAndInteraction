// Fill out your copyright notice in the Description page of Project Settings.

#include "ManixBoard.h"
#include "Components/WidgetComponent.h"
#include "Components/CapsuleComponent.h"
#include "Materials/Material.h"
#include "ManixInteractWidget.h"
#include "Components/PrimitiveComponent.h"
#include "PhysicalMaterials/PhysicalMaterial.h"

AManixBoard::AManixBoard()
{
	PrimaryActorTick.bCanEverTick = false;

	Root = CreateDefaultSubobject<USceneComponent>(FName(TEXT("Root")));
	SetRootComponent(Root);

	for (int32 index = 0; index < CubesQuantity; ++index)
	{
		UStaticMeshComponent* StaticMesh = CreateDefaultSubobject<UStaticMeshComponent>(FName(FString::Printf(TEXT("Cube_%d"), index)));
		BoardComponents.Add(StaticMesh);
		StateComponents.Add(Basic);
		StaticMesh->AttachTo(RootComponent);
	}

	WidgetComponent = CreateDefaultSubobject<UWidgetComponent>(FName(TEXT("Widget")));
	WidgetComponent->SetupAttachment(BoardComponents[specialCubes]);

	TriggerCapsule = CreateDefaultSubobject<UCapsuleComponent>(TEXT("TriggerCapsule"));
	TriggerCapsule->InitCapsuleSize(200.f, 200.f);
	TriggerCapsule->SetCollisionProfileName(TEXT("Trigger"));
	TriggerCapsule->SetupAttachment(BoardComponents[specialCubes]);
}

void AManixBoard::BeginPlay()
{
	Super::BeginPlay();
}

void AManixBoard::Interact(FName Component)
{
	for (auto index = 0; index < BoardComponents.Num(); index++)
	{
		if (FName(BoardComponents[index]->GetName()) == Component)
		{
			if (StateComponents[index] != Used)
			{
				UStaticMeshComponent* StaticComponent = BoardComponents[index];
				StaticComponent->SetMaterial(0, MaterialUsed);

				if (bFirstActiveObject)
				{
					if (InteractWidget)
					{
						InteractWidget->UpdateInteractText(UsedInteractText);
					}
					bFirstActiveObject = !bFirstActiveObject;
				}
				StateComponents[index] = Used;
				StaticComponent->SetSimulatePhysics(true);
			}
		}
	}
}

void AManixBoard::LookOver(FName Component)
{
	if(bNoticicationOverlap)
	{ 
		for (auto index = 0; index < BoardComponents.Num(); index++)
		{
			if (FName(BoardComponents[index]->GetName()) == Component)
			{
				if (StateComponents[index] != Used)
				{
					BoardComponents[index]->SetMaterial(0, MaterialMarked);
					StateComponents[index] = Marked;
				}
			}
		}
	}
}

void AManixBoard::NotifyActorBeginOverlap(AActor* OtherActor)
{
		if (InteractWidget == nullptr)
		{
			InteractWidget = Cast<UManixInteractWidget>(WidgetComponent->GetWidget());
		}

		if (InteractWidget)
		{
			if (bFirstActiveObject)
			{
				InteractWidget->UpdateInteractText(InteractText);
			}
			InteractWidget->ToggleInteractVisibility(true);
		}

		bNoticicationOverlap = true;
}

void AManixBoard::NotifyActorEndOverlap(AActor* OtherActor)
{
	if (InteractWidget)
	{
		InteractWidget->ToggleInteractVisibility(false);
	}

	bNoticicationOverlap = false;
}