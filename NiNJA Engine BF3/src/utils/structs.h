#pragma once

template<typename Type>
struct ScrollStruct {
	const char* pName;
	Type Result;
};

struct UIEngine;
struct ClientSoldierEntity;
struct HavokPhysicsManager;
struct ClientPlayer;
struct ComponentCollection;
struct ClientGameContext;
struct ClientAimingReplication;
struct GameEntity;
struct AimingConstraints;
struct MaterialContainerPair;
struct ComponentInfo;
struct ClientControllableEntity;
struct SoldierWeaponUnlockAsset;

struct FixedVector {
	DWORD dwStartOfList;
	DWORD dwEndOfList;
	char _0x0008[0xC];

	DWORD get(int index) {
		return *(DWORD*)(dwStartOfList + (index * 4));
	}

	template<typename type>
	type get(int index) {
		return (type)*(DWORD*)(dwStartOfList + (index * 4));
	}

	int size() {
		return (dwEndOfList - dwStartOfList) / 4;
	}
};

struct Vector {
	DWORD dwStartOfList;
	DWORD dwEndOfList;
	char _0x0008[0x8];

	DWORD get(int index) {
		return *(DWORD*)(dwStartOfList + (index * 4));
	}

	template<typename T>
	T get(int index) {
		return *(T*)(dwStartOfList + (index * 4));
	}

	DWORD getInline(int index) {
		return (dwStartOfList + (index * 4));
	}

	DWORD get(int index, int size) {
		return *(DWORD*)(dwStartOfList + (index * size));
	}

	DWORD getInline(int index, int size) {
		return (dwStartOfList + (index * size));
	}

	int size() {
		return (dwEndOfList - dwStartOfList) / 4;
	}
};

struct DxRenderer {
	void* pVtable;
	void* pGlobalHeapArena;
	DWORD dwFrameCounter;
	char _0x000C[0xC];
	D3DDevice* pDevice;
};

struct Vec3 {
	float x;
	float y;
	float z;
	float w;

	Vec3() {
		x = 0.f;
		y = 0.f;
		z = 0.f;
		w = 0.f;
	}

	Vec3(float _x, float _y, float _z) {
		x = _x;
		y = _y;
		z = _z;
	}

	Vec3(float _x, float _y, float _z, float _w) {
		x = _x;
		y = _y;
		z = _z;
		w = _w;
	}

	Vec3 operator*(float other) {
		x *= other;
		y *= other;
		z *= other;
		return *this;
	}

	Vec3 operator/(float other) {
		x /= other;
		y /= other;
		z /= other;
		return *this;
	}

	Vec3 operator*(Vec3 other) {
		x *= other.x;
		y *= other.y;
		z *= other.z;
		return *this;
	}

	Vec3 operator+(Vec3 other) {
		Vec3 v;
		v.x = x + other.x;
		v.y = y + other.y;
		v.z = z + other.z;
		return v;
	}

	Vec3 operator-(Vec3 other) {
		Vec3 k;
		k.x = x - other.x;
		k.y = y - other.y;
		k.z = z - other.z;
		return k;
	}

	Vec3 operator+=(Vec3 other) {
		x += other.x;
		y += other.y;
		z += other.z;
		return *this;
	}

	Vec3 operator*=(Vec3 other) {
		x *= other.x;
		y *= other.y;
		z *= other.z;
		return *this;
	}

	Vec3 operator*=(float other) {
		x *= other;
		y *= other;
		z *= other;
		return *this;
	}

	Vec3 operator-=(Vec3 other) {
		x -= other.x;
		y -= other.y;
		z -= other.z;
		return *this;
	}

	bool operator==(Vec3 const &other) {
		if (this->x == other.x) {
			if (this->y == other.y) {
				if (this->z == other.z) {
					return true;
				}
			}
		}
		return false;
	}

	float Length() {
		return sqrt(x * x + y * y + z * z);
	}

	void Normalize() {
		float _l = Length();
		this->x /= _l;
		this->y /= _l;
		this->z /= _l;
	}

	float VectorLength2() {
		return sqrt((x * x) + (z * z));
	}

	void Negate() {
		this->x = -this->x;
		this->y = -this->y;
		this->z = -this->z;
		this->w = -this->w;
	}
};

struct Vec2 {
	float x, y;

	Vec2() {
		x = 0.f;
		y = 0.f;
	}

	Vec2(float _x, float _y) {
		x = _x;
		y = _y;
	}

	Vec2 operator*(float other) {
		x *= other;
		y *= other;
		return *this;
	}

	Vec2 operator*(Vec2 other) {
		x *= other.x;
		y *= other.y;
		return *this;
	}

	Vec2 operator+(Vec2 other) {
		Vec2 v;
		v.x = x + other.x;
		v.y = y + other.y;
		return v;
	}

	Vec2 operator-(Vec2 other) {
		return Vec2(x - other.x, y - other.y);
	}

	Vec2 operator+=(Vec2 other) {
		x += other.x;
		y += other.y;
		return *this;
	}

	Vec2 operator*=(Vec2 other) {
		x *= other.x;
		y *= other.y;
		return *this;
	}

	Vec2 operator*=(float other) {
		x *= other;
		y *= other;
		return *this;
	}

	Vec2 operator-=(Vec2 other) {
		x -= other.x;
		y -= other.y;
		return *this;
	}
};

struct TargetInformation {
	const char* pUsingBone;
	bool bVisible;
	bool bHittable;
	Vec3 BonePosition;

	TargetInformation() {}
};

struct DataDesc {
	DWORD dwSize;
	volatile int nRefCount;
	char bData[1];
};

template <typename T>
struct SmartRef {
	T* pPtr;
};

template <typename T>
struct GPtr {
	T* pObject;
};

class GString {
public:
	union {
		DataDesc* pData;
		DWORD dwHeapTypeBits;
	};
public:
	const char* Get() {
		return (const char*)((dwHeapTypeBits & 0xFFFFFFFC));
	}

	void Set(const char* str) {
		((void(*)(GString*, const char*))0x83A0C268)(this, str);
	}
};

struct Color32 {
	BYTE R;
	BYTE G;
	BYTE B;
	BYTE A;
};


