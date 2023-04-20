// Copyright Epic Games, Inc. All Rights Reserved.

#include "ManixHUD.h"
#include "Engine/Canvas.h"
#include "Engine/Texture2D.h"
#include "TextureResource.h"
#include "CanvasItem.h"
#include "UObject/ConstructorHelpers.h"
#include "ManixMainHudWidget.h"

AManixHUD::AManixHUD()
{
	// Set the crosshair texture
	static ConstructorHelpers::FObjectFinder<UTexture2D> CrosshairTexObj(TEXT("/Game/FirstPerson/Textures/FirstPersonCrosshair"));
	CrosshairTex = CrosshairTexObj.Object;
}

void AManixHUD::DrawHUD()
{
	if (bNeedsInventoryInit)
	{
		bNeedsInventoryInit = false;

		InitializeHud();
	}

	Super::DrawHUD();


	// Draw very simple crosshair

	// find center of the Canvas
	const FVector2D Center(Canvas->ClipX * 0.5f, Canvas->ClipY * 0.5f);

	// offset by half the texture's dimensions so that the center of the texture aligns with the center of the Canvas
	const FVector2D CrosshairDrawPosition((Center.X),
		(Center.Y + 20.0f));

	// draw the crosshair
	FCanvasTileItem TileItem(CrosshairDrawPosition, CrosshairTex->Resource, FLinearColor::White);
	TileItem.BlendMode = SE_BLEND_Translucent;
	Canvas->DrawItem(TileItem);

}

void AManixHUD::InitializeHud()
{
	if (IsValid(WidgetClass))
	{
		if (MainHudWidget == NULL)
		{
			MainHudWidget = Cast <UManixMainHudWidget>(CreateWidget(GetWorld(), WidgetClass));
		}

		if (MainHudWidget != nullptr)
		{
			MainHudWidget->AddToViewport();
		}
	}
}

void AManixHUD::ToggleStatsPanelHud()
{
	if(MainHudWidget != nullptr)
	{
		MainHudWidget->ToggleStatsPanel();
	}
}

void AManixHUD::UpdateAliveProjectileHud(int32 Value)
{
	if (MainHudWidget != nullptr)
	{
		MainHudWidget->UpdateAliveProjectile(Value);
	}
}

void AManixHUD::UpdateTotalProjectileHud(int32 Value)
{
	if (MainHudWidget != nullptr)
	{
		MainHudWidget->UpdateTotalProjectile(Value);
	}
}

void AManixHUD::UpdateFocusObjectHud(FName ObjectName)
{
	if (MainHudWidget != nullptr)
	{
		MainHudWidget->UpdateFocusObject(ObjectName);
	}
}