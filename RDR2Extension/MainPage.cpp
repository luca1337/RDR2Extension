#include "MainPage.h"
#include "MenuItemSwitchPage.h"
#include "MenuController.h"

MainPage::MainPage(const std::string& caption) 
	: caption(caption)
{
	AddItem(new MenuItemSwitchPage({}, "PLAYER", []() { MenuController::Get().SwitchPage(MenuPage::PLAYER_PAGE); }));
	AddItem(new MenuItemSwitchPage({0.0f, 0.02f}, "WEATHER", []() { MenuController::Get().SwitchPage(MenuPage::WEATHER_PAGE); }));
	AddItem(new MenuItemSwitchPage({0.0f, 0.04f}, "WEAPONS", []() { MenuController::Get().SwitchPage(MenuPage::WEAPON_PAGE); }));
	AddItem(new MenuItemSwitchPage({0.0f, 0.06f}, "WORLD", []() { MenuController::Get().SwitchPage(MenuPage::WORLD_PAGE); }));
	AddItem(new MenuItemSwitchPage({0.0f, 0.08f}, "MENU SETTINGS", []() { MenuController::Get().SwitchPage(MenuPage::MENU_SETTINGS); }));

	MenuController::Get().Add(MenuPage::MAIN_PAGE, this);
}