class GColor {
public:
	union {
		struct {
			BYTE A;
			BYTE R;
			BYTE G;
			BYTE B;
		};
		DWORD dwColor;
	};

	float AsFloat_R() { return (float)(R / 255.f); }
	float AsFloat_G() { return (float)(G / 255.f); }
	float AsFloat_B() { return (float)(B / 255.f); }
	float AsFloat_A() { return (float)(A / 255.f); }

	GColor(DWORD _Color) {
		dwColor = _Color;
	}

	GColor() {

	}

	GColor(BYTE Red, BYTE Green, BYTE Blue, BYTE Alpha = 255) {
		A = Alpha;
		R = Red;
		G = Green;
		B = Blue;
	}

	DWORD GetVertexVal() {
		return DWORD(A << 24 |
			B << 16 |
			G << 8 |
			R);
	}
};

template <typename T>
class WeakPtr {
private:
	T** pPtr;

public:
	T* GetData() {
		if (pPtr == NULL)
			return NULL;

		if (*pPtr == NULL)
			return NULL;

		return (T*)((DWORD)(*pPtr) - offsetof(T, m_weakTokenHolderToken));
	}
};

template <typename T>
class Array {
private:
	T* pFirstElement;

public:
	T At(INT nIndex) {
		if (pFirstElement == NULL)
			return NULL;

		return *(T*)((DWORD)pFirstElement + (nIndex * sizeof(T)));
	};

	T operator [](INT index) { return At(index); }
};

template<typename T>
struct GRect {
	T Left;
	T Top;
	T Right;
	T Bottom;

	GRect() {}

	GRect(T left, T top, T right, T bottom) {
		Left = left; Top = top; Right = right; Bottom = bottom;
	}
};

struct FloatRGBA {
	float fpR;
	float fpG;
	float fpB;
	float fpA;
};

struct GFxDrawTextManagerTextParams {
	GColor TextColor;
	Alignment HAlignment;
	VAlignment VAlignment;
	FontStyle FontStyle;
	float flFontSize;
	GString FontName;
	bool bUnderline;
	bool bMultiline;
	bool bWordWrap;
	int nLeading;
	int nIndent;
	DWORD dwLeftMargin;
	DWORD dwRightMargin;

	void ConstructGString(const char* pStr) {
		FontName.Set(pStr);
	}
};

struct GViewport {
	int nBufferWidth;
	int nBufferHeight;
	int nLeft;
	int nTop;
	int nWidth;
	int nHeight;
	int nScissorLeft;
	int nScissorTop;
	int nScissorWidth;
	int nScissorHeight;
	float flScale;
	float flAspectRatio;
	DWORD dwFlags;
};

struct IndexBufferData {
	int nOffset;
	int nSize;
};

struct UIScaleformRenderer {
	char _0x0000[0x30];
	DWORD dwRenderState;
};

struct GFxDrawTextManager {
	char _0x0000[0xC];
	DWORD pManagerImpl;
	DWORD pMemoryManager;
};

struct UIRenderer {};

struct UIEngine {
	char _0x0000[0x3C];
	UIRenderer* pRenderer;
	UIScaleformRenderer* pScaleformRenderer;
	char _0x0040[0x10];
	GFxDrawTextManager* pDrawTextManager;
	char _0x0058[0x10];
	DWORD dwFrameIndex;
	float fTime;
	void* pHudRender;
	char componentRender[0x10];
	bool bWireframeFillMode;
};

struct EditBlur {
	float flBlurX;
	float flBlurY;
	float flStrength;
};

struct EditGlow {
	float flBlurX;
	float flBlurY;
	float flStrength;
	DWORD dwColor;
	char bFlags;
};

struct EditDropShadow {
	float flBlurX;
	float flBlurY;
	float flStrength;
	DWORD dwColor;
	char bFlags;
	float flAngle;
	float flDistance;
};

union uEdits {
	EditBlur Blur;
	EditGlow Glow;
	EditDropShadow DropShadow;
};

struct Filter {
	FilterModes FilterMode;
	uEdits Edits;
};

struct TypeInfoData {
	const char* pName;
};

struct TypeInfo {
	TypeInfoData* pInfoData;
};

struct ComponentData {};

struct ComponentCollection {
	GameEntity* pOwner;
	BYTE bPlayerCount;
	BYTE bTotalCount;
	BYTE bOffsetCount;
	char _0x0000[0x1];
};

struct Component {
	virtual TypeInfo* GetType();

	ComponentData* pData;
	ComponentCollection* pCollection;
};

struct ComponentInfo {
	Component* pComponent;
	Component* pEntry;
	DWORD dwFlags;
	char _0x000C[4];
};

struct GameEntity {
	char _0x0000[0x8];
	DWORD dwFlags;
	char _0x0008[0xC];
	DWORD dwUpdateInterval;
	ComponentCollection* pCollection;
};

struct OnlineID {
	ULONGLONG NativeData;
	char szID[0x18];
};

struct BitArray {
	void* pVtable;
	int* pBits;
	DWORD dwExternalBufferSize;
	DWORD dwBitCount;
	DWORD dwWordCount;
};

struct ClientSoldierReplication {
	char _0x0000[0x10];
	Vec3 ParachuteRotation;
	Vec3 Position;
	Vec3 SurfaceVelocity;
	Vec3 Velocity;
	Vec3 GroundNormal;
	DWORD dwGroundSupported;
	DWORD dwGroundMaterialIndex;
	int nState;
	int nPose; // 0 = standing, 1 = crouch, 2 = lay down
	int nChangingToPose;
	char _0x0001[0x4];
	float flGroundHeight;
	float flLadderHeightClimbed;
	float flLadderHeightLeft;
	char _0x0002[0x4];
	int nActionState;
};

struct DeltaState {
	Vec3 Position;
	Vec3 Velocity;
	Vec3 EyePosition;
};

struct ClientSoldierPrediction {
	char _0x0000[0x10];
	DeltaState CorrectionDelta;
	DeltaState FrameCorrectionDelta;
	Vec3 Velocity;
	float flCorrectionInterpolationTime;
	float flCorrectionInterpolationTimer;
	float flFrameInterpolationFactor;
	int nNoInterpolateNextCorrection;
};

