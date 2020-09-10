#pragma once

#include <iostream>
#include <vector>
#include "natives.h"
#include "types.h"
#include "Color.h"

const float startScreenX = 0.05f,
			startScreenY = 0.05f;

const float padding = 2.0f;

const float textScaleX = 0.3f,
			textScaleY = 0.3f;

const ColorRGBA8 selectedItemColor = { 255, 0, 0, 255 };

class MenuItemBase
{
public:
	MenuItemBase() 
		: m_State(false) 
	{}
	virtual						~MenuItemBase() { }
	virtual void				Execute() { }
	virtual void				OnRender() { }
	virtual void				OnFrame() { }
	virtual void				OnInput() { }
	void						OnSelect();
	virtual const std::string&	GetCaption() const { return ""; }

	const ColorRGBA8&			GetTextColor() const { return !m_State ? textColor : selectedItemColor; }
	const ColorRGBA8&			GetRectColor() const { return textColor; }
	void						SetState() { m_State = !m_State; }
	bool						GetState() { return m_State; }
private:
	const ColorRGBA8 textColor { 255, 255, 255, 255 },
					 rectColor { 0, 0, 0, 115 };
	bool			 m_State;
};

/// <summary>
/// MENU ITEM DEFAULT
/// </summary>

class MenuItem : public MenuItemBase
{
public:
	MenuItem(const Vector3& screenPos,
			 const std::string& caption)
			 : MenuItemBase(), position(screenPos),
			 caption(caption)
	{}

	virtual void				OnRender();
	virtual void				OnFrame() {}
	virtual void				Execute() {}
	virtual void				OnInput() {}
	virtual const std::string&	GetCaption() { return caption; }
private:
	Vector3 position;
	std::string caption;
};

/// <summary>
/// MENU ITEM SWITCH ON/OFF
/// </summary>

class MenuItemSwitchOnOff : public MenuItemBase
{
public:
	MenuItemSwitchOnOff(const Vector3& screenPos,
						const std::string& caption,
						const ColorRGBA8& switchColor)
						: MenuItemBase(), position(screenPos),
						caption(caption), switchColor(switchColor),
						m_Switch(false)
	{}

	virtual void				OnRender();
	virtual void				Execute() {}
	virtual void				OnFrame();
	virtual void				OnInput() {}
	virtual const std::string&	GetCaption() { return caption; }
	bool						GetSwitchState() const { return m_Switch; }
private:
	Vector3 position;
	std::string caption;
	ColorRGBA8 switchColor;
	bool m_Switch;
};

/// <summary>
/// STRING SWITCH
/// </summary>

class MenuItemSwitch : public MenuItemBase
{
public:
	MenuItemSwitch(const Vector3& screenPos,
				   const std::string& caption,
				   const ColorRGBA8& switchColor,
				   std::vector<std::string> keys)
				   : MenuItemBase(), caption(caption),
				   switchColor(switchColor), keys(keys),
				   currentDataIndex(0), position(screenPos)
	{}

	virtual void						OnRender();
	virtual void						Execute() {}
	virtual void						OnFrame();
	virtual void						OnInput() {}
	virtual const	std::string&		GetCaption() const			{ return caption; }
	virtual const	std::string&		GetCurrentKey() const		{ return keys[currentDataIndex]; }
	const size_t						GetCurrentDataIndex() const	{ return currentDataIndex; }
private:
	Vector3								position;
	std::string							caption;
	const			ColorRGBA8			switchColor;
	std::vector<std::string>			keys;
	size_t								currentDataIndex;
};

/// <summary>
/// FLOAT SWITCH
/// </summary>

const int maxStepInt = 1;
const int bufferSizeInt = 128;

class MenuItemSwitchFloat : public MenuItemBase
{
public:
	MenuItemSwitchFloat(const Vector3& screenPos,
						const std::string& caption,
						const ColorRGBA8& switchColor,
						float minValue, float maxValue,
						float maxStep = maxStepInt,
						float leftStepOffset = 0.1f)
						: MenuItemBase(), caption(caption),
						switchColor(switchColor), minValue(minValue),
						maxValue(maxValue), value(0.0f), format("%.2f"),
						position(screenPos), leftStepOffset(leftStepOffset)
	{}
	
	virtual void					OnRender();
	virtual void					Execute() {}
	virtual void					OnFrame();
	virtual void					OnInput() {}

	virtual const	std::string&	GetCaption()		const { return caption;	 }
	const			std::string&	GetFormat()			const { return format;	 }
	float							GetSliderValue()	const { return value;	 }
	const			Vector3&		GetTextPosition()	const { return position; }
private:
	Vector3				position;
	std::string			caption;
	const ColorRGBA8	switchColor;

	float				minValue, 
						maxValue, 
						value, 
						leftStepOffset;

	std::string			format;
	void SetFormat(const std::string& switchFormat) { format = switchFormat; }
};

/// <summary>
/// MENU ITEM SWITCH INT
/// </summary>

const float maxStep = 1;
const int bufferSize = 128;

class MenuItemSwitchInt : public MenuItemBase
{
public:
	MenuItemSwitchInt(const Vector3& screenPos,
		const std::string& caption,
		const ColorRGBA8& switchColor,
		int minValue, int maxValue,
		int maxStep = maxStep,
		float leftStepOffset = 0.1f)
		: MenuItemBase(), caption(caption),
		switchColor(switchColor), minValue(minValue),
		maxValue(maxValue), value(0), format("%d"),
		position(screenPos), leftStepOffset(leftStepOffset)
	{}

	virtual void					OnRender();
	virtual void					Execute() {}
	virtual void					OnFrame();
	virtual void					OnInput() {}

	virtual const	std::string&	GetCaption()		const { return caption;	 }
	const			std::string&	GetFormat()			const { return format;	 }
	int								GetSliderValue()	const { return value;	 }
	const			Vector3&		GetTextPosition()	const { return position; }
private:
	Vector3				position;
	std::string			caption;
	const ColorRGBA8	switchColor;

	int					minValue,
						maxValue,
						value;
	float				leftStepOffset;

	std::string			format;
	void SetFormat(const std::string& switchFormat) { format = switchFormat; }
};