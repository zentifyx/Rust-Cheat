bool mfound = false;
void ESP(BasePlayer* BP, BasePlayer* LP);
inline void RadarPlayer(BasePlayer* player);
void RenderActiveSlot(BasePlayer* player, float Pos_x, float Pos_Y);
BasePlayer* Player;
D3DCOLOR FLOAT4TOD3DCOLOR(float Col[]);
void FindMatrix() {
	static DWORD64 dwGameObjectManager = 0;
	if (!dwGameObjectManager)
		dwGameObjectManager = RVA(FindPattern((PBYTE)"\x48\x8B\x15\x00\x00\x00\x00\x66\x39", "xxx????xx", L"UnityPlayer.dll"), 7);

	DWORD64 ObjMgr = safe_read(dwGameObjectManager, DWORD64);
	if (!ObjMgr) return;
	UINT64 end = safe_read(ObjMgr, UINT64);
	for (UINT64 Obj = safe_read(ObjMgr + 0x8, UINT64); (Obj && (Obj != end)); Obj = safe_read(Obj + 0x8, UINT64))
	{
		UINT64 GameObject = safe_read(Obj + 0x10, UINT64);
		WORD Tag = safe_read(GameObject + 0x54, WORD);
		if (Tag == 5)
		{
			UINT64 ObjClass = safe_read(GameObject + 0x30, UINT64);
			UINT64	Entity = safe_read(ObjClass + 0x18, UINT64);
			LocalPlayer.pViewMatrix = (Matrix4x4*)(Entity + 0x2E4);// 0xDC
			mfound = true;
			return;
		}
	}
}

void PickupItem(DWORD64 item)
{
	typedef void(__stdcall* Pick)(DWORD64, Str);
	return ((Pick)(GetModBase(L"GameAssembly.dll") + oServerRPC))(item, Str(L"Pickup"));
}
int dlastKnock;
int dlastOpen;
void EbynMozga(DWORD64 Door) {
	typedef void(__stdcall* Daun)(DWORD64, BasePlayer*);
	float time = LocalPlayer.BasePlayer->GetTickTime();
	if (time > dlastKnock + 1.f)
	{	
		//0x493CC0
		((Daun)(GetModBase(L"GameAssembly.dll") + oKnockDoor))(Door, LocalPlayer.BasePlayer);
		dlastKnock = time;
	}

	if (time > dlastOpen + 1.f) 
	{
		//0x493D40
		((Daun)(GetModBase(L"GameAssembly.dll") + oKnockDoor))(Door, LocalPlayer.BasePlayer);
		dlastOpen = time;
	}

}

inline void FakeLag()
{
	if (Vars::Misc::FakeLag)
	{
		safe_write(reinterpret_cast<uintptr_t>(LocalPlayer.BasePlayer) + oClientTickInterval, 0.4f, float);
	}
	else
	{
		safe_write(reinterpret_cast<uintptr_t>(LocalPlayer.BasePlayer) + oClientTickInterval, 0.05f, float);
	}
}

class AimResult 
{
public:
	bool valid;
	BasePlayer* entity;
	Vector3 pos;
	float dist = 10000.f;
	float realdist = 0.f;
	float fov = 10000.f;

	bool operator<(const AimResult& b) 
	{
		if (fov == 10000.f) {
			return this->dist < b.dist;
		}
		else{
			return this->fov < b.fov;
		}
	}

	AimResult() {
		this->valid = false;
		this->fov = 10000.f;
	}
	AimResult(Vector3 target) 
	{
		this->valid = false;
		this->pos = target;
	}
};

float CurFOV;
BasePlayer* SilentTargetedPlayer = 0;

AimResult TargetMeleeTest(BasePlayer* Player, DWORD64 melee) 
{
	AimResult res = AimResult();
	if (!Player || !Player->IsValid()) return res;

	if (Player->IsWounded()) return res;
	
	typedef Vector3(__stdcall* CPoint)(BasePlayer*, Vector3);

	Vector3 prepos = Player->GetBoneByID(BoneList::head);
	Vector3 lppos = LocalPlayer.BasePlayer->GetBoneByID(head);
	if (!res.valid) return res;
}