struct QuatTransform {
	Vec3 TransAndScale;
	Vec3 Rotation;
};

struct Animatable {
	char _0x0000[0x18];
	QuatTransform* pLocalTransforms;
	QuatTransform* pWorldTransforms;
	LPD3DXMATRIX pRenderTransforms;
	QuatTransform* pInterpolatedLocalTransforms;
	QuatTransform* pInterpolatedWorldTransforms;
	QuatTransform* pActiveWorldTransforms;
	QuatTransform* pActiveLocalTransforms;
	int nSlot;
	int nReaderIndex;
	byte bValidTransforms;
};

struct ClientAntAnimatableComponent {
	char _0x0000[0xE4];
	Animatable* pAnimatable;
	char _0x00E8[4];
	DWORD dwAnimatableInstanceID;
	bool bHadVisualUpdate;
};

struct ClientSoldierHealthModule {};

struct AnimatedSoldierWeapon {};

struct WeaponState {
	AnimatedSoldierWeapon* pAnimation;
	char _0x0004[0x10];
	DWORD dwMeshVariationSet;
	DWORD dwMeshZoomVariationSet;
	DWORD dwMesh;
	DWORD dwMeshZoom;
	WORD wMeshInstanceHandle;
	WORD wMeshZoomInstanceHandle;
	DWORD dwProjectileBoneIndex;
};

struct WeaponShotModifier {
	char _0x0000[0x10];
	Vec3 InitialSpeed;
	int nNumberOfBulletsPerShell;
};

struct WeaponSuppressionData {
	char _0x0000[0x8];
	float flMaxMultiplier;
	float flMinMultiplier;
	float flMinDistance;
	float flMaxDistance;
};

struct MaterialContainerPair {
	DWORD dwFlagsAndIndex;
	char bPhysicsPropertyIndex;
	char bPhysicsMaterialIndex;
	char _0x0006[0x2];

	bool IsPenetrable() {
		// return (bool)(dwFlagsAndIndex & 0x80000000);
		return dwFlagsAndIndex & 0x1000000;
	};

	bool IsSeeThrough() {
		// return (bool)(dwFlagsAndIndex & 0x20000000);
		return dwFlagsAndIndex & 0x8000000;
	};

	bool IsClientDestructable() {
		// return (bool)(dwFlagsAndIndex & 0x40000000);
		return dwFlagsAndIndex & 0x2000000;
	};
};

struct ProjectileEntityData {
	char _0x0000[0x70];
	int nHitReactionWeaponType;
	float flInitialSpeed;
	float flTimeToLive;
	float flInitMeshHideTime;
	float flVisualConvergeDistance;
	float flUnknown;
	MaterialContainerPair* pMaterialPair;
	void* pExplosion;
	WeaponSuppressionData* pSuppressionData;
	char* pAmmunitionType;
	bool bServerProjectileDisabled;
	bool bDetonateOnTimeout;
	char _0x0001[0x2];
};

struct WeaponProjectileModifier {
	char _0x0000[0x8];
	ProjectileEntityData* pProjectileData;
};

struct WeaponMagazineModifier {
	char _0x0000[0x8];
	int nMagazineCapacity;
	int nNumberOfMagazines;
};

struct WeaponZoomModifier {
	char _0x0000[0x8];
	float flZoomRenderFov;
};

struct WeaponModifier {
	char _0x0000[0x34];
	SoldierWeaponUnlockAsset* pCurrentSoldierWeaponUnlockAsset;
	char _0x0038[0x70];
	bool bEnableBreathControl;
	bool bCanBeInSupportedShooting;
	bool bUnZoomOnBoltAction;
	bool bHoldBoltActionUntilZoomRelease;
	char _0x0001[0x4];
	void* pWeaponFiringDataModifier;
	void* pWeaponFiringEffectsModifier;
	void* pWeaponSoundModifier;
	WeaponShotModifier* pWeaponShotModifier;
	WeaponProjectileModifier* pWeaponProjectileModifier;
	void* pWeaponAimingSimulationModifier;
	void* pWeaponAimingConfigurationModifier;
	void* pWeaponAnimTypeModifier;
	WeaponMagazineModifier* pWeaponMagazineModifier; // 0xD0
	WeaponZoomModifier* pWeaponZoomModifier;
};

struct ZoomLevelData {
	float flFieldOfView;
	float flTimeYawMultiplier;
	float flLookSpeedMultiplier;
	float flSprintLookSpeedMultiplier;
	float flMoveSpeedMultiplier;
	float flSwayPitchMultiplier;
	float flSwayYawMultiplier;
	float flSupportedSwayPitchMultiplier;
	float flSupportedSwayYawMultiplier;
	float flTimePitchMultiplier;
	float flDispersionMultiplier;
	float flStartFadeToBlackAtTime;
	float flRecoilMultiplier;
	float flRecoilFovMultiplier;
	float flCameraImpulseMultiplier;
	int nOnActivateEventType;
	float flStartFadeFromBlackAtTime;
	float flFadeToBlackDuration;
	float flFadeFromBlackDuration;
	float flUnknown;
	bool bFadeToBlackInZoomTransition;
	bool bUseFovSpecialisation;
	bool bAllowFieldOfViewScaling;
};

struct SoldierAimingSimulationData {
	ZoomLevelData** pZoomLevels;
};

struct AimingConstraints {
	float flMinYaw;
	float flMaxYaw;
	float flMinPitch;
	float flMaxPitch;
	float flPitchOffset;
	float flYawOffset;
	float flMinYawDefault;
	float flMaxYawDefault;
};

struct AimAssist {
	void* pData;
	AimingConstraints* pAimingConstraints;
	DWORD dwLastZoomLevel;
	float flYaw;
	char _0x0010[0x8];
	float flPitch;
};

struct SoldierAimingEnvironment {
	ClientSoldierEntity* pSoldier;
	ClientControllableEntity* pTarget;
	bool bHasTarget;
	bool bHasFriendlyTarget;
	bool bHasChangedTarget;
	bool bHasStickBoxTarget;
	bool bHasSnapBoxTarget;
};

