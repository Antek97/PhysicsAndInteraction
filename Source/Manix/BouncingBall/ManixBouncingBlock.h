// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "ManixBouncingBlock.generated.h"

class UCapsuleComponent;
class UManixInteractWidget;
class UMaterial;
class UWidgetComponent;

UCLASS()
class MANIX_API AManixBouncingBlock : public AActor
{
	GENERATED_BODY()

public:
	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	int32 BouncingBlockQuantity = 5;

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	UStaticMeshComponent* MainBouncingComponent;

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	USceneComponent* Root;

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	UCapsuleComponent* TriggerCapsule;

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	UWidgetComponent* WidgetComponent;

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	UManixInteractWidget* InteractWidget;

	UPROPERTY(EditAnywhere, Category = "BouncingComponent")
	FName TextWidget;

	UPROPERTY(EditAnywhere, Category = "BouncingComponent")
	UMaterial* DefaultMaterial;

protected:
	virtual void NotifyActorBeginOverlap(AActor* OtherActor) override;
	virtual void NotifyActorEndOverlap(AActor* OtherActor) override;

public:	
	AManixBouncingBlock();

	UFUNCTION()
	void OnHit(UPrimitiveComponent* HitComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, FVector NormalImpulse, const FHitResult& Hit);

protected:
	virtual void BeginPlay() override;

	void ChangeMaterial();

private:
	bool bIsFirstHit = true;

public:	
	UPROPERTY(EditAnywhere)
	TArray<UStaticMeshComponent*> BouncingBlock;
	UPROPERTY(EditAnywhere, Category = "BouncingComponent")
	TArray<UMaterial*> BouncingBlockMaterials;

};
