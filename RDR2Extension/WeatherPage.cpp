#include "WeatherPage.h"
#include "MenuItemSwitchPage.h"
#include "MenuController.h"

class MenuItemSwitchWeather : public MenuItemSwitch
{
public:
	MenuItemSwitchWeather(const Vector3& screenPos, const std::string& caption,
		const ColorRGBA8& color, std::vector<std::string> keys)
		: MenuItemSwitch(screenPos, caption, color, keys)
	{ }

	virtual void Execute()
	{
		GAMEPLAY::CLEAR_OVERRIDE_WEATHER();
		Hash weather = GAMEPLAY::GET_HASH_KEY(const_cast<char*>(GetCurrentKey().c_str()));
		GAMEPLAY::SET_WEATHER_TYPE(weather, TRUE, TRUE, FALSE, 0.0, FALSE);
		GAMEPLAY::CLEAR_WEATHER_TYPE_PERSIST();
	}
};

WeatherPage::WeatherPage(const std::string& caption)
	: caption(caption)
{
	std::vector<std::string> weatherTypes =
	{
		"SUNNY",
		"MISTY",
		"FOG",
		"CLOUDS",
		"OVERCAST",
		"OVERCASTDARK",
		"DRIZZLE",
		"RAIN",
		"THUNDER",
		"THUNDERSTORM",
		"HURRICANE",
		"HIGHPRESSURE",
		"SHOWER",
		"HAIL",
		"SLEET",
		"SNOWCLEARING",
		"SNOWLIGHT",
		"SNOW",
		"BLIZZARD",
		"GROUNDBLIZZARD",
		"WHITEOUT",
		"SANDSTORM"
	};

	AddItem(new MenuItemSwitchWeather({}, "SWITCH WEATHER", { 255, 255, 255, 255 }, weatherTypes));
	AddItem(new MenuItemSwitchPage({ 0.0f, 0.02f }, "> MAIN PAGE", []() {MenuController::Get().SwitchPage(MenuPage::MAIN_PAGE); }));

	MenuController::Get().Add(MenuPage::WEATHER_PAGE, this);
}
