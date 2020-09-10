#include "WorldPage.h"
#include "MenuItemSwitchPage.h"
#include "MenuController.h"
#include "GameHashKeys.h"
#include "Utils.h"

class MenuItemRevealMap : public MenuItem
{
public:
	MenuItemRevealMap(const Vector3& screenPos, const std::string& caption)
		: MenuItem(screenPos, caption)
	{}

	virtual void Execute()
	{
		RADAR::_SET_MINIMAP_REVEALED(true);
		RADAR::REVEAL_MAP(0);
	}
};

class MenuItemDisplayRadar : public MenuItemSwitchOnOff
{
public:
	MenuItemDisplayRadar(const Vector3& screenPos, const std::string& caption, const ColorRGBA8& switchColor)
		: MenuItemSwitchOnOff(screenPos, caption, switchColor)
	{}
	
	virtual void OnInput()
	{
		RADAR::DISPLAY_RADAR(GetSwitchState());
	}
};

class MenuItemBlowUpAllEntities : public MenuItem
{
public:
	MenuItemBlowUpAllEntities(const Vector3& screenPos, const std::string& caption)
		: MenuItem(screenPos, caption)
	{}

	virtual void Execute()
	{
		auto entities = utils::WorldGetAllPeds();

		for (int i = 0; i < entities.second; i++)
		{
			Vector3 entityCoords = ENTITY::GET_ENTITY_COORDS(entities.first[i], true, false);
			FIRE::ADD_EXPLOSION(entityCoords.x, entityCoords.y, entityCoords.z, 24, 100.0f, true, false, true);
		}
	}
};

class MenuItemTeleport : public MenuItemSwitch
{
public:
	MenuItemTeleport(const Vector3& screenPos, const std::string& caption, const ColorRGBA8& switchColor, std::vector<std::string> keys)
		: MenuItemSwitch(screenPos, caption, switchColor, keys)
	{}

	virtual void Execute()
	{
		auto location = teleportList[GetCurrentDataIndex()].locationCoords;
		ENTITY::SET_ENTITY_COORDS(PLAYER::PLAYER_PED_ID(), location.x, location.y, location.z, false, false, true, false);
	}
};

WorldPage::WorldPage(const std::string& caption)
	: caption(caption)
{
	std::vector<std::string> locations = {};
	for (auto location : teleportList)
		locations.push_back(location.locationName);

	AddItem(new MenuItemRevealMap({}, "REVEAL MAP"));
	AddItem(new MenuItemDisplayRadar({ 0.0f, 0.02f }, "DISPLAY RADAR", { 255, 0, 255, 255 }));
	AddItem(new MenuItemBlowUpAllEntities({ 0.0f, 0.04f }, "BLOW UP ENTITIES"));
	AddItem(new MenuItemTeleport({ 0.0f, 0.06f }, "TELEPORT TO", { 255, 255, 255, 255 }, locations));
	AddItem(new MenuItemSwitchPage({ 0.0f, 0.08f }, "> MAIN PAGE", []() {MenuController::Get().SwitchPage(MenuPage::MAIN_PAGE); }));

	MenuController::Get().Add(MenuPage::WORLD_PAGE, this);
}
