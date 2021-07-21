
uintptr_t closestHeli;
namespace Vars
{
	namespace Tabs
	{
		bool Aim, Silent, ESP, BOTESP, OtherESP, Player, Weapon, Color, Config = false;
		bool Preview = false;
	}
	namespace Global
	{
		
		Vector2 MenuPos = { 0, 0 };
		bool Panic = false;
		float ScreenHigh = 0;
		float ScreenWidth = 0;
		HWND hWindow = nullptr;
		bool MenuVisible = false;
		WNDPROC oWindproc = nullptr;

		Vector3 LastPos = { 0.f, 0.f, 0.f };
		ULONGLONG LastTime = 0;
		DWORD64 LastSteamID = 0;
		const wchar_t* LastName;
		Vector3 PlayerVeloc = { 0.f, 0.f, 0.f };

		int BoneToAim = 1;
		float BulletSpeed = 250.f;
		DWORD64 PresentDelta = 0;
		float CorX = 0.f;
		float CorY = 0.f;
		char ConfigName[0x100] = "Config";
	}
	namespace Test
	{

	}
	namespace Storage
	{
		__declspec(selectany) uintptr_t gBase = (DWORD64)GetModuleHandleA("GameAssembly.dll");
		
	}
	namespace AimBot
	{
		
		bool pSilent = false;
		bool PSilentTarget = false;
		bool DrawPSilentFov = false;
		
		float PSilentFov = 100.f;
		float LimitDist = 300.f;
		bool PSilentClear = false;
		int Psilentclearkey = 0;
		
		bool FatBullet = false;//Set_Psilent
		bool Fake_Dist = false;
		float distancefake = 500.f;
		bool Activate = false;
		bool BodyAim = false;
		bool RCS = false;
		bool Standalone = false;
		bool VisibleCheck = false;
		bool DrawFov = false;
		
		float Range = 400.f;
		float Fov = 100.f;

		int aimkey = 0;
		static int keystatus = 0;
		bool toggleaim = false;
		bool SilentBody = false;
		bool EnableSilentAim = false;
		bool AlwaysHeadshot = false;
		bool ThroughWall = false;
		bool DrawSilentFov = false;
		bool SilentTarget = false;
		float SilentDist = 500.f;
		float SilentFov = 100.f;
		bool SilentIgnoreBot = false;
		bool SilentIgnoreSleep = false;
		bool SilentIgnoreWounded = false;
		bool SilentClear = false;
		int silentclearkey = 0;

		int firekey = 0;
		bool Trigger = false;
		bool DrawTriggerFov = true;
		float TriggerFov = 10;
		bool toggleauto = false;
		int autokey = 0;

	}

	namespace Visuals
	{
		bool FillBox = false;
		bool ShowPlayerBox = false;
		bool ShowPlayerName = false;
		bool ShowPlayerHealth = false;
		bool ShowPlayerWeapon = false;
		bool ShowPlayerDist = false;
		//bool CSnapLines = false;
		bool AlwaysDay = false;
		bool NightMode = false;
		bool IgnoreSleepers = false;
		bool SkeletonPlayer = false;
		bool SkeletonBots = false;
		bool Crosshair = false;
		bool CircleCrosshair = false;
		namespace Preview
		{
			bool Box, Health, Name, Weapon, Dist = false;
		}
		bool TargetLine = false;
		bool PlayerESP = false;
		bool BotsESP = false;
	}

	namespace Misc
	{
		bool AdminTools = false;
		bool MeleeAimPlayers = false;
		bool MeleeAutoFarm = false;
		bool Door = false;
		bool AutoPickUp = false;
		bool FastHeal = false;
		bool FakeLag = false;
		bool AntiAim = false;
		bool SlideWalk = false;
		bool SilentWalk = false;
		bool Flyhack = false;
		bool ShotGunTochka = false;
		bool CustomTime = false;
		float Time = 1.0f;
		bool CustomFov = false; //Camera
		float GraphicsFov = 90.f;
		float pred = 0.f;
		bool SpiderMan = false;
		bool InfinityJump = false;
		bool AntiSpread = false;
		bool NoRecoil = false;
		bool FastReload = false;
		bool Automatic = false;
		bool SuperEoka = false;
		bool SkinChanger = false;
		bool BuildAsUWant = false;
		int buildkey = 0;
		bool NoSway = false;
		bool SuperBow = false;
		bool FakeAdmin = false; //need
		bool NoGreenZone = false;
		bool LongHand = false;
		bool FatHand = false;
		bool RunOnHit = false;
		bool HighJump = false;
		bool SpeedHack = false;
		float SpeedValue = 5;
		bool JumpAiming = false;
		int highkey = 0;
		////////////////////////////
		bool WalkOnWater = false;
		int walkkey = 0;
		///////////////////////////
		float JumpValue = 1.0f;
		bool WaterBoost = false;
		bool NoFall = false;
		bool AirStuck = false;
		bool AntiKastrulya = false;
		bool NoHeavyReduct = false;
		//meme dot
		bool Crosshair = false;


	}

