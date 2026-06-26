///----------------------------------------------------------------------------------------------------
/// Copyright (c) Raidcore.GG - All rights reserved.
/// 
/// Name         :  Util.h
/// Description  :  Utility functions
/// Authors      :  K. Bieniek
///----------------------------------------------------------------------------------------------------

#ifndef UTIL_H
#define UTIL_H

#include <cstdint>
#include <string>

#include "imgui/imgui.h"
#include "nexus/Nexus.h"
#include "Globals.h"


inline void PlayerLeftTooltip(const bool& aActive, const long long& aSeconds)
{
	if (!aActive) { return; }

	if (ImGui::IsItemHovered())
	{
		ImGui::BeginTooltip();
		ImGui::Text("最後上線於 %u %s 前。",
					aSeconds < 60 ? aSeconds : aSeconds / 60,
					aSeconds < 60 ? "秒" : "分鐘");
		ImGui::EndTooltip();
	};
}


inline void RenderIcon(float aSize, Texture** aTexture, std::string aIdentifer, std::string aAltText, uint32_t aResourceID)
{
	if (*aTexture)
	{
		ImGui::Image((*aTexture)->Resource, ImVec2(aSize, aSize));
		if (ImGui::IsItemHovered())
		{
			ImGui::BeginTooltip();
			ImGui::Text(aAltText.c_str());
			ImGui::EndTooltip();
		}
	}
	else
	{
		*aTexture = G::APIDefs->Textures.GetOrCreateFromResource(aIdentifer.c_str(), aResourceID, G::Module);
		ImGui::Text(aAltText.c_str());
	}
}

inline bool RenderIconButton(float aSize, Texture** aTexture, std::string aIdentifer, std::string aAltText, uint32_t aResourceID, ImVec4 aTint = ImVec4(1, 1, 1, 1))
{
	bool pressed = false;
	if (*aTexture)
	{
		ImGui::PushID(aAltText.c_str());
		if (ImGui::ImageButton((*aTexture)->Resource, ImVec2(aSize, aSize), ImVec2(0, 0), ImVec2(1, 1), -1, ImVec4(0, 0, 0, 0), aTint))
		{
			pressed = true;
		}
		ImGui::PopID();
	}
	else
	{
		*aTexture = G::APIDefs->Textures.GetOrCreateFromResource(aIdentifer.c_str(), aResourceID, G::Module);
		if (ImGui::Button(aAltText.c_str()))
		{
			pressed = true;
		}
	}

	return pressed;
}

