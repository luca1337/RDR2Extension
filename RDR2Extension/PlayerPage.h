#pragma once

#include "MenuItemSwitchPage.h"
#include "MenuPageBase.h"
#include "MenuController.h"

class MenuItemSwitchStaminaAmount : public MenuItemSwitchFloat
{
public:
	MenuItemSwitchStaminaAmount(const Vector3& screenPos, const std::string& caption, const ColorRGBA8& color, float minValue, float maxValue)
		: MenuItemSwitchFloat(screenPos, caption, color, minValue, maxValue)
	{}

	virtual void Execute()
	{
		PLAYER::RESTORE_PLAYER_STAMINA(PLAYER::PLAYER_ID(), GetSliderValue());
	}
};

class MenuItemSwitchGodmode : public MenuItemSwitchOnOff
{
public:
	MenuItemSwitchGodmode(const Vector3& screenPos, const std::string& caption, const ColorRGBA8& switchColor)
		: MenuItemSwitchOnOff(screenPos, caption, switchColor)
	{}

	virtual void OnInput()
	{
		PLAYER::SET_PLAYER_INVINCIBLE(PLAYER::PLAYER_ID(), GetSwitchState());
	}
};

class PlayerPage : MenuPageBase
{
public:
	PlayerPage(const std::string& caption) : MenuPageBase(), caption(caption)
	{
		AddItem(new MenuItemSwitchStaminaAmount({}, "STAMINA AMOUNT", { 255, 255, 255, 255 }, 1.0f, 5.0f));
		AddItem(new MenuItemSwitchGodmode({ 0.0f, 0.02f }, "GOD MODE", { 0, 255, 255, 255 }));
		AddItem(new MenuItemSwitchPage({ 0.0f, 0.04f }, "> MAIN PAGE", []() {MenuController::Get().SwitchPage(MenuPage::MAIN_PAGE); }));

		MenuController::Get().Add(MenuPage::PLAYER_PAGE, this);
	}
	virtual const std::string& GetCaption() const { return caption; }
private:
	std::string caption;
};
