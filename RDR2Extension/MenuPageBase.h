#pragma once

#include <string>
#include <vector>

#include  "Color.h"

class MenuPageBase
{
public:
	MenuPageBase()
		: pageItems{}, selectedItem(0),
		itemIndex(), bFirstStart(true),
		m_Color{ 255, 0, 0, 255 }
	{}
	virtual ~MenuPageBase();
	virtual const std::string& GetCaption() const { return ""; }
	void OnRender();
	void OnFrame();
	void OnInput();
	void AddItem(class MenuItemBase* pageItem);
	void SetTitleColor(const ColorRGBA8& color) { m_Color = color; }
	size_t GetPageItemLength() const { return pageItems.size(); }
protected:
	std::vector<class MenuItemBase*>	pageItems;
	class MenuItemBase*					selectedItem;
	size_t								itemIndex;
	bool								bFirstStart;
	ColorRGBA8							m_Color;
};