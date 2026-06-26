///----------------------------------------------------------------------------------------------------
/// Copyright (c) Raidcore.GG - All rights reserved.
/// 
/// Name         :  SquadMgr.cpp
/// Description  :  Squad manager logic.
/// Authors      :  K. Bieniek
///----------------------------------------------------------------------------------------------------

#include "SquadMgr.h"

#include <thread>
#pragma comment(lib, "wininet.lib")
#include <wininet.h>

#define IMGUI_DEFINE_MATH_OPERATORS
#include "imgui/imgui.h"
#include "imgui/imgui_internal.h"

#include "nlohmann/json.hpp"
using nlohmann::json;

#include "nexus/Nexus.h"
#include "RTAPI/RTAPI.hpp"
#include "resource.h"
#include "Globals.h"
#include "Util/src/Strings.h"
#include "Util/src/Time.h"
#include "Util.h"

void KPRequirementEditor(KPMEInfo_t& aKP)
{
	std::string popupName = "KPRequirementEditor";

	if (ImGui::SmallButton("KP 要求"))
	{
		ImGui::OpenPopup(popupName.c_str());
	}

	float sz = ImGui::GetFontSize();

	if (ImGui::BeginPopupContextItem(popupName.c_str()))
	{
		ImGui::Text("設定用於檢查團隊成員的擊殺證明(KP)要求。");
		ImGui::Text("Raid 寶箱將統一折算為 3 個代幣。");
		if (ImGui::TreeNode("大型地下城(Raid)"))
		{
			ImGui::SetNextItemWidth(sz * 10);
			ImGui::InputInt("傳奇見解(LI)", &aKP.Raids.LI, 1, 50);
			ImGui::Checkbox("萬無一失(Infallible)", &aKP.Raids.Infallible);
			ImGui::Checkbox("大型地下城神明(Raid God)", &aKP.Raids.RaidGod);

			if (ImGui::TreeNode("W1 - 靈魂山谷(Spirit Vale)"))
			{
				ImGui::SetNextItemWidth(sz * 10);
				ImGui::InputInt("山谷守護者(Vale Guardian)", &aKP.Raids.W1_ValeGuardian, 1, 50);

				ImGui::SetNextItemWidth(sz * 10);
				ImGui::InputInt("戈瑟瓦爾(Gorseval)", &aKP.Raids.W1_Gorseval, 1, 50);

				ImGui::SetNextItemWidth(sz * 10);
				ImGui::InputInt("薩蓓莎(Sabetha)", &aKP.Raids.W1_Sabetha, 1, 50);

				ImGui::Checkbox("永恆化身(The Eternal)", &aKP.Raids.W1_TheEternal);
				ImGui::Checkbox("山谷守護者(Guardian of the Vale)", &aKP.Raids.W1_GuardianOfTheVale);

				ImGui::TreePop();
			}

			if (ImGui::TreeNode("W2 - 救贖小道(Salvation Pass)"))
			{
				ImGui::SetNextItemWidth(sz * 10);
				ImGui::InputInt("斯洛薩索(Slothasor)", &aKP.Raids.W2_Slothasor, 1, 50);

				ImGui::SetNextItemWidth(sz * 10);
				ImGui::InputInt("馬蒂亞斯(Matthias)", &aKP.Raids.W2_Matthias, 1, 50);

				ImGui::Checkbox("黏滑毛蟲(Slippery Slubling)", &aKP.Raids.W2_SlipperySlubling);
				ImGui::Checkbox("永恆救贖小道(The Eternal)", &aKP.Raids.W2_TheEternal);
				ImGui::Checkbox("救贖使者(Bringer of Salvation)", &aKP.Raids.W2_BringerOfSalvation);

				ImGui::TreePop();
			}

			if (ImGui::TreeNode("W3 - 信仰要塞(Stronghold of the Faithful)"))
			{
				ImGui::SetNextItemWidth(sz * 10);
				ImGui::InputInt("要塞圍攻(Escort)", &aKP.Raids.W3_Escort, 1, 50);

				ImGui::SetNextItemWidth(sz * 10);
				ImGui::InputInt("要塞構造體(Keep Construct)", &aKP.Raids.W3_KeepConstruct, 1, 50);

				ImGui::SetNextItemWidth(sz * 10);
				ImGui::InputInt("琦拉(Xera)", &aKP.Raids.W3_Xera, 1, 50);

				ImGui::Checkbox("永恆信仰要塞(The Eternal)", &aKP.Raids.W3_TheEternal);
				ImGui::Checkbox("城堡突破者(Castle Crasher)", &aKP.Raids.W3_CastleCrasher);

				ImGui::TreePop();
			}

			if (ImGui::TreeNode("W4 - 懺悔者堡壘(Bastion of the Penitent)"))
			{
				ImGui::SetNextItemWidth(sz * 10);
				ImGui::InputInt("凱玲(Cairn)", &aKP.Raids.W4_Cairn, 1, 50);

				ImGui::SetNextItemWidth(sz * 10);
				ImGui::InputInt("末世魔監工(Mursaat Overseer)", &aKP.Raids.W4_MursaatOverseer, 1, 50);

				ImGui::SetNextItemWidth(sz * 10);
				ImGui::InputInt("薩瑪洛格(Samarog)", &aKP.Raids.W4_Samarog, 1, 50);

				ImGui::SetNextItemWidth(sz * 10);
				ImGui::InputInt("戴莫斯(Deimos)", &aKP.Raids.W4_Deimos, 1, 50);

				ImGui::Checkbox("堅毅不屈的玩家(Committed)", &aKP.Raids.W4_Committed);
				ImGui::Checkbox("沉默救星(Silent Savior)", &aKP.Raids.W4_SilentSavior);
				ImGui::Checkbox("惡魔之死(Demon's Demise)", &aKP.Raids.W4_DemonsDemise);
				ImGui::Checkbox("永恆懺悔者堡壘(The Eternal)", &aKP.Raids.W4_TheEternal);
				ImGui::Checkbox("越獄者(Jailbreaker)", &aKP.Raids.W4_Jailbreaker);

				ImGui::TreePop();
			}

			if (ImGui::TreeNode("W5 - 鎖鏈殿堂(Hall of Chains)"))
			{
				ImGui::SetNextItemWidth(sz * 10);
				ImGui::InputInt("無魂懼魔(Soulless Horror)", &aKP.Raids.W5_SoullessHorror, 1, 50);

				ImGui::SetNextItemWidth(sz * 10);
				ImGui::InputInt("德姆(Dhuum)", &aKP.Raids.W5_Dhuum, 1, 50);

				ImGui::Checkbox("虛空之聲(Voice in the Void)", &aKP.Raids.W5_VoiceInTheVoid);
				ImGui::Checkbox("永恆鎖鏈殿堂(The Eternal)", &aKP.Raids.W5_TheEternal);
				ImGui::Checkbox("地下世界救星(Savior of the Underworld)", &aKP.Raids.W5_SaviorOfTheUnderworld);
				ImGui::Checkbox("德姆殺手(Dhuum's Butcher)", &aKP.Raids.W5_DhuumsButcher);

				ImGui::TreePop();
			}

			if (ImGui::TreeNode("W6 - 祕法對決(Mythwright Gambit)"))
			{
				ImGui::SetNextItemWidth(sz * 10);
				ImGui::InputInt("咒術融合體(Conjured Amalgamate)", &aKP.Raids.W6_ConjuredAmalgamate, 1, 50);

				ImGui::SetNextItemWidth(sz * 10);
				ImGui::InputInt("孿生蝶翼人(Largos Twins)", &aKP.Raids.W6_LargosTwins, 1, 50);

				ImGui::SetNextItemWidth(sz * 10);
				ImGui::InputInt("卡迪姆(Qadim)", &aKP.Raids.W6_Qadim, 1, 50);

				ImGui::Checkbox("蟲師保鑣(Champion of Zomorros)", &aKP.Raids.W6_ChampionOfZomorros);
				ImGui::Checkbox("永恆祕法對決(The Eternal)", &aKP.Raids.W6_TheEternal);
				ImGui::Checkbox("神秘冒險者(Mystic Adventurer)", &aKP.Raids.W6_MysticAdventurer);

				ImGui::TreePop();
			}

			if (ImGui::TreeNode("W7 - 阿達西姆之鑰(The Key of Ahdashim)"))
			{
				ImGui::SetNextItemWidth(sz * 10);
				ImGui::InputInt("基石守護者艾迪娜(Cardinal Adina)", &aKP.Raids.W7_CardinalAdina, 1, 50);

				ImGui::SetNextItemWidth(sz * 10);
				ImGui::InputInt("基石守護者薩比爾(Cardinal Sabir)", &aKP.Raids.W7_CardinalSabir, 1, 50);

				ImGui::SetNextItemWidth(sz * 10);
				ImGui::InputInt("無可匹敵的卡迪姆(Qadim the Peerless)", &aKP.Raids.W7_QadimThePeerless, 1, 50);

				ImGui::Checkbox("阿達西姆的永恆盟友(Everlasting Ally of Ahdashim)", &aKP.Raids.W7_EverlastingAllyOfAhdashim);
				ImGui::Checkbox("永恆阿達西姆之鑰(The Eternal)", &aKP.Raids.W7_TheEternal);
				ImGui::Checkbox("巨靈之友(Friend to Djinn)", &aKP.Raids.W7_FriendToDjinn);

				ImGui::TreePop();
			}

			if (ImGui::TreeNode("W8 - 巴里爾山(Mount Balrior)"))
			{
				ImGui::SetNextItemWidth(sz * 10);
				ImGui::InputInt("格里爾(Greer)", &aKP.Raids.W8_Greer, 1, 50);
				ImGui::SetNextItemWidth(sz * 10);
				ImGui::InputInt("格里爾 挑戰模式(Greer CM)", &aKP.Raids.W8_GreerCM, 1, 50);

				ImGui::SetNextItemWidth(sz * 10);
				ImGui::InputInt("迪西瑪(Decima)", &aKP.Raids.W8_Decima, 1, 50);
				ImGui::SetNextItemWidth(sz * 10);
				ImGui::InputInt("迪西瑪 挑戰模式(Decima CM)", &aKP.Raids.W8_DecimaCM, 1, 50);

				ImGui::SetNextItemWidth(sz * 10);
				ImGui::InputInt("厄拉(Ura)", &aKP.Raids.W8_Ura, 1, 50);
				ImGui::SetNextItemWidth(sz * 10);
				ImGui::InputInt("厄拉 挑戰模式(Ura CM)", &aKP.Raids.W8_UraCM, 1, 50);

				ImGui::Checkbox("巴里爾山末日(The Eternal)", &aKP.Raids.W8_TheEternal);
				ImGui::Checkbox("泰坦粉碎者(Breaker of Titans)", &aKP.Raids.W8_BreakerOfTitans);
				ImGui::Checkbox("巴里爾山大型地下城專家(Raid Expert)", &aKP.Raids.W8_RaidExpert);
				ImGui::Checkbox("神明之災(Godsbane)", &aKP.Raids.W8_Godsbane);
				ImGui::Checkbox("傳奇厄拉征服者(Legendary Conqueror of Ura)", &aKP.Raids.W8_LegendaryConquerorOfUra);

				ImGui::TreePop();
			}

			ImGui::TreePop();
		}

		if (ImGui::TreeNode("進攻任務(SM)"))
		{
			if (ImGui::TreeNode("冰巢傳說(Icebrood Saga)"))
			{
				ImGui::SetNextItemWidth(sz * 10);
				ImGui::InputInt("骸骨剝皮怪儀式瓶(Boneskinner Ritual Vials)", &aKP.Strikes.IBS_BoneskinnerVial, 1, 50);

				ImGui::TreePop();
			}

			if (ImGui::TreeNode("巨龍絕境(End of Dragons)"))
			{
				ImGui::SetNextItemWidth(sz * 10);
				ImGui::InputInt("以太之刃藏身處(Aetherblade Hideout)", &aKP.Strikes.EOD_AH, 1, 50);

				ImGui::SetNextItemWidth(sz * 10);
				ImGui::InputInt("以太之刃藏身處 挑戰模式(Aetherblade Hideout CM)", &aKP.Strikes.EOD_AHCM, 1, 50);

				ImGui::Checkbox("傑出幾何學家(Peerless Geometer)", &aKP.Strikes.EOD_PeerlessGeometer);

				ImGui::SetNextItemWidth(sz * 10);
				ImGui::InputInt("凱寧瞭望台(Kaineng Overlook)", &aKP.Strikes.EOD_KO, 1, 50);

				ImGui::SetNextItemWidth(sz * 10);
				ImGui::InputInt("凱寧瞭望台 挑戰模式(Kaineng Overlook CM)", &aKP.Strikes.EOD_KOCM, 1, 50);

				ImGui::Checkbox("偉大平衡者(The Great Equalizer)", &aKP.Strikes.EOD_TheGreatEqualizer);

				ImGui::SetNextItemWidth(sz * 10);
				ImGui::InputInt("安卡(Ankka)", &aKP.Strikes.EOD_Ankka, 1, 50);

				ImGui::SetNextItemWidth(sz * 10);
				ImGui::InputInt("安卡 挑戰模式(Ankka CM)", &aKP.Strikes.EOD_AnkkaCM, 1, 50);

				ImGui::Checkbox("凝視虛空(Gazed into the Void)", &aKP.Strikes.EOD_GazedIntoTheVoid);

				ImGui::SetNextItemWidth(sz * 10);
				ImGui::InputInt("豐收神殿(Harvest Temple)", &aKP.Strikes.EOD_HT, 1, 50);

				ImGui::SetNextItemWidth(sz * 10);
				ImGui::InputInt("豐收神殿 挑戰模式(Harvest Temple CM)", &aKP.Strikes.EOD_HTCM, 1, 50);

				ImGui::Checkbox("虛空行者(The Voidwalker)", &aKP.Strikes.EOD_TheVoidwalker);

				ImGui::TreePop();
			}

			if (ImGui::TreeNode("LWS1 - Scarlet's War"))
			{
				ImGui::SetNextItemWidth(sz * 10);
				ImGui::InputInt("舊雄獅廣場(Old Lion's Court)", &aKP.Strikes.EOD_OLC, 1, 50);

				ImGui::SetNextItemWidth(sz * 10);
				ImGui::InputInt("舊雄獅廣場 挑戰模式(Old Lion's Court CM)", &aKP.Strikes.EOD_OLCCM, 1, 50);

				ImGui::Checkbox("雄獅廣場守衛者(Defender of Lion's Court)", &aKP.Strikes.EOD_DefenderOfLionsCourt);

				ImGui::TreePop();
			}

			if (ImGui::TreeNode("天界之謎(Secrets of the Obscure)"))
			{
				ImGui::SetNextItemWidth(sz * 10);
				ImGui::InputInt("宇宙觀測台(Cosmic Observatory)", &aKP.Strikes.EOD_Dagda, 1, 50);

				ImGui::SetNextItemWidth(sz * 10);
				ImGui::InputInt("宇宙觀測台 挑戰模式(Cosmic Observatory CM)", &aKP.Strikes.EOD_DagdaCM, 1, 50);

				ImGui::Checkbox("奪心魔(Mind Flayer)", &aKP.Strikes.EOD_MindFlayer);

				ImGui::SetNextItemWidth(sz * 10);
				ImGui::InputInt("菲勃神殿(Temple of Febe)", &aKP.Strikes.EOD_Cerus, 1, 50);

				ImGui::SetNextItemWidth(sz * 10);
				ImGui::InputInt("菲勃神殿 挑戰模式(Temple of Febe CM)", &aKP.Strikes.EOD_CerusCM, 1, 50);

				ImGui::Checkbox("罪惡化身(Embodiment of Sin)", &aKP.Strikes.EOD_EmbodimentOfSin);
				ImGui::Checkbox("傳奇賽魯斯征服者(Legendary Conqueror of Cerus)", &aKP.Strikes.EOD_LegendaryConquerorOfCerus);

				ImGui::TreePop();
			}
			
			if (ImGui::TreeNode("永恆願景(Visions of Eternity)"))
			{
				ImGui::SetNextItemWidth(sz * 10);
				ImGui::InputInt("齊拉(Kela)", &aKP.Strikes.VOE_Kela, 1, 50);

				ImGui::SetNextItemWidth(sz * 10);
				ImGui::InputInt("齊拉 挑戰模式(Kela CM)", &aKP.Strikes.VOE_KelaCM, 1, 50);

				ImGui::Checkbox("甲殼生物飼養者(Crustacean Corraller)", &aKP.Strikes.VOE_CrustaceanCorraler);

				ImGui::TreePop();
			}

			ImGui::TreePop();
		}

		if (ImGui::TreeNode("迷霧碎層(FotM)"))
		{
			ImGui::SetNextItemWidth(sz * 10);
			ImGui::InputInt("不穩定碎層精華(Unstable Fractal Essence)", &aKP.Fractals.UFE, 1, 50);

			ImGui::Checkbox("不淨者(The Unclean) - 噩夢(Nightmare)", &aKP.Fractals.TheUnclean);
			ImGui::Checkbox("決不放棄(Leaves No Hero Behind) - 破碎觀測台(Shattered Observatory)", &aKP.Fractals.LNHB);
			ImGui::Checkbox("對抗懷疑(Defier of Doubt) - 桑泉峰(Sunqua Peak)", &aKP.Fractals.DoD);
			ImGui::Checkbox("與魔共舞(Dances with Demons) - 桑泉峰(Sunqua Peak)", &aKP.Fractals.DwD);
			ImGui::Checkbox("噩夢分身(Nightmare Aspect) - 寂靜之浪(Silent Surf)", &aKP.Fractals.NightmareAspect);
			ImGui::Checkbox("氪族驅魔師(Kryptis Exorcist) - 孤高尖塔(Lonely Tower)", &aKP.Fractals.KryptisExorcist);

			ImGui::Checkbox("碎層學士(Fractal Savant)", &aKP.Fractals.FractalSavant);
			ImGui::Checkbox("碎層天才(Fractal Prodigy)", &aKP.Fractals.FractalProdigy);
			ImGui::Checkbox("碎層冠軍(Fractal Champion)", &aKP.Fractals.FractalChampion);
			ImGui::Checkbox("碎層神明(Fractal God)", &aKP.Fractals.FractalGod);

			ImGui::TreePop();
		}

		ImGui::EndPopup();
	}
}

