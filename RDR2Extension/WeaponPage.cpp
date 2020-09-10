#include "WeaponPage.h"
#include "MenuItemSwitchPage.h"
#include "MenuController.h"
#include "GameHashKeys.h"

class MenuItemGetWeapon : public MenuItemSwitch
{
public:
	MenuItemGetWeapon(const Vector3& screenPos, const std::string& caption,
		const ColorRGBA8& color, std::vector<std::string> keys)
		: MenuItemSwitch(screenPos, caption, color, keys)
	{ }

	virtual void Execute()
	{
		Hash hash = GAMEPLAY::GET_HASH_KEY(const_cast<char*>(weaponList[GetCurrentDataIndex()].hashKey.c_str()));
		WEAPON::GIVE_DELAYED_WEAPON_TO_PED(PLAYER::PLAYER_PED_ID(), hash, 100, 1, 0x2CD419DC);
		WEAPON::SET_PED_AMMO(PLAYER::PLAYER_PED_ID(), hash, 999);
		WEAPON::SET_CURRENT_PED_WEAPON(PLAYER::PLAYER_PED_ID(), hash, 1, 0, false, false);
	}
};

class MenuItemSetAmmo : public MenuItemSwitchInt
{
public:
	MenuItemSetAmmo(const Vector3& screenPos, const std::string& caption, const ColorRGBA8& color, int minValue, int maxValue)
		: MenuItemSwitchInt(screenPos, caption, color, minValue, maxValue)
	{}

	virtual void Execute()
	{
		Ped playerPed = PLAYER::PLAYER_PED_ID();
		Hash weaponHash;
		if (WEAPON::GET_CURRENT_PED_WEAPON(playerPed, &weaponHash, 0, 0, 0) && WEAPON::IS_WEAPON_VALID(weaponHash))
			WEAPON::SET_PED_AMMO(playerPed, weaponHash, GetSliderValue());
	}
};

class MenuItemDropWeapon : public MenuItem
{
public:
	MenuItemDropWeapon(const Vector3& screenPos, const std::string& caption)
		: MenuItem(screenPos, caption)
	{}

	virtual void Execute()
	{
		Ped playerPed = PLAYER::PLAYER_PED_ID();
		Hash weaponHash;
		if (WEAPON::GET_CURRENT_PED_WEAPON(playerPed, &weaponHash, 0, 0, 0) && WEAPON::IS_WEAPON_VALID(weaponHash))
		{
			Vector3 localCoords = ENTITY::GET_ENTITY_COORDS(playerPed, true, false);
			int ammoCount = WEAPON::GET_AMMO_IN_PED_WEAPON(playerPed, weaponHash);
			WEAPON::SET_PED_DROPS_INVENTORY_WEAPON(playerPed, weaponHash, localCoords.x, localCoords.y, localCoords.z, ammoCount);
		}
	}
};

class MenuItemGiveAllWeapons : public MenuItem
{
public:
	MenuItemGiveAllWeapons(const Vector3& screenPos, const std::string& caption)
		: MenuItem(screenPos, caption)
	{}

	virtual void Execute()
	{
		for (auto& weapon : weaponList)
		{
			Hash weaponHash = GAMEPLAY::GET_HASH_KEY(const_cast<char*>(weapon.hashKey.c_str()));
			WEAPON::GIVE_DELAYED_WEAPON_TO_PED(PLAYER::PLAYER_PED_ID(), weaponHash, 100, 1, 0x2CD419DC);
			WEAPON::SET_PED_AMMO(PLAYER::PLAYER_PED_ID(), weaponHash, 999);
			WEAPON::SET_CURRENT_PED_WEAPON(PLAYER::PLAYER_PED_ID(), weaponHash, 1, 0, false, false);
		}
	}
private:
	std::string caption;
};

class MenuItemShootExplosion : public MenuItemSwitchOnOff
{
public:
	MenuItemShootExplosion(const Vector3& screenPos, const std::string& caption, const ColorRGBA8& switchColor)
		: MenuItemSwitchOnOff(screenPos, caption, switchColor)
	{}

	virtual void OnInput()
	{
		if (GetSwitchState())
		{
			Vector3 impactCoords;
			WEAPON::GET_PED_LAST_WEAPON_IMPACT_COORD(PLAYER::PLAYER_PED_ID(), &impactCoords);
			FIRE::ADD_EXPLOSION(impactCoords.x, impactCoords.y, impactCoords.z, 1, 100.0f, true, false, true);
		}
	}
};

WeaponPage::WeaponPage(const std::string& caption)
	: caption(caption)
{
	std::vector<std::string> weaponNames;

	for (auto& weapon : weaponList)
		weaponNames.push_back(weapon.uiName);

	AddItem(new MenuItemGetWeapon({}, "GET WEAPON", { 255, 255, 255, 255 }, weaponNames));
	AddItem(new MenuItemSetAmmo({ 0.0f, 0.02f }, "SET AMMO", { 255, 255, 255, 255 }, 10, 999));
	AddItem(new MenuItemDropWeapon({ 0.0f, 0.04f }, "DROP WEAPON"));
	AddItem(new MenuItemGiveAllWeapons({ 0.0f, 0.06f }, "GIVE ALL WEAPONS"));
	AddItem(new MenuItemShootExplosion({ 0.0f, 0.08f }, "SHOOT EXPLOSION", { 0, 0, 255, 255 }));
	AddItem(new MenuItemSwitchPage({ 0.0f, 0.1f } , "> MAIN PAGE", []() {MenuController::Get().SwitchPage(MenuPage::MAIN_PAGE); }));

	MenuController::Get().Add(MenuPage::WEAPON_PAGE, this);
}