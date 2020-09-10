#pragma once

#include "MenuPageBase.h"

class WorldPage : MenuPageBase
{
public:
	WorldPage(const std::string& caption);
	virtual const std::string& GetCaption() const { return caption; }
private:
	std::string caption;
};