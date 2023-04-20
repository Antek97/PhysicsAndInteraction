// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Manix/Interfaces/ManixInteractInterface.h"
#include "Components/TimeLineComponent.h"

#include "ManixInteractSphere.generated.h"

class UCapsuleComponent;
class UWidgetComponent;
class UManixInteractWidget;
class AManixCharacter;
class UCurveFloat;

UCLASS()
class MANIX_API AManixInteractSphere : public AActor, public IManixInteractInterface
{
	GENERATED_BODY()
	
public:	
	AManixInteractSphere();

	virtual void Interact(FName Component) override;
	virtual void LookOver(FName Component) override;
	void TrigerComponent();

protected:
	virtual void BeginPlay() override;

	virtual void NotifyActorBeginOverlap(AActor* OtherActor) override;
	virtual void NotifyActorEndOverlap(AActor* OtherActor) override;

	UPROPERTY(EditAnywhere, Category = "Target")
	FName FirstStateText;
	UPROPERTY(EditAnywhere, Category = "Target")
	FName InteractText;

	void ActionRotation();

	UPROPERTY(EditAnywhere, Category = "Target")
	float Amplitude = 90.f;

	UPROPERTY(EditAnywhere, Category = "Target")
	float TimeConstant = .5f;
	float DeltaYBall = 0;
	float RunningTimeline;

private:
	bool bFirstTimeFocus = true;
	bool bNoticicationOverlap = true;

public:	
	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	UCurveFloat* CurveBall;

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	USceneComponent* Root;

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	UStaticMeshComponent* BouncingBall;

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	UStaticMeshComponent* RotatingCube;

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	UWidgetComponent* WidgetComponent;

	UPROPERTY(EditAnywhere, Category = "Target")
	UManixInteractWidget* InteractWidget;

	UPROPERTY(BlueprintReadOnly)
	UCapsuleComponent* TriggerCapsule;

	UFUNCTION()
	void TimelineProgress(float Value);

	FTimeline CurveTimeline;

protected:
	UPROPERTY(EditAnywhere, Category = "Timeline")
	UCurveFloat* CurveFloat;

	virtual void Tick(float DeltaTime) override;
};
