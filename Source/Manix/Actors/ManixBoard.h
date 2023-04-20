// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Manix/Interfaces/ManixInteractInterface.h"

#include "ManixBoard.generated.h"

class UCapsuleComponent;
class UWidgetComponent;
class UManixInteractWidget;
class UMaterial;
class UPhysicalMaterial;

UENUM()
enum EStatusObject
{
	Basic		UMETA(DisplayName = "Basic"),
	Marked      UMETA(DisplayName = "Marked"),
	Used		UMETA(DisplayName = "Used"),
};

UCLASS()
class MANIX_API AManixBoard : public AActor, public IManixInteractInterface
{
	GENERATED_BODY()
	
public:	
	AManixBoard();

	virtual void Interact(FName Component) override;
	virtual void LookOver(FName Component) override;

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	USceneComponent* Root;

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	UCapsuleComponent* TriggerCapsule;

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	UWidgetComponent* WidgetComponent;

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	UManixInteractWidget* InteractWidget;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Board")
	UMaterial* MaterialMarked;
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Board")
	UMaterial* MaterialUsed;

protected:
	UPROPERTY(BlueprintReadOnly)
	int32 CubesQuantity = 9;
	UPROPERTY(BlueprintReadOnly)
	int32 specialCubes = 4;

	virtual void BeginPlay() override;

	UPROPERTY(EditAnywhere, Category = "Board")
	FName InteractText;
	UPROPERTY(EditAnywhere, Category = "Board")
	FName UsedInteractText;

	virtual void NotifyActorBeginOverlap(AActor* OtherActor) override;
	virtual void NotifyActorEndOverlap(AActor* OtherActor) override;

private:
	bool bFirstActiveObject = true;
	bool bNoticicationOverlap = false;

public:

	UPROPERTY(EditAnywhere, Category = Gameplay)
	TArray<UStaticMeshComponent*> BoardComponents;
	UPROPERTY(BlueprintReadOnly, Category = Gameplay)
	TArray<TEnumAsByte<EStatusObject>> StateComponents;
};