void Entity()
{
	bool LP_isValid = true;
	float FOV = 1000000.f;
	BasePlayer* AimEntity = 0;
	BasePlayer* TargetAimBotPlayer = nullptr;
	BasePlayer* AimEntity2 = 0;

	if (!LocalPlayer.pViewMatrix || !mfound)
	{
		FindMatrix();
	}

	DWORD64 BaseNetworkable;
	BaseNetworkable = safe_read(GetModBase(StrW(L"GameAssembly.dll")) + oBaseNetworkable, DWORD64);
	DWORD64 EntityRealm = safe_read(BaseNetworkable + 0xB8, DWORD64);
	DWORD64 ClientEntities = safe_read(EntityRealm, DWORD64);
	DWORD64 ClientEntities_list = safe_read(ClientEntities + 0x10, DWORD64);
	DWORD64 ClientEntities_values = safe_read(ClientEntities_list + 0x28, DWORD64);
	if (!ClientEntities_values) return;
	int EntityCount = safe_read(ClientEntities_values + 0x10, int);
	DWORD64 EntityBuffer = safe_read(ClientEntities_values + 0x18, DWORD64);

	for (int i = 0; i <= EntityCount; i++)
	{
		DWORD64 Entity = safe_read(EntityBuffer + 0x20 + (i * 0x8), DWORD64);
		if (Entity <= 100000) continue;
		DWORD64 Object = safe_read(Entity + 0x10, DWORD64); //BaseObject
		if (Object <= 100000) continue;
		DWORD64 ObjectClass = safe_read(Object + 0x30, DWORD64); //Object
		//
		WORD tag = safe_read(ObjectClass + 0x54, WORD);
		uintptr_t localElement = safe_read(EntityBuffer + 0x20, uintptr_t);
		//
		if (ObjectClass <= 100000) continue;
		pUncStr name = safe_read(ObjectClass + 0x60, pUncStr);
		uintptr_t BaseObject = safe_read(ObjectClass + 0x30, uintptr_t);
		uintptr_t BaseEntity = safe_read(BaseObject + 0x18, uintptr_t);
		uintptr_t BaseHelicopter = safe_read(BaseEntity + 0x28, uintptr_t);
		if (!name) continue;
		char* buff = name->stub;
		BasePlayer* Player = (BasePlayer*)safe_read(Object + 0x28, DWORD64);
		if (strstr(buff, StrA("Local"))) {
			Player = (BasePlayer*)safe_read(Object + 0x28, DWORD64);
			if (!safe_read(Player + 0x4A8, DWORD64)) continue; 
			if (Player != LocalPlayer.BasePlayer ) 
            {
				
				mfound = false;
			}
			
			LocalPlayer.BasePlayer = Player;
			LP_isValid = true;
			

		}

		if (strstr(buff, "player.prefab") || (strstr(buff, "scientist")) && (!strstr(buff, "prop") && !strstr(buff, "corpse")))
		{
			BasePlayer* Player = (BasePlayer*)safe_read(Object + 0x28, DWORD64); //public ulong playerID;
			if (!safe_read(Player + 0x4A8, DWORD64)) continue;
			if (!Player->IsValid()) continue;
			bool ex = false;
			RadarPlayer(Player);
			//printf("Esp on %lld\n", Player->GetSteamID());
			ESP(Player, LocalPlayer.BasePlayer);

			if (Vars::Radar::ActiveSlot && GetFov(Player, head) <= 150)
				RenderActiveSlot(Player, Vars::Radar::ActiveSlotPos_X, Vars::Radar::ActiveSlotPos_Y);

			if (Vars::Visuals::IgnoreSleepers && Player->HasFlags(16)) continue;

			
			if (ex) continue;
			//cut distance
			if (Math::Calc3D_Dist(LocalPlayer.BasePlayer->GetBoneByID(head), Player->GetBoneByID(head)) > Vars::AimBot::Range)
				continue;

			//calc visible & low fov
			if (Player->IsVisible() && (FOV > (CurFOV = GetFov(Player, BoneList(Vars::Global::BoneToAim))))) 
			{
				if (CurFOV <= Vars::AimBot::Fov) 
				{
					FOV = CurFOV; AimEntity = Player;
				}
				if (CurFOV <= Vars::AimBot::SilentFov) 
				{
					TargetSilentPlayer = (uintptr_t)Player;
				}
				if (CurFOV <= Vars::AimBot::PSilentFov) 
				{
					TargetPSilentPlayer = (uintptr_t)Player;
				}
			}
		}
		DWORD64 ent = safe_read(Object + 0x28, UINT64);

		auto* weapon_ = LocalPlayer.BasePlayer->GetActiveWeapon();
		char* classname = weapon_->ClassName();
		bool weaponmelee = weapon_ && classname && (m_strcmp(classname, "BaseMelee") || m_strcmp(classname, "Jackhammer"));
		DWORD64 active = safe_read(weapon_ + oHeldEntity, DWORD64);
		
		if (Vars::Misc::Door && m_strstr((char*)safe_read(safe_read(ent, DWORD64) + 0x10, DWORD64), "Door")) 
		{
			UINT64 gameObject = safe_read(ObjectClass + 0x30, UINT64);
			UINT64 Trans = safe_read(gameObject + 0x8, UINT64);
			UINT64 Vec = safe_read(Trans + 0x38, UINT64);
			Vector3 pos = safe_read(Vec + 0x90, Vector3);
			typedef Vector3(__stdcall* CPoint)(BasePlayer*, Vector3);
			Vector3 local = ((CPoint)(GetModBase(L"GameAssembly.dll") + oClosestPoint))(LocalPlayer.BasePlayer, pos);
			if (ent && Math::Calc3D_Dist(local, pos) < 3.f) 
			{
				EbynMozga(ent);
			}
		}

		if (Vars::Misc::AutoPickUp && m_strstr(buff, "/collectable/")) 
		{
			UINT64 gameObject = safe_read(ObjectClass + 0x30, UINT64);
			UINT64 Trans = safe_read(gameObject + 0x8, UINT64);
			UINT64 Vec = safe_read(Trans + 0x38, UINT64);
			Vector3 pos = safe_read(Vec + 0x90, Vector3);
			typedef Vector3(__stdcall* CPoint)(BasePlayer*, Vector3);
			Vector3 local = ((CPoint)(GetModBase(L"GameAssembly.dll") + oClosestPoint))(LocalPlayer.BasePlayer, pos);
			if (Math::Calc3D_Dist(local, pos) < 5.f) 
			{
				PickupItem(ent);
			}
		}

		if (Vars::Visuals::Stone && strstr(buff, "stone-ore.prefab"))
		{
			DWORD64 Res = safe_read(Object + 0x28, DWORD64);
			DWORD64 gameObject = safe_read(ObjectClass + 0x30, DWORD64); //Tag 449
			DWORD64 Trans = safe_read(gameObject + 0x8, DWORD64);
			DWORD64 Vec = safe_read(Trans + 0x38, DWORD64);
			Vector3 pos = safe_read(Vec + 0x90, Vector3);
			Vector2 Pos;

			if (LocalPlayer.WorldToScreen(pos, Pos))
			{
				int distation = (int)Math::Calc3D_Dist(LocalPlayer.BasePlayer->GetBoneByID(head), pos);
				wchar_t text[0x100];
				
				_swprintf(text, L"Stone-Ore [%d m]", distation);
				if (distation <= Vars::Visuals::StoneOreDistation)
				GUI::Render.String(Pos, text, FLOAT4TOD3DCOLOR(Vars::Color::StoneEsp));


			}
		}

		if (Vars::Visuals::Sulphur && strstr(buff, "sulfur-ore.prefab")) 
		{
			DWORD64 Res = safe_read(Object + 0x28, DWORD64);
			DWORD64 gameObject = safe_read(ObjectClass + 0x30, DWORD64); //Tag 449
			DWORD64 Trans = safe_read(gameObject + 0x8, DWORD64);
			DWORD64 Vec = safe_read(Trans + 0x38, DWORD64);
			Vector3 pos = safe_read(Vec + 0x90, Vector3);
			Vector2 Pos;
			if (LocalPlayer.WorldToScreen(pos, Pos)) {
				int distation = (int)Math::Calc3D_Dist(LocalPlayer.BasePlayer->GetBoneByID(head), pos);
				wchar_t text[0x100];

				_swprintf(text, L"Sulfur ore [%d m]", distation);
				if (distation <= Vars::Visuals::SulphurOreDistation)
				GUI::Render.String(Pos, text, FLOAT4TOD3DCOLOR(Vars::Color::SulfurEsp));
			}
		}

		if (Vars::Visuals::Metal && strstr(buff, "metal-ore.prefab"))
		{
			DWORD64 Res = safe_read(Object + 0x28, DWORD64);
			DWORD64 gameObject = safe_read(ObjectClass + 0x30, DWORD64); //Tag 449
			DWORD64 Trans = safe_read(gameObject + 0x8, DWORD64);
			DWORD64 Vec = safe_read(Trans + 0x38, DWORD64);
			Vector3 pos = safe_read(Vec + 0x90, Vector3);
			Vector2 Pos;
			if (LocalPlayer.WorldToScreen(pos, Pos)) {
				int distation = (int)Math::Calc3D_Dist(LocalPlayer.BasePlayer->GetBoneByID(head), pos);
				wchar_t text[0x100];
				
				_swprintf(text, L"Metal ore [%d m]", distation);
				if (distation <= Vars::Visuals::MetalOreDistation)
				GUI::Render.String(Pos, text, FLOAT4TOD3DCOLOR(Vars::Color::MetalEsp));
			}
		}

		if (Vars::Visuals::Stash && strstr(buff, "small_stash_deployed.prefab")) 
		{
			DWORD64 Res = safe_read(Object + 0x28, DWORD64);
			DWORD64 gameObject = safe_read(ObjectClass + 0x30, DWORD64); //Tag 449
			DWORD64 Trans = safe_read(gameObject + 0x8, DWORD64);
			DWORD64 Vec = safe_read(Trans + 0x38, DWORD64);
			Vector3 pos = safe_read(Vec + 0x90, Vector3);
			Vector2 Pos;
			if (LocalPlayer.WorldToScreen(pos, Pos))
			{
				int distation = (int)Math::Calc3D_Dist(LocalPlayer.BasePlayer->GetBoneByID(head), pos);
				wchar_t text[0x100];
				
				_swprintf(text, L"Stash [%d m]", distation);
				if (distation <= Vars::Visuals::StashDistation)
				GUI::Render.String(Pos, text, FLOAT4TOD3DCOLOR(Vars::Color::StashEsp));
			}
		}

		if (Vars::Visuals::Minicopter && strstr(buff, "minicopter.entity.prefab"))
		{
			DWORD64 Res = safe_read(Object + 0x28, DWORD64);
			DWORD64 gameObject = safe_read(ObjectClass + 0x30, DWORD64); //Tag 449
			DWORD64 Trans = safe_read(gameObject + 0x8, DWORD64);
			DWORD64 Vec = safe_read(Trans + 0x38, DWORD64);
			Vector3 pos = safe_read(Vec + 0x90, Vector3);
			Vector2 Pos;
			if (LocalPlayer.WorldToScreen(pos, Pos)) 
			{
				int distation = (int)Math::Calc3D_Dist(LocalPlayer.BasePlayer->GetBoneByID(head), pos);
				wchar_t text[0x100];
				
				_swprintf(text, L"minicopter [%d m]", distation);
				if (distation <= Vars::Visuals::MinicopterDistation)
				GUI::Render.String(Pos, text, FLOAT4TOD3DCOLOR(Vars::Color::MinicopterEsp));
			}
		}
		if (Vars::Visuals::Patrul && strstr(buff, "patrolhelicopter.prefab")) 
		{
			DWORD64 Res = safe_read(Object + 0x28, DWORD64);
			DWORD64 gameObject = safe_read(ObjectClass + 0x30, DWORD64); //Tag 449
			DWORD64 Trans = safe_read(gameObject + 0x8, DWORD64);
			DWORD64 Vec = safe_read(Trans + 0x38, DWORD64);
			Vector3 pos = safe_read(Vec + 0x90, Vector3);
			Vector2 Pos;
			if (LocalPlayer.WorldToScreen(pos, Pos))
			{
				int distation = (int)Math::Calc3D_Dist(LocalPlayer.BasePlayer->GetBoneByID(head), pos);
				wchar_t text[0x100];
				
				_swprintf(text, L"Patrul [%d m]", distation);
				if (distation <= Vars::Visuals::PatrulDistation)
				GUI::Render.String(Pos, text, FLOAT4TOD3DCOLOR(Vars::Color::PatrulEsp));
			}
		}
		
		if (Vars::Visuals::Traps && strstr(buff, "guntrap.deployed.prefab")) 
		{
			DWORD64 Res = safe_read(Object + 0x28, DWORD64);
			DWORD64 gameObject = safe_read(ObjectClass + 0x30, DWORD64); //Tag 449
			DWORD64 Trans = safe_read(gameObject + 0x8, DWORD64);
			DWORD64 Vec = safe_read(Trans + 0x38, DWORD64);
			Vector3 pos = safe_read(Vec + 0x90, Vector3);
			Vector2 Pos;
			if (LocalPlayer.WorldToScreen(pos, Pos)) 
			{
				int distation = (int)Math::Calc3D_Dist(LocalPlayer.BasePlayer->GetBoneByID(head), pos);
				wchar_t text[0x100];
				
				_swprintf(text, L"ShGun Trap [%d m]", distation);
				if (distation <= Vars::Visuals::TrapsDistation)
				GUI::Render.String(Pos, text, FLOAT4TOD3DCOLOR(Vars::Color::TrapsEsp));
			}
		}
		if (Vars::Visuals::Traps && strstr(buff, "flameturret.deployed.prefab")) 
		{
			DWORD64 Res = safe_read(Object + 0x28, DWORD64);
			DWORD64 gameObject = safe_read(ObjectClass + 0x30, DWORD64); //Tag 449
			DWORD64 Trans = safe_read(gameObject + 0x8, DWORD64);
			DWORD64 Vec = safe_read(Trans + 0x38, DWORD64);
			Vector3 pos = safe_read(Vec + 0x90, Vector3);
			Vector2 Pos;
			if (LocalPlayer.WorldToScreen(pos, Pos)) 
			{
				int distation = (int)Math::Calc3D_Dist(LocalPlayer.BasePlayer->GetBoneByID(head), pos);
				wchar_t text[0x100];
				
				_swprintf(text, L"Flameturret [%d m]", distation);
				if (distation <= Vars::Visuals::TrapsDistation)
				GUI::Render.String(Pos, text, FLOAT4TOD3DCOLOR(Vars::Color::TrapsEsp));
			}
		}
		if (Vars::Visuals::Traps && strstr(buff, "autoturret_deployed.prefab")) 
		{
			DWORD64 Res = safe_read(Object + 0x28, DWORD64);
			DWORD64 gameObject = safe_read(ObjectClass + 0x30, DWORD64); //Tag 449
			DWORD64 Trans = safe_read(gameObject + 0x8, DWORD64);
			DWORD64 Vec = safe_read(Trans + 0x38, DWORD64);
			Vector3 pos = safe_read(Vec + 0x90, Vector3);
			Vector2 Pos;
			if (LocalPlayer.WorldToScreen(pos, Pos)) {
				int distation = (int)Math::Calc3D_Dist(LocalPlayer.BasePlayer->GetBoneByID(head), pos);
				wchar_t text[0x100];
				
				_swprintf(text, L"Autoturret [%d m]", distation);
				if (distation <= Vars::Visuals::TrapsDistation)
				GUI::Render.String(Pos, text, FLOAT4TOD3DCOLOR(Vars::Color::TrapsEsp));
			}
		}
		if (Vars::Visuals::Traps && strstr(buff, "sam_site_turret_deployed.prefab")) 
		{
			DWORD64 Res = safe_read(Object + 0x28, DWORD64);
			DWORD64 gameObject = safe_read(ObjectClass + 0x30, DWORD64); //Tag 449
			DWORD64 Trans = safe_read(gameObject + 0x8, DWORD64);
			DWORD64 Vec = safe_read(Trans + 0x38, DWORD64);
			Vector3 pos = safe_read(Vec + 0x90, Vector3);
			Vector2 Pos;
			if (LocalPlayer.WorldToScreen(pos, Pos))
			{
				int distation = (int)Math::Calc3D_Dist(LocalPlayer.BasePlayer->GetBoneByID(head), pos);
				wchar_t text[0x100];
				
				_swprintf(text, L"Land-Air Turret [%d m]", distation);
				if (distation <= Vars::Visuals::TrapsDistation)
				GUI::Render.String(Pos, text, FLOAT4TOD3DCOLOR(Vars::Color::TrapsEsp));
			}
		}

		if (Vars::Visuals::Hemp && strstr(buff, "hemp-collectable.prefab")) 
		{
			DWORD64 Res = safe_read(Object + 0x28, DWORD64);
			DWORD64 gameObject = safe_read(ObjectClass + 0x30, DWORD64); //Tag 449
			DWORD64 Trans = safe_read(gameObject + 0x8, DWORD64);
			DWORD64 Vec = safe_read(Trans + 0x38, DWORD64);
			Vector3 pos = safe_read(Vec + 0x90, Vector3);
			Vector2 Pos;
			if (LocalPlayer.WorldToScreen(pos, Pos)) 
			{
				int distation = (int)Math::Calc3D_Dist(LocalPlayer.BasePlayer->GetBoneByID(head), pos);
				wchar_t text[0x100];
				
				_swprintf(text, L"Hemp [%d m]", distation);
				if (distation <= Vars::Visuals::HempDistation)
				GUI::Render.String(Pos, text, FLOAT4TOD3DCOLOR(Vars::Color::HempEsp));
			}
		}

		if (strstr(buff, "supply_drop.prefab") && Vars::Visuals::Supply) 
		{
			DWORD64 Res = safe_read(Object + 0x28, DWORD64);
			DWORD64 gameObject = safe_read(ObjectClass + 0x30, DWORD64); //Tag 449
			DWORD64 Trans = safe_read(gameObject + 0x8, DWORD64);
			DWORD64 Vec = safe_read(Trans + 0x38, DWORD64);
			Vector3 pos = safe_read(Vec + 0x90, Vector3);
			Vector2 Pos;
			if (LocalPlayer.WorldToScreen(pos, Pos)) 
			{
				int distation = (int)Math::Calc3D_Dist(LocalPlayer.BasePlayer->GetBoneByID(head), pos);
				wchar_t text[0x100];
				
				_swprintf(text, L"Airdrop [%d m]", distation);
				if (distation <= Vars::Visuals::SupplyDistation)
				GUI::Render.String(Pos, text, FLOAT4TOD3DCOLOR(Vars::Color::SupplyEsp));
			}
		}
		if (strstr(buff, "codelockedhackablecrate.prefab") && Vars::Visuals::Supply) 
		{
			DWORD64 Res = safe_read(Object + 0x28, DWORD64);
			DWORD64 gameObject = safe_read(ObjectClass + 0x30, DWORD64); //Tag 449
			DWORD64 Trans = safe_read(gameObject + 0x8, DWORD64);
			DWORD64 Vec = safe_read(Trans + 0x38, DWORD64);
			Vector3 pos = safe_read(Vec + 0x90, Vector3);
			Vector2 Pos;
			if (LocalPlayer.WorldToScreen(pos, Pos)) 
			{
				int distation = (int)Math::Calc3D_Dist(LocalPlayer.BasePlayer->GetBoneByID(head), pos);
				wchar_t text[0x100];
				
				_swprintf(text, L"Ch47_drop [%d m]", distation);
				if (distation <= Vars::Visuals::SupplyDistation)
				GUI::Render.String(Pos, text, FLOAT4TOD3DCOLOR(Vars::Color::SupplyEsp));
			}
		}

		if (Vars::Visuals::Corpse && strstr(buff, "player_corpse.prefab")) 
		{
			DWORD64 Res = safe_read(Object + 0x28, DWORD64);
			DWORD64 gameObject = safe_read(ObjectClass + 0x30, DWORD64); //Tag 449
			DWORD64 Trans = safe_read(gameObject + 0x8, DWORD64);
			DWORD64 Vec = safe_read(Trans + 0x38, DWORD64);
			Vector3 pos = safe_read(Vec + 0x90, Vector3);
			Vector2 Pos;
			if (LocalPlayer.WorldToScreen(pos, Pos)) 
			{
				int distation = (int)Math::Calc3D_Dist(LocalPlayer.BasePlayer->GetBoneByID(head), pos);
				wchar_t text[0x100];
				

				_swprintf(text, L"Corpse [%d m]", distation);
				if (distation <= Vars::Visuals::CorpseDistation)
				GUI::Render.String(Pos, text, FLOAT4TOD3DCOLOR(Vars::Color::CorpseEsp));
			}
		}
		if (Vars::Visuals::Corpse && strstr(buff, "item_drop_backpack.prefab"))
		{
			DWORD64 Res = safe_read(Object + 0x28, DWORD64);
			DWORD64 gameObject = safe_read(ObjectClass + 0x30, DWORD64); //Tag 449
			DWORD64 Trans = safe_read(gameObject + 0x8, DWORD64);
			DWORD64 Vec = safe_read(Trans + 0x38, DWORD64);
			Vector3 pos = safe_read(Vec + 0x90, Vector3);
			Vector2 Pos;
			if (LocalPlayer.WorldToScreen(pos, Pos)) 
			{
				int distation = (int)Math::Calc3D_Dist(LocalPlayer.BasePlayer->GetBoneByID(head), pos);
				wchar_t text[0x100];
				
				_swprintf(text, L"Backpack [%d m]", distation);
				if (distation <= Vars::Visuals::CorpseDistation)
				GUI::Render.String(Pos, text, FLOAT4TOD3DCOLOR(Vars::Color::CorpseEsp));
			}
		}

		if (Vars::Visuals::show_Weapons && strstr(buff, "lmg.m249")) 
		{
			DWORD64 Res = safe_read(Object + 0x28, DWORD64);
			DWORD64 gameObject = safe_read(ObjectClass + 0x30, DWORD64); //Tag 449
			DWORD64 Trans = safe_read(gameObject + 0x8, DWORD64);
			DWORD64 Vec = safe_read(Trans + 0x38, DWORD64);
			Vector3 pos = safe_read(Vec + 0x90, Vector3);
			Vector2 Pos;
			if (LocalPlayer.WorldToScreen(pos, Pos)) 
			{
				int distation = (int)Math::Calc3D_Dist(LocalPlayer.BasePlayer->GetBoneByID(head), pos);
				wchar_t text[0x100];
				
				_swprintf(text, L"M249 LMG [%d m]", distation);
				if (distation <= Vars::Visuals::show_WeaponsDistation)
				GUI::Render.String(Pos, text, FLOAT4TOD3DCOLOR(Vars::Color::show_WeaponsEsp));
			}
		}

		if (Vars::Visuals::show_Weapons && strstr(buff, "rifle.bolt")) 
		{
			DWORD64 Res = safe_read(Object + 0x28, DWORD64);
			DWORD64 gameObject = safe_read(ObjectClass + 0x30, DWORD64); //Tag 449
			DWORD64 Trans = safe_read(gameObject + 0x8, DWORD64);
			DWORD64 Vec = safe_read(Trans + 0x38, DWORD64);
			Vector3 pos = safe_read(Vec + 0x90, Vector3);
			Vector2 Pos;
			if (LocalPlayer.WorldToScreen(pos, Pos)) 
			{
				int distation = (int)Math::Calc3D_Dist(LocalPlayer.BasePlayer->GetBoneByID(head), pos);
				wchar_t text[0x100];
				
				_swprintf(text, L"BOLT Sniper [%d m]", distation);
				if (distation <= Vars::Visuals::show_WeaponsDistation)
				GUI::Render.String(Pos, text, FLOAT4TOD3DCOLOR(Vars::Color::show_WeaponsEsp));
			}
		}

		if (Vars::Visuals::show_Weapons && strstr(buff, "rifle.ak")) 
		{
			DWORD64 Res = safe_read(Object + 0x28, DWORD64);
			DWORD64 gameObject = safe_read(ObjectClass + 0x30, DWORD64); //Tag 449
			DWORD64 Trans = safe_read(gameObject + 0x8, DWORD64);
			DWORD64 Vec = safe_read(Trans + 0x38, DWORD64);
			Vector3 pos = safe_read(Vec + 0x90, Vector3);
			Vector2 Pos;
			if (LocalPlayer.WorldToScreen(pos, Pos))
			{
				int distation = (int)Math::Calc3D_Dist(LocalPlayer.BasePlayer->GetBoneByID(head), pos);
				wchar_t text[0x100];
				
				_swprintf(text, L"AK-47 Rifle [%d m]", distation);
				if (distation <= Vars::Visuals::show_WeaponsDistation)
				GUI::Render.String(Pos, text, FLOAT4TOD3DCOLOR(Vars::Color::show_WeaponsEsp));
			}
		}

		if (Vars::Visuals::show_Weapons && strstr(buff, "rifle.lr300")) 
		{
			DWORD64 Res = safe_read(Object + 0x28, DWORD64);
			DWORD64 gameObject = safe_read(ObjectClass + 0x30, DWORD64); //Tag 449
			DWORD64 Trans = safe_read(gameObject + 0x8, DWORD64);
			DWORD64 Vec = safe_read(Trans + 0x38, DWORD64);
			Vector3 pos = safe_read(Vec + 0x90, Vector3);
			Vector2 Pos;
			if (LocalPlayer.WorldToScreen(pos, Pos)) 
			{
				int distation = (int)Math::Calc3D_Dist(LocalPlayer.BasePlayer->GetBoneByID(head), pos);
				wchar_t text[0x100];
				
				_swprintf(text, L"LR300 Rifle [%d m]", distation);
				if (distation <= Vars::Visuals::show_WeaponsDistation)
				GUI::Render.String(Pos, text, FLOAT4TOD3DCOLOR(Vars::Color::show_WeaponsEsp));
			}
		}

		if (Vars::Visuals::show_Weapons && strstr(buff, "rifle.l96")) 
		{
			DWORD64 Res = safe_read(Object + 0x28, DWORD64);
			DWORD64 gameObject = safe_read(ObjectClass + 0x30, DWORD64); //Tag 449
			DWORD64 Trans = safe_read(gameObject + 0x8, DWORD64);
			DWORD64 Vec = safe_read(Trans + 0x38, DWORD64);
			Vector3 pos = safe_read(Vec + 0x90, Vector3);
			Vector2 Pos;
			if (LocalPlayer.WorldToScreen(pos, Pos)) 
			{
				int distation = (int)Math::Calc3D_Dist(LocalPlayer.BasePlayer->GetBoneByID(head), pos);
				wchar_t text[0x100];
				
				_swprintf(text, L"AWM Sniper [%d m]", distation);
				if (distation <= Vars::Visuals::show_WeaponsDistation)
				GUI::Render.String(Pos, text, FLOAT4TOD3DCOLOR(Vars::Color::show_WeaponsEsp));
			}
		}

		if (Vars::Visuals::show_Weapons && strstr(buff, "rifle.m39")) 
		{
			DWORD64 Res = safe_read(Object + 0x28, DWORD64);
			DWORD64 gameObject = safe_read(ObjectClass + 0x30, DWORD64); //Tag 449
			DWORD64 Trans = safe_read(gameObject + 0x8, DWORD64);
			DWORD64 Vec = safe_read(Trans + 0x38, DWORD64);
			Vector3 pos = safe_read(Vec + 0x90, Vector3);
			Vector2 Pos;
			if (LocalPlayer.WorldToScreen(pos, Pos))
			{
				int distation = (int)Math::Calc3D_Dist(LocalPlayer.BasePlayer->GetBoneByID(head), pos);
				wchar_t text[0x100];
				
				_swprintf(text, L"M39 Rifle [%d m]", distation);
				if (distation <= Vars::Visuals::show_WeaponsDistation)
				GUI::Render.String(Pos, text, FLOAT4TOD3DCOLOR(Vars::Color::show_WeaponsEsp));
			}
		}

		if (Vars::Visuals::show_Weapons && strstr(buff, "rifle.semiauto"))
		{
			DWORD64 Res = safe_read(Object + 0x28, DWORD64);
			DWORD64 gameObject = safe_read(ObjectClass + 0x30, DWORD64); //Tag 449
			DWORD64 Trans = safe_read(gameObject + 0x8, DWORD64);
			DWORD64 Vec = safe_read(Trans + 0x38, DWORD64);
			Vector3 pos = safe_read(Vec + 0x90, Vector3);
			Vector2 Pos;
			if (LocalPlayer.WorldToScreen(pos, Pos))
			{
				int distation = (int)Math::Calc3D_Dist(LocalPlayer.BasePlayer->GetBoneByID(head), pos);
				wchar_t text[0x100];
				
				_swprintf(text, L"Semi Auto Rifle [%d m]", distation);
				if (distation <= Vars::Visuals::show_WeaponsDistation)
				GUI::Render.String(Pos, text, FLOAT4TOD3DCOLOR(Vars::Color::show_WeaponsEsp));
			}
		}

		if (Vars::Visuals::show_Weapons && strstr(buff, "smg.mp5"))
		{
			DWORD64 Res = safe_read(Object + 0x28, DWORD64);
			DWORD64 gameObject = safe_read(ObjectClass + 0x30, DWORD64); //Tag 449
			DWORD64 Trans = safe_read(gameObject + 0x8, DWORD64);
			DWORD64 Vec = safe_read(Trans + 0x38, DWORD64);
			Vector3 pos = safe_read(Vec + 0x90, Vector3);
			Vector2 Pos;
			if (LocalPlayer.WorldToScreen(pos, Pos)) 
			{
				int distation = (int)Math::Calc3D_Dist(LocalPlayer.BasePlayer->GetBoneByID(head), pos);
				wchar_t text[0x100];
				
				_swprintf(text, L"MP5 SMG [%d m]", distation);
				if (distation <= Vars::Visuals::show_WeaponsDistation)
				GUI::Render.String(Pos, text, FLOAT4TOD3DCOLOR(Vars::Color::show_WeaponsEsp));
			}
		}

		if (Vars::Visuals::show_Weapons && strstr(buff, "smg.2")) 
		{
			DWORD64 Res = safe_read(Object + 0x28, DWORD64);
			DWORD64 gameObject = safe_read(ObjectClass + 0x30, DWORD64); //Tag 449
			DWORD64 Trans = safe_read(gameObject + 0x8, DWORD64);
			DWORD64 Vec = safe_read(Trans + 0x38, DWORD64);
			Vector3 pos = safe_read(Vec + 0x90, Vector3);
			Vector2 Pos;
			if (LocalPlayer.WorldToScreen(pos, Pos))
			{
				int distation = (int)Math::Calc3D_Dist(LocalPlayer.BasePlayer->GetBoneByID(head), pos);
				wchar_t text[0x100];
				
				_swprintf(text, L"SMG Auto [%d m]", distation);
				if (distation <= Vars::Visuals::show_WeaponsDistation)
				GUI::Render.String(Pos, text, FLOAT4TOD3DCOLOR(Vars::Color::show_WeaponsEsp));
			}
		}

		if (Vars::Visuals::show_Weapons && strstr(buff, "smg.thompson")) 
		{
			DWORD64 Res = safe_read(Object + 0x28, DWORD64);
			DWORD64 gameObject = safe_read(ObjectClass + 0x30, DWORD64); //Tag 449
			DWORD64 Trans = safe_read(gameObject + 0x8, DWORD64);
			DWORD64 Vec = safe_read(Trans + 0x38, DWORD64);
			Vector3 pos = safe_read(Vec + 0x90, Vector3);
			Vector2 Pos;
			if (LocalPlayer.WorldToScreen(pos, Pos)) 
			{
				int distation = (int)Math::Calc3D_Dist(LocalPlayer.BasePlayer->GetBoneByID(head), pos);
				wchar_t text[0x100];
				
				_swprintf(text, L"Thompson SMG [%d m]", distation);
				if (distation <= Vars::Visuals::show_WeaponsDistation)
				GUI::Render.String(Pos, text, FLOAT4TOD3DCOLOR(Vars::Color::show_WeaponsEsp));
			}
		}

		if (Vars::Visuals::show_Weapons && strstr(buff, "pistol.nailgun"))
		{
			DWORD64 Res = safe_read(Object + 0x28, DWORD64);
			DWORD64 gameObject = safe_read(ObjectClass + 0x30, DWORD64); //Tag 449
			DWORD64 Trans = safe_read(gameObject + 0x8, DWORD64);
			DWORD64 Vec = safe_read(Trans + 0x38, DWORD64);
			Vector3 pos = safe_read(Vec + 0x90, Vector3);
			Vector2 Pos;
			if (LocalPlayer.WorldToScreen(pos, Pos)) 
			{
				int distation = (int)Math::Calc3D_Dist(LocalPlayer.BasePlayer->GetBoneByID(head), pos);
				wchar_t text[0x100];
				
				_swprintf(text, L"Nailgun Pistol [%d m]", distation);
				if (distation <= Vars::Visuals::show_WeaponsDistation)
				GUI::Render.String(Pos, text, FLOAT4TOD3DCOLOR(Vars::Color::show_WeaponsEsp));
			}
		}

		if (Vars::Visuals::show_Weapons && strstr(buff, "pistol.eoka"))
		{
			DWORD64 Res = safe_read(Object + 0x28, DWORD64);
			DWORD64 gameObject = safe_read(ObjectClass + 0x30, DWORD64); //Tag 449
			DWORD64 Trans = safe_read(gameObject + 0x8, DWORD64);
			DWORD64 Vec = safe_read(Trans + 0x38, DWORD64);
			Vector3 pos = safe_read(Vec + 0x90, Vector3);
			Vector2 Pos;
			if (LocalPlayer.WorldToScreen(pos, Pos)) 
			{
				int distation = (int)Math::Calc3D_Dist(LocalPlayer.BasePlayer->GetBoneByID(head), pos);
				wchar_t text[0x100];
				
				_swprintf(text, L"EOKA Pistol [%d m]", distation);
				if (distation <= Vars::Visuals::show_WeaponsDistation)
				GUI::Render.String(Pos, text, FLOAT4TOD3DCOLOR(Vars::Color::show_WeaponsEsp));
			}
		}

		if (Vars::Visuals::show_Weapons && strstr(buff, "pistol.m92"))
		{
			DWORD64 Res = safe_read(Object + 0x28, DWORD64);
			DWORD64 gameObject = safe_read(ObjectClass + 0x30, DWORD64); //Tag 449
			DWORD64 Trans = safe_read(gameObject + 0x8, DWORD64);
			DWORD64 Vec = safe_read(Trans + 0x38, DWORD64);
			Vector3 pos = safe_read(Vec + 0x90, Vector3);
			Vector2 Pos;
			if (LocalPlayer.WorldToScreen(pos, Pos)) 
			{
				int distation = (int)Math::Calc3D_Dist(LocalPlayer.BasePlayer->GetBoneByID(head), pos);
				wchar_t text[0x100];
				
				_swprintf(text, L"M92 Pistol [%d m]", distation);
				if (distation <= Vars::Visuals::show_WeaponsDistation)
				GUI::Render.String(Pos, text, FLOAT4TOD3DCOLOR(Vars::Color::show_WeaponsEsp));
			}
		}

		if (Vars::Visuals::show_Weapons && strstr(buff, "pistol.python"))
		{
			DWORD64 Res = safe_read(Object + 0x28, DWORD64);
			DWORD64 gameObject = safe_read(ObjectClass + 0x30, DWORD64); //Tag 449
			DWORD64 Trans = safe_read(gameObject + 0x8, DWORD64);
			DWORD64 Vec = safe_read(Trans + 0x38, DWORD64);
			Vector3 pos = safe_read(Vec + 0x90, Vector3);
			Vector2 Pos;
			if (LocalPlayer.WorldToScreen(pos, Pos))
			{
				int distation = (int)Math::Calc3D_Dist(LocalPlayer.BasePlayer->GetBoneByID(head), pos);
				wchar_t text[0x100];
				
				_swprintf(text, L"Python Pistol [%d m]", distation);
				if (distation <= Vars::Visuals::show_WeaponsDistation)
				GUI::Render.String(Pos, text, FLOAT4TOD3DCOLOR(Vars::Color::show_WeaponsEsp));
			}
		}

		if (Vars::Visuals::show_Weapons && strstr(buff, "pistol.revolver")) 
		{
			DWORD64 Res = safe_read(Object + 0x28, DWORD64);
			DWORD64 gameObject = safe_read(ObjectClass + 0x30, DWORD64); //Tag 449
			DWORD64 Trans = safe_read(gameObject + 0x8, DWORD64);
			DWORD64 Vec = safe_read(Trans + 0x38, DWORD64);
			Vector3 pos = safe_read(Vec + 0x90, Vector3);
			Vector2 Pos;
			if (LocalPlayer.WorldToScreen(pos, Pos)) 
			{
				int distation = (int)Math::Calc3D_Dist(LocalPlayer.BasePlayer->GetBoneByID(head), pos);
				wchar_t text[0x100];
				
				_swprintf(text, L"Revolver Pistol [%d m]", distation);
				if (distation <= Vars::Visuals::show_WeaponsDistation)
				GUI::Render.String(Pos, text, FLOAT4TOD3DCOLOR(Vars::Color::show_WeaponsEsp));
			}
		}

		if (Vars::Visuals::show_Weapons && strstr(buff, "pistol.semiauto"))
		{
			DWORD64 Res = safe_read(Object + 0x28, DWORD64);
			DWORD64 gameObject = safe_read(ObjectClass + 0x30, DWORD64); //Tag 449
			DWORD64 Trans = safe_read(gameObject + 0x8, DWORD64);
			DWORD64 Vec = safe_read(Trans + 0x38, DWORD64);
			Vector3 pos = safe_read(Vec + 0x90, Vector3);
			Vector2 Pos;
			if (LocalPlayer.WorldToScreen(pos, Pos))
			{
				int distation = (int)Math::Calc3D_Dist(LocalPlayer.BasePlayer->GetBoneByID(head), pos);
				wchar_t text[0x100];
				
				_swprintf(text, L"Semi Auto Pistol [%d m]", distation);
				if (distation <= Vars::Visuals::show_WeaponsDistation)
				GUI::Render.String(Pos, text, FLOAT4TOD3DCOLOR(Vars::Color::show_WeaponsEsp));
			}
		}

		if (Vars::Visuals::show_Weapons && strstr(buff, "shotgun.pump")) 
		{
			DWORD64 Res = safe_read(Object + 0x28, DWORD64);
			DWORD64 gameObject = safe_read(ObjectClass + 0x30, DWORD64); //Tag 449
			DWORD64 Trans = safe_read(gameObject + 0x8, DWORD64);
			DWORD64 Vec = safe_read(Trans + 0x38, DWORD64);
			Vector3 pos = safe_read(Vec + 0x90, Vector3);
			Vector2 Pos;
			if (LocalPlayer.WorldToScreen(pos, Pos)) 
			{
				int distation = (int)Math::Calc3D_Dist(LocalPlayer.BasePlayer->GetBoneByID(head), pos);
				wchar_t text[0x100];
				
				_swprintf(text, L"Shotgun Pump [%d m]", distation);
				if (distation <= Vars::Visuals::show_WeaponsDistation)
				GUI::Render.String(Pos, text, FLOAT4TOD3DCOLOR(Vars::Color::show_WeaponsEsp));
			}
		}

		if (Vars::Visuals::show_Weapons && strstr(buff, "shotgun.double"))
		{
			DWORD64 Res = safe_read(Object + 0x28, DWORD64);
			DWORD64 gameObject = safe_read(ObjectClass + 0x30, DWORD64); //Tag 449
			DWORD64 Trans = safe_read(gameObject + 0x8, DWORD64);
			DWORD64 Vec = safe_read(Trans + 0x38, DWORD64);
			Vector3 pos = safe_read(Vec + 0x90, Vector3);
			Vector2 Pos;
			if (LocalPlayer.WorldToScreen(pos, Pos)) 
			{
				int distation = (int)Math::Calc3D_Dist(LocalPlayer.BasePlayer->GetBoneByID(head), pos);
				wchar_t text[0x100];
				
				_swprintf(text, L"Double Shotgun [%d m]", distation);
				if (distation <= Vars::Visuals::show_WeaponsDistation)
				GUI::Render.String(Pos, text, FLOAT4TOD3DCOLOR(Vars::Color::show_WeaponsEsp));
			}
		}

		if (Vars::Visuals::show_Weapons && strstr(buff, "shotgun.spas12")) 
		{
			DWORD64 Res = safe_read(Object + 0x28, DWORD64);
			DWORD64 gameObject = safe_read(ObjectClass + 0x30, DWORD64); //Tag 449
			DWORD64 Trans = safe_read(gameObject + 0x8, DWORD64);
			DWORD64 Vec = safe_read(Trans + 0x38, DWORD64);
			Vector3 pos = safe_read(Vec + 0x90, Vector3);
			Vector2 Pos;
			if (LocalPlayer.WorldToScreen(pos, Pos))
			{
				int distation = (int)Math::Calc3D_Dist(LocalPlayer.BasePlayer->GetBoneByID(head), pos);
				wchar_t text[0x100];
				
				_swprintf(text, L"SPAS-12 Shotgun [%d m]", distation);
				if (distation <= Vars::Visuals::show_WeaponsDistation)
				GUI::Render.String(Pos, text, FLOAT4TOD3DCOLOR(Vars::Color::show_WeaponsEsp));
			}
		}

	}

	if (LP_isValid)
	{
		WeaponPatch();
		Aim(AimEntity);
		Misc();
		FakeLag();
	}

	//LP not valid
	else LocalPlayer.BasePlayer = nullptr;

	static DWORD64 dwGameObjectManager = 0;
	if (!dwGameObjectManager)
		dwGameObjectManager = RVA(FindPattern((PBYTE)"\x48\x8B\x15\x00\x00\x00\x00\x66\x39", "xxx????xx", L"UnityPlayer.dll"), 7);

	DWORD64 ObjMgr = safe_read(dwGameObjectManager, DWORD64); if (!ObjMgr) return;

	for (DWORD64 Obj = safe_read(ObjMgr + 0x8, DWORD64); (Obj && (Obj != safe_read(ObjMgr, DWORD64))); Obj = safe_read(Obj + 0x8, DWORD64))
	{
		DWORD64 GameObject = safe_read(Obj + 0x10, DWORD64);
		WORD Tag = safe_read(GameObject + 0x54, WORD);

		if (Tag == 6 || Tag == 5 || Tag == 20011)
		{
			DWORD64 ObjClass = safe_read(GameObject + 0x30, DWORD64);
			DWORD64	Entity = safe_read(ObjClass + 0x18, DWORD64);

			//entity
			if (Tag == 6)
			{
				BasePlayer* Player = (BasePlayer*)safe_read(Entity + 0x28, DWORD64);
				if (!Player->IsValid()) continue;

				//entity
				if (safe_read(safe_read(GameObject + 0x60, DWORD64), DWORD64) != 0x616C506C61636F4C)
				{
					//exec esp
					ESP(Player, LocalPlayer.BasePlayer);
					if (Math::Calc3D_Dist(LocalPlayer.BasePlayer->GetBoneByID(head), Player->GetBoneByID(head)) > Vars::AimBot::Range)
						goto NextEnt;

				}

				//LP
				else 
				{
					LP_isValid = true;
					LocalPlayer.BasePlayer = Player;
				}
			}

			//camera
			else if (Tag == 5)
				LocalPlayer.pViewMatrix = (Matrix4x4*)(Entity + 0x2E4);// 0xDC

			//sky
			else if (Tag == 20011 && Vars::Visuals::AlwaysDay) 
			{
				DWORD64 Dome = safe_read(Entity + 0x28, DWORD64);
				DWORD64 TodCycle = safe_read(Dome + 0x38, DWORD64);
				safe_write(TodCycle + 0x10, 13.37f, float);
			}

			else if (Tag == 20011 && Vars::Misc::CustomTime) 
			{
				DWORD64 Dome = safe_read(Entity + 0x28, DWORD64);
				DWORD64 TodCycle = safe_read(Dome + 0x38, DWORD64);
				safe_write(TodCycle + 0x10, Vars::Misc::Time, float);
			}

		}

		//goto next entity
	NextEnt: continue;
	}

	//GET MEMES
	if (LP_isValid)
	{
		WeaponPatch();
		Aim(AimEntity);
		Misc();
	}

	//LP not valid
	else LocalPlayer.BasePlayer = nullptr;
}