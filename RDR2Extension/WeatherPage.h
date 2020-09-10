#pragma once

#include "MenuPageBase.h"

class WeatherPage : public MenuPageBase
{
public:
	WeatherPage(const std::string& caption);
	virtual const std::string& GetCaption() const { return caption; }
private:
	std::string caption;
};