void CSquadMgr::Render()
{
	if (!this->Visible)
	{
		return;
	}

	static ImGuiWindowFlags s_WndFlags = ImGuiWindowFlags_AlwaysAutoResize | ImGuiWindowFlags_NoResize | ImGuiWindowFlags_NoCollapse;

	long long now = Time::GetTimestamp();

	static ImU32 successCol = IM_COL32(89, 172, 98, 255);
	static ImU32 warnCol = IM_COL32(255, 148, 79, 255);
	static ImU32 errCol = IM_COL32(172, 89, 89, 255);

	ImGui::SetNextWindowSizeConstraints(ImVec2(-1, 100), ImVec2(-1, ImGui::GetIO().DisplaySize.y / 2));
	if (ImGui::Begin("團隊管理器", &this->Visible, s_WndFlags))
	{
		const std::lock_guard<std::mutex> lock(this->Mutex);

		/* Cache these so that no race cond can happen. */
		bool hasRTAPI = G::RTAPI != nullptr;
		bool hasUE = G::IsUEEnabled;
		static const KPMEInfo_t nullcmp{};
		bool hasKPReq = memcmp(&this->KPRequirement, &nullcmp, sizeof(KPMEInfo_t)) != 0;

		float sz = ImGui::GetFontSize();

		if (this->Players.size() == 0)
		{
			ImGui::Text("不在小隊或團隊中。");
		}
		else
		{
			if (!(hasRTAPI || hasUE))
			{
				ImGui::TextColored(ImColor(warnCol), "未安裝 RealTime API。");
			}

			KPRequirementEditor(this->KPRequirement);
			if (hasKPReq)
			{
				if (ImGui::IsItemHovered())
				{
					ImGui::BeginTooltip();
					ImGui::Text("要求:");
					ImGui::Text(CheckRequirements(KPMEInfo_t{}, this->KPRequirement, true).c_str());
					ImGui::EndTooltip();
				}

				ImGui::SameLine();
				ImGui::PushStyleVar(ImGuiStyleVar_FramePadding, ImVec2(0, 0));
				if (RenderIconButton(sz, &G::Textures[ETextures::BtnClose], "ICON_CLOSE", "清除 KP 要求", IDB_CLOSE))
				{
					this->KPRequirement = {};
				}
				ImGui::PopStyleVar();
			}

			static bool s_AnyUntracked = false;
			bool anyUntracked = false;

			int subIdx = 2;
			int kpIdx = 2;
			int dmgIdx = 2;
			int alacIdx = 3;
			int quicIdx = 4;
			int noteIdx = 5;
			int trckIdx = 6;

			/* Advance columns. */
			if (!(hasRTAPI || hasUE))
			{
				kpIdx++;
				dmgIdx++;
				alacIdx++;
				quicIdx++;
				noteIdx++;
				trckIdx++;
			}

			/* Advance columns. */
			if (hasKPReq)
			{
				dmgIdx++;
				alacIdx++;
				quicIdx++;
				noteIdx++;
				trckIdx++;
			}

			int columns = 6;
			if (!(hasRTAPI || hasUE)) { columns++; } // To render subgroup column.
			if (s_AnyUntracked)       { columns++; } // To render untracked column.
			if (hasKPReq)             { columns++; } // To render kp column.

			ImGui::PushStyleVar(ImGuiStyleVar_FramePadding, ImVec2(0, 0));

			if (ImGui::BeginTable("##TableSquadMgr", columns, ImGuiTableFlags_Borders | ImGuiTableFlags_RowBg))
			{
				ImDrawList* dl = ImGui::GetWindowDrawList();

				/* Header Row*/
				{
					ImGui::TableHeadersRow();
					ImGui::TableSetColumnIndex(0);
					ImGui::Text("帳號");

					ImGui::TableSetColumnIndex(1);
					ImGui::Text("角色");

					if (!(hasRTAPI || hasUE))
					{
						ImGui::TableSetColumnIndex(subIdx);
						ImGui::Text("小隊");
					}

					if (hasKPReq)
					{
						ImGui::TableSetColumnIndex(kpIdx);
						ImGui::Text("KP");
					}

					ImGui::TableSetColumnIndex(dmgIdx);
					ImGui::Text("傷害");

					ImGui::TableSetColumnIndex(alacIdx);
					RenderIcon(sz, &G::Textures[ETextures::BoonAlacrity], "TEX_BOON_ALACRITY", "敏捷(Alacrity)", IDB_ALACRITY);

					ImGui::TableSetColumnIndex(quicIdx);
					RenderIcon(sz, &G::Textures[ETextures::BoonQuickness], "TEX_BOON_QUICKNESS", "急速(Quickness)", IDB_QUICKNESS);

					ImGui::TableSetColumnIndex(noteIdx);
					ImGui::Text("備註");

					if (s_AnyUntracked)
					{
						ImGui::TableSetColumnIndex(trckIdx);
						if (RenderIconButton(sz, &G::Textures[ETextures::BtnClose], "ICON_CLOSE", "Remove all untracked##RemoveAll", IDB_CLOSE))
						{
							for (auto it = this->Players.begin(); it != this->Players.end(); )
							{
								if (it->second.HasLeft > 0)
								{
									it = this->Players.erase(it);
								}
								else
								{
									++it;
								}
							}
						}
						
						if (ImGui::IsItemHovered())
						{
							ImGui::BeginTooltip();
							ImGui::Text("移除所有未追蹤的玩家。");
							ImGui::EndTooltip();
						};
					}
				}

				for (size_t sub = 0; sub <= 15; sub++)
				{
					int           playerCount = 0;
					UtilityInfo_t summary = {};
					int           dmgType_pwr = 0;
					int           dmgType_cnd = 0;
					int           dmgType_heal = 0;

					std::string rem;

					for (auto& [accname, player] : this->Players)
					{
						if (player.Member.Subgroup != sub) { continue; }

						/* Push red font, if player left. */
						if (player.HasLeft && !player.Member.IsSelf)
						{
							ImGui::PushStyleColor(ImGuiCol_Text, IM_COL32(172, 89, 89, 255));
						}

						long long secondsSinceLeft = now - player.HasLeft;

						ImGui::TableNextRow();
						ImGui::TableNextColumn();
						if (player.Member.IsCommander)
						{
							RenderIcon(sz, &G::Textures[ETextures::TagCommander], "TEX_TAG_COMMANDER", "指揮官", IDB_TAG_COMMANDER);
							ImGui::SameLine();
						}
						else if (player.Member.IsLieutenant)
						{
							RenderIcon(sz, &G::Textures[ETextures::TagLieutenant], "TEX_TAG_LIEUTENANT", "副官", IDB_TAG_LIEUTENANT);
							ImGui::SameLine();
						}
						if (player.KPMEInfo == nullptr || player.KPMEInfo->ProofURL.empty())
						{
							ImGui::Text(player.Member.AccountName);
						}
						else
						{
							if (ImGui::Button(player.Member.AccountName))
							{
								ShellExecute(NULL, "open", player.KPMEInfo->ProofURL.c_str(), 0, 0, 0);
							}
						}
						PlayerLeftTooltip(player.HasLeft, secondsSinceLeft);

						ImGui::TableNextColumn();
						RenderSpecIcon(sz, player.Member.Profession, player.Member.EliteSpecialization);
						ImGui::SameLine();
						float chnameWidth = ImGui::CalcTextSize(player.Member.CharacterName).x;
						ImGui::Text(player.Member.CharacterName);
						float minchnameWidth = ImGui::CalcTextSize("xx Subgroup xx").x;
						if (chnameWidth < minchnameWidth)
						{
							ImGui::SameLine();
							ImGui::Dummy(ImVec2(minchnameWidth - chnameWidth, ImGui::GetFontSize()));
						}
						PlayerLeftTooltip(player.HasLeft, secondsSinceLeft);

						/* Render subgroup input if no RTAPI. */
						if (!(hasRTAPI || hasUE))
						{
							ImGui::TableNextColumn();
							ImGui::SetNextItemWidth(sz * 5);
							ImGui::InputInt(("##Subgroup_" + std::string(player.Member.AccountName)).c_str(), (int*)&player.Member.Subgroup);
							player.Member.Subgroup = min(max(player.Member.Subgroup, 1), 15);
						}

						if (hasKPReq)
						{
							ImGui::TableNextColumn();
							if (player.KPMEInfo != nullptr)
							{
								if (player.KPMEInfo->IsInvalid == true)
								{
									ImGui::Text("-");
									if (ImGui::IsItemHovered())
									{
										ImGui::BeginTooltip();
										ImGui::Text("此玩家沒有 killproof.me 帳號，或是未公開其帳號。");
										ImGui::EndTooltip();
									}
								}
								else
								{
									std::string reqs = CheckRequirements(*player.KPMEInfo, this->KPRequirement).c_str();

									if (!reqs.empty())
									{
										ImGui::TextColored(ImColor(warnCol), reqs.c_str());
									}
									else
									{
										ImGui::RenderCheckMark(dl, ImGui::GetCursorPos() + ImGui::GetWindowPos() - ImVec2(ImGui::GetScrollX(), ImGui::GetScrollY()), successCol, sz);
										ImGui::Dummy(ImVec2(sz, sz));
									}
								}
							}
							else
							{
								ImGui::Text("沒有資料");

								/* Fetch the KP data. */
								const std::lock_guard<std::mutex> kplock(this->KPMutex);
								auto it = this->KPData.find(player.Member.AccountName);
								if (it != this->KPData.end())
								{
									player.KPMEInfo = it->second;
								}
							}
						}

						ImGui::TableNextColumn();
						std::string dmgTypePreview =
							player.UtilityInfo.DamageType == EDamageType::None
								? "無"
								: player.UtilityInfo.DamageType == EDamageType::Power
									? "直傷"
									: player.UtilityInfo.DamageType == EDamageType::Condition
										? "症狀"
										: "治療";
						ImGui::SetNextItemWidth(sz * 5);
						if (ImGui::BeginCombo(("##DamageType_" + std::string(player.Member.AccountName)).c_str(), dmgTypePreview.c_str()))
						{
							if (ImGui::Selectable("無", player.UtilityInfo.DamageType == EDamageType::None))
							{
								player.UtilityInfo.DamageType = EDamageType::None;
							}

							if (ImGui::Selectable("直傷", player.UtilityInfo.DamageType == EDamageType::Power))
							{
								player.UtilityInfo.DamageType = EDamageType::Power;
							}

							if (ImGui::Selectable("症狀", player.UtilityInfo.DamageType == EDamageType::Condition))
							{
								player.UtilityInfo.DamageType = EDamageType::Condition;
							}

							if (ImGui::Selectable("治療", player.UtilityInfo.DamageType == EDamageType::Heal))
							{
								player.UtilityInfo.DamageType = EDamageType::Heal;
							}

							ImGui::EndCombo();
						}

						ImGui::TableNextColumn();
						ImGui::Checkbox(("##Alacrity_" + std::string(player.Member.AccountName)).c_str(), &player.UtilityInfo.Alacrity);

						ImGui::TableNextColumn();
						ImGui::Checkbox(("##Quickness_" + std::string(player.Member.AccountName)).c_str(), &player.UtilityInfo.Quickness);

						ImGui::TableNextColumn();
						ImGui::SetNextItemWidth(sz * 10);
						ImGui::InputText(("##Note_" + std::string(player.Member.AccountName)).c_str(), &player.Note[0], sizeof(player.Note));
						PlayerLeftTooltip(player.HasLeft, secondsSinceLeft);

						if (player.HasLeft && !player.Member.IsSelf)
						{
							anyUntracked = true;

							ImGui::TableNextColumn();

							if (RenderIconButton(sz, &G::Textures[ETextures::BtnClose], "ICON_CLOSE", ("X##Remove_" + std::string(player.Member.AccountName)).c_str(), IDB_CLOSE))
							{
								rem = accname;
							}
							PlayerLeftTooltip(player.HasLeft, secondsSinceLeft);

							/* Pop red font, if player left. */
							ImGui::PopStyleColor();

							/* Automatically remove, if left 5 minutes ago. */
							if (secondsSinceLeft >= 60 * 5)
							{
								rem = accname;
							}
						}

						switch (player.UtilityInfo.DamageType)
						{
							case EDamageType::Power:
								dmgType_pwr++;
								break;
							case EDamageType::Condition:
								dmgType_cnd++;
								break;
							case EDamageType::Heal:
								dmgType_heal++;
								break;
						}
						if (player.UtilityInfo.Alacrity) { summary.Alacrity = true; }
						if (player.UtilityInfo.Quickness) { summary.Quickness = true; }

						playerCount++;
					}

					if (!rem.empty())
					{
						this->Players.erase(rem);
					}

					if (playerCount == 0) { continue; }

					// subgroup totals
					bool fullCoverage = false;
					if (summary.Alacrity && summary.Quickness)
					{
						ImGui::PushStyleColor(ImGuiCol_Text, IM_COL32(89, 172, 98, 255)); // if all utilities are covered -> green text
						fullCoverage = true;
					}

					ImGui::TableHeadersRow();
					ImGui::TableSetColumnIndex(1);
					if (hasRTAPI && sub == 0)
					{
						if (G::RTAPI->GroupType == RTAPI::EGroupType::Party)
						{
							ImGui::Text("隊伍");
						}
						else
						{
							ImGui::Text("等候中");
						}
					}
					else
					{
						ImGui::Text("小隊 %d", sub);
					}
					ImGui::TableSetColumnIndex(dmgIdx);
					ImGui::Text(
						"%s%s%s",
						dmgType_pwr ? String::Format("直傷: %d\n", dmgType_pwr).c_str() : "",
						dmgType_cnd ? String::Format("症狀: %d\n", dmgType_cnd).c_str() : "",
						dmgType_heal ? String::Format("治療: %d", dmgType_heal).c_str() : ""
					);

					ImU32 textCol = ImU32(ImColor(ImGui::GetStyle().Colors[ImGuiCol_Text]));

					if (summary.Alacrity) { ImGui::TableSetColumnIndex(alacIdx); ImGui::RenderCheckMark(dl, ImGui::GetCursorPos() + ImGui::GetWindowPos() - ImVec2(ImGui::GetScrollX(), ImGui::GetScrollY()), fullCoverage ? successCol : ImU32(ImColor(textCol)), sz); }
					if (summary.Quickness) { ImGui::TableSetColumnIndex(quicIdx); ImGui::RenderCheckMark(dl, ImGui::GetCursorPos() + ImGui::GetWindowPos() - ImVec2(ImGui::GetScrollX(), ImGui::GetScrollY()), fullCoverage ? successCol : ImU32(ImColor(textCol)), sz); }

					if (fullCoverage) { ImGui::PopStyleColor(); } // reset green text

					if (playerCount > 5) { ImGui::TableSetColumnIndex(noteIdx); ImGui::TextColored(ImColor(warnCol), "警告: 超過 5 名玩家!"); }
				}

				s_AnyUntracked = anyUntracked;

				ImGui::EndTable();
			}

			ImGui::PopStyleVar();
		}
	}
	ImGui::End();
}