inline void RenderSpecIcon(float aSize, int aProfession, int aSpec)
{
	struct IconEntry
	{
		ETextures textureEnum;
		const char* identifier;
		const char* altText;
		uint32_t resourceID;
	};

	IconEntry entry = { ETextures::SpecUnknown, "TEX_SPEC_UNKNOWN", "未知", IDB_SPEC_UNNKOWN };

	// Mapping helpers
	switch (aProfession)
	{
		case 1: // Guardian
			if (aSpec == 27) entry = { ETextures::SpecGrdDgh, "TEX_SPEC_GRD_DGH", "獵龍者", IDB_SPEC_GRD_DGH };
			else if (aSpec == 65) entry = { ETextures::SpecGrdWbd, "TEX_SPEC_GRD_WBD", "破峰者", IDB_SPEC_GRD_WBD };
			else if (aSpec == 62) entry = { ETextures::SpecGrdFbd, "TEX_SPEC_GRD_FBD", "燃火者", IDB_SPEC_GRD_FBD };
			else if (aSpec == 81) entry = { ETextures::SpecGrdLum, "TEX_SPEC_GRD_LUM", "聖輝者", IDB_SPEC_GRD_LUM };
			else entry = { ETextures::SpecGrd, "TEX_SPEC_GRD", "守護者", IDB_SPEC_GRD };
			break;
		case 2: // Warrior
			if (aSpec == 18) entry = { ETextures::SpecWarBrs, "TEX_SPEC_WAR_BRS", "狂戰士", IDB_SPEC_WAR_BRS };
			else if (aSpec == 61) entry = { ETextures::SpecWarSpb, "TEX_SPEC_WAR_SPB", "破法者", IDB_SPEC_WAR_SPB };
			else if (aSpec == 68) entry = { ETextures::SpecWarBsw, "TEX_SPEC_WAR_BSW", "誓刃鬥士", IDB_SPEC_WAR_BSW };
			else if (aSpec == 74) entry = { ETextures::SpecWarPar, "TEX_SPEC_WAR_PAR", "聖言者", IDB_SPEC_WAR_PAR };
			else entry = { ETextures::SpecWar, "TEX_SPEC_WAR", "戰士", IDB_SPEC_WAR };
			break;
		case 3: // Engineer
			if (aSpec == 43) entry = { ETextures::SpecEngScr, "TEX_SPEC_ENG_SCR", "機械師", IDB_SPEC_ENG_SCR };
			else if (aSpec == 57) entry = { ETextures::SpecEngHls, "TEX_SPEC_ENG_HLS", "全息師", IDB_SPEC_ENG_HLS };
			else if (aSpec == 70) entry = { ETextures::SpecEngMch, "TEX_SPEC_ENG_MCH", "玉偃師", IDB_SPEC_ENG_MCH };
			else if (aSpec == 75) entry = { ETextures::SpecEngAma, "TEX_SPEC_ENG_AMA", "流金師", IDB_SPEC_ENG_AMA };
			else entry = { ETextures::SpecEng, "TEX_SPEC_ENG", "工程師", IDB_SPEC_ENG };
			break;
		case 4: // Ranger
			if (aSpec == 55) entry = { ETextures::SpecRgrSlb, "TEX_SPEC_RGR_SLB", "魂獸師", IDB_SPEC_RGR_SLB };
			else if (aSpec == 72) entry = { ETextures::SpecRgrUtd, "TEX_SPEC_RGR_UTD", "狂獸師", IDB_SPEC_RGR_UTD };
			else if (aSpec == 5) entry = { ETextures::SpecRgrDrd, "TEX_SPEC_RGR_DRD", "德魯伊", IDB_SPEC_RGR_DRD };
			else if (aSpec == 78) entry = { ETextures::SpecRgrGal, "TEX_SPEC_RGR_GAL", "風羽者", IDB_SPEC_RGR_GAL };
			else entry = { ETextures::SpecRgr, "TEX_SPEC_RGR", "遊俠", IDB_SPEC_RGR };
			break;
		case 5: // Thief
			if (aSpec == 58) entry = { ETextures::SpecThfDde, "TEX_SPEC_THF_DDE", "獨行俠", IDB_SPEC_THF_DDE };
			else if (aSpec == 7) entry = { ETextures::SpecThfDdl, "TEX_SPEC_THF_DDL", "神槍手", IDB_SPEC_THF_DDL };
			else if (aSpec == 71) entry = { ETextures::SpecThfSpc, "TEX_SPEC_THF_SPC", "縛影者", IDB_SPEC_THF_SPC };
			else if (aSpec == 77) entry = { ETextures::SpecThfAtq, "TEX_SPEC_THF_ATQ", "彩戲師", IDB_SPEC_THF_ATQ };
			else entry = { ETextures::SpecThf, "TEX_SPEC_THF", "盜賊", IDB_SPEC_THF };
			break;
		case 6: // Elementalist
			if (aSpec == 48) entry = { ETextures::SpecEleTmp, "TEX_SPEC_ELE_TMP", "暴風使", IDB_SPEC_ELE_TMP };
			else if (aSpec == 56) entry = { ETextures::SpecEleWvr, "TEX_SPEC_ELE_WVR", "編織者", IDB_SPEC_ELE_WVR };
			else if (aSpec == 67) entry = { ETextures::SpecEleCat, "TEX_SPEC_ELE_CAT", "元晶師", IDB_SPEC_ELE_CAT };
			else if (aSpec == 80) entry = { ETextures::SpecEleEvk, "TEX_SPEC_ELE_EVK", "喚元師", IDB_SPEC_ELE_EVK };
			else entry = { ETextures::SpecEle, "TEX_SPEC_ELE", "元素使", IDB_SPEC_ELE };
			break;
		case 7: // Mesmer
			if (aSpec == 40) entry = { ETextures::SpecMesChr, "TEX_SPEC_MES_CHR", "時空術士", IDB_SPEC_MES_CHR };
			else if (aSpec == 59) entry = { ETextures::SpecMesMir, "TEX_SPEC_MES_MIR", "幻象術士", IDB_SPEC_MES_MIR };
			else if (aSpec == 66) entry = { ETextures::SpecMesVrt, "TEX_SPEC_MES_VRT", "靈刃術士", IDB_SPEC_MES_VRT };
			else if (aSpec == 73) entry = { ETextures::SpecMesTbd, "TEX_SPEC_MES_TBD", "吟遊詩人", IDB_SPEC_MES_TBD };
			else entry = { ETextures::SpecMes, "TEX_SPEC_MES", "幻術師", IDB_SPEC_MES };
			break;
		case 8: // Necromancer
			if (aSpec == 34) entry = { ETextures::SpecNecRpr, "TEX_SPEC_NEC_RPR", "奪魂者", IDB_SPEC_NEC_RPR };
			else if (aSpec == 60) entry = { ETextures::SpecNecScg, "TEX_SPEC_NEC_SCG", "災厄師", IDB_SPEC_NEC_SCG };
			else if (aSpec == 64) entry = { ETextures::SpecNecHrb, "TEX_SPEC_NEC_HRB", "先驅者", IDB_SPEC_NEC_HRB };
			else if (aSpec == 76) entry = { ETextures::SpecNecRit, "TEX_SPEC_NEC_RIT", "祭祀者", IDB_SPEC_NEC_RIT };
			else entry = { ETextures::SpecNec, "TEX_SPEC_NEC", "死靈術師", IDB_SPEC_NEC };
			break;
		case 9: // Revenant
			if (aSpec == 52) entry = { ETextures::SpecRevHer, "TEX_SPEC_REV_HER", "預告者", IDB_SPEC_REV_HER };
			else if (aSpec == 63) entry = { ETextures::SpecRevRen, "TEX_SPEC_REV_REN", "龍魂使", IDB_SPEC_REV_REN };
			else if (aSpec == 69) entry = { ETextures::SpecRevVin, "TEX_SPEC_REV_VIN", "裁決者", IDB_SPEC_REV_VIN };
			else if (aSpec == 79) entry = { ETextures::SpecRevCnd, "TEX_SPEC_REV_CND", "契靈使", IDB_SPEC_REV_CND };
			else entry = { ETextures::SpecRev, "TEX_SPEC_REV", "魂武者", IDB_SPEC_REV };
			break;
	}

	Texture** texPtr = &G::Textures[entry.textureEnum];
	if (*texPtr)
	{
		ImGui::Image((*texPtr)->Resource, ImVec2(aSize, aSize));
		if (ImGui::IsItemHovered())
		{
			ImGui::BeginTooltip();
			ImGui::Text(entry.altText);
			ImGui::EndTooltip();
		}
	}
	else
	{
		*texPtr = G::APIDefs->Textures.GetOrCreateFromResource(entry.identifier, entry.resourceID, G::Module);
		ImGui::Text(entry.altText);
	}
}

#endif
