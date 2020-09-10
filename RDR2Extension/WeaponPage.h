#pragma once

#include "MenuPageBase.h"

class WeaponPage : public MenuPageBase
{
public:
	WeaponPage(const std::string& caption);
	virtual const std::string& GetCaption() const { return caption; }
private:
	std::string caption;
};