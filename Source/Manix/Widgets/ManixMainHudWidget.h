// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "ManixMainHudWidget.generated.h"

/**
 * 
 */
UCLASS()
class MANIX_API UManixMainHudWidget : public UUserWidget
{
	GENERATED_BODY()

public:

	UFUNCTION(BlueprintImplementableEvent, Category = Stats)
	void UpdateAliveProjectile(int32 Value);

	UFUNCTION(BlueprintImplementableEvent, Category = Stats)
	void UpdateTotalProjectile(int32 Value);

	UFUNCTION(BlueprintImplementableEvent, Category = Stats)
	void ToggleStatsPanel();

	UFUNCTION(BlueprintImplementableEvent, Category = FocusObject)
	void UpdateFocusObject(FName ObjectName);
};
