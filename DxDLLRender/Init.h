void EspPreview()
{
	static bool enabled = true;
	ImGui::SetNextWindowSize(ImVec2(200, 400));
	ImGui::Begin("ESP Preview", &enabled, ImGuiWindowFlags_NoResize | ImGuiWindowFlags_NoCollapse | ImGuiWindowFlags_NoTitleBar);
	{
		auto cur_window = ImGui::GetCurrentWindow();
		ImVec2 w_pos = cur_window->Pos;
		if (Vars::Visuals::Preview::Box)
		{
			cur_window->DrawList->AddRect(ImVec2(w_pos.x + 40, w_pos.y + 60), ImVec2(w_pos.x + 200, w_pos.y + 360), ImColor(Vars::Color::BoxColor));
		}
		if (Vars::Visuals::Preview::Name)
		{
			cur_window->DrawList->AddText(ImVec2{ w_pos.x + 210, w_pos.y + 75 }, ImColor(Vars::Color::NameColor), "NAME");
		}
		if (Vars::Visuals::Preview::Health)
		{
			cur_window->DrawList->AddText(ImVec2{ w_pos.x + 210, w_pos.y + 90 }, ImColor(Vars::Color::PlayerHeath), "1337 HP");
		}
		if (Vars::Visuals::Preview::Dist)
		{
			cur_window->DrawList->AddText(ImVec2{ w_pos.x + 210, w_pos.y + 105 }, ImColor(Vars::Color::DistanceColor), "228 M");
		}
		if (Vars::Visuals::Preview::Weapon)
		{
			cur_window->DrawList->AddText(ImVec2{ w_pos.x + 210, w_pos.y + 120 }, ImColor(Vars::Color::WeaponColor), "WEAPON");
		}
	}
	ImGui::End();
}

void InitCheat()
{
	float Y = GetSystemMetrics(SM_CYSCREEN);

	Vector2 kek = GUI::Render.CanvasSize();
	Vars::Global::ScreenWidth = kek.x;
	Vars::Global::ScreenHigh = kek.y;


	if (Vars::AimBot::BodyAim) Vars::Global::BoneToAim = 21;
	else Vars::Global::BoneToAim = 46;

	if (Vars::Visuals::Crosshair)
		Crosshair();

	if (Vars::Visuals::CircleCrosshair)
		circlecrosshair();

	if (Vars::AimBot::DrawFov)
		DrawFOV();

	if (Vars::Radar::Enable)
		RenderRadarBackground(Vars::Radar::Pos_X, Vars::Radar::Pos_Y, Vars::Radar::Radar_Size);


	if (TargetSilentPlayer != NULL && Vars::AimBot::EnableSilentAim) // && Player->GetSteamID() < 1000000000
	{
		auto* TargetPlayer = reinterpret_cast<BasePlayer*>(TargetSilentPlayer);
		Vector2 ScreenPos;
		const Vector2 ScreenSize = GUI::Render.CanvasSize();
		Vars::Global::ScreenWidth = ScreenSize.x;
		Vars::Global::ScreenHigh = ScreenSize.y;
		if (Vars::AimBot::SilentTarget)
		{
			if (!(TargetPlayer->GetBoneByID(spine1).x == 0 && TargetPlayer->GetBoneByID(spine1).y == 0 && TargetPlayer->GetBoneByID(spine1).z == 0)) {
				if (LocalPlayer.WorldToScreen(TargetPlayer->GetBoneByID(spine1), ScreenPos))
					GUI::Render.Line({ Vars::Global::ScreenWidth / 2, Vars::Global::ScreenHigh }, ScreenPos, FLOAT4TOD3DCOLOR(Vars::Color::SilentColor));
			}
		}
	}

	if (TargetPSilentPlayer != NULL && Vars::AimBot::pSilent) // && Player->GetSteamID() < 1000000000
	{
		auto* TargetPlayer = reinterpret_cast<BasePlayer*>(TargetPSilentPlayer);
		Vector2 ScreenPos;
		const Vector2 ScreenSize = GUI::Render.CanvasSize();
		Vars::Global::ScreenWidth = ScreenSize.x;
		Vars::Global::ScreenHigh = ScreenSize.y;
		if (Vars::AimBot::PSilentTarget)
		{
			if (!(TargetPlayer->GetBoneByID(spine1).x == 0 && TargetPlayer->GetBoneByID(spine1).y == 0 && TargetPlayer->GetBoneByID(spine1).z == 0)) 
			{
				if (LocalPlayer.WorldToScreen(TargetPlayer->GetBoneByID(spine1), ScreenPos))
					GUI::Render.Line({ Vars::Global::ScreenWidth / 2, Vars::Global::ScreenHigh }, ScreenPos, FLOAT4TOD3DCOLOR(Vars::Color::SilentColor));
			}
		}
	}

	/*if (Vars::Test::Preview)
		EspPreview();
		*/
	if (Vars::AimBot::DrawSilentFov)
		DrawSilentFOV();

	if (Vars::AimBot::DrawPSilentFov)
		DrawPSilentFov();

	if (GetAsyncKeyState(Vars::AimBot::silentclearkey) && Vars::AimBot::SilentClear)
		TargetSilentPlayer = NULL;

	if (GetAsyncKeyState(Vars::AimBot::Psilentclearkey) && Vars::AimBot::PSilentClear)
		TargetPSilentPlayer = NULL;

	static float r = 1.00f, g = 0.00f, b = 1.00f;
	static int cases = 0;
	switch (cases)
	{
	case 0: { r -= 0.005f; if (r <= 0) cases += 1; break; }
	case 1: { g += 0.005f; b -= 0.005f; if (g >= 1) cases += 1; break; }
	case 2: { r += 0.005f; if (r >= 1) cases += 1; break; }
	case 3: { b += 0.005f; g -= 0.005f; if (b >= 1) cases = 0; break; }
	default: { r = 1.00f; g = 0.00f; b = 1.00f; break; }
	}

	GUI::Render.String({ 10.f, 10.f }, (L"Cheat"), D2D1::ColorF(r,g,b, 1.00f));


	Entity();
}