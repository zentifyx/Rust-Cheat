#include <d3d9.h>
#include "cheat_funcs/Entity.h"
#include "../ImGUI/imgui_internal.h"

inline void CornerBox(float Entity_x, float Entity_y, float Entity_w, float Entity_h, D2D1::ColorF ColorRectangle = D2D1::ColorF::Lime)
{
	GUI::Render.Line({ Entity_x, Entity_y }, { Entity_x + Entity_w / 3.5f,Entity_y }, FLOAT4TOD3DCOLOR(Vars::Color::BoxColor), 3.f);
	GUI::Render.Line({ Entity_x, Entity_y }, { Entity_x + Entity_w / 3.5f,Entity_y }, ColorRectangle);
	GUI::Render.Line({ Entity_x, Entity_y }, { Entity_x,Entity_y + Entity_h / 3.5f }, FLOAT4TOD3DCOLOR(Vars::Color::BoxColor), 3.f);
	GUI::Render.Line({ Entity_x, Entity_y }, { Entity_x,Entity_y + Entity_h / 3.5f }, ColorRectangle);

	GUI::Render.Line({ Entity_x + Entity_w, Entity_y }, { (Entity_x + Entity_w) - Entity_w / 3.5f,Entity_y }, FLOAT4TOD3DCOLOR(Vars::Color::BoxColor), 3.f);
	GUI::Render.Line({ Entity_x + Entity_w, Entity_y }, { (Entity_x + Entity_w) - Entity_w / 3.5f,Entity_y }, ColorRectangle);
	GUI::Render.Line({ Entity_x + Entity_w, Entity_y }, { Entity_x + Entity_w,Entity_y + Entity_h / 3.5f }, FLOAT4TOD3DCOLOR(Vars::Color::BoxColor), 3.f);
	GUI::Render.Line({ Entity_x + Entity_w, Entity_y }, { Entity_x + Entity_w,Entity_y + Entity_h / 3.5f }, ColorRectangle);

	GUI::Render.Line({ Entity_x + Entity_w, Entity_y + Entity_h }, { (Entity_x + Entity_w) - Entity_w / 3.5f,Entity_y + Entity_h }, FLOAT4TOD3DCOLOR(Vars::Color::BoxColor), 3.f);
	GUI::Render.Line({ Entity_x + Entity_w, Entity_y + Entity_h }, { (Entity_x + Entity_w) - Entity_w / 3.5f,Entity_y + Entity_h }, ColorRectangle);
	GUI::Render.Line({ Entity_x + Entity_w, Entity_y + Entity_h }, { Entity_x + Entity_w,(Entity_y + Entity_h) - Entity_h / 3.5f }, FLOAT4TOD3DCOLOR(Vars::Color::BoxColor), 3.f);
	GUI::Render.Line({ Entity_x + Entity_w, Entity_y + Entity_h }, { Entity_x + Entity_w,(Entity_y + Entity_h) - Entity_h / 3.5f }, ColorRectangle);

	GUI::Render.Line({ Entity_x, Entity_y + Entity_h }, { Entity_x + Entity_w / 3.5f,Entity_y + Entity_h }, FLOAT4TOD3DCOLOR(Vars::Color::BoxColor), 3.f);
	GUI::Render.Line({ Entity_x, Entity_y + Entity_h }, { Entity_x + Entity_w / 3.5f,Entity_y + Entity_h }, ColorRectangle);
	GUI::Render.Line({ Entity_x, Entity_y + Entity_h }, { Entity_x,(Entity_y + Entity_h) - Entity_h / 3.5f }, FLOAT4TOD3DCOLOR(Vars::Color::BoxColor), 3.f);
	GUI::Render.Line({ Entity_x, Entity_y + Entity_h }, { Entity_x,(Entity_y + Entity_h) - Entity_h / 3.5f }, ColorRectangle);
	if (Vars::Visuals::FillBox)
		GUI::Render.FillRectangle(Vector2{ Entity_x, Entity_y }, Vector2{ Entity_w, Entity_h }, D2D1::ColorF(0, 0, 0, 0.45));
}

