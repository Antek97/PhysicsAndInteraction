// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "ManixInteractWidget.generated.h"

/**
 * 
 */
UCLASS()
class MANIX_API UManixInteractWidget : public UUserWidget
{
	GENERATED_BODY()

public:
	UFUNCTION(BlueprintImplementableEvent, Category = Stats)
	void ToggleInteractVisibility(bool bInteractState);

	UFUNCTION(BlueprintImplementableEvent, Category = Stats)
	void UpdateInteractText(FName InteractText);
};
