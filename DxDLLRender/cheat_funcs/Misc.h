void Misc()
{
	if (Vars::Misc::HighJump) {
		if (FC(user32, GetAsyncKeyState, Vars::Misc::highkey))
			LocalPlayer.BasePlayer->SetGravity(Vars::Misc::JumpValue);
		else LocalPlayer.BasePlayer->SetGravity(3.0f);
	}

	//air stuck
	if (Vars::Misc::AirStuck) {
		if (FC(user32, GetAsyncKeyState, VK_XBUTTON1))
			LocalPlayer.BasePlayer->AirStuck(true);
		else LocalPlayer.BasePlayer->AirStuck(false);
	}

	if (Vars::Misc::CustomFov)
		LocalPlayer.BasePlayer->SetFov();

	//boost speed on water
	if (Vars::Misc::WaterBoost)
		LocalPlayer.BasePlayer->WaterBoost();

	//on aim on kastrulya
	if (Vars::Misc::AntiKastrulya)
		LocalPlayer.BasePlayer->NoBlockAiming();

	//boost speed on heavy armor
	if (Vars::Misc::NoHeavyReduct)
		LocalPlayer.BasePlayer->NoHeavyReduct();

	//spider man
	if (Vars::Misc::SpiderMan)
		LocalPlayer.BasePlayer->SpiderMan();

	if (Vars::Misc::InfinityJump)
		if (FC(user32, GetAsyncKeyState, VK_SPACE))
		LocalPlayer.BasePlayer->InfinityJump();
	//remove weapon sway
	if (Vars::Misc::NoSway)
		LocalPlayer.BasePlayer->NoSway();
	if (Vars::Misc::FakeAdmin)
		LocalPlayer.BasePlayer->FakeAdmin(4);

	if (Vars::Misc::WalkOnWater && GetAsyncKeyState(Vars::Misc::walkkey))
		LocalPlayer.BasePlayer->WalkWater();

	if (Vars::Visuals::NightMode) {
		LocalPlayer.BasePlayer->Pizda228();
		return;
	}
}