D3DCOLOR FLOAT4TOD3DCOLOR(float Col[])
{
	ImU32 col32_no_alpha = ImGui::ColorConvertFloat4ToU32(ImVec4(Col[0], Col[1], Col[2], Col[3]));
	float a = (col32_no_alpha >> 24) & 255;
	float r = (col32_no_alpha >> 16) & 255;
	float g = (col32_no_alpha >> 8) & 255;
	float b = col32_no_alpha & 255;
	return D3DCOLOR_ARGB((int)a, (int)b, (int)g, (int)r);
}
void Skeleton(BasePlayer* BasePlayer)
{
	BoneList Bones[15] = {
		/*LF*/l_foot, l_knee, l_hip,
		/*RF*/r_foot, r_knee, r_hip,
		/*BD*/spine1, neck, head,
		/*LH*/l_upperarm, l_forearm, l_hand,
		/*RH*/r_upperarm, r_forearm, r_hand
	}; Vector2 BonesPos[15];

	//get bones screen pos
	for (int j = 0; j < 15; j++) {
		if (!LocalPlayer.WorldToScreen(BasePlayer->GetBoneByID(Bones[j]), BonesPos[j]))
			return;
	}

	//draw main lines
	for (int j = 0; j < 15; j += 3) {
		GUI::Render.Line(Vector2{ BonesPos[j].x, BonesPos[j].y }, Vector2{ BonesPos[j + 1].x, BonesPos[j + 1].y }, FLOAT4TOD3DCOLOR(Vars::Color::SkeletonColor), 3.f);
		GUI::Render.Line(Vector2{ BonesPos[j + 1].x, BonesPos[j + 1].y }, Vector2{ BonesPos[j + 2].x, BonesPos[j + 2].y }, FLOAT4TOD3DCOLOR(Vars::Color::SkeletonColor), 3.f);
	}

	//draw add lines
	GUI::Render.Line(Vector2{ BonesPos[2].x, BonesPos[2].y }, Vector2{ BonesPos[6].x, BonesPos[6].y }, FLOAT4TOD3DCOLOR(Vars::Color::SkeletonColor), 3.f);
	GUI::Render.Line(Vector2{ BonesPos[5].x, BonesPos[5].y }, Vector2{ BonesPos[6].x, BonesPos[6].y }, FLOAT4TOD3DCOLOR(Vars::Color::SkeletonColor), 3.f);
	GUI::Render.Line(Vector2{ BonesPos[9].x, BonesPos[9].y }, Vector2{ BonesPos[7].x, BonesPos[7].y }, FLOAT4TOD3DCOLOR(Vars::Color::SkeletonColor), 3.f);
	GUI::Render.Line(Vector2{ BonesPos[12].x, BonesPos[12].y }, Vector2{ BonesPos[7].x, BonesPos[7].y }, FLOAT4TOD3DCOLOR(Vars::Color::SkeletonColor), 3.f);
}

void MemeBox(const D2D1::ColorF& PlayerClr, BasePlayer* BasePlayer)
{
	BoneList Bones[4] = {
		/*UP*/l_upperarm, r_upperarm,
		/*DOWN*/r_foot, l_foot
	}; Vector2 BonesPos[4];

	//get bones screen pos
	for (int j = 0; j < 4; j++) {
		if (!LocalPlayer.WorldToScreen(BasePlayer->GetBoneByID(Bones[j]), BonesPos[j]))
			return;
	}

	//draw main lines
	GUI::Render.Line(Vector2{ BonesPos[0].x, BonesPos[0].y }, Vector2{ BonesPos[1].x, BonesPos[1].y }, FLOAT4TOD3DCOLOR(Vars::Color::LineEsp), 3.f);
	GUI::Render.Line(Vector2{ BonesPos[0].x, BonesPos[0].y }, Vector2{ BonesPos[3].x, BonesPos[3].y }, FLOAT4TOD3DCOLOR(Vars::Color::LineEsp), 3.f);
	GUI::Render.Line(Vector2{ BonesPos[2].x, BonesPos[2].y }, Vector2{ BonesPos[1].x, BonesPos[1].y }, FLOAT4TOD3DCOLOR(Vars::Color::LineEsp), 3.f);
	GUI::Render.Line(Vector2{ BonesPos[2].x, BonesPos[2].y }, Vector2{ BonesPos[3].x, BonesPos[3].y }, FLOAT4TOD3DCOLOR(Vars::Color::LineEsp), 3.f);
}