bool CSquadMgr::IsVisible()
{
	return this->Visible;
}

void CSquadMgr::ToggleVisible()
{
	this->Visible = !this->Visible;
}

void CSquadMgr::GetKPData(PlayerInfo_t& aPlayer)
{
	if (aPlayer.KPMEInfo == nullptr)
	{
		std::thread([this](std::string aAccountName) {
			KPMEInfo_t* kpmeInfo = nullptr;

			{
				const std::lock_guard<std::mutex> lock(this->KPMutex);
				auto it = this->KPData.find(aAccountName);

				if (it != this->KPData.end() && it->second != nullptr)
				{
					return;
				}
				else
				{
					kpmeInfo = new KPMEInfo_t();
				}
			}

			HINTERNET hInternet = InternetOpen(
				"Raidcore/GW2/CommandersToolkit", INTERNET_OPEN_TYPE_DIRECT, NULL, NULL, 0);

			std::string result;

			if (hInternet)
			{
				HINTERNET hConnect = InternetOpenUrl(
					hInternet,
					("https://killproof.me/api/kp/" + aAccountName + "?lang=en").c_str(),
					NULL,
					0,
					INTERNET_FLAG_RELOAD,
					0
				);

				if (hConnect)
				{
					std::vector<char> buffer(4096);
					DWORD bytesRead;

					while (InternetReadFile(hConnect, buffer.data(), static_cast<DWORD>(buffer.size()), &bytesRead) && bytesRead > 0)
					{
						result.append(buffer.data(), bytesRead);
					}

					InternetCloseHandle(hConnect);
				}
				else
				{
					G::APIDefs->Log(ELogLevel_DEBUG, ADDON_NAME, "InternetOpenUrl failed.");
				}

				InternetCloseHandle(hInternet);
			}
			else
			{
				G::APIDefs->Log(ELogLevel_DEBUG, ADDON_NAME, "InternetOpen failed.");
			}

			try
			{
				json response = json::parse(result);

				if (!response.is_null() && !response["error"].is_null())
				{
					kpmeInfo->IsInvalid = response["error"].get<std::string>() == "Account not found";
				}

				if (!response.is_null() && !response["proof_url"].is_null())
				{
					kpmeInfo->ProofURL = response["proof_url"].get<std::string>();
				}

				if (!response.is_null() && !response["linked_totals"].is_null())
				{
					response = response["linked_totals"];
				}

				for (json title : response["titles"])
				{
					if (!title["id"].is_null())
					{
						switch (title["id"].get<int>())
						{
							case 622: kpmeInfo->Raids.Infallible = true; break;
							case 623: kpmeInfo->Raids.RaidGod = true; break;

							case 230: kpmeInfo->Raids.W1_TheEternal = true; break;
							case 617: kpmeInfo->Raids.W1_GuardianOfTheVale = true; break;
							case 238: kpmeInfo->Raids.W2_SlipperySlubling = true; break;
							case 616: kpmeInfo->Raids.W2_TheEternal = true; break;
							case 621: kpmeInfo->Raids.W2_BringerOfSalvation = true; break;
							case 606: kpmeInfo->Raids.W3_TheEternal = true; break;
							case 614: kpmeInfo->Raids.W3_CastleCrasher = true; break;
							case 264: kpmeInfo->Raids.W4_Committed = true; break;
							case 262: kpmeInfo->Raids.W4_SilentSavior = true; break;
							case 269: kpmeInfo->Raids.W4_DemonsDemise = true; break;
							case 615: kpmeInfo->Raids.W4_TheEternal = true; break;
							case 609: kpmeInfo->Raids.W4_Jailbreaker = true; break;
							case 300: kpmeInfo->Raids.W5_VoiceInTheVoid = true; break;
							case 613: kpmeInfo->Raids.W5_TheEternal = true; break;
							case 610: kpmeInfo->Raids.W5_SaviorOfTheUnderworld = true; break;
							case 612: kpmeInfo->Raids.W5_DhuumsButcher = true; break;
							case 318: kpmeInfo->Raids.W6_ChampionOfZomorros = true; break;
							case 611: kpmeInfo->Raids.W6_TheEternal = true; break;
							case 619: kpmeInfo->Raids.W6_MysticAdventurer = true; break;
							case 328: kpmeInfo->Raids.W7_EverlastingAllyOfAhdashim = true; break;
							case 607: kpmeInfo->Raids.W7_TheEternal = true; break;
							case 608: kpmeInfo->Raids.W7_FriendToDjinn = true; break;
							case 549: kpmeInfo->Raids.W8_TheEternal = true; break;
							case 620: kpmeInfo->Raids.W8_BreakerOfTitans = true; break;
							case 550: kpmeInfo->Raids.W8_RaidExpert = true; break;
							case 570: kpmeInfo->Raids.W8_Godsbane = true; break;
							case 574: kpmeInfo->Raids.W8_LegendaryConquerorOfUra = true; break;

							case 388: kpmeInfo->Strikes.EOD_PeerlessGeometer = true; break;
							case 389: kpmeInfo->Strikes.EOD_GazedIntoTheVoid = true; break;
							case 387: kpmeInfo->Strikes.EOD_TheGreatEqualizer = true; break;
							case 386: kpmeInfo->Strikes.EOD_TheVoidwalker = true; break;
							case 395: kpmeInfo->Strikes.EOD_DefenderOfLionsCourt = true; break;
							case 419: kpmeInfo->Strikes.EOD_MindFlayer = true; break;
							case 418: kpmeInfo->Strikes.EOD_EmbodimentOfSin = true; break;
							case 456: kpmeInfo->Strikes.EOD_LegendaryConquerorOfCerus = true; break;
							case 624: kpmeInfo->Strikes.VOE_CrustaceanCorraler = true; break;

							case 250: kpmeInfo->Fractals.TheUnclean = true; break;
							case 277: kpmeInfo->Fractals.LNHB = true; break;
							case 366: kpmeInfo->Fractals.DwD = true; break;
							case 365: kpmeInfo->Fractals.DoD = true; break;
							case 399: kpmeInfo->Fractals.NightmareAspect = true; break;
							case 526: kpmeInfo->Fractals.KryptisExorcist = true; break;
							case 299: kpmeInfo->Fractals.FractalSavant = true; break;
							case 297: kpmeInfo->Fractals.FractalProdigy = true; break;
							case 296: kpmeInfo->Fractals.FractalChampion = true; break;
							case 298: kpmeInfo->Fractals.FractalGod = true; break;
						}
					}
				}

				for (json kp : response["killproofs"])
				{
					if (!kp["id"].is_null())
					{
						switch (kp["id"].get<int>())
						{
							case 88485: kpmeInfo->Raids.LI += kp["amount"].get<int>(); break;
							case 77302: kpmeInfo->Raids.LI += kp["amount"].get<int>(); break;
							case 94020: kpmeInfo->Fractals.UFE += kp["amount"].get<int>(); break;
							case 81743: kpmeInfo->Fractals.UFE += kp["amount"].get<int>() * 5; break;
							case 93781: kpmeInfo->Strikes.IBS_BoneskinnerVial += kp["amount"].get<int>(); break;
						}
					}
				}

				for (json token : response["tokens"])
				{
					if (!token["id"].is_null())
					{
						switch (token["id"].get<int>())
						{
							// Wing 1
							case 77705: kpmeInfo->Raids.W1_ValeGuardian += token["amount"].get<int>(); break;
							case 77751: kpmeInfo->Raids.W1_Gorseval += token["amount"].get<int>(); break;
							case 77728: kpmeInfo->Raids.W1_Sabetha += token["amount"].get<int>(); break;

							// Wing 2
							case 77706: kpmeInfo->Raids.W2_Slothasor += token["amount"].get<int>(); break;
							case 77679: kpmeInfo->Raids.W2_Matthias += token["amount"].get<int>(); break;

							// Wing 3
							case 78873: kpmeInfo->Raids.W3_Escort += token["amount"].get<int>(); break;
							case 78902: kpmeInfo->Raids.W3_KeepConstruct += token["amount"].get<int>(); break;
							case 78942: kpmeInfo->Raids.W3_Xera += token["amount"].get<int>(); break;

							// Wing 4
							case 80623: kpmeInfo->Raids.W4_Cairn += token["amount"].get<int>(); break;
							case 80269: kpmeInfo->Raids.W4_MursaatOverseer += token["amount"].get<int>(); break;
							case 80087: kpmeInfo->Raids.W4_Samarog += token["amount"].get<int>(); break;
							case 80542: kpmeInfo->Raids.W4_Deimos += token["amount"].get<int>(); break;

							// Wing 5
							case 85993: kpmeInfo->Raids.W5_SoullessHorror += token["amount"].get<int>(); break;
							case 85633: kpmeInfo->Raids.W5_Dhuum += token["amount"].get<int>(); break;

							// Wing 6
							case 88543: kpmeInfo->Raids.W6_ConjuredAmalgamate += token["amount"].get<int>(); break;
							case 88860: kpmeInfo->Raids.W6_LargosTwins += token["amount"].get<int>(); break;
							case 88645: kpmeInfo->Raids.W6_Qadim += token["amount"].get<int>(); break;

							// Wing 7
							case 91246: kpmeInfo->Raids.W7_CardinalAdina += token["amount"].get<int>(); break;
							case 91270: kpmeInfo->Raids.W7_CardinalSabir += token["amount"].get<int>(); break;
							case 91175: kpmeInfo->Raids.W7_QadimThePeerless += token["amount"].get<int>(); break;

							// Wing 8
							case 104047: kpmeInfo->Raids.W8_Greer += token["amount"].get<int>(); break;
							case 103754: kpmeInfo->Raids.W8_Decima += token["amount"].get<int>(); break;
							case 103996: kpmeInfo->Raids.W8_Ura += token["amount"].get<int>(); break;
						
							// AH
							case 95638: case 107067: kpmeInfo->Strikes.EOD_AH += token["amount"].get<int>(); break;
							case 97269: case 106935: kpmeInfo->Strikes.EOD_AHCM += token["amount"].get<int>(); break;

							// Ankka
							case 95982: case 106954: kpmeInfo->Strikes.EOD_Ankka += token["amount"].get<int>(); break;
							case 96638: case 106999: kpmeInfo->Strikes.EOD_AnkkaCM += token["amount"].get<int>(); break;

							// KO
							case 97451: case 107026: kpmeInfo->Strikes.EOD_KO += token["amount"].get<int>(); break;
							case 96419: case 107028: kpmeInfo->Strikes.EOD_KOCM += token["amount"].get<int>(); break;

							// HT
							case 97132: case 106956: kpmeInfo->Strikes.EOD_HT += token["amount"].get<int>(); break;
							case 95986: case 106910: kpmeInfo->Strikes.EOD_HTCM += token["amount"].get<int>(); break;

							// OLC
							case 99165: case 106951: kpmeInfo->Strikes.EOD_OLC += token["amount"].get<int>(); break;
							case 99204: case 107132: kpmeInfo->Strikes.EOD_OLCCM += token["amount"].get<int>(); break;
							
							// Dagda
							case 100068: case 107087: kpmeInfo->Strikes.EOD_Dagda += token["amount"].get<int>(); break;
							case 101172: case 106940: kpmeInfo->Strikes.EOD_DagdaCM += token["amount"].get<int>(); break;

							// Cerus
							case 100858: case 107114: kpmeInfo->Strikes.EOD_Cerus += token["amount"].get<int>(); break;
							case 101542: case 107065: kpmeInfo->Strikes.EOD_CerusCM += token["amount"].get<int>(); break;

							// Kela
							case 106994: kpmeInfo->Strikes.VOE_Kela += token["amount"].get<int>(); break;
							case 107608: kpmeInfo->Strikes.VOE_KelaCM += token["amount"].get<int>(); break;
						}
					}
				}

				for (json coffer : response["coffers"])
				{
					if (!coffer["id"].is_null())
					{
						switch (coffer["id"].get<int>())
						{
							// Wing 1
							case 91203: kpmeInfo->Raids.W1_ValeGuardian += coffer["amount"].get<int>() * 3; break;
							case 91215: kpmeInfo->Raids.W1_Gorseval += coffer["amount"].get<int>() * 3; break;
							case 91147: kpmeInfo->Raids.W1_Sabetha += coffer["amount"].get<int>() * 3; break;

							// Wing 2
							case 91160: kpmeInfo->Raids.W2_Slothasor += coffer["amount"].get<int>() * 3; break;
							case 91252: kpmeInfo->Raids.W2_Matthias += coffer["amount"].get<int>() * 3; break;

							// Wing 3
							case 91262: kpmeInfo->Raids.W3_Escort += coffer["amount"].get<int>() * 3; break;
							case 91187: kpmeInfo->Raids.W3_KeepConstruct += coffer["amount"].get<int>() * 3; break;
							case 91182: kpmeInfo->Raids.W3_Xera += coffer["amount"].get<int>() * 3; break;

							// Wing 4
							case 91186: kpmeInfo->Raids.W4_Cairn += coffer["amount"].get<int>() * 3; break;
							case 91191: kpmeInfo->Raids.W4_MursaatOverseer += coffer["amount"].get<int>() * 3; break;
							case 91267: kpmeInfo->Raids.W4_Samarog += coffer["amount"].get<int>() * 3; break;
							case 91233: kpmeInfo->Raids.W4_Deimos += coffer["amount"].get<int>() * 3; break;

							// Wing 5
							case 91211: kpmeInfo->Raids.W5_SoullessHorror += coffer["amount"].get<int>() * 3; break;
							case 91220: kpmeInfo->Raids.W5_Dhuum += coffer["amount"].get<int>() * 3; break;

							// Wing 6
							case 91157: kpmeInfo->Raids.W6_ConjuredAmalgamate += coffer["amount"].get<int>() * 3; break;
							case 91166: kpmeInfo->Raids.W6_LargosTwins += coffer["amount"].get<int>() * 3; break;
							case 91237: kpmeInfo->Raids.W6_Qadim += coffer["amount"].get<int>() * 3; break;

							// Wing 7
							case 91200: kpmeInfo->Raids.W7_CardinalAdina += coffer["amount"].get<int>() * 3; break;
							case 91241: kpmeInfo->Raids.W7_CardinalSabir += coffer["amount"].get<int>() * 3; break;
							case 91260: kpmeInfo->Raids.W7_QadimThePeerless += coffer["amount"].get<int>() * 3; break;

							// Wing 8
							case 103783: case 104306: kpmeInfo->Raids.W8_Greer += coffer["amount"].get<int>(); break;
							case 104399: case 107171: kpmeInfo->Raids.W8_GreerCM += coffer["amount"].get<int>(); break;
							case 103926: case 104410: kpmeInfo->Raids.W8_Decima += coffer["amount"].get<int>(); break;
							case 104246: case 106934: kpmeInfo->Raids.W8_DecimaCM += coffer["amount"].get<int>(); break;
							case 103946: case 104439: kpmeInfo->Raids.W8_Ura += coffer["amount"].get<int>(); break;
							case 104355: case 106938: kpmeInfo->Raids.W8_UraCM += coffer["amount"].get<int>(); break;
						}
					}
				}

				{
					const std::lock_guard<std::mutex> lock(this->KPMutex);
					this->KPData.emplace(aAccountName, kpmeInfo);
				}
			}
			catch (json::parse_error& exc)
			{
				G::APIDefs->Log(ELogLevel_WARNING, ADDON_NAME, String::Format("KPME API: Json Parse error\n\t%s", exc.what()).c_str());
			}
		}, aPlayer.Member.AccountName).detach();
	}
}

