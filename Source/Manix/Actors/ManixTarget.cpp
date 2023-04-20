// Fill out your copyright notice in the Description page of Project Settings.


#include "ManixTarget.h"
#include "Components/WidgetComponent.h"
#include "Components/CapsuleComponent.h"
#include "Components/TimeLineComponent.h"
#include "Manix/Widgets/ManixTargetWidget.h"

// Sets default values
AManixTarget::AManixTarget()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	Root = CreateDefaultSubobject<USceneComponent>(FName(TEXT("Root")));
	SetRootComponent(Root);

	Target = CreateDefaultSubobject<UStaticMeshComponent>(FName(TEXT("Target")));
	Target->SetupAttachment(Root);

	TargetTextWidget = CreateDefaultSubobject<UWidgetComponent>(FName(TEXT("WidgetText")));
	TargetTextWidget->SetupAttachment(Target);
	TargetTextWidget->SetCollisionEnabled(ECollisionEnabled::NoCollision);

	TriggerCapsule = CreateDefaultSubobject<UCapsuleComponent>(FName(TEXT("CapsuleTarget")));
	TriggerCapsule->InitCapsuleSize(55.f, 55.f);
	TriggerCapsule->SetCollisionProfileName(TEXT("Trigger"));
	TriggerCapsule->SetupAttachment(Target);

	Target->OnComponentHit.AddDynamic(this, &AManixTarget::OnHit);
	TriggerCapsule->OnComponentBeginOverlap.AddDynamic(this, &AManixTarget::OnOverlapBegin);
}

// Called when the game starts or when spawned
void AManixTarget::BeginPlay()
{
	Super::BeginPlay();

	SetStateTarget(Moving);
}

// Called every frame
void AManixTarget::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	CurveTimeline.TickTimeline(DeltaTime);
}

void AManixTarget::DashTimeline(float RunningTime)
{
	float DeltaXBall = FMath::Sin(RunningTime * TimeToMove) * TargetRange;

	Target->SetRelativeLocation(FVector(bDirectionDash ? DeltaXBall : -DeltaXBall, 0, 0));
}

void AManixTarget::SetStateTarget(EStatusTarget Status)
{
	StatusTarget = Status;
	
	switch (StatusTarget)
	{
	case EStatusTarget::Moving:

		if (TextWidget == nullptr)
		{
			TextWidget = Cast<UManixTargetWidget>(TargetTextWidget->GetWidget());
		}
		if (TextWidget)
		{
			TextWidget->SetMoving(MovingText);
		}

		break;
	case EStatusTarget::Dash:

		if (TextWidget)
		{
			TextWidget->SetDash(DashText);
		}

		bDirectionDash = !bDirectionDash;

		break;
	case EStatusTarget::Stopped:

		TriggerCapsule->SetCollisionEnabled(ECollisionEnabled::NoCollision);
		if (TextWidget)
		{
			TextWidget->SetStopped(StoppedText);
		}
		Target->SetSimulatePhysics(true);

		break;
	default:
		GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::Red, TEXT("StateIsNull"));
		break;
	}
}

void AManixTarget::OnOverlapBegin(class UPrimitiveComponent* OverlappedComp, class AActor* OtherActor, class UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	if (StatusTarget != Stopped)
	{
		SetStateTarget(Dash);
		if (DashCurve)
		{
			FOnTimelineFloat DashTimeline;
			DashTimeline.BindUFunction(this, FName("DashTimeline"));
			CurveTimeline.AddInterpFloat(DashCurve, DashTimeline);
			CurveTimeline.SetLooping(false);

			CurveTimeline.PlayFromStart();
		}
	}
}

void AManixTarget::OnOverlapEnd(class UPrimitiveComponent* OverlappedComp, class AActor* OtherActor, class UPrimitiveComponent* OtherComp, int32 OtherBodyIndex)
{

}

void AManixTarget::OnHit(UPrimitiveComponent* HitComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, FVector NormalImpulse, const FHitResult& Hit)
{
	SetStateTarget(Stopped);
}