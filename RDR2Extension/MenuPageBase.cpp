#include "MenuPageBase.h"
#include "MenuItemBase.h"
#include "keyboard.h"

/// <summary>
/// PAGE BASE METHOD DEFINITIONS
/// </summary>

MenuPageBase::~MenuPageBase()
{
	for (auto item : pageItems)
		delete item;

	delete selectedItem;
}

void MenuPageBase::OnRender()
{
	// Render page title
	UI::SET_TEXT_SCALE(textScaleX, textScaleY);
	UI::SET_TEXT_COLOR_RGBA(m_Color.rgba[0], m_Color.rgba[1], m_Color.rgba[2], m_Color.rgba[3]);
	UI::SET_TEXT_CENTRE(0);
	UI::SET_TEXT_DROPSHADOW(0, 0, 0, 0, 0);
	UI::DRAW_TEXT(GAMEPLAY::CREATE_STRING(10, const_cast<char*>("LITERAL_STRING"), const_cast<char*>(GetCaption().c_str())), startScreenX, startScreenY - 0.03f);

	//float width = (0.02f * this->GetPageItemLength()) + 0.04f;
	//GRAPHICS::DRAW_RECT(0.095f, 0.06f + (0.05f * 0.5f), 0.1f, width, 0, 0, 0, 115, false, false);

	for (auto& item : pageItems)
	{
		item->OnRender();
		item->OnInput();
	}
}

void MenuPageBase::OnFrame()
{
	if (selectedItem)
		selectedItem->OnFrame();
}

void MenuPageBase::OnInput()
{
	if (bFirstStart)
	{
		selectedItem = pageItems[itemIndex];
		selectedItem->SetState();
		bFirstStart = false;
	}

	if (IsKeyJustUp(VK_UP))
	{
		if (itemIndex == 0)
		{
			pageItems[itemIndex]->SetState();
			itemIndex = pageItems.size() - 1;
			pageItems[itemIndex]->SetState();
			return;
		}
		pageItems[itemIndex]->SetState();
		itemIndex--;
		pageItems[itemIndex]->SetState();
	}

	if (IsKeyJustUp(VK_DOWN))
	{
		if (itemIndex == pageItems.size() - 1)
		{
			pageItems[itemIndex]->SetState();
			itemIndex = 0;
			pageItems[itemIndex]->SetState();
			return;
		}
		pageItems[itemIndex]->SetState();
		itemIndex++;
		pageItems[itemIndex]->SetState();
	}

	selectedItem = pageItems[itemIndex];
	selectedItem->OnSelect();
}

void MenuPageBase::AddItem(MenuItemBase* pageItem)
{
	pageItems.push_back(pageItem);
}