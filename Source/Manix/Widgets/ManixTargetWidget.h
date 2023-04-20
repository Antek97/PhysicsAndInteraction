// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "ManixTargetWidget.generated.h"


UCLASS()
class MANIX_API UManixTargetWidget : public UUserWidget
{
	GENERATED_BODY()
	
public:
	UFUNCTION(BlueprintImplementableEvent, Category = Stats)
	void SetMoving(FName TargetText);

	UFUNCTION(BlueprintImplementableEvent, Category = Stats)
	void SetDash(FName TargetText);

	UFUNCTION(BlueprintImplementableEvent, Category = Stats)
	void SetStopped(FName TargetText);
};