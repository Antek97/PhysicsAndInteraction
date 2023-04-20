// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/Interface.h"
#include "ManixInteractInterface.generated.h"

UINTERFACE(MinimalAPI)
class UManixInteractInterface : public UInterface
{
	GENERATED_BODY()
};

class MANIX_API IManixInteractInterface
{
	GENERATED_BODY()

public:

	UFUNCTION()
	virtual void Interact(FName Component) = 0;

	UFUNCTION()
	virtual void LookOver(FName Component) = 0;
};