	namespace HvH
	{
		float Tick = 2.3f;
		float Tick2 = 2.3f;
		float FOV = 0.5f;
	}

	namespace Visuals
	{
		bool ore = false;
		bool EnableBoxResourses = false;
		bool Sulphur = false;
		float SulphurOreDistation = 100.f;
		bool Metal = false;
		float MetalOreDistation = 100.f;
		bool Stone = false;
		float StoneOreDistation = 100.f;
		bool Stash = false;
		float StashDistation = 100.f;
		bool Minicopter = false;
		float MinicopterDistation = 100.f;
		bool Patrul = false;
		float PatrulDistation = 100.f;
		bool Traps = false;
		float TrapsDistation = 100.f;
		bool Hemp = false;
		float HempDistation = 100.f;
		bool Supply = false;
		float SupplyDistation = 100.f;
		bool Corpse = false;
		float CorpseDistation = 100.f;
		bool Crate = false;
		float CrateDistation = 100.f;
		
		
		//
		bool show_Weapons = false;
		float show_WeaponsDistation = 100.f;

	}

	namespace WorckbeanchEsp
	{
		bool Activate = false;
		bool workbench1 = false;
		bool workbench2 = false;
		bool workbench3 = false;
	}

	namespace Drop
	{
		bool Activate = false;
		bool supply_drop = false;
		bool WoodBox_bacpack = false;
		bool closestPlayer = false;
		bool inventoryESP = false;
	}

	namespace PicUpEsp
	{
		bool Activate = false;
		bool StonePicUp = false;
		bool MetalPicUp = false;
		bool SulfurPicUp = false;
		bool WoodPicUp = false;
		bool hempEsp = false;
	}

	namespace Color {
		float CSnapColor[] = { 255.f,255.f,255.f,255.f };
		
		float Fov[] = { 255.f, 255.f, 255.f };
		float SilentFovColor[] = { 0.f, 0.f, 0.f };
		float TriggerFovColor[] = { 0.f, 0.f, 0.f };

		
		/// <summary>
		float StoneEsp[] = { 255.f, 0.f, 0.f };
		float SulfurEsp[] = { 255.f, 0.f, 0.f };
		float MetalEsp[] = { 255.f, 0.f, 0.f };
		float StashEsp[] = { 255.f, 0.f, 0.f };
		float MinicopterEsp[] = { 255.f, 0.f, 0.f };
		float PatrulEsp[] = { 255.f, 0.f, 0.f };
		float TrapsEsp[] = { 255.f, 0.f, 0.f };
		float HempEsp[] = { 255.f, 0.f, 0.f };
		float SupplyEsp[] = { 255.f, 0.f, 0.f };
		float CorpseEsp[] = { 255.f, 0.f, 0.f };
		float CrateEsp[] = { 255.f, 0.f, 0.f };
		float show_WeaponsEsp[] = { 255.f, 0.f, 0.f };
		/// </summary>
		float SkeletonColor[] = { 255.f, 0.f, 0.f };
		float LineEsp[] = { 255.f, 0.f, 0.f };
		float BoxColor[] = { 255.f, 0.f, 0.f };
		float NameColor[] = { 255.f, 0.f, 0.f };
		float PlayerHeath[] = { 255.f, 0.f, 0.f };
		float DistanceColor[] = { 255.f, 0.f, 0.f };
		float WeaponColor[] = { 255.f, 0.f, 0.f };
		float CircleCrosshair[] = { 255.f,255.f,255.f,255.f };
		float CrosshairColor[] = { 0.f, 255.f, 0.f };
		
			float BotColor[] = { 255, 0, 255 };
		float SilentColor[] = { 255, 255, 0 };
		float ColorPreview[] = { 25, 30, 35 };
		float Steep[] = { 255, 0, 255 };
	}

	namespace Radar
	{
		float ActiveSlotPos_X = 0.f;
		float ActiveSlotPos_Y = 0.f;
		bool ActiveSlot = false;
		bool Enable = false;
		bool ShowRadarBackground = false;
		bool ShowRadarPlayer = false;
		bool ShowRadarSleeper = false;
		bool ShowRadarStoneOre = false;
		bool ShowRadarMettalOre = false;
		bool ShowRadarSulfureOre = false;
		float Pos_X = 0;
		float Pos_Y = 0;
		float Radar_Size = 250.f;
		float Radar_Range = 300.f;
		bool EnableDinamicRadar = false;
	}

	namespace RadarColor
	{
		static float RadarBackground[] = { 0,0,0,1, 0.5f };
		static float RadarPlayerColor[] = { 1,0,0,1 };
		static float RadarPlayerSleeperColor[] = { 0,0,1,1 };
		static float RadarStoneOreColor[] = { 0.487,0.487,0.487,1 };
		static float RadarMettalOreColor[] = { 0.162,0.178,0.440,1 };
		static float RadarSulfureOreColor[] = { 0.392,0.353,0.84,1 };
	}

	namespace Config {
		static char configname[128] = "My";
		bool LoadConfig = false;
		bool SaveConfig = false;
		bool InitConfig = false;
	}
}