void Crosshair()
{
	float xs = Vars::Global::ScreenWidth / 2, ys = Vars::Global::ScreenHigh / 2;

	GUI::Render.Line(Vector2{ xs, ys - -10 }, Vector2{ xs , ys + 5 }, FLOAT4TOD3DCOLOR(Vars::Color::CrosshairColor));
	GUI::Render.Line(Vector2{ xs - -10, ys }, Vector2{ xs + 5, ys }, FLOAT4TOD3DCOLOR(Vars::Color::CrosshairColor));
	GUI::Render.Line(Vector2{ xs, ys - 4 }, Vector2{ xs , ys + -10 }, FLOAT4TOD3DCOLOR(Vars::Color::CrosshairColor));
	GUI::Render.Line(Vector2{ xs - 4, ys }, Vector2{ xs + -10, ys }, FLOAT4TOD3DCOLOR(Vars::Color::CrosshairColor));
}


void circlecrosshair()
{
	float xs = Vars::Global::ScreenWidth / 2, ys = Vars::Global::ScreenHigh / 2;

	if (Vars::Visuals::CircleCrosshair)
	{
		GUI::Render.Ñircle(Vector2{ xs - 1, ys }, FLOAT4TOD3DCOLOR(Vars::Color::CircleCrosshair), Vars::HvH::Tick2);
	}
}

void DrawFOV()
{
	float xs = Vars::Global::ScreenWidth / 2, ys = Vars::Global::ScreenHigh / 2;
	GUI::Render.Ñircle(Vector2{ xs, ys }, FLOAT4TOD3DCOLOR(Vars::Color::Fov), Vars::AimBot::Fov, 1.f);
	GUI::Render.Ñircle(Vector2{ xs, ys }, FLOAT4TOD3DCOLOR(Vars::Color::Fov), Vars::AimBot::Fov);
}

void DrawSilentFOV()
{
	float xs = Vars::Global::ScreenWidth / 2, ys = Vars::Global::ScreenHigh / 2;
	GUI::Render.Ñircle(Vector2{ xs, ys }, FLOAT4TOD3DCOLOR(Vars::Color::SilentFovColor), Vars::AimBot::SilentFov, 1.f);
	GUI::Render.Ñircle(Vector2{ xs, ys }, FLOAT4TOD3DCOLOR(Vars::Color::SilentFovColor), Vars::AimBot::SilentFov);
}


void DrawPSilentFov()
{
	float xs = Vars::Global::ScreenWidth / 2, ys = Vars::Global::ScreenHigh / 2;
	GUI::Render.Ñircle(Vector2{ xs, ys }, FLOAT4TOD3DCOLOR(Vars::Color::SilentFovColor), Vars::AimBot::SilentFov, 1.f);
	GUI::Render.Ñircle(Vector2{ xs, ys }, FLOAT4TOD3DCOLOR(Vars::Color::SilentFovColor), Vars::AimBot::SilentFov);
}



#pragma region Player ESP

