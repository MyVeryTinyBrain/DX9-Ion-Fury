#pragma once

enum class OverlayRenderOrders
{
	Generic = 0,

	OrthoBackEffect0,
	OrthoBackEffect1,
	OrthoBackEffect2,
	OrthoBackEffect3,

	PlayerRightHand,
	PlayerLeftHand,

	PlayerWeaponOverlay0,
	PlayerWeaponOverlay1,
	PlayerWeaponOverlay2,
	PlayerWeaponOverlay3,

	UIFont,
	UIPic,
	UIForeground,

	EndOverlay,

	Crosshair = 100000,

	Fade,

	// Main Scene
	Logo,
	PressAnyKey,
	LogoFade,
};