struct ClientSoldierAimingSimulation {
	SoldierAimingSimulationData* pData;
	SoldierAimingEnvironment* pEnvironment;
	AimAssist* pAimAssist;
	float flYaw;
	float flPitch;
	float flYawTimer;
	float flPitchTimer;
	float flSwayX;
	float flSwayY;
};

struct CtrRefBase {
	DWORD* pPtr;
};

struct ClientWeapon {};

struct ClientLockingController {};

struct BulletEntityData : ProjectileEntityData {
	char _0x0000[0x4];
	Vec3 InitialAngularVelocity;
	void* pTrailEffect;
	void* pMesh;
	float flMaxAttachableInclination;
	bool bExtraDamping;
	bool bIsAttachable;
	float flStamina;
	void* pFlyBySound;
	void* pDudExplosion;
	float flGravity;
	float flImpactImpulse;
	float flDetonationTimeVariation;
	float flVehicleDetonationRadius;
	float flVehicleDetonationActivationDelay;
	float flFlyBySoundRadius;
	float flFlyBySoundSpeed;
	float flFirstFrameTravelDistance;
	float flDistributeDamageOverTime;
	float flStartDamage;
	float flEndDamage;
	float flDamageFalloffStartDistance;
	float flDamageFalloffEndDistance;
	float flTimeToArmExplosion;
	bool bGasVehicleDetonation;
	bool bInstantHit;
	bool bStopTrailEffectOnUnspawn;
};

struct ShotConfigData {
	Vec3 InitialPosition;
	Vec3 InitialDirection;
	Vec3 InitialSpeed;
	float flInheritWeaponSpeedAmount;
	DWORD dwMuzzleExplosion;
	BulletEntityData* pProjectileData;
	BulletEntityData* pSecondaryProjectileData;
	CtrRefBase Projectile;
	CtrRefBase SecondaryProjectile;
	float flSpawnDelay;
	DWORD dwNumberOfBulletsPerShell;
	DWORD dwNumberOfBulletsPerShot;
	DWORD dwNumberOfBulletsPerBurst;
	char bRelativeTargetAiming;
	char bForceSpawnToCamera;
	char bSpawnVisualAtWeaponBone;
	char bActiveForceSpawnToCamera;
};

struct HoldAndReleaseData {
	float flMaxHoldTime;
	float flMinPowerModifier;
	float flMaxPowerModifier;
	float flPowerIncreasePerSecond;
	float flDelay;
	float flKilledHoldingPowerModifier;
	int nForceFireWhenKilledHolding;
};

struct BoltActionData {
	float flBoltActionDelay;
	float flBoltActionTime;
	char bHoldBoltActionUntilFireRelease;
	char bHoldBoltActionUntilZoomRelease;
	char bForceBoltActionOnFireTrigger;
	char bUnZoomOnBoltAction;
	char bReturnToZoomAfterBoltAction;
	char _0x0000[0x3];
};

struct RecoilData {
	float flMaxRecoilAngleX;
	float flMinRecoilAngleX;
	float flMaxRecoilAngleY;
	float flMinRecoilAngleY;
	float flMaxRecoilAngleZ;
	float flMinRecoilAngleZ;
	float flMaxRecoilFov;
	float flMinRecoilFov;
	int nRecoilFollowsDispersion;
};

struct FireLogicData {
	HoldAndReleaseData HoldAndRelease;
	BoltActionData BoltAction;
	RecoilData Recoil;
	int nFireInputAction;
	int nReloadInputAction;
	int nCycleFireModeInputAction;
	float flTriggerPullWeight;
	float flRateOfFire;
	float flRateOfFireForBurst;
	float flClientFireRateMultiplier;
	float flReloadDelay;
	int nFireLogicTypeArray;
	float flReloadThreshold;
	float flPreFireDelay;
	float flReloadTime;
	float flReloadTimeBulletsLeft;
	int nFireLogicType;
	int nReloadLogic;
	float flAutomaticDelay;
	int nReloadType;
	char bHoldOffReloadUntilZoomRelease;
	char bForceReloadActionOnFireTrigger;
	char bHoldOffReloadUntilFireRelease;
	char bAlwaysAutoReload;
};

struct FireEffectData {
	Vec3 Rotation;
	Vec3 Offset;
	Vec3 ZoomRotation;
	Vec3 ZoomOffset;
	int* nEffect;
	char bUseZoomOffset;
	char bUseZoomRotation;
	char bDisableDuringZoom;
	char bUpdateTransform;
	char bStopLoopingEffects;
	char _0x0000[0x3];
};

struct OverHeatData {
	float flHeatPerBullet;
	float flHeatDropPerSecond;
	float flOverHeatPenaltyTime;
	float flOverHeatThreshold;
	FireEffectData OverHeatEffect;
};

struct AmmoConfigData {
	int nMagazineCapacity;
	int nNumberOfMagazines;
	DWORD dwTraceFrequency;
	DWORD dwAmmoPickupMinAmount;
	DWORD dwAmmoPickupMaxAmount;
	float flAutoReplenishDelay;
	int nAmmoBagPickupAmount;
	float flAmmoBagPickupDelayMultiplier;
	int nAutoReplenishMagazine;
};

struct FiringFunctionData {
	char _0x0000[0x60];
	ShotConfigData Shot;
	char _0x0001[0x4];
	FireLogicData FireLogic;
	AmmoConfigData Ammo;
	char _0x0002[0x4];
	OverHeatData OverHeat;
	char _0x0003[0x4];
	float flSelfHealTimeWhenDeployed;
	float flAmmoCrateReloadDelay;
	char bUnlimitedAmmoForAI;
	char bUsePrimaryAmmo;
};

struct WeaponFiringData {
	char _0x000[0x8];
	FiringFunctionData* pPrimaryFire;
};

struct ClientWeaponFiringReplication {
	char _0x0000[0x8C];
	WeaponFiringData* pData;
};

struct Deviation {
	float flPitch;
	float flYaw;
	float flRoll;
	float flTransY;
};

struct Random {
	DWORD dwValue;
	DWORD dwTableIndex;
	float flNextNormal;
	bool bNextNormalIsValid;
};