void ESP(BasePlayer* BP, BasePlayer* LP)
{
	bool PlayerSleeping = BP->HasFlags(16);
	if (Vars::Visuals::IgnoreSleepers && PlayerSleeping)
		return;

	if (Vars::Visuals::SkeletonPlayer && BP->GetSteamID() > 1000000000)
	{
		Skeleton(BP);
	}

	else if (Vars::Visuals::SkeletonBots && BP->GetSteamID() < 1000000000)
	{
		Skeleton(BP);
	}

	Vector2 tempFeetR, tempFeetL;
	if (LocalPlayer.WorldToScreen(BP->GetBoneByID(r_foot), tempFeetR) && LocalPlayer.WorldToScreen(BP->GetBoneByID(l_foot), tempFeetL))
	{
		Vector2 tempHead;
		if (LocalPlayer.WorldToScreen(BP->GetBoneByID(jaw) + Vector3(0.f, 0.16f, 0.f), tempHead))
		{
			Vector2 tempFeet = (tempFeetR + tempFeetL) / 2.f;
			float Entity_h = tempHead.y - tempFeet.y;
			float w = Entity_h / 4;
			float Entity_x = tempFeet.x - w;
			float Entity_y = tempFeet.y;
			float Entity_w = Entity_h / 2;

			bool PlayerWounded = BP->HasFlags(64);
			D2D1::ColorF::Enum PlayerClr = PlayerSleeping ? D2D1::ColorF::BlueViolet : PlayerWounded ? D2D1::ColorF::DarkOrange : D2D1::ColorF::Gold;

			int CurPos = 0;

			if (Vars::Visuals::PlayerESP && BP->GetSteamID() > 1000000000)
			{
				GUI::Render.String(Vector2{ (Entity_x + 7), (Entity_y + Entity_h) }, BP->GetName(), FLOAT4TOD3DCOLOR(Vars::Color::NameColor));
				CurPos += 15;


				if (Vars::Visuals::ShowPlayerBox)
				{
					if (!PlayerWounded && !PlayerSleeping)
					{
						CornerBox(Entity_x, Entity_y, Entity_w, Entity_h, FLOAT4TOD3DCOLOR(Vars::Color::BoxColor));
					}
					else MemeBox(PlayerClr, BP);

					if (Vars::Visuals::ShowPlayerHealth) {

						GUI::Render.String(Vector2{ (Entity_x + 7), (Entity_y + Entity_h + CurPos) }, FC_FORMAT_W(L"%d HP", (int)BP->GetHealth()), FLOAT4TOD3DCOLOR(Vars::Color::PlayerHeath));
						CurPos += 15;
					}

					if (Vars::Visuals::ShowPlayerWeapon)
					{
						const wchar_t* ActiveWeaponName;
						WeaponData* ActWeapon = BP->GetActiveWeapon();
						ActiveWeaponName = ActWeapon->GetName();
						if (!ActWeapon)
						{
							ActiveWeaponName = L"-";

						}
						else
						{
							ActiveWeaponName = ActWeapon->GetName();
						}

						GUI::Render.String(Vector2{ (Entity_x + 7), (Entity_y + Entity_h + CurPos) }, ActiveWeaponName, FLOAT4TOD3DCOLOR(Vars::Color::WeaponColor));
						CurPos += 15;
					}

					if (Vars::Visuals::ShowPlayerDist) {
						GUI::Render.String(Vector2{ (Entity_x + 7), (Entity_y + Entity_h + CurPos) }, FC_FORMAT_W(L"%d : M", (int)Math::Calc3D_Dist(LP->GetBoneByID(head), BP->GetBoneByID(head))), FLOAT4TOD3DCOLOR(Vars::Color::DistanceColor));
						CurPos += 15;
					}
				}
			}
			else if (Vars::Visuals::BotsESP && BP->GetSteamID() < 1000000000)
			{
				GUI::Render.String(Vector2{ (Entity_x + 7), (Entity_y + Entity_h) }, L"Bots", FLOAT4TOD3DCOLOR(Vars::Color::BotColor));
				CurPos += 15;
				GUI::Render.String(Vector2{ (Entity_x + 7), (Entity_y + Entity_h + CurPos) }, FC_FORMAT_W(L"%d : HP", (int)BP->GetHealth()), FLOAT4TOD3DCOLOR(Vars::Color::BotColor));
				CurPos += 15;
				GUI::Render.String(Vector2{ (Entity_x + 7), (Entity_y + Entity_h + CurPos) }, FC_FORMAT_W(L"%d : M", (int)Math::Calc3D_Dist(LP->GetBoneByID(head), BP->GetBoneByID(head))), FLOAT4TOD3DCOLOR(Vars::Color::BotColor));
				CurPos += 15;

			}
		}
	}
}

__forceinline float Distance3D(const Vector3& Src, const Vector3& Dst)
{
	return sqrtf(pow((Src.x - Dst.x), 2) + pow((Src.y - Dst.y), 2) + pow((Src.z - Dst.z), 2));
}


