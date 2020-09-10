#pragma once

#include <map>
#include "MenuPage.h"

class MenuPageBase;

class MenuController final
{
public:
	MenuController(const MenuController& other) = delete;
	~MenuController();
	static MenuController& Get();
	void SwitchPage(MenuPage ePage);
	void Init();
	void Run();
	void Add(MenuPage ePage, MenuPageBase* page);
	MenuPageBase* Find(MenuPage ePage);
private:
	MenuController();
	std::map<MenuPage, MenuPageBase*> menuPages;
	MenuPageBase* currentPage;
	bool m_IsMenuOpen;
};