struct WeaponSway {
	void* pVtable;
	char _0x0004[0xA8];
	Deviation CurrentRecoilDeviation;
	float flTimeSinceLastShot;
	DWORD dwCameraRecoilDeviation;
	float flSpringPos;
	float flSpringRestPos;
	float flSpringVelocity;
	D3DXMATRIX CameraRecoilTransform;
	Deviation CurrentLagDeviation;
	float flDispersionAngle;
	float flDeviationPitch;
	float flCrossHairDispersionFactor;
	Deviation CurrentDispersionDeviation;
	float flCurrentGameplayDeviationScaleFactor;
	float flCurrentVisualDeviationScaleFactor;
	float flSuppressionMinDispersionAngleFactor;
	Random Random;
	DWORD dwSeed;
	float flRandomAngle;
	float flRandomRadius;
	bool bFireShot;
	DWORD dwInitialFireShot;
	bool bIsFiring;
};

struct Function {
	char _0x0000[0x4];
	int nAmmoInClip;
	int nAmmoInReserve;
	int nNumberOfProjectilesToFire;
	bool bHasStoppedFiring;
	bool bPrimaryFireTriggeredLastFrame;
	bool bIsOverheated;
	char _0x0001[0x1];
	float flHeat;
	float flOverheatTimer;
	DWORD dwTicks;
	DWORD dwCurrentFireModeIndex;
	int nExternalMagazineCapacity;
};

struct WeaponFiring {
	char _0x0000[0x3C];
	WeaponSway* pWeaponSway_;
	char _0x0040[0x60];
	WeaponSway* pWeaponSway;
	eWeaponState pWeaponState;
	eWeaponState pLastWeaponState;
	eWeaponState pNextWeaponState;
	float flSwitchCooldownTimer;
	float flAutoReplenishTime;
	float flTimeToWait;
	float flStateData;
	float flHoldReleaseMinDelay;
	float flRecoilTimer;
	float flRecoilAngleX;
	float flRecoilAngleY;
	float flRecoilAngleZ;
	float flRecoilFovAngle;
	float flPrimaryAmmoReplenishDelay;
	float flReloadTimeMultiplier;
	float flOverheatDropMultiplier;
	int nPrimaryAmmoToFill;
	DWORD* pCharacterMeleeEntity;
	int nExternalPrimaryMagazineCapacity;
	Function PrimaryFire;
};

struct ClientSoldierWeapon : GameEntity {
	char _0x0020[0x8];
	WeaponState** pWeaponStates1p;
	char _0x00024[0xC];
	WeaponState** pWeaponStates3p;
	char _0x0034[0xC];
	DWORD** pSocketPointers;
	char _0x0044[0xC];
	WeaponModifier WeaponModifier;
	char m_0x00pad[0x10];
	void* pCameraLagEffect;
	ClientSoldierAimingSimulation* pAuthorativeAiming; // 0x144
	ClientAimingReplication* pReplicatedAiming;
	ClientLockingController* pLockingController;
	ClientLockingController* pSecondaryLockingController;
	ClientWeapon* pWeapon;
	ClientWeaponFiringReplication* pReplicatedFiring;
	void* pCorrectionCallbackHandler;
	WeaponFiring* pPredictedFiring;
	WeaponFiring* pCorrectedFiring;
	int nCompartment;
};

struct ClientAnimatedSoldierWeaponHandler {
	char _0x0000[0x14];
	ClientSoldierWeapon* pCurrentWeapon;
};

struct WeaponSwitching {
	void* pVtable;
	int nCurrentWeaponId;
	int nPreviousWeaponId;
	int nLastPrimary;
	int nWeaponCount;
	int nFireAndSwitchBackToPrevAction;
	float flWeaponSwitchTimer;
	float flSwitchBackToPrevMaxTimePressed;
	bool bPlayerSwitchedWeapons;
	bool bQuickSwitch;
	bool bAutomaticFire;
};

struct ClientWeaponSwayCallbackImpl {};

struct ClientSoldierWeaponsComponent {
	char _0x0000[0x70];
	D3DXMATRIX WeaponTransform;
	ClientAntAnimatableComponent* pAnimatableComponent[2];
	ClientSoldierEntity* pSoldier;
	ClientSoldierWeapon** pWeapons;
	char _0x0001[12];
	ClientAnimatedSoldierWeaponHandler* pCurrentAnimatedWeaponHandler;
	int nWeaponMeshWasEnabled;
	WeaponSwitching* pReplicatedWeaponSwitching;
	WeaponSwitching* pPredictedWeaponSwitching;
	ClientWeaponSwayCallbackImpl* pWeaponSwayCallback;
	int nHasOrHadLocalPlayer;
	SoldierAimingEnvironment* pAimingEnvironment;
	AimingConstraints* pSwimAimingConstraints;
	char _0x0002[0x64];
	int nOldZoomState;
	int nLastZoomLevel;
	float flTimeSinceLastShoot; // round to int for seconds
	bool bIsVisible;

	ClientSoldierWeapon* GetWeaponAtIndex(int index) {
		if (!pWeapons)
			return nullptr;
		return pWeapons[index];
	}
};

struct ClientSoldierBodyComponent {};

struct ClientBoneCollisionComponent {};

struct ClientRagdollComponent {};

struct ClientAimingReplication {
	void* pVtable;
	float flYaw;
	float flPitch;
	float flDeltaYaw;
	float flDeltaPitch;
	float flActivated;
};

struct BreathControlHandler {
	void* pData;
	float flBreathControlTimer;
	float flBreathControlMultiplier;
	float flBreathControlPenaltyTimer;
	float flBreathControlPenaltyMultiplier;
	BYTE bBreathControlActive;
};

struct SprintInputHandler {
	SprintInputHandlerState CurrentState;
	float flDoubleTapTimer;
	float flSprintReleaseTimer;
	int nWaitForSprintRelease;
};

struct PhysicsEntityBase {
	char _0x0000[0x38];
	HavokPhysicsManager* pManager;
};

struct CharacterEntity {
	virtual float GetYaw();
	virtual float GetPitch();
	virtual BOOL IsVisible();
	virtual BOOL IsAlive();
	virtual BOOL IsDead();
	virtual BOOL IsDying();
	virtual float GetHealth();
	virtual float GetMaxHealth();
	virtual BOOL IsAIPlayer();
	virtual BOOL IsSingleplayer();
	virtual void GetPhysicsInfoForAnimation(LPVOID, LPVOID);
	virtual BOOL IsInVehicle();
	virtual PhysicsEntityBase* GetPhysics();
	virtual CharacterPoseType GetPose();
	virtual PersonViewEnum GetActiveView();
};