inline void RadarPlayer(BasePlayer* player)
{
	if (LocalPlayer.BasePlayer)
	{
		if (Vars::Radar::Enable)
		{
			if (Vars::Radar::ShowRadarPlayer || Vars::Radar::ShowRadarSleeper)
			{
				if (!player->IsDead() && player->GetHealth() >= 0.2f)
				{
					const Vector3 LocalPos = LocalPlayer.BasePlayer->GetPosition();
					const Vector3 PlayerPos = player->GetPosition();
					const float Distance = Distance3D(LocalPos, PlayerPos);
					const float y = LocalPos.x - PlayerPos.x;
					const float x = LocalPos.z - PlayerPos.z;
					Vector3 LocalEulerAngles;
					if (Vars::Radar::EnableDinamicRadar)
					{
						LocalEulerAngles = LocalPlayer.BasePlayer->GetEulerAngles();
					}
					else
					{
						LocalEulerAngles = LocalPlayer.BasePlayer->GetPosition();
					}
					const float num = atan2(y, x) * 57.29578f - 270.f - LocalEulerAngles.y;
					float PointPos_X = Distance * cos(num * 0.0174532924f);
					float PointPos_Y = Distance * sin(num * 0.0174532924f);
					PointPos_X = PointPos_X * (Vars::Radar::Radar_Size / Vars::Radar::Radar_Range) / 2.f;
					PointPos_Y = PointPos_Y * (Vars::Radar::Radar_Size / Vars::Radar::Radar_Range) / 2.f;
					if (!player->HasFlags(16) && Vars::Radar::ShowRadarPlayer)
					{
						if (Distance <= Vars::Radar::Radar_Range)
						{
							GUI::Render.FillCircle({ Vars::Radar::Pos_X + Vars::Radar::Radar_Size / 2.f + PointPos_X - 3.f, Vars::Radar::Pos_Y + Vars::Radar::Radar_Size / 2.f + PointPos_Y - 3.f }, D2D1::ColorF::Lime, 3.f);
						}
					}
					else if (player->HasFlags(16) && Vars::Radar::ShowRadarSleeper)
					{
						if (Distance <= Vars::Radar::Radar_Range)
						{
							GUI::Render.FillCircle({ Vars::Radar::Pos_X + Vars::Radar::Radar_Size / 2.f + PointPos_X - 3.f, Vars::Radar::Pos_Y + Vars::Radar::Radar_Size / 2.f + PointPos_Y - 3.f }, D2D1::ColorF::Red, 3.f);
						}
					}
				}
			}
		}
	}
}

inline void RenderActiveSlot(BasePlayer* player, float Pos_x, float Pos_Y)
{


	const float Height = 150.f;
	const float With = 260.f;
	GUI::Render.FillRoundedRectangle({ Pos_x, Pos_Y }, { With, Height }, D2D1::ColorF::Black, 2);
	GUI::Render.RenderString({ Pos_x + (With / 2), Pos_Y + 5 }, player->GetName(), true, D2D1::ColorF::Lime);
	float Pos = 0;
	GUI::Render.Line({ Pos_x, Pos_Y + 20 }, { Pos_x + With, Pos_Y + 20 }, D2D1::ColorF::Red, 3);
	for (int i = 0; i < 6; i++)
	{
		WeaponData* GetWeaponInfo = player->GetWeaponInfo(i);
		if (GetWeaponInfo)
		{
			const wchar_t* Item = player->GetWeaponInfo(i)->GetName();
			if (wcslen(Item) < 20)
			{
				GUI::Render.RenderString({ Pos_x + (With / 2), Pos_Y + 40 + Pos }, Item, true);
			}
		}
		else
		{
			GUI::Render.RenderString({ Pos_x + (With / 2), Pos_Y + 40 + Pos }, L"Nothing", true, D2D1::ColorF::Red);
		}
		Pos += 15;
	}

}



inline void RenderRadarBackground(float Pos_x, float Pos_Y, float Rad)
{
	if (Vars::Radar::ShowRadarBackground)
     GUI::Render.FillCircle({ Pos_x + Rad / 2, Pos_Y + Rad / 2 }, FLOAT4TOD3DCOLOR(Vars::RadarColor::RadarBackground), Rad / 2);
	 GUI::Render.Ñircle({ Pos_x + Rad / 2, Pos_Y + Rad / 2 }, ConverToRGB(20, 15, 52), Rad / 2, 3.f);
	 GUI::Render.Line({ Pos_x + Rad / 2, Pos_Y }, { Pos_x + Rad / 2,Pos_Y + Rad }, D2D1::ColorF::White);
	 GUI::Render.Line({ Pos_x, Pos_Y + Rad / 2 }, { Pos_x + Rad, Pos_Y + Rad / 2 }, D2D1::ColorF::White);
}


#pragma endregion

