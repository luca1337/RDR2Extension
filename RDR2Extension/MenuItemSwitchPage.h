#pragma once

#include <functional>
#include "MenuItemBase.h"

class MenuItemSwitchPage : public MenuItem
{
public:
	MenuItemSwitchPage(const Vector3& position,
					   const std::string& caption,
					   std::function<void()> switchPageFunc)
					   : MenuItem(position, caption), pageFunc(switchPageFunc)
	{ }

	virtual void Execute()
	{
		pageFunc();
	}

private:
	std::function<void()> pageFunc;
};