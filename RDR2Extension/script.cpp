#include "MenuController.h"
#include "script.h"

void update()
{
	// Get player
	Player player = PLAYER::PLAYER_ID();
	Ped playerPed = PLAYER::PLAYER_PED_ID();

	// if entity doesn't exist or it's in cutscene dont don anything
	if (!ENTITY::DOES_ENTITY_EXIST(playerPed) || !PLAYER::IS_PLAYER_CONTROL_ON(player))
		return;

	/*const int arr_sz = 1024; // 1mb of mem
	Ped ped_arr[arr_sz];
	int count = worldGetAllPeds(ped_arr, arr_sz);

	const float minDist = 0.5f;
	const float maxDist = 900.0f;

	for (int i = 0; i < count; i++)
	{
		float screenX, screenY;
		Vector3 entityCoords = ENTITY::GET_ENTITY_COORDS(ped_arr[i], true, false);

		int boneIndex = ENTITY::GET_ENTITY_BONE_INDEX_BY_NAME(ped_arr[i], const_cast<char*>("SKEL_Head"));
		Vector3 boneCoords = ENTITY::GET_WORLD_POSITION_OF_ENTITY_BONE(ped_arr[i], boneIndex);

		if (GRAPHICS::GET_SCREEN_COORD_FROM_WORLD_COORD(boneCoords.x, boneCoords.y, boneCoords.z, &screenX, &screenY))
		{
			// draw bounds
			if (screenX < 0.01f || screenY < 0.01f || screenX > 0.93f || screenY > 0.93f)
				return;

			Vector3 playerCoords = ENTITY::GET_ENTITY_COORDS(playerPed, true, false);
			float distance = GAMEPLAY::GET_DISTANCE_BETWEEN_COORDS(playerCoords.x, playerCoords.y, playerCoords.z, entityCoords.x, entityCoords.y, entityCoords.z, true);

			// SKEL_R_Hand
			Vector3 fromCoords = ENTITY::GET_WORLD_POSITION_OF_ENTITY_BONE(playerPed, ENTITY::GET_ENTITY_BONE_INDEX_BY_NAME(playerPed, const_cast<char*>("SKEL_R_Hand")));

			if (IsKeyDownLong(0x26))
			{
				Hash wHash;
				WEAPON::GET_CURRENT_PED_WEAPON(playerPed, &wHash, 0, 0, 0);
				GAMEPLAY::SHOOT_SINGLE_BULLET_BETWEEN_COORDS(fromCoords.x, fromCoords.y, fromCoords.z, boneCoords.x, boneCoords.y, boneCoords.z, 100, 0, wHash, playerPed, true, false, 100.0f, false);
			}

			if (IsKeyDown(0x28))
			{
				PED::SET_PED_MONEY(player, 1000);
				CASH::PLAYER_ADD_CASH(10000, 0x2cd419dc);
			}

			if (distance > minDist && distance < maxDist)
			{
				int health = ENTITY::GET_ENTITY_HEALTH(ped_arr[i]);
				char buffer[256];
				sprintf_s(buffer, "DIST: %0.2f\nHP: %d", distance, health);
				DrawText(screenX, screenY, buffer);
			}
		}
	}*/
}

int main()
{
	MenuController& controller = MenuController::Get();
	controller.Init();
	controller.Run();
}

void ScriptMain()
{
	srand(GetTickCount());
	main();
}