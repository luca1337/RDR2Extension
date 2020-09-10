#pragma once

#include "MenuPageBase.h"

class MenuSettingsPage : public MenuPageBase
{
public:
	MenuSettingsPage(const std::string& caption);
	virtual const std::string& GetCaption() const { return caption; }
private:
	std::string caption;
};