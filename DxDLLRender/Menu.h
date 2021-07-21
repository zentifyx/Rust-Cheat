
using namespace ImGui;

void MenuSteep() {
	
	ImGui::SetWindowSize(ImVec2(850, 430));
	
	{
		if (ImGui::Begin("sharawin.pw", 0, ImGuiWindowFlags_NoCollapse | ImGuiWindowFlags_NoResize))
		ImGui::BeginChild("Aimbot", ImVec2(200, 398), true);
		{
			ImGui::Text("Aimbot");
			ImGui::Separator();
			CheckboxD("Activate", &Vars::AimBot::Activate);
			if (Vars::AimBot::Activate) {
				Hotkey("Aim Key", &Vars::AimBot::aimkey, ImVec2(150, 30));
				CheckboxD("Body Aim", &Vars::AimBot::BodyAim);
				
				CheckboxD("Recoil control system", &Vars::AimBot::RCS);
				CheckboxD("RCS standalone", &Vars::AimBot::Standalone);
				CheckboxD("Visible check", &Vars::AimBot::VisibleCheck);
				CheckboxD("Show FOV", &Vars::AimBot::DrawFov);
				ImGui::SliderFloat("Fov", &Vars::AimBot::Fov, 0, 400);
				ImGui::SliderFloat("Max Distance", &Vars::AimBot::Range, 0.f, 400.f);
			}
			CheckboxD(("Always Headshot"), &Vars::AimBot::AlwaysHeadshot);
			ImGui::Text("pSilent");//and Silent
			CheckboxD("pSilent", &Vars::AimBot::pSilent);
			if (Vars::AimBot::pSilent) {
				CheckboxD("Draw pSilent Fov", &Vars::AimBot::DrawPSilentFov);
				
				CheckboxD("pSilent Draw Target Line", &Vars::AimBot::PSilentTarget);
				CheckboxD("pSilent Clear Target", &Vars::AimBot::PSilentClear);
			}
			if (Vars::AimBot::PSilentClear)
			{
				Hotkey(("PSilentClear Key"), &Vars::AimBot::Psilentclearkey, ImVec2(150, 30));
			}
			
			CheckboxD("FatBullet", &Vars::AimBot::FatBullet);//SuperBow
			CheckboxD("SuperBow", &Vars::Misc::SuperBow);//SuperBow
			CheckboxD("Fake_Dist", &Vars::AimBot::Fake_Dist);
			if (Vars::AimBot::Fake_Dist)
			{
				ImGui::SliderFloat("Fake Dist", &Vars::AimBot::distancefake, 0.f, 4000.f);
			}
			
		}
		ImGui::EndChild();
		ImGui::SameLine();

		ImGui::BeginChild("Visual", ImVec2(200, 398), true);
		{
			ImGui::Text("Player");
			CheckboxD("Enable player ESP", &Vars::Visuals::PlayerESP);
			CheckboxD("Box", &Vars::Visuals::ShowPlayerBox);
			CheckboxD("FillBox", &Vars::Visuals::FillBox);
			CheckboxD("Health", &Vars::Visuals::ShowPlayerHealth);
			CheckboxD("Weapon", &Vars::Visuals::ShowPlayerWeapon);
			CheckboxD("Distance", &Vars::Visuals::ShowPlayerDist);
			CheckboxD("Ignore sleepers", &Vars::Visuals::IgnoreSleepers);
			CheckboxD("Skeleton", &Vars::Visuals::SkeletonPlayer);
			ImGui::Text("Bot");
			CheckboxD("enable bots ESP", &Vars::Visuals::BotsESP);
			CheckboxD("enable bots skeleton", &Vars::Visuals::SkeletonBots);
			ImGui::Text("Ore and Others ESP");
			CheckboxD("Show Weapons", &Vars::Visuals::show_Weapons);
			if (Vars::Visuals::show_Weapons)
			{
				ImGui::SliderFloat("show_WeaponsDistation", &Vars::Visuals::show_WeaponsDistation, 0.f, 400.f);
			}
			CheckboxD("Sulphur", &Vars::Visuals::Sulphur);
			if (Vars::Visuals::Sulphur)
			{
				ImGui::SliderFloat("SulphurOreDistation", &Vars::Visuals::SulphurOreDistation, 0.f, 400.f);
			}
			CheckboxD("Metal", &Vars::Visuals::Metal);
			if (Vars::Visuals::Metal)
			{
				ImGui::SliderFloat("MetalOreDistation", &Vars::Visuals::MetalOreDistation, 0.f, 400.f);
			}
			CheckboxD("Stone", &Vars::Visuals::Stone);
			if (Vars::Visuals::Stone)
			{
				ImGui::SliderFloat("StoneOreDistation", &Vars::Visuals::StoneOreDistation, 0.f, 400.f);
			}
			CheckboxD("Stash", &Vars::Visuals::Stash);
			if (Vars::Visuals::Stash)
			{
				ImGui::SliderFloat("StashDistation", &Vars::Visuals::StashDistation, 0.f, 400.f);
			}
			CheckboxD("Minicopter", &Vars::Visuals::Minicopter);
			if (Vars::Visuals::Minicopter)
			{
				ImGui::SliderFloat("MinicopterDistation", &Vars::Visuals::MinicopterDistation, 0.f, 4000.f);
			}
			CheckboxD("Patrol Helicopter", &Vars::Visuals::Patrul);
			if (Vars::Visuals::Patrul)
			{
				ImGui::SliderFloat("PatrulDistation", &Vars::Visuals::PatrulDistation, 0.f, 4000.f);
			}
			CheckboxD("Traps", &Vars::Visuals::Traps);
			if (Vars::Visuals::Traps)
			{
				ImGui::SliderFloat("TrapsDistation", &Vars::Visuals::TrapsDistation, 0.f, 400.f);
			}
			CheckboxD("Hemp", &Vars::Visuals::Hemp);
			if (Vars::Visuals::Hemp)
			{
				ImGui::SliderFloat("HempDistation", &Vars::Visuals::HempDistation, 0.f, 400.f);
			}
			CheckboxD("Supply", &Vars::Visuals::Supply);
			if (Vars::Visuals::Supply)
			{
				ImGui::SliderFloat("SupplyDistation", &Vars::Visuals::SupplyDistation, 0.f, 4000.f);
			}
			CheckboxD("Corpse", &Vars::Visuals::Corpse);
			if (Vars::Visuals::Corpse)
			{
				ImGui::SliderFloat("CorpseDistation", &Vars::Visuals::CorpseDistation, 0.f, 400.f);
			}
		}
		ImGui::EndChild();
		ImGui::SameLine();

		ImGui::BeginChild("Misc", ImVec2(200, 398), true);
		{
			ImGui::Text("Other");
			ImGui::Separator();
			
			CheckboxD("AutoPickUp", &Vars::Misc::AutoPickUp);
			CheckboxD("Door", &Vars::Misc::Door);
			CheckboxD("Fast Heal", &Vars::Misc::FastHeal);
			CheckboxD("AdminTools", &Vars::Misc::AdminTools);
			CheckboxD("Anti Aim", &Vars::Misc::AntiAim);
			CheckboxD("Fake Lag", &Vars::Misc::FakeLag);
			ImGui::Separator();
			ImGui::Text("Movement");
			CheckboxD("Slide Walk", &Vars::Misc::SlideWalk);
			CheckboxD("Spoof OnLadder", &Vars::Misc::Flyhack);
			CheckboxD("SilentWalk", &Vars::Misc::SilentWalk);
			CheckboxD("SpiderMan", &Vars::Misc::SpiderMan);
			CheckboxD("InfinityJump", &Vars::Misc::InfinityJump);
			CheckboxD("Change Gravity", &Vars::Misc::HighJump);
			if (Vars::Misc::HighJump)
			{
				ImGui::SliderFloat("Gravity percentage", &Vars::Misc::JumpValue, 0.f, 2.5f);
				Hotkey("Gravity Key", &Vars::Misc::highkey, ImVec2(150, 30));
			}
			CheckboxD("WalkOnWater", &Vars::Misc::WalkOnWater);
			if (Vars::Misc::WalkOnWater)
			{
				Hotkey("Walk Key", &Vars::Misc::walkkey, ImVec2(150, 30));
			}
			CheckboxD("Speed Hack", &Vars::Misc::SpeedHack);
			if (Vars::Misc::SpeedHack) {
				ImGui::SliderFloat("SpeedHack", &Vars::Misc::SpeedValue, 0.f, 10.f);
			}
			ImGui::Text("Weapon");
			ImGui::Separator();
			CheckboxD("No recoil", &Vars::Misc::NoRecoil);
			CheckboxD("No spread", &Vars::Misc::AntiSpread);

			CheckboxD("Custom fov", &Vars::Misc::CustomFov);
			if (Vars::Misc::CustomFov)
			{
				ImGui::SliderFloat("fov", &Vars::Misc::GraphicsFov, 0.f, 180.f);
			}
			CheckboxD("Automatic", &Vars::Misc::Automatic);
			CheckboxD("No sway", &Vars::Misc::NoSway);
			CheckboxD("100% EOKA", &Vars::Misc::SuperEoka);
			CheckboxD("Shot Gun No Spread", &Vars::Misc::ShotGunTochka);
			CheckboxD("JumpAiming", &Vars::Misc::JumpAiming);
			CheckboxD("Long Hand", &Vars::Misc::LongHand);
			CheckboxD("Fake admin", &Vars::Misc::FakeAdmin);
			if (ImGui::BeginCombo(" ","Crosshair"))
			{
				CheckboxD("Circle", &Vars::Visuals::CircleCrosshair);
				CheckboxD("Default", &Vars::Visuals::Crosshair);
				ImGui::EndCombo();
			}
			
			CheckboxD("Unlock aiming in heavy", &Vars::Misc::AntiKastrulya);
			CheckboxD("Always day", &Vars::Visuals::AlwaysDay);
			CheckboxD("Custom Time", &Vars::Misc::CustomTime);
			if (Vars::Misc::CustomTime) 
			{
				ImGui::SliderFloat("Time", &Vars::Misc::Time, 0.f, 12.f);
			}
			CheckboxD("NightMode", &Vars::Visuals::NightMode);
		}
		ImGui::EndChild();
		ImGui::SameLine();

		ImGui::BeginChild("Visual1", ImVec2(200, 398), true);
		{
			ImGui::Text("Colors");

			ImGui::SetColorEditOptions(ImGuiColorEditFlags_Float | ImGuiColorEditFlags_PickerHueWheel | ImGuiColorEditFlags_NoInputs);
			ImGui::ColorEdit4("Box", Vars::Color::BoxColor);
			ImGui::ColorEdit4("Skeleton", Vars::Color::SkeletonColor);
			ImGui::ColorEdit4("Name", Vars::Color::NameColor);
			ImGui::ColorEdit4("Health", Vars::Color::PlayerHeath);
			ImGui::ColorEdit4("Distance", Vars::Color::DistanceColor);
			ImGui::ColorEdit4("Weapon", Vars::Color::WeaponColor);
			ImGui::ColorEdit4("BotBox", Vars::Color::BotColor);
			ImGui::ColorEdit4("Default_Crosshair", Vars::Color::CrosshairColor);
			ImGui::ColorEdit4("CircleCrosshair", Vars::Color::CircleCrosshair);
			ImGui::ColorEdit4("AimFov", Vars::Color::Fov);
			ImGui::ColorEdit4("SilentFov", Vars::Color::SilentFovColor);
			ImGui::ColorEdit4("LinePlayer", Vars::Color::LineEsp);
			ImGui::ColorEdit4("Silent Target Line", Vars::Color::SilentColor);
			ImGui::Text("Colors Ore and Others ESP");
			ImGui::ColorEdit4("StoneEsp", Vars::Color::StoneEsp);
			ImGui::ColorEdit4("SulfurEsp", Vars::Color::SulfurEsp);
			ImGui::ColorEdit4("MetalEsp", Vars::Color::MetalEsp);
			ImGui::ColorEdit4("StashEsp", Vars::Color::StashEsp);
			ImGui::ColorEdit4("MinicopterEsp", Vars::Color::MinicopterEsp);
			ImGui::ColorEdit4("PatrulEsp", Vars::Color::PatrulEsp);
			ImGui::ColorEdit4("TrapsEsp", Vars::Color::TrapsEsp);
			ImGui::ColorEdit4("HempEsp", Vars::Color::HempEsp);
			ImGui::ColorEdit4("SupplyEsp", Vars::Color::SupplyEsp);
			ImGui::ColorEdit4("CorpseEsp", Vars::Color::CorpseEsp);
			ImGui::ColorEdit4("show_WeaponsEsp", Vars::Color::show_WeaponsEsp);

		}
		ImGui::EndChild();
		ImGui::SameLine();

	}

	ImGui::BeginChild("Radar_Active Slot", ImVec2(200, 398), true);
	{
		ImGui::Text("Radar");

		ImGui::Checkbox("Enable", &Vars::Radar::Enable);
		ImGui::Checkbox("ShowRadarBackground", &Vars::Radar::ShowRadarBackground);
		ImGui::Checkbox("ShowRadarPlayer", &Vars::Radar::ShowRadarPlayer);
		ImGui::Checkbox("ShowRadarSleeper", &Vars::Radar::ShowRadarSleeper);
		ImGui::SliderFloat("Radar_X", &Vars::Radar::Pos_X, 0.f, 2000.f);
		ImGui::SliderFloat("Radar_Y", &Vars::Radar::Pos_Y, 0.f, 1000.f);
		ImGui::SliderFloat("Radar_Size", &Vars::Radar::Radar_Size, 0.f, 250.f);
		ImGui::SliderFloat("Radar_Range", &Vars::Radar::Radar_Range, 0.f, 300.f);

		ImGui::Text("Active Slot");

		if (Checkbox(("Show Player Active Slot"), &Vars::Radar::ActiveSlot))
		{
			TextEx(("Active Slot Pos X"));
			SliderFloat(("135715"), &Vars::Radar::ActiveSlotPos_X, 0, Vars::Global::ScreenWidth - 260);
			TextEx(("Active Slot Pos Y"));
			SliderFloat(("13465634"), &Vars::Radar::ActiveSlotPos_Y, 0, Vars::Global::ScreenHigh - 170);
		}
	}
	ImGui::EndChild();
	ImGui::SameLine();

}