void CSquadMgr::OnGroupMemberJoin(RTAPI::GroupMember* aGroupMember)
{
	const std::lock_guard<std::mutex> lock(this->Mutex);

	auto plIt = this->Players.find(aGroupMember->AccountName);

	if (plIt != this->Players.end())
	{
		plIt->second.Member = *aGroupMember;
		plIt->second.HasLeft = 0;

		GetKPData(plIt->second);
	}
	else
	{
		auto [newIt, inserted] = this->Players.emplace(aGroupMember->AccountName, PlayerInfo_t{ *aGroupMember });
		// HasLeft is null initialized.

		GetKPData(newIt->second);
	}
}
void CSquadMgr::OnGroupMemberLeave(RTAPI::GroupMember* aGroupMember)
{
	const std::lock_guard<std::mutex> lock(this->Mutex);

	if (aGroupMember->IsSelf)
	{
		/* Only clear for RT/UE, because arc also reports changes on load screen. */
		if (G::RTAPI || G::IsUEEnabled)
		{
			this->Players.clear();
		}
		this->KPRequirement = {};
	}
	else
	{
		auto it = this->Players.find(aGroupMember->AccountName);
		if (it != this->Players.end())
		{
			it->second.HasLeft = Time::GetTimestamp();
		}
	}
}
void CSquadMgr::OnGroupMemberUpdate(RTAPI::GroupMember* aGroupMember)
{
	/* Code is identical to Join. */
	const std::lock_guard<std::mutex> lock(this->Mutex);

	auto plIt = this->Players.find(aGroupMember->AccountName);

	if (plIt != this->Players.end())
	{
		plIt->second.Member = *aGroupMember;
		plIt->second.HasLeft = 0;

		GetKPData(plIt->second);
	}
	else
	{
		auto [newIt, inserted] = this->Players.emplace(aGroupMember->AccountName, PlayerInfo_t{*aGroupMember});
		// HasLeft is null initialized.

		GetKPData(newIt->second);
	}
}

