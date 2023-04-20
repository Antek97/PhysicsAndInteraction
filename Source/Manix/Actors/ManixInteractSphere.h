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

	UPROPERTY(EditAnywhere, Category = "Target")
	float Amplitude = 90.f;

	UPROPERTY(EditAnywhere, Category = "Target")
	float TimeConstantRotation = .5f;
	float DeltaYBall = 0;
	float RunningTimeline;

private:
	bool bFirstTimeFocus = true;
	bool bNoticicationOverlap = true;

public:	
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

	FTimeline CurveTimeline;

	UFUNCTION()
	void TimelineProgress(float Value);

	UFUNCTION()
	void ActionRotation(float RunningTime);

protected:
	UPROPERTY(EditAnywhere, Category = "Timeline")
	UCurveFloat* CurveBall;

	UPROPERTY(EditAnywhere, Category = "Timeline")
	UCurveFloat* CurveCube;

	virtual void Tick(float DeltaTime) override;

};