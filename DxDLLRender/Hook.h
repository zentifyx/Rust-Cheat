#pragma once
#include "Ofssets.h"


class Color 
{
public:
	float r;
	float g;
	float b;
	float a;
	Color(float rr, float gg, float bb, float aa) 
	{
		r = rr;
		g = gg;
		b = bb;
		a = aa;
	}
};

typedef void(__fastcall* SendProjectileAttack_fn)(void*, void*);
SendProjectileAttack_fn Orig_SendProjectileAttack{ };

typedef void(__fastcall* SetFlying_fn)(void*, void*);
SetFlying_fn original_setflying{};

__declspec(selectany) uintptr_t TargetSilentPlayer = NULL;
__declspec(selectany) uintptr_t TargetPSilentPlayer = NULL;
__declspec(selectany) uintptr_t closestPlayer = NULL;


typedef bool(__fastcall* Can_Attack)(void*, void*);
inline Can_Attack Orig_CanAttack;

typedef float(__fastcall* GetSpeed)(float* a1, float* a2);
inline GetSpeed Orig_GetSpeed;

typedef Vector3(__fastcall* clientinput)(DWORD64, DWORD64);
inline clientinput original_clientinput;

typedef void(__fastcall* BlockSprint)(void*);
inline BlockSprint Orig_BlockSprint;

typedef void(__fastcall* HandleRunning_fn)(void* a1, void* a2, bool);
inline HandleRunning_fn orig_handleRunning;

typedef void(__fastcall* FastHeal_)(void* a1, void* a2);
inline FastHeal_ Orig_Heal;

typedef uintptr_t(__fastcall* create_projectile_fn)(void*, void*, Vector3, Vector3, Vector3);
inline create_projectile_fn original_create_projectile{ };

typedef float(__fastcall* GetIndexedSpreadScalar)(int*, int*);
inline GetIndexedSpreadScalar Orig_GetIndexedSpreadScalar{ };

typedef void(__fastcall* AntiAim)(void*);
inline AntiAim original_sendclienttick;

typedef void(__fastcall* NightMode_)(void* a1, void* a2);
inline NightMode_ original_mode;


void __fastcall NightMode(void* a1, void* a2) 
{
  if (Vars::Visuals::NightMode)
  {
    typedef void(__stdcall* F)(float);
    typedef void(__stdcall* I)(int);
    typedef void(__stdcall* C)(D2D1::ColorF);
    ((I)(GetModBase(StrW(L"GameAssembly.dll")) + oAmbientMode))(3);
    ((F)(GetModBase(StrW(L"GameAssembly.dll")) + oambientIntensit))(1.f);
    ((C)(GetModBase(StrW(L"GameAssembly.dll")) + oambientLight))(D2D1::ColorF(0.8f, 0.8f, 0.8f, 0.8f));

  }
  return  original_mode(a1, a2);
}

inline void __fastcall hook_sendclienttick(void* self)
{
	if (Vars::Misc::AntiAim)
	{
		auto input = safe_read(self + 0x4C8, uintptr_t);
		if (!input)
		{
			return original_sendclienttick(self);
		}

		auto state = safe_read(input + 0x20, uintptr_t);
		if (!state)
		{
			return original_sendclienttick(self);
		}

		auto current = safe_read(state + 0x10, uintptr_t);
		if (!current)
		{
			return original_sendclienttick(self);
		}
		safe_write(current + 0x18, Vector3(100, rand() % 999 + -999, rand() % 999 + -999), Vector3);//public Vector3 aimAngles; // 0x18
	
	}
	return original_sendclienttick(self);
}


inline uintptr_t __fastcall CreateProjectile(void* BaseProjectile, void* prefab_pathptr, Vector3 pos, Vector3 forward, Vector3 velocity) 
{
	uintptr_t projectile = original_create_projectile(BaseProjectile, prefab_pathptr, pos, forward, velocity);
	auto* TargetPlayer = reinterpret_cast<BasePlayer*>(closestPlayer);
	safe_write(projectile + 0x114, true, bool);
	if (Vars::AimBot::Fake_Dist)
	{
		safe_write(projectile + 0x130, 1337.f, float);
	}
	if (Vars::AimBot::FatBullet) {
		safe_write(projectile + 0x2C, 2.f, float);
	}
	else {
		safe_write(projectile + 0x2C, 0.1f, float);
	}
	return projectile;
}

void __fastcall Fake_handleRunning(void* a1, void* a2, bool wantsRun)
{
	if (Vars::Misc::SlideWalk)
		return orig_handleRunning(a1, a2, true);
	return orig_handleRunning(a1, a2, wantsRun);
}

