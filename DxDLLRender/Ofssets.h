#pragma once

#define oGameObjectManager 0x17C1F18

#pragma region BasePlayer

#define oPlayerInput 0x4C8// public PlayerInput input;
#define oPlayerModel 0x4A8// public PlayerModel playerModel;
#define oPlayerFlags 0x5F8// public BasePlayer.PlayerFlags playerFlags;
#define oUserID 0x640// public ulong userID;
#define oDisplayName 0x658// protected string _displayName
#define oClientTickInterval 0x5C8// public float clientTickInterval;
#define oClActiveItem 0x570// private uint clActiveItem; 
#define oInventory 0x608// public PlayerInventory inventory;
#define oMovement 0x4D0// public BaseMovement movement;


#pragma endregion


//*** Projectile ***//

#define oThickness 0x2C// public float thickness;

	//*** TOD_Sky ***//

#define oInstances 0x0// private static List<TOD_Sky> instances;
#define oCycle 0x38// public TOD_CycleParameters Cycle;

	//*** TOD_CycleParameters ***//

#define OHour 0x10// public float Hour;

#pragma region PlayerWalkMovement

#define oGroundAngle 0xB4// private float groundAngle;
#define oGroundAngleNew 0xB8// private float groundAngleNew;
#define oGravityMultiplier 0x74// public float gravityMultiplier;
#define oFlying 0x13C// private bool flying;
#define oGravityMultiplierSwimming 0x78 // public float gravityMultiplierSwimming;


#pragma endregion

#pragma region ItemDefinition

#define oShortname 0x20// public string shortname;
#define odisplayname 0x28// public Translate.Phrase displayName;
#define oID 0x18// public int itemid;

#pragma endregion


		//*** Item ***//
#define oUID 0x28// public uint uid;
#define ItemDefinition 0x20// public ItemDefinition info;
#define oHeldEntity 0x98// private EntityRef heldEntity;

		//*** Player Model ***//

#define oSmoothVelocity 0x1FC// private Vector3 newVelocity
#define oVisible 0x248// internal bool visible;

		//*** BaseProjectile ***//

#define oPrimaryMagazine 0x2A0// public BaseProjectile.Magazine primaryMagazine;

		//*** BaseNetworkable ***//

#define oNetworkable 0x50// public Networkable net;

		//*** HeldEntity ***//

#define oPunches 0x148// protected List<HeldEntity.PunchEntry> _punches;

		//*** Networkable ***//

#define oNetworkId 0x10//public uint ID;

		//*** PlayerAttack ***//

#define oAttack 0x18// public Attack attack;

		//*** Attack ***//

#define oHitID 0x2C// public uint hitID;
#define oHitPartID 0x64// public uint hitPartID;
#define oHitBone 0x30// public uint hitBone;  ? //HitInfo 
#define oHitMaterialID 0x68 // public uint hitMaterialID;
#define oPlayerAttack 0x18 // public PlayerAttack playerAttack;
#define oAttack 0x18 // public Attack attack;
#define oHitNormalWorld 0x4C // public Vector3 hitNormalWorld; ? //public class Attack : IDisposable, Pool.IPooled, IProto 


		//*** BaseCombatEntity ***//

#define oLifeState 0x204// public BaseCombatEntity.LifeState lifestate; 
#define oHealth 0x20C// private float _health;

	//*** PlayerInput ***//

#define oKeyFocus 0x94// private bool hasKeyFocus;
#define oBodyAngles 0x3C// private Vector3 bodyAngles;


				//***  ***//

#define oStancePenalty 0x304 //private float stancePenalty;
#define oAimconePenalty 0x308 //private float aimconePenalty;
#define oAimCone 0x2D0 //public float aimCone;
#define oHipAimCone 0x2D4 //public float hipAimCone;
#define oAimconePenaltyPerShot 0x2D8 //public float aimconePenaltyPerShot;
#define oCorpsePlayerName 0x2A8// public string _playerName;