void CSquadMgr::OnAgentJoin(AgentUpdate* aAgentUpdate)
{
	if (!aAgentUpdate) { return; }

	const std::lock_guard<std::mutex> lock(this->CacheMutex);

	auto [agIt, inserted] = this->CachedAgents.insert_or_assign(&aAgentUpdate->AccountName[1], *aAgentUpdate);

	/* Is in party according to arc, else it'd give the display sub. */
	if (aAgentUpdate->Subgroup == 0)
	{
		agIt->second.Subgroup++;
	}

	RTAPI::GroupMember member{};
	strcpy_s(&member.AccountName[0],   sizeof(aAgentUpdate->AccountName)   - 1, &aAgentUpdate->AccountName[1]);
	strcpy_s(&member.CharacterName[0], sizeof(aAgentUpdate->CharacterName) - 1, &aAgentUpdate->CharacterName[0]);
	member.Profession          = aAgentUpdate->Prof;
	member.EliteSpecialization = aAgentUpdate->Elite;
	member.IsSelf              = aAgentUpdate->Self;
	member.IsInInstance        = true; // arc only reports in instance players

	auto ue = this->CachedUsers.find(member.AccountName);

	if (ue != this->CachedUsers.end())
	{
		member.Subgroup     = ue->second.Subgroup;
		member.IsCommander  = ue->second.Role == UserRole::SquadLeader;
		member.IsLieutenant = ue->second.Role == UserRole::Lieutenant;
	}
	else
	{
		member.Subgroup = aAgentUpdate->Subgroup;
	}

	if (G::RTAPI) { return; } /* Do not process. */
	this->OnGroupMemberUpdate(&member);
}
void CSquadMgr::OnAgentLeave(AgentUpdate* aAgentUpdate)
{
	if (!aAgentUpdate) { return; }
	if (G::IsUEEnabled) { return; } // We only want leave events from UE.

	RTAPI::GroupMember member{};

	/* Minimal data needed here. */
	strcpy_s(&member.AccountName[0], sizeof(aAgentUpdate->AccountName) - 1, &aAgentUpdate->AccountName[1]);
	member.IsSelf = aAgentUpdate->Self;

	if (G::RTAPI) { return; } /* Do not process. */
	this->OnGroupMemberLeave(&member);
}
void CSquadMgr::OnSquadUpdate(SquadUpdate* aSquadUpdate)
{
	G::IsUEEnabled = true;
	
	for (size_t i = 0; i < aSquadUpdate->UsersCount; i++)
	{
		const std::lock_guard<std::mutex> lock(this->CacheMutex);

		RTAPI::GroupMember member{};

		auto [usrIt, inserted] = this->CachedUsers.insert_or_assign(&aSquadUpdate->UserInfo[i].AccountName[1], aSquadUpdate->UserInfo[i]);

		strcpy_s(&member.AccountName[0], sizeof(member.AccountName) - 1, usrIt->first.c_str());
		member.Subgroup     = usrIt->second.Subgroup;
		/* UE reports 0 based subgroup instead of display value. So we increment it manually. */
		member.Subgroup    += (usrIt->second.Role != UserRole::Invited && usrIt->second.Role != UserRole::Applied) ? 1 : 0;
		member.IsCommander  = usrIt->second.Role == UserRole::SquadLeader;
		member.IsLieutenant = usrIt->second.Role == UserRole::Lieutenant;

		auto agIt = this->CachedAgents.find(usrIt->first);

		if (agIt != this->CachedAgents.end())
		{
			strcpy_s(&member.CharacterName[0], sizeof(member.CharacterName) - 1, agIt->first.c_str());
			member.Profession          = agIt->second.Prof;
			member.EliteSpecialization = agIt->second.Elite;
			member.IsInInstance        = agIt->second.ID > 0;
			member.IsSelf              = agIt->second.Self;
		}

		if (usrIt->second.Role == UserRole::None)
		{
			this->CachedUsers.erase(usrIt);
			if (agIt != this->CachedAgents.end() && !agIt->second.Self)
			{
				this->CachedAgents.erase(agIt);
			}

			if (G::RTAPI) { continue; } /* Do not process. */
			this->OnGroupMemberLeave(&member);
		}
		else
		{
			if (G::RTAPI) { continue; } /* Do not process. */
			this->OnGroupMemberUpdate(&member);
		}
	}
}
