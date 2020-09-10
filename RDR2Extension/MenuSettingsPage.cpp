#include "MenuSettingsPage.h"
#include "MenuItemSwitchPage.h"
#include "MenuController.h"
#include "Registry.h"

// pages
#include "PlayerPage.h"

class MenuItemSaveSettings : public MenuItemSwitchOnOff
{
public:
	MenuItemSaveSettings(const Vector3& screenPos, const std::string& caption, const ColorRGBA8& switchColor)
		: MenuItemSwitchOnOff(screenPos, caption, switchColor), menuPage(nullptr)
	{}

	virtual void Execute()
	{
		MenuController& controller = MenuController::Get();
		menuPage = controller.Find(MenuPage::PLAYER_PAGE);
	}

	virtual void OnInput()
	{
		if (GetSwitchState())
		{
			// Left text
			UI::SET_TEXT_SCALE(textScaleX, textScaleY);
			UI::SET_TEXT_COLOR_RGBA(GetTextColor().rgba[0], GetTextColor().rgba[1], GetTextColor().rgba[2], GetTextColor().rgba[3]);
			UI::SET_TEXT_CENTRE(0);
			UI::SET_TEXT_DROPSHADOW(0, 0, 0, 0, 0);
			char buf[256];
			sprintf_s(buf, "%s", menuPage->GetCaption());
			UI::DRAW_TEXT(GAMEPLAY::CREATE_STRING(10, const_cast<char*>("LITERAL_STRING"), buf), 0.5f, 0.5f);
		}
	}

private:
	MenuPageBase* menuPage;
};

class MenuItemLoadSettings : public MenuItem
{
public:
	MenuItemLoadSettings(const Vector3& screenPos, const std::string& caption)
		: MenuItem(screenPos, caption)
	{}

	virtual void Execute()
	{
	}
};

MenuSettingsPage::MenuSettingsPage(const std::string& caption)
	: caption(caption)
{
	AddItem(new MenuItemSaveSettings({}, "SAVE SETTINGS", { 255, 255, 255, 255 }));
	AddItem(new MenuItemLoadSettings({ 0.0f, 0.02f }, "LOAD SETTINGS"));
	AddItem(new MenuItemSwitchPage({ 0.0f, 0.04f }, "> MAIN PAGE", []() {MenuController::Get().SwitchPage(MenuPage::MAIN_PAGE); }));

	MenuController::Get().Add(MenuPage::MENU_SETTINGS, this);
}