struct ClientSoldierParachuteComponent {
	char _0x0000[0x4C];
	AimingConstraints* pAimingConstraints;
	char _0x0050[0x50];
	DWORD dwFlags; // 0 = on_ground, 7 = in_air, 4 = falling, 5 = parachuting

	bool IsInAir() {
		return dwFlags == 7;
	}

	bool IsParachuting() {
		return dwFlags == 5;
	}

	bool IsFalling() {
		return dwFlags == 4;
	}
};

struct ClientSoldierEntity {
	char _0x0001[0xB4];
	CharacterEntity pCharacter;
	ClientPlayer* pPlayer;
	ClientAntAnimatableComponent* pAnimatableComponent0;
	ClientAntAnimatableComponent* pAnimatableComponent1;
	char _0x00C4[388];
	ClientSoldierPrediction* pPredictedController;
	ClientSoldierReplication* pReplicatedController;
	char _0x0003[0x104];
	ClientSoldierHealthModule* pHealthModule; // 0x354
	float flDeathTimer;
	ClientSoldierWeaponsComponent* pSoldierWeaponsComponent;
	ClientSoldierBodyComponent* pBodyComponent;
	ClientBoneCollisionComponent* pBoneCollisionComponent;
	ClientRagdollComponent* pRagdollComponent;
	ClientAimingReplication* pReplicatedAiming;
	BreathControlHandler* pBreathControlHandler;
	SprintInputHandler* pSprintInputHandler;
	int nSprintInterruptAction;
	float flSprintRecoveryTimer;
	bool bWasSprinting;
	bool bIsOccluded;

	ClientSoldierParachuteComponent* GetClientSoldierParachiteComponent() {
		return (ClientSoldierParachuteComponent*)*(DWORD*)((DWORD)this + 0x400);
	}

	ClientSoldierWeapon* GetSoldierWeapon() {
		if (ValidPtr(pSoldierWeaponsComponent)) {
			if (ValidPtr(pSoldierWeaponsComponent->pCurrentAnimatedWeaponHandler)) {
				return pSoldierWeaponsComponent->pCurrentAnimatedWeaponHandler->pCurrentWeapon;
			}
		}
		return nullptr;
	}

	bool IsVisible() {
		return !bIsOccluded;
	}
};

struct ClientCharacterEntity {};

struct ClientSpottingTargetComponent {
	char _0x0000[0x18];
	int nSpotType;
	ClientPlayer* pSpotterPlayer;
	ClientPlayer* pPlayerThatOrders;
	float flLastOrderTime;
};

struct ClientControllableEntity {
	ClientSpottingTargetComponent* GetClientSpottingTargetComponent(bool unk) {
		return ((ClientSpottingTargetComponent*(*)(ClientControllableEntity*, bool))0x8340C818)(this, unk);
	}
};

struct ClientPlayerName {
	char szName[0x10];
};

struct ClientVehicleEntity {};

struct CustomizationUnlockParts {
	char _0x0000[0x10];
	DWORD** pVisualAssets;
};

struct CustomizationTable {
	void* pVtable;
	DWORD dwRef;
	CustomizationUnlockParts** pParts;
};

struct Asset {
	DWORD dwVTable;
};

struct VeniceSoldierCustomizationAsset {
	char _0x0000[0x18];
	CustomizationTable* pWeaponTable;
	Asset* pAsset[1000];
};

struct ClientPlayer {
	char _0x0000[0x10];
	ClientPlayerName* pNamePtr;
	char _0x0014[0xC];
	OnlineID OnlineID_;
	OnlineID GroupID;
	OnlineID ClubID;
	int nTeamPreference;
	char pad[0x298];
	int nTeam; // 0x31C
	char _0x0320[0x88];
	BitArray UnlocksBitArray; // 0x14 in size
	int nRefCount;
	ClientSoldierEntity* pSoldier;
	ClientSoldierEntity* pCorpse;
	ClientCharacterEntity* pCharacter;
	DWORD dwWeakTokenHolderToken;
	ClientControllableEntity* pAttachedControllable;
	DWORD dwAttachedEntryId;
	ClientControllableEntity* pControlledControllable; // 0x3D8
	DWORD dwControlledEntryId;
	char _0x03E0[0xC];
	int nID;
	char _0x03F0[0x7C];
	int nSquadId; // 0x46c
	bool bIsSquadLeader;
	bool bIsSquadPrivate;
	bool bIsAllowedToSpawnOn;
	bool bIsAdmin;

	bool IsAlive() {
		return pCorpse == nullptr;
	}

	bool InVehicle() {
		return pAttachedControllable != nullptr;
	}

	ClientVehicleEntity *GetVehicleEntity() {
		if (InVehicle())
			return (ClientVehicleEntity*)pAttachedControllable;
		return nullptr;
	}

	ClientSoldierEntity* GetClientSoldier() {
		return (ClientSoldierEntity*)pControlledControllable;
	}

	VeniceSoldierCustomizationAsset* GetVeniceSoldierCustomizationAsset() {
		return (VeniceSoldierCustomizationAsset*)*(DWORD*)((DWORD)this + 0x90);
	}
};

struct ClientPlayerManager {
	char _0x0000[0x8];
	int nMaxPlayers;
	char _0x000C[0xB0];
	ClientPlayer* pLocalPlayer;
	ClientPlayer** pPlayerMap;

	ClientPlayer* GetPlayer(int index) {
		return pPlayerMap[index];
	}
};

struct ClientSettings {};

struct InputCache {
	bool bDisableCache;
	char _0x0001[0x3];
	float bInputBuffer[0x7B];
	float bJuiceConceptCache[0x7B];
	float bPrevJuiceConceptCache[0x7B];
};

struct BorderInputNode {
	void* pVtable;
	char _0x0004[4];
	InputCache* pInputCache;
};

