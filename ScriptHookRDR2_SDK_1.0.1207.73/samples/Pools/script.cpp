/*
	THIS FILE IS A PART OF RDR 2 SCRIPT HOOK SDK
				http://dev-c.com
			(C) Alexander Blade 2019
*/

#include "script.h"
#include <string>
#include <vector>

DWORD	vehUpdateTime;
DWORD	pedUpdateTime;

struct text_box_t
{
	std::string text;
	float x, y;
	byte r, g, b, a;
};

void entity_draw_info_add(std::vector<text_box_t> &textOnScreen, Entity entity, float mindist, float maxdist, std::string type, byte r, byte g, byte b, byte a)
{
	Vector3 v = ENTITY::GET_ENTITY_COORDS(entity, TRUE, FALSE);
	float x, y;
	if (GRAPHICS::GET_SCREEN_COORD_FROM_WORLD_COORD(v.x, v.y, v.z, &x, &y))
	{
		// draw bounds
		if (x < 0.01 || y < 0.01 || x > 0.93 || y > 0.93)
			return;
		// get coords
		Vector3 plv = ENTITY::GET_ENTITY_COORDS(PLAYER::PLAYER_PED_ID(), TRUE, FALSE);
		float dist = GAMEPLAY::GET_DISTANCE_BETWEEN_COORDS(plv.x, plv.y, plv.z, v.x, v.y, v.z, TRUE);
		// draw text if entity isn't close to the player
		if (dist > mindist && dist < maxdist)
		{
			// check if the text fits on screen
			bool bFitsOnscreen = true;
			for each (auto &iter in textOnScreen)
			{
				float textDist = sqrtf((iter.x - x)*(iter.x - x) + (iter.y - y)*(iter.y - y));
				if (textDist < 0.05)
				{
					bFitsOnscreen = false;
					break;
				}
			}
			// if text doesn't fit then skip draw
			if (!bFitsOnscreen) return;
			// add info to the vector
			int health = ENTITY::GET_ENTITY_HEALTH(entity);
			Hash model = ENTITY::GET_ENTITY_MODEL(entity);
			char text[256];
			sprintf_s(text, "^\n| %s %08X\n| Distance %.02f\n| Health %d", type.c_str(), model, dist, health);
			textOnScreen.push_back({ text, x, y, r, g, b, a });
		}
	}
}

void update()
{
	// player
	Player player = PLAYER::PLAYER_ID();
	Ped playerPed = PLAYER::PLAYER_PED_ID();

	// check if player ped exists and control is on (e.g. not in a cutscene)
	if (!ENTITY::DOES_ENTITY_EXIST(playerPed) || !PLAYER::IS_PLAYER_CONTROL_ON(player))
		return;

	// there are lots of entities in some places so we need to
	// remove possibilty of text being drawn on top of another text
	// thats why we will check distance between text on screen
	std::vector<text_box_t> textOnScreen;

	// get all vehicles
	const int ARR_SIZE = 1024;
	Vehicle vehicles[ARR_SIZE];
	int count = worldGetAllVehicles(vehicles, ARR_SIZE);

	// let's track all existing vehicles
	for (int i = 0; i < count; i++)
		entity_draw_info_add(textOnScreen, vehicles[i], 15, 9999, "V", 75, 75, 75, 75);

	/*	
	// delete all vehicles
	for (int i = 0; i < count; i++)
	{		
		if (!ENTITY::IS_ENTITY_A_MISSION_ENTITY(vehicles[i]))
			ENTITY::SET_ENTITY_AS_MISSION_ENTITY(vehicles[i], TRUE, TRUE);
		VEHICLE::DELETE_VEHICLE(&vehicles[i]);
	}
	*/

	// get all peds
	Ped peds[ARR_SIZE];
	count = worldGetAllPeds(peds, ARR_SIZE);

	// let's track all animals
	for (int i = 0; i < count; i++)
	{
		if (PED::IS_PED_HUMAN(peds[i]))
			continue;
		entity_draw_info_add(textOnScreen, peds[i], 15, 9999, "A", 75, 110, 75, 75);
	}

	// get all objects
	Object objects[ARR_SIZE];
	count = worldGetAllObjects(objects, ARR_SIZE);

	// track all near objects
	for (int i = 0; i < count; i++)
		entity_draw_info_add(textOnScreen, objects[i], 2, 200, "O", 75, 75, 110, 75);

	// get all pickups
	Pickup pickups[ARR_SIZE];
	count = worldGetAllPickups(pickups, ARR_SIZE);

	// track all pickups
	for (int i = 0; i < count; i++)
		entity_draw_info_add(textOnScreen, pickups[i], 2, 9999, "P", 75, 75, 75, 75);

	// draw
	for each (auto &iter in textOnScreen)
	{
		UI::SET_TEXT_SCALE(0.2, 0.2);
		UI::SET_TEXT_COLOR_RGBA(255, 255, 255, 255);
		UI::SET_TEXT_CENTRE(0);
		UI::SET_TEXT_DROPSHADOW(0, 0, 0, 0, 0);
		UI::DRAW_TEXT(GAMEPLAY::CREATE_STRING(10, "LITERAL_STRING", const_cast<char *>(iter.text.c_str())), iter.x, iter.y);
		// box
		GRAPHICS::DRAW_RECT(iter.x + 0.028f, iter.y + 0.033f, 0.058f, 0.041f, iter.r, iter.g, iter.b, iter.a, 0, 0);
	}
}

void main()
{		
	while (true)
	{
		update();
		WAIT(0);
	}
}

void ScriptMain()
{	
	srand(GetTickCount());
	main();
}
