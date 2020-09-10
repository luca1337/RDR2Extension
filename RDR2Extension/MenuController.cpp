#include "MenuController.h"
#include "script.h"
#include "keyboard.h"

#include "MainPage.h"
#include "PlayerPage.h"
#include "WeatherPage.h"
#include "WeaponPage.h"
#include "WorldPage.h"
#include "MenuSettingsPage.h"
#include "Registry.h"

MenuController::MenuController()
	: menuPages{}, currentPage(nullptr), m_IsMenuOpen(false)
{
	regedit::CreateRegistryKey(L"RDR2Extension");
}

MenuController::~MenuController()
{
	for (auto [key, value] : menuPages)
		delete value;

	delete currentPage;
}

MenuController& MenuController::Get()
{
	static MenuController* menuController = nullptr;

	if (!menuController)
		menuController = new MenuController();
	return *menuController;
}

void MenuController::SwitchPage(MenuPage ePage)
{
	currentPage = Find(ePage);
}

void MenuController::Init()
{
	MainPage* mainPage = new MainPage(">> MAIN <<");
	new PlayerPage(">> PLAYER <<");
	new WeatherPage(">> WEATHER <<");
	new WeaponPage(">> WEAPONS << ");
	new WorldPage(">> WORLD <<");
	new MenuSettingsPage(">> SETTINGS <<");

	currentPage = mainPage;
}

void MenuController::Run()
{
	while (true)
	{
		if (IsKeyJustUp(VK_F3))
			m_IsMenuOpen = !m_IsMenuOpen;

		if (m_IsMenuOpen)
		{
			currentPage->OnRender();
			currentPage->OnFrame();
			currentPage->OnInput();
		}

		WAIT(0);
	}
}

void MenuController::Add(MenuPage ePage, MenuPageBase* page)
{
	// Key already present
	if (Find(ePage))
		return;

	menuPages.emplace(ePage, page);
}

MenuPageBase* MenuController::Find(MenuPage ePage)
{
	std::map<MenuPage, MenuPageBase*>::iterator pageIterator;

	pageIterator = menuPages.find(ePage);

	if (pageIterator != menuPages.end())
		return menuPages[ePage];

	return nullptr;
}
