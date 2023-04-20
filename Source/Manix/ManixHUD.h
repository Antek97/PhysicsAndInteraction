// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once 

#include "CoreMinimal.h"
#include "GameFramework/HUD.h"
#include "ManixHUD.generated.h"

class UManixMainHudWidget;

UCLASS()
class AManixHUD : public AHUD
{
	GENERATED_BODY()

public:
	AManixHUD();

	/** Primary draw call for the HUD */
	virtual void DrawHUD() override;

private:
	/** Crosshair asset pointer */
	class UTexture2D* CrosshairTex;

	virtual void InitializeHud();

protected:
	bool bNeedsInventoryInit = true;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Main Hud")
	TSubclassOf<UUserWidget> WidgetClass;

	UPROPERTY(VisibleInstanceOnly, Category = "Main Hud")
	UManixMainHudWidget* MainHudWidget;

public:

	void ToggleStatsPanelHud();
	void UpdateAliveProjectileHud(int32 Value);
	void UpdateTotalProjectileHud(int32 Value);
	void UpdateFocusObjectHud(FName ObjectName);
};