#define oRecoil 0x2C0 // public RecoilProperties recoil;
#define oRecoilYawMin 0x18 // public float recoilYawMin;
#define oRecoilYawMax 0x1C // public float recoilYawMax;
#define oRecoilPitchMin 0x20 // public float recoilPitchMin;
#define oRecoilPitchMax 0x24  // public float recoilPitchMax;
#define oADSScale 0x30 // public float ADSScale; 
#define oMovementPenalty 0x34 // public float movementPenalty;
#define oAutomatic 0x270 // public bool automatic;
#define oSuccessFraction 0x340 // public float successFraction;
#define oAttackReady 0x340 // protected bool attackReady;
#define oArrowBack 0x344 // private float arrowBack;
#define oHornOrigin 0x1C8 // public GameObject hornOrigin;
#define oAttackRadius 0x27C //public float attackRadius;
#define oBlockSprintOnAttack 0x281 //public bool blockSprintOnAttack;
#define oNewVelocity 0x1FC // private Vector3 newVelocity;
#define oLastSentTickTime 0x5CC // private float lastSentTickTime;
#define oClientTeam 0x540 // public PlayerTeam clientTeam
#define oRecoilAngles 0x64 // public Vector3 recoilAngles;
#define oInventory 0x608// public PlayerInventory inventory;
#define oFrozen 0x4B0 // public bool Frozen;
#define oClothingWaterSpeedBonus 0x6C0 // public float clothingWaterSpeedBonus;
#define oClothingAccuracyBonus 0x6C4 // public float clothingAccuracyBonus;
#define oClothingBlocksAiming 0x6B8 // public bool clothingBlocksAiming;
#define oClothingMoveSpeedReduction 0x6BC // public float clothingMoveSpeedReduction;

// hooks
#define oSetFlying 0x1C58240 //public void set_flying(bool value) { } 
#define oSendProjectileAttack 0x30E270 // public void SendProjectileAttack(PlayerProjectileAttack attack) { }
#define oCanAttack 0x2F6A10 // public bool CanAttack() { }
#define oCreateProjectile 0x76F160 // private Projectile CreateProjectile(string prefabPath, Vector3 pos, Vector3 forward, Vector3 velocity) { } (2)
#define oBlockSprint 0x2F5D80 // public virtual void BlockSprint(float duration = 0,2) { }
#define oGetSpeed 0x3005D0 // public float GetSpeed(float running, float ducking) { }
#define oGetIndexedSpreadScalar 0x4DEF10 // public float GetIndexedSpreadScalar(int shotIndex, int maxShots) { }
#define oAntiAim 0x30DBB0 //internal void SendClientTick() { }
#define oFakeCard 0x4EB000 //public int get_accessLevel() { }
#define oAimConeUtil 0x9159C0 //public static Vector3 GetModifiedAimConeDirection(float aimCone, Vector3 inputVec, bool anywhereInside = True) { }
#define oClientInput 0x2E6760 //public virtual void ClientInput(InputState state, ModelState modelState) { }
#define oTodSky 0x146A510 // public T GetComponent() { } ?
#define oClosestPoint 0x3C5C60 //public Vector3 ClosestPoint(Vector3 position) { }
#define oKnockDoor 0x86AC70 //public void Menu_KnockDoor(BasePlayer player) { }
#define oServerRPC 0x3CEE10 //public void ServerRPC(string funcName) { }
#define oAmbientMode 0x182CBE0//// public static void set_ambientMode(AmbientMode value) { }
#define oambientIntensit 0x182CB20 //public static void set_ambientIntensity(float value) { }
#define oambientLight 0x182CBA0 //public static void set_ambientLight(Color value) { }
#define oRun 0x204C360 //public static string Run(ConsoleSystem.Option options, string strCommand, object[] args) { } //ConsoleSystem$$Run // ConsoleSystem$$Run //scripts.json

// hooks script 
#define oBaseNetworkable 0x2FC3FC8 //BN Class$BaseNetworkable BaseNetworkable_c*
#define oSlideWalk 0xB367C0 // PlayerWalkMovement$$HandleRunning // private void HandleRunning(ModelState state, bool wantsRun) { }
#define oConVar 0x2FC2CF8 //ConVar_Graphics_c*  Class$ConVar.Graphics
#define oEulerAngles 0x1F72A80 // "Name": "UnityEngine.Transform$$get_eulerAngles"
#define oPosition 0x1F730B0//UnityEngine.Transform$$get_position