struct VegetationSystemSettings {
	void* pVtable;
	char _0x0004[4];
	float flWindVariation;
	float flWindVariationRate;
	float flWindStrength;
	float flJointTentionLimit;
	int nForceShadowLod;
	int nMaxPreSimsPerJob;
	int nSimulationMemKbServer;
	float flMaxActiveDistance;
	int nSimulationMemKbClient;
	float flTimeScale;
	int nJobCount;
	int nJointTentionLimitIndex;
	bool bSimulateServerSide;
	bool bLocalInfluenceEnable;
	bool bUseShadowLodOffset;
	bool bDestructionEnabled;
	bool bEnableJobs;
	bool bEnable;
	bool bDrawNodes;
	bool bBatchDrawEnable;
	bool bDrawEnable;
	bool bDissolveEnable;
	bool bShadowMeshEnable;
};

struct VegetationManager {
	char _0x0000[0x310];
	VegetationSystemSettings* pVegetationSystemSettings;
};

struct RayCastHit {
	Vec3 Position;
	Vec3 Normal;
	void* pRigidBody;
	MaterialContainerPair* pMaterial;
	DWORD dwPart;
	int nBone;
	float flLambda;
	char _0x0001[0xC];
};

struct SafeQueryResult {
	void* pQueryResult;
};

struct IPhysicsRayCaster {
	virtual bool PhysicsRayQuery(char* text, Vec3 *from, Vec3 *to, RayCastHit *hit, int flag, void* PhysicsEntityList);
	virtual SafeQueryResult* AsyncPhysicsRayQuery(const char *ident, Vec3 *from, Vec3 *to, unsigned int flags, void* excluded);
};

struct HavokPhysicsManager {
	char _0x0000[0x40];
	IPhysicsRayCaster* pRayCaster;
};

struct EntityCreator {
	enum RayCastTest {
		RCTDetailed = 0,
		RCTCollision
	};

	void* pVTable;
	EntityCreator* pPreviousCreator;
	EntityCreator* pNextCreator;
	int nRealm;
	int nLinked;
};

struct EntityCollectionSegment {
	Vector Collections;
	void* pSubLevel;
	EntityCollectionSegment* pPrevious;
	EntityCollectionSegment* pNext;
	DWORD dwIterableSize;
	DWORD dwCollectonIndex;
};

struct EntityCollection {
	EntityCollectionSegment* pFirstSegment;
	EntityCreator* pCreator;
};

struct GameWorld {
	char _0x0000[0x820];
	Vector Collections;
};

struct LevelSetup {
	char _0x0000[0x4];
	const char* pGameType;
};

struct ClientLevel {
	char _0x0000[0x68];
	const char* pLevelName;
	LevelSetup* pLevelSetup;
	char _0x0070[0x2C];
	void* pDebrisManager;
	char _0x0001[0x4];
	VegetationManager* pVegetationManager;
	char _0x00A4[0x14];
	HavokPhysicsManager* pPhysicsManager;
	GameWorld* pGameWorld;
	void* pClientLevelTweaker;
	bool bIsFinalized;
	bool bHasStartedServer;
	bool bAutoRespawn;

	// 0x68 = char* pLevelName
	// 0x6C = ptr, +4 inside ptr = char* pGameType
};

struct Client {
	char _0x0000[0xC];
	ClientGameContext* pGameContext;
	char _0x0010[0x4];
	ClientSettings* pClientSettings;
	char _0x0014[0x4];
	ClientPlayerManager* pClientPlayerManager;
	char _0x0018[0x10];
	BorderInputNode* pInputNode;
	char _0x000pad[0x4];
	ClientLevel* pClientLevel; 
	char _0x003C[0x19C];
	ClientGameType GameType;
	bool bQuit; // set to 1 will go to dash
};

struct OnlineManager {
	char _0x0000[0x4];
	Client* pGame;
	bool bIsSinglePlayer;
	bool bLocalhost;
	char _0x0001[10];
	void* pServerConnection;
	void* pConnection;
};

struct ClientPlayerScore {
	char _0x0000[0x148];
	int	nRank;
	int nKills;
	int	nDeaths;
	int	nScore;
	int	nGlobalScoreOrginal;
	int	nGlobalScoreUpdated;
	int	nVeteran;
	float flTime;
};

struct ClientPlayerScoreManager {
	ClientPlayerScore* GetPlayerScore(ClientPlayer* player) {
		return ((ClientPlayerScore*(*)(ClientPlayerScoreManager*, ClientPlayer*))0x83212338)(this, player);
	}
};

struct ClientGameContext {
	char _0x0000[0x30];
	ClientPlayerManager* pClientPlayerManager;
	OnlineManager* pOnlineManager;
	DWORD* pGameView;
	DWORD* pInterpolationManager;
	ClientPlayerScoreManager* pClientPlayerScoreManager;
	Client* pClient;
};

struct GameRenderViewParams {
	D3DXMATRIX Transform;
	int nType;
	char _0x0044[4];
	float flFovY;
	float flDefaultFovY;
	float flNearPlane;
	float flFarPlane;
	float flAspect;
	float flOrthoWidth;
	float flOrthoHeight;
	char _0x0002[0x41C];
	D3DXMATRIX ViewMatrixInverse;
	D3DXMATRIX ProjectionMatrix;
	D3DXMATRIX ViewMatrixAtOrigin;
	D3DXMATRIX ProjectionMatrixTranspose;
	D3DXMATRIX ProjectionMatrixInverse;
	D3DXMATRIX ViewProjectionMatrix;
	D3DXMATRIX ViewProjectionMatrixTranspose;
	D3DXMATRIX ViewProjectionMatrixInverse;

	void Update() {
		((void(*)(GameRenderViewParams*, DWORD))0x8316CEE0)(this, 0);
	}
};

struct GameRenderer {
	char _0x0000[0x20];
	GameRenderViewParams ViewParams;
};

struct ITypedObject {
	virtual TypeInfo* GetType();
};

struct Message : ITypedObject {
	//char _0x0000[0x4];
	int nCategory;
	int nType;
	const char* pSenderCallstack;
	long double DispatchTime;
	Message* pNext;
	int nPostedAtProcessMessageCounter;
	bool bOwnedByMessageManager;
};

struct ClientWeaponPlayerPrimaryWeaponFireMessage : Message {
	ClientPlayer* pShooter;
};

struct ClientDamageInfo {
	char _0x0000[0x50];
};

struct SoldierWeaponUnlockAsset {
	char _0x0000[0x8];
	const char* pFullName;
	char _0x000C[0x8];
	const char* pName;
};

struct ClientDamageGiverInfo {
	ClientPlayer* pDamageGiver;
	SoldierWeaponUnlockAsset* pWeaponUnlockAsset;
};

struct DamageData {
	int nVictimPlayerId;
	int nVictimInstanceId;
	int nInflictorPlayerId;
	int nHitType; // 1 = headshot
	SoldierWeaponUnlockAsset* pWeaponUnlockAsset;
	Vec3 Direction;
	float flDamage;
	bool bClientAiKilled;
	char bId;
};

struct ServerAdminBanPlayerMessage : Message {
	const char* pPlayerName;
	OnlineID* pOnlineID;
};

struct UIPopupButton {
	UIInputAction InputConcept;
	char* pLabel;
};

struct UIPopupTextInput {
	char* pId;
	char* pLabel;
	char* pDefaultValue;
	bool bIsPassword;
};

struct UIPopupShowMessage : Message {
	UIPopupType PopupType;
	char* pTitle;
	char* pDesc;
	void* Buttons;
	void* TextInputs;
	void* pResponseHandler;
	void* pUserData;
	DWORD dwId;
};

struct NetworkableMessage : Message {
	void* pServerConnection;
	void* pClientConnection;
	DWORD* pSyncObject;
	int nValidationResult;
};

struct EntryInputState {
	// 0x1F8 = dwCustomBits
	// 0x204 = angles
	// 0x220 = vault position
	char _0x0000[0x10];
	float fAnalogInput[10];
	char _0x0001[0x1B0];
	DWORD dwCustomBitFlags;
	char _0x01EC[0x8];
	Vec2 AuthoritiveViewAngles;
	char _0x01FC[0x24];
	Vec3 VaultPosition;
};

struct EntryInputStateNetworkMove {
	char _0x0000[0x10];
	EntryInputState State;
};

struct UINetworkTextInfo {
	char* m_stringId;
	float m_displayTime;
};

struct UINetworkPlayerKillsTextMessage : NetworkableMessage {
	UINetworkTextInfo TextInfo;
	DWORD dwKillerID;
	DWORD dwVictimID;
	bool bHeadshot;
	int iWeaponType;
	CtrRefBase WeaponUnlock;
	CtrRefBase VehicleData;
};

struct UINetworkOwnPlayerKilledMessage : NetworkableMessage {
	void* pServerKiller;
	ClientPlayer* pClientKiller;
	int iWeaponType;
	CtrRefBase WeaponUnlock;
	CtrRefBase VehicleData;
	bool bHeadshot;
	DWORD dwOwnKillCount;
	DWORD dwKillerKillCount;
	unsigned __int16 KillerBasicDogTag;
	unsigned __int16 KillerAdvancedDogTag;
	float fKillerAdvancedDogTagStat;
	DWORD dwKillerWeaponKills;
	DWORD dwKillerHealth;
};

struct UINetworkKilledOtherPlayerMessage : NetworkableMessage {
	void* pServerVictim;
	ClientPlayer* pClientVictim;
	int iWeaponType;
	CtrRefBase WeaponUnlock;
	CtrRefBase VehicleData;
	bool bHeadshot;
	DWORD dwOwnKillCount;
	DWORD dwVictimKillCount;
};

template<typename T>
struct StringBuilderBaseImpl {
	T* pBuffer;
	T* pPos;
	T* pMax;
};

struct ExtendableWideStringBuilder : StringBuilderBaseImpl<wchar_t> {
	wchar_t szBuffer[128];
};

struct NetworkChatMessage {
	wchar_t* pBuffer;
	wchar_t* pPos;
	wchar_t* pMax;
	wchar_t szBuffer[128];

	DWORD dwPlayerID;
	unsigned __int64 RecipientMask;
	DWORD dwChannelID;
	bool bSenderIsDead;
};

struct SyncedBFSettings {
	char _0x0000[0xC];
	float fGameModeCounterModifier;
	bool bAllUnlocksUnlocked;
	bool bHideMinimap;
	bool bHideHUD;
	bool bNoMinimapSpotting;
	bool bNo3DSpotting;
	bool bNoNameTags;
	bool bOnlySquadLeaderSpawn;
	bool bTeamSwitchingAllowed;
	bool bRevertBackToKillerCamera;
	bool bDisableHitIndicators;
	bool bDisableVehicleCommanderActions;
	bool bIsCompetitive;
	bool bCommanderEnabled;
	bool bFieldUpgradeSystemActive;
	bool bNotifyServerWhenIgnoringDamage;
	bool bForceCrashWhenIgnoringDamage;
};

struct Compartment {
	char _0x0000[0xE8];
	DWORD dwPtrToFirstList;
	DWORD dwPtrToEndList;
};

struct ResourceManager {
	DWORD dwBundleLoadInProgress;
	Compartment* pCompartments[50];
};

struct AxisAlignedBox {
	Vec3 Min;
	Vec3 Max;

	AxisAlignedBox() {}
};

struct LinearTransform {
	Vec3 left;
	Vec3 up;
	Vec3 forward;
	Vec3 trans;
};

struct EntityVirtual {
	virtual TypeInfo* GetTypeInfo();
	virtual void func1();
	virtual void func2();
	virtual void func3();
	virtual void func4();
	virtual void func5();
	virtual void func6();
	virtual void func7();
	virtual void func8();
	virtual void func9();
	virtual void func10();
	virtual void func11();
	virtual void func12();
	virtual void func13();
	virtual void func14();
	virtual void func15();
	virtual void func16();
	virtual void func17();
	virtual void func18();
	virtual void func19();
	virtual void GetTransform(D3DXMATRIX* pMatrix);
	virtual void SetTransform(D3DXMATRIX* pMatrix);
	virtual void ComputeBoundingBoxWorldTransform(D3DXMATRIX* pMatrix);
	virtual void ComputeBoundingBox(AxisAlignedBox* pAxisAlignedBox);
};