inline float __fastcall Fake_GetSpeed(float* a1, float* a2)
{
	if (Vars::Misc::SpeedHack)
	{
		return Vars::Misc::SpeedValue;
	}
	return  Orig_GetSpeed(a1, a2);
}
__forceinline Vector2 CalcAngle(const Vector3& Src, const Vector3& Dst) 
{
	Vector3 dir = Src - Dst;

	return Vector2{ RAD2DEG(asin(dir.y / dir.Length())), RAD2DEG(-atan2(dir.x, -dir.z)) };
}

inline bool __fastcall Fake_Can_Attack(void* a1, void* a2)
{
	if (Vars::Misc::JumpAiming)
		return true;
	return Orig_CanAttack(a1, a2);
}

inline void __fastcall Fake_BlockSprint(void* a1)
{
	if (Vars::Misc::JumpAiming)
		return;

	return Orig_BlockSprint(a1);
}

bool IsUsing_FastHeal = true;
float Use_Last_FastHeal;

inline void __fastcall Fake_SendProjectileAttack(void* a1, void* a2) 
{
	uintptr_t PlayerAttack = safe_read((uintptr_t)a2 + 0x18, uintptr_t); // PlayerAttack playerAttack;
	uintptr_t Attack = safe_read(PlayerAttack + 0x18, uintptr_t); // public Attack attack;
	if (Vars::AimBot::EnableSilentAim)
	{
		if (TargetSilentPlayer != NULL) 
		{
			safe_write(Attack + 0x30, 698017942, uint32_t); // public uint hitBone;
			safe_write(Attack + 0x64, 16144115, uint32_t); // public uint hitPartID;
			if (Vars::AimBot::ThroughWall) 
			{
				safe_write(Attack + oHitNormalWorld, Vector3(0.f, -1000.f, 0.f) * -10000.f, Vector3);
			}
			safe_write(Attack + oHitID, safe_read(safe_read(TargetSilentPlayer + oNetworkable, uintptr_t) + oNetworkId, uint32_t), uint32_t);
		}
	}
	if (Vars::AimBot::AlwaysHeadshot) 
	{
		safe_write(Attack + 0x30, 698017942, uint32_t); // public uint hitBone;
	}
	return Orig_SendProjectileAttack(a1, a2);
}

inline float __fastcall Fake_GetIndexedSpreadScalar(int* a1, int* a2)
{
	if (Vars::Misc::ShotGunTochka)
	{
		return 0;
	}
	return  Orig_GetIndexedSpreadScalar(a1, a2);
}

void __fastcall SetFlying(void* a1, void* a2) 
{
	if(Vars::Misc::FakeAdmin)
		return;
}

inline void CreateHook(void* Function, void** Original, void* Detour, bool autoEnable = true)
{
	if (MH_Initialize() != MH_OK && MH_Initialize() != MH_ERROR_ALREADY_INITIALIZED)
	{
		std::cout << "Failed to initialize Hook" << std::endl;
		return;
	}
	MH_CreateHook(Function, Detour, Original);
	if (autoEnable)
		MH_EnableHook(Function);
}

typedef Vector3(__fastcall* aimconedirection)(float, Vector3, bool);
inline aimconedirection original_aimconedirection;

Vector3 Prediction(const Vector3& LP_Pos, BasePlayer* Player, BoneList Bone);

typedef pUncStr(__fastcall* consoleRun)(uintptr_t, pUncStr, DWORD64);
inline consoleRun original_consolerun{};

pUncStr __fastcall Run(uintptr_t options, pUncStr strCommand, DWORD64 args) {
	bool IsFromServer = safe_read(options + 0x6, bool);
	if (IsFromServer) {
		std::wstring cmd = std::wstring(strCommand->str);
		if (cmd.find(L"noclip") != std::wstring::npos || cmd.find(L"debugcamera") != std::wstring::npos || cmd.find(L"camspeed") != std::wstring::npos || cmd.find(L"admintime") != std::wstring::npos) {
			strCommand = nullptr;
		}
	}
	return original_consolerun(options, strCommand, args);
}


Vector3 __fastcall pSilent(float aimCone, Vector3 inputVec, bool anywhereInside = true) // wanna hang myself
{ 
	auto* TargetPlayer = reinterpret_cast<BasePlayer*>(TargetPSilentPlayer);
	Vector3 dir = (Prediction(LocalPlayer.BasePlayer->GetBoneByID(head), TargetPlayer, head) - LocalPlayer.BasePlayer->GetBoneByID(head)).Normalized();
	if (Vars::AimBot::pSilent) {
		if (!(TargetPlayer->GetBoneByID(spine1).x == 0 && TargetPlayer->GetBoneByID(spine1).y == 0 && TargetPlayer->GetBoneByID(spine1).z == 0)) {
			return original_aimconedirection(0.f, dir, anywhereInside);
		}
		else {
			return original_aimconedirection(aimCone, inputVec, anywhereInside);
		}
	}
	else return original_aimconedirection(aimCone, inputVec, anywhereInside);
}

void __fastcall ClientInput(DWORD64 baseplayah, DWORD64 ModelState) 
{
	typedef void(__stdcall* ClientInput)(DWORD64, DWORD64);
	((ClientInput)original_clientinput)(baseplayah, ModelState);
	if (Vars::Misc::Flyhack)
		LocalPlayer.BasePlayer->AddFlag(32);
	if (Vars::Misc::SilentWalk)
		LocalPlayer.BasePlayer->SetRemoveFlag(4);
}

inline void InitHook()
{
	if (MH_Initialize() != MH_OK && MH_Initialize() != MH_ERROR_ALREADY_INITIALIZED)
	{
		std::cout << "Failed to initialize Hook" << std::endl;
		return;
	}

	CreateHook(reinterpret_cast<void*>(static_cast<uintptr_t>(GetModBase(L"GameAssembly.dll") + 0x1B88400)), reinterpret_cast<void**>(&original_consolerun), Run);//&public static string Run(ConsoleSystem.Option options, string strCommand, object[] args) { }
	CreateHook(reinterpret_cast<void*>(static_cast<uintptr_t>(GetModBase(L"GameAssembly.dll") + 0x58A450)), reinterpret_cast<void**>(&original_create_projectile), CreateProjectile);// private Projectile CreateProjectile(string prefabPath, Vector3 pos, Vector3 forward, Vector3 velocity) { }
	CreateHook(reinterpret_cast<void*>(static_cast<uintptr_t>(GetModBase(L"GameAssembly.dll") + oTodSky)), reinterpret_cast<void**>(&original_mode), NightMode);
	CreateHook(reinterpret_cast<void*>(static_cast<uintptr_t>(GetModBase(L"GameAssembly.dll") + oClientInput)), reinterpret_cast<void**>(&original_clientinput), ClientInput);
	CreateHook(reinterpret_cast<void*>(static_cast<uintptr_t>(GetModBase(L"GameAssembly.dll") + oAimConeUtil)), reinterpret_cast<void**>(&original_aimconedirection), pSilent);
	CreateHook(reinterpret_cast<void*>(static_cast<uintptr_t>(GetModBase(L"GameAssembly.dll") + oSetFlying)), reinterpret_cast<void**>(&original_setflying), SetFlying);
	CreateHook(reinterpret_cast<void*>(static_cast<uintptr_t>(GetModBase(L"GameAssembly.dll") + oSendProjectileAttack)), reinterpret_cast<void**>(&Orig_SendProjectileAttack), Fake_SendProjectileAttack);
	CreateHook(reinterpret_cast<void*>(static_cast<uintptr_t>(GetModBase(L"GameAssembly.dll") + oCanAttack)), reinterpret_cast<void**>(&Orig_CanAttack), Fake_Can_Attack);
	CreateHook(reinterpret_cast<void*>(static_cast<uintptr_t>(GetModBase(L"GameAssembly.dll") + oBlockSprint)), reinterpret_cast<void**>(&Orig_BlockSprint), Fake_BlockSprint);
	CreateHook(reinterpret_cast<void*>(static_cast<uintptr_t>(GetModBase(L"GameAssembly.dll") + oGetSpeed)), reinterpret_cast<void**>(&Orig_GetSpeed), Fake_GetSpeed);
	CreateHook(reinterpret_cast<void*>(static_cast<uintptr_t>(GetModBase(L"GameAssembly.dll") + oGetIndexedSpreadScalar)), reinterpret_cast<void**>(&Orig_GetIndexedSpreadScalar), Fake_GetIndexedSpreadScalar);
	CreateHook(reinterpret_cast<void*>(static_cast<uintptr_t>(GetModBase(L"GameAssembly.dll") + oSlideWalk)), reinterpret_cast<void**>(&orig_handleRunning), Fake_handleRunning);
	CreateHook(reinterpret_cast<void*>(static_cast<uintptr_t>(GetModBase(L"GameAssembly.dll") + oAntiAim)), reinterpret_cast<void**>(&original_sendclienttick), hook_sendclienttick);

}
