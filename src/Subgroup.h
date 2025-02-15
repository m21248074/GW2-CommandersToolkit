#pragma once
#include <Windows.h>
#include "Utility.h"
#include "imgui_extensions.h"

class Subgroup
{
public:
	int AmountPlayers;
	Utility Utilities;
	char Notes[64] = "";

	bool Covered()
	{
		if (Utilities.Might && Utilities.Alacrity && Utilities.Quickness && Utilities.Fury && Utilities.Vulnerability && Utilities.Heal)
		{
			ImGui::PushStyleColor(ImGuiCol_Text, IM_COL32(89, 172, 98, 255)); // if all utilities are covered -> green text
			return true;
		}

		return false;
	}

	void Warning()
	{
		if (AmountPlayers > 5)
		{
			ImGui::Separator();
			ImGui::TextColored(ImVec4(1.00f, 0.58f, 0.31f, 1.00f), u8"警告:超過5名玩家!");
		}
	}

	void WarningShort()
	{
		if (AmountPlayers > 5)
		{
			ImGui::SameLine();
			ImGui::TextColored(ImVec4(1.00f, 0.58f, 0.31f, 1.00f), "(!)");
			ImGui::Tooltip([]
				{
					ImGui::TextColored(ImVec4(1.00f, 0.58f, 0.31f, 1.00f), u8"小隊有超過5位玩家。\n增益可能沒有被合適分配!");
				});
		}
	}
};