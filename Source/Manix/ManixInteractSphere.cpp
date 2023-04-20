// Fill out your copyright notice in the Description page of Project Settings.


#include "ManixInteractSphere.h"
#include "Components/CapsuleComponent.h"
#include "Components/TimelineComponent.h"
#include "Components/WidgetComponent.h"
#include "ManixInteractWidget.h"
#include "ManixCharacter.h"
#include "Curves/CurveFloat.h"

// Sets default values
AManixInteractSphere::AManixInteractSphere()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	Root = CreateDefaultSubobject<USceneComponent>(FName(TEXT("Root")));
	SetRootComponent(Root);

	BouncingBall = CreateDefaultSubobject<UStaticMeshComponent>(FName(TEXT("Ball")));
	BouncingBall->SetupAttachment(Root);

	RotatingCube = CreateDefaultSubobject<UStaticMeshComponent>(FName(TEXT("Cube")));
	RotatingCube->SetupAttachment(Root);

	WidgetComponent = CreateDefaultSubobject<UWidgetComponent>(FName(TEXT("Widget")));
	WidgetComponent->SetupAttachment(Root);

	TriggerCapsule = CreateDefaultSubobject<UCapsuleComponent>(TEXT("TriggerCapsule"));
	TriggerCapsule->InitCapsuleSize(200.f, 200.f);
	TriggerCapsule->SetCollisionProfileName(TEXT("Trigger"));
	TriggerCapsule->SetupAttachment(Root);

}

// Called when the game starts or when spawned
void AManixInteractSphere::BeginPlay()
{
	Super::BeginPlay();

	// Todo: spin Box

	if (CurveFloat)
	{
	//	FOnImelineFloat TimelineProgress;
	//	TimelineProgress.BindUFunction(this, FName("TimelineProgress"));
	//	CurveTimeline.AddInterpFloat(CurveFloat, TimelineProgress);
	}
}

void AManixInteractSphere::NotifyActorBeginOverlap(AActor* OtherActor)
{

	if (InteractWidget == nullptr)
	{
		InteractWidget = Cast<UManixInteractWidget>(WidgetComponent->GetWidget());
	}

	if (InteractWidget)
	{	
		if (bFirstTimeFocus)
		{
			InteractWidget->UpdateInteractText(FirstStateText);
		}
		InteractWidget->ToggleInteractVisibility(true);
	}

	bNoticicationOverlap = true;
}

void AManixInteractSphere::NotifyActorEndOverlap(AActor* OtherActor)
{
	if (InteractWidget)
	{
		InteractWidget->ToggleInteractVisibility(false);
	}

	bNoticicationOverlap = false;
}

void AManixInteractSphere::ActionRotation(float RunningTime)
{
	float DeltaZ = Amplitude * FMath::Sin(RunningTime * TimeConstant);
	RotatingCube->SetRelativeRotation(FRotator(0, DeltaZ, 0));
}

void AManixInteractSphere::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	
	CurveTimeline.TickTimeline(DeltaTime);
}

void AManixInteractSphere::Interact(FName Component)
{
	if (Component == BouncingBall->GetFName()) 
	{
		if (CurveFloat)
		{
			FOnTimelineFloat TimelineProgress;
			TimelineProgress.BindUFunction(this, FName("TimelineProgress"));
			CurveTimeline.AddInterpFloat(CurveFloat, TimelineProgress);
			CurveTimeline.SetLooping(true);

			CurveTimeline.PlayFromStart();
		}
	}
}

void AManixInteractSphere::LookOver(FName Component)
{	
	if (bNoticicationOverlap)
	{
		if (Component == BouncingBall->GetFName())
		{
			if (bFirstTimeFocus)
			{
				if (InteractWidget)
				{
					InteractWidget->UpdateInteractText(InteractText);
					bFirstTimeFocus = false;
				}
			}
		}
	}
}

void AManixInteractSphere::TimelineProgress(float RunningTime)
{
	float BouncingBallDeltaY = FMath::Sin(RunningTime * .1f) * 3000.f;
	BouncingBall->SetRelativeLocation(FVector(0, 0, BouncingBallDeltaY));
}

//animacje
//RunningTime += DeltaTime;
//float DeltaZCube = Amplitude * FMath::Sin(RunningTime * TimeConstant);
//RotatingCube->SetRelativeRotation(FRotator(0, DeltaZCube, 0));
//
//DeltaYBall = DeltaYBall > 0 ? .25f : 1.5f * FMath::Sin(RunningTime * 1.25f);
//BouncingBall->AddRelativeLocation(FVector(0, 0, DeltaYBall));

//void AManixInteractSphere::BallBouncing()
//{
// 
//	//RunningTime += DeltaTime;
//	float DeltaZ = Amplitude * FMath::Sin(RunningTime * TimeConstant);
//	RotatingCube->SetRelativeRotation(FRotator(0, DeltaZ, 0));
//}