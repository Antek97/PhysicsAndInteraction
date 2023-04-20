// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Components/TimeLineComponent.h"

#include "ManixTarget.generated.h"

UENUM()
enum EStatusTarget
{
	Moving    UMETA(DisplayName = "Moving"),
	Dash      UMETA(DisplayName = "Dash"),
	Stopped   UMETA(DisplayName = "Stopped"),
};

class UCapsuleComponent;
class UCurveFloat;
class UManixTargetWidget;
class UWidgetComponent;

UCLASS()
class MANIX_API AManixTarget : public AActor
{
	GENERATED_BODY()

public:
	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	USceneComponent* Root;

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	UStaticMeshComponent* Target;

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	UWidgetComponent* TargetTextWidget;

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	UCapsuleComponent* TriggerCapsule;

	UPROPERTY(VisibleAnywhere)
	UManixTargetWidget* TextWidget;

	AManixTarget();

	UFUNCTION()
	void OnOverlapBegin(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);

	UFUNCTION()
	void OnOverlapEnd(class UPrimitiveComponent* OverlappedComp, class AActor* OtherActor, class UPrimitiveComponent* OtherComp, int32 OtherBodyIndex);

	UFUNCTION()
	void OnHit(UPrimitiveComponent* HitComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, FVector NormalImpulse, const FHitResult& Hit);

	UFUNCTION()
	void DashTimeline(float RunningTime);

	UPROPERTY(EditAnywhere, Category = "Target")
	float TimeToMove = .85f;
	UPROPERTY(EditAnywhere, Category = "Target")
	float TargetRange = 1500.f;
	UPROPERTY(EditAnywhere, Category = "Target")
	float TargetSpeed = .85f;

	UPROPERTY(EditAnywhere, Category = "Target")
	float CooldownTimer = .6f;
	
	FTimerHandle HandleTimer;

	void CooldownReduction();

	UFUNCTION(BlueprintCallable)
	void SetStateTarget(EStatusTarget Status);

protected:
	virtual void BeginPlay() override;
	
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Target)
	FName MovingText;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Target)
	FName DashText;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Target)
	FName StoppedText;
	
	UPROPERTY(EditAnywhere, Category = "Timeline")
	UCurveFloat* DashCurve;

public:	
	UPROPERTY(EditAnywhere)
	TEnumAsByte<EStatusTarget> StatusTarget = Moving;

	virtual void Tick(float DeltaTime) override;

private:
	bool bDirectionDash = false;
};
