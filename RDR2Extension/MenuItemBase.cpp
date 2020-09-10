#include "MenuItemBase.h"
#include "keyboard.h"

/// <summary>
/// BASE CLASS
/// </summary>

void MenuItemBase::OnSelect()
{
	if (IsKeyJustUp(VK_RETURN))
		Execute();
}

/// <summary>
/// MENU ITEM DEFAULT
/// </summary>

void MenuItem::OnRender()
{
	// Left text
	UI::SET_TEXT_SCALE(textScaleX, textScaleY);
	UI::SET_TEXT_COLOR_RGBA(GetTextColor().rgba[0], GetTextColor().rgba[1], GetTextColor().rgba[2], GetTextColor().rgba[3]);
	UI::SET_TEXT_CENTRE(0);
	UI::SET_TEXT_DROPSHADOW(0, 0, 0, 0, 0);
	UI::DRAW_TEXT(GAMEPLAY::CREATE_STRING(10, const_cast<char*>("LITERAL_STRING"), const_cast<char*>(GetCaption().c_str())), startScreenX + position.x, startScreenY + position.y);
}

void MenuItemSwitchOnOff::OnRender()
{
	// Left text
	UI::SET_TEXT_SCALE(textScaleX, textScaleY);
	UI::SET_TEXT_COLOR_RGBA(GetTextColor().rgba[0], GetTextColor().rgba[1], GetTextColor().rgba[2], GetTextColor().rgba[3]);
	UI::SET_TEXT_CENTRE(0);
	UI::SET_TEXT_DROPSHADOW(0, 0, 0, 0, 0);
	UI::DRAW_TEXT(GAMEPLAY::CREATE_STRING(10, const_cast<char*>("LITERAL_STRING"), const_cast<char*>(GetCaption().c_str())), startScreenX + position.x, startScreenY + position.y);

	// Right text
	UI::SET_TEXT_SCALE(textScaleX, textScaleY);
	UI::SET_TEXT_COLOR_RGBA(switchColor.rgba[0], switchColor.rgba[1], switchColor.rgba[2], switchColor.rgba[3]);
	UI::SET_TEXT_CENTRE(0);
	UI::SET_TEXT_DROPSHADOW(0, 0, 0, 0, 0);
	UI::DRAW_TEXT(GAMEPLAY::CREATE_STRING(10, const_cast<char*>("LITERAL_STRING"), const_cast<char*>(GetSwitchState() ? "ON" : "OFF")), startScreenX + 0.1f, startScreenY + position.y);
}

void MenuItemSwitchOnOff::OnFrame()
{
	if (IsKeyJustUp(VK_RIGHT))
		m_Switch = !m_Switch;

	if (IsKeyJustUp(VK_LEFT))
		m_Switch = !m_Switch;
}

/// <summary>
/// DATA SWITCH
/// </summary>

void MenuItemSwitch::OnRender()
{
	// Left text
	UI::SET_TEXT_SCALE(textScaleX, textScaleY);
	UI::SET_TEXT_COLOR_RGBA(GetTextColor().rgba[0], GetTextColor().rgba[1], GetTextColor().rgba[2], GetTextColor().rgba[3]);
	UI::SET_TEXT_CENTRE(0);
	UI::SET_TEXT_DROPSHADOW(0, 0, 0, 0, 0);
	UI::DRAW_TEXT(GAMEPLAY::CREATE_STRING(10, const_cast<char*>("LITERAL_STRING"), const_cast<char*>(GetCaption().c_str())), startScreenX + position.x, startScreenY + position.y);

	// Right text
	UI::SET_TEXT_SCALE(textScaleX, textScaleY);
	UI::SET_TEXT_COLOR_RGBA(switchColor.rgba[0], switchColor.rgba[1], switchColor.rgba[2], switchColor.rgba[3]);
	UI::SET_TEXT_CENTRE(0);
	UI::SET_TEXT_DROPSHADOW(0, 0, 0, 0, 0);
	UI::DRAW_TEXT(GAMEPLAY::CREATE_STRING(10, const_cast<char*>("LITERAL_STRING"), const_cast<char*>(keys[currentDataIndex].c_str())), startScreenX + 0.1f, startScreenY + position.y);
}

