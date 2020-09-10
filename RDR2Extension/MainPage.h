#pragma once

#include "MenuPageBase.h"

class MainPage : public MenuPageBase
{
public:
	MainPage(const std::string& caption);
	virtual const std::string& GetCaption() const { return caption; }
private:
	std::string	caption;
};