void MenuItemSwitch::OnFrame()
{
	if (IsKeyJustUp(VK_RIGHT))
	{
		if (currentDataIndex == (keys.size() - 1)) {
			currentDataIndex = 0;
			return;
		}
		currentDataIndex++;
	}

	if (IsKeyJustUp(VK_LEFT))
	{
		if (currentDataIndex == 0) {
			currentDataIndex = (keys.size() - 1);
			return;
		}
		currentDataIndex--;
	}
}

/// <summary>
/// MENU SWITCH FLOAT TYPE
/// </summary>

void MenuItemSwitchFloat::OnRender()
{
	// Left text
	UI::SET_TEXT_SCALE(textScaleX, textScaleY);
	UI::SET_TEXT_COLOR_RGBA(GetTextColor().rgba[0], GetTextColor().rgba[1], GetTextColor().rgba[2], GetTextColor().rgba[3]);
	UI::SET_TEXT_CENTRE(NULL);
	UI::SET_TEXT_DROPSHADOW(NULL, NULL, NULL, NULL, NULL);
	UI::DRAW_TEXT(GAMEPLAY::CREATE_STRING(10, const_cast<char*>("LITERAL_STRING"), const_cast<char*>(GetCaption().c_str())), startScreenX + position.x, startScreenY + position.y);

	// Right text
	UI::SET_TEXT_SCALE(textScaleX, textScaleY);
	UI::SET_TEXT_COLOR_RGBA(switchColor.rgba[0], switchColor.rgba[1], switchColor.rgba[2], switchColor.rgba[3]);
	UI::SET_TEXT_CENTRE(NULL);
	UI::SET_TEXT_DROPSHADOW(NULL, NULL, NULL, NULL, NULL);

	char buffer[bufferSize] = {};
	sprintf_s(buffer, GetFormat().c_str(), value);
	UI::DRAW_TEXT(GAMEPLAY::CREATE_STRING(10, const_cast<char*>("LITERAL_STRING"), const_cast<char*>(buffer)), (startScreenX + leftStepOffset) + position.x, startScreenY + position.y);
}

void MenuItemSwitchFloat::OnFrame()
{
	if (IsKeyJustUp(VK_RIGHT))
	{
		if (value >= maxValue) {
			value = minValue;
			return;
		}
		value += maxStep;
	}

	if (IsKeyJustUp(VK_LEFT))
	{
		if (value <= minValue) {
			value = maxValue;
			return;
		}
		value -= maxStep;
	}
}

/// <summary>
/// MENU SWITCH FLOAT TYPE
/// </summary>

void MenuItemSwitchInt::OnRender()
{
	// Left text
	UI::SET_TEXT_SCALE(textScaleX, textScaleY);
	UI::SET_TEXT_COLOR_RGBA(GetTextColor().rgba[0], GetTextColor().rgba[1], GetTextColor().rgba[2], GetTextColor().rgba[3]);
	UI::SET_TEXT_CENTRE(NULL);
	UI::SET_TEXT_DROPSHADOW(NULL, NULL, NULL, NULL, NULL);
	UI::DRAW_TEXT(GAMEPLAY::CREATE_STRING(10, const_cast<char*>("LITERAL_STRING"), const_cast<char*>(GetCaption().c_str())), startScreenX + position.x, startScreenY + position.y);

	// Right text
	UI::SET_TEXT_SCALE(textScaleX, textScaleY);
	UI::SET_TEXT_COLOR_RGBA(switchColor.rgba[0], switchColor.rgba[1], switchColor.rgba[2], switchColor.rgba[3]);
	UI::SET_TEXT_CENTRE(NULL);
	UI::SET_TEXT_DROPSHADOW(NULL, NULL, NULL, NULL, NULL);

	char buffer[bufferSizeInt] = {};
	sprintf_s(buffer, GetFormat().c_str(), value);
	UI::DRAW_TEXT(GAMEPLAY::CREATE_STRING(10, const_cast<char*>("LITERAL_STRING"), const_cast<char*>(buffer)), (startScreenX + leftStepOffset) + position.x, startScreenY + position.y);
}

void MenuItemSwitchInt::OnFrame()
{
	if (IsKeyJustUp(VK_RIGHT))
	{
		if (value == maxValue) {
			value = minValue;
			return;
		}
		value += maxStepInt;
	}

	if (IsKeyJustUp(VK_LEFT))
	{
		if (value == minValue) {
			value = maxValue;
			return;
		}
		value -= maxStepInt;
	}
}