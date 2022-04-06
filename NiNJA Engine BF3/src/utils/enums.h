#pragma once

enum WeaponSlot {
	M_PRIMARY = 0,
	M_SECONDARY = 1,
	M_GADGET = 2,
	M_GADGET_2 = 5,
	M_GRENADE = 6,
	M_KNIFE = 7
};

enum ESPTypes {
	ESP_Off,
	ESP_Friendly,
	ESP_Enemy,
	ESP_Both
};

enum ScrollOptionType {
	SCROLL,
	SELECT,
	TOGGLE,
	SCROLLSELECT
};

enum Justification {
	JustifyLeft,
	JustifyCenter,
	JustifyRight
};

enum ChatChannelType {
	CctSayAll = 0,
	CctTeam = 1,
	CctSquad = 2,
	CctSquadLeader = 3,
	CctAdmin = 4,
	CctGame = 5,
	CctSize = 6
};

enum UIInputAction {
	UIInputAction_NavigateUp = 0x0,
	UIInputAction_NavigateDown = 0x1,
	UIInputAction_NavigateLeft = 0x2,
	UIInputAction_NavigateRight = 0x3,
	UIInputAction_TabLeft = 0x4,
	UIInputAction_TabRight = 0x5,
	UIInputAction_Activate = 0x6,
	UIInputAction_Deactivate = 0x7,
	UIInputAction_Menu = 0x8,
	UIInputAction_Cancel = 0x9,
	UIInputAction_OK = 0xA,
	UIInputAction_Back = 0xB,
	UIInputAction_Tab = 0xC,
	UIInputAction_Edit = 0xD,
	UIInputAction_View = 0xE,
	UIInputAction_LThumb = 0xF,
	UIInputAction_RThumb = 0x10,
	UIInputAction_MapZoom = 0x11,
	UIInputAction_MapSize = 0x12,
	UIInputAction_SayAllChat = 0x13,
	UIInputAction_TeamChat = 0x14,
	UIInputAction_SquadChat = 0x15,
	UIInputAction_Size = 0x16,
	UIInputAction_None = 0x17,
};

enum UIPopupType {
	PopupType_MemCard = 0x0,
	PopupType_ControllerDisconnected = 0x1,
	PopupType_Login = 0x2,
	PopupType_TermsOfService = 0x3,
	PopupType_PrivacyPolicy = 0x4,
	PopupType_RevivePrompt = 0x5,
	PopupType_Generic = 0x6,
	PopupType_ServerReminder = 0x7,
	PopupType_Error = 0x8,
	PopupType_ManagePlayer = 0x9,
	PopupType_Invalid = 0xA,
	PopupType_IngamePlayer = 0xB,
	PopupType_OnlinePass = 0xC,
	PopupType_Origin = 0xD,
};

enum Alignment {
	Alignment_BaseLine,
	Alignment_Right,
	Alignment_Left
};

enum RayCastFlags {
	CheckDetailMesh = 0x1,
	IsAsyncRaycast = 0x2,
	DontCheckWater = 0x4,
	DontCheckTerrain = 0x8,
	DontCheckRagdoll = 0x10,
	DontCheckCharacter = 0x20,
	DontCheckGroup = 0x40,
	DontCheckPhantoms = 0x80
};

enum VAlignment {
	VAlignment_None,
	VAlignment_Top,
	VAlignment_Bottom,
	VAlignment_Center
};

enum FontStyle {
	FontStyle_BelowNormal,
	FontStyle_Normal, // bold
	FontStyle_AboveNormal // italic
};

enum ClientGameType {
	ClientGameType_SinglePlayer,
	ClientGameType_Hosted,
	ClientGameType_Joined
};

enum CharacterPoseType {
	CharacterPoseType_Stand,
	CharacterPoseType_Crouch,
	CharacterPoseType_Prone
};

enum PersonViewEnum {
	PersonView_FirstPerson,
	PersonView_ThirdPerson
};

enum eWeaponState {
	eWeaponState_Deploy,
	eWeaponState_AltDeploy,
	eWeaponState_TriggerReleaseWait,
	eWeaponState_NoTrigger,
	eWeaponState_PreFireDelay,
	eWeaponState_PrimarySingleDelay,
	eWeaponState_PrimarySingle,
	eWeaponState_BoltActionDelay,
	eWeaponState_BoltAction,
	eWeaponState_PrimaryAutomaticFire,
	eWeaponState_ReloadDelay,
	eWeaponState_Reload,
	eWeaponState_PostReload,
	eWeaponState_PrimaryHoldAndRelease_Hold,
	eWeaponState_PrimaryHoldAndRelease_ReleaseDelay,
	eWeaponState_PrimaryHoldAndRelease_Release
};

enum SprintInputHandlerState {
	SprintInputHandlerState_WaitForward,
	SprintInputHandlerState_WaitReleaseForward,
	SprintInputHandlerState_DoubleTapSprint,
	SprintInputHandlerState_ButtonSprint,
	SprintInputHandlerState_WaitReleaseButtonSprint,
	SprintInputHandlerState_PostSprint
};

enum OrderType {
	OrderType_None,
	OrderType_RequestHeal,
	OrderType_LetMeHeal,
	OrderType_RequestAmmo,
	OrderType_LetMeGiveAmmo,
	OrderType_LetMeRepair,
	OrderType_RequestRide,
	OrderType_GoGoGo,
	OrderType_FollowMe,
	OrderType_Negative,
	OrderType_Sorry,
	OrderType_ThankYou,
	OrderType_RogerThat,
	OrderType_NeedBackup
};

enum FilterModes {
	FilterModes_Blur = 1,
	FilterModes_Shadow = 2,
	FilterModes_Highlight = 4,
	FilterModes_Knockout = 0x100,
	FilterModes_Inner = 0x200,
	FilterModes_HideObject = 0x400,
	FilterModes_UserModes = 0xFFFF,
	FilterModes_SkipLastPass = 0x10000,
	FilterModes_LastPassOnly = 0x20000
};

enum PlayerBones {
	Reference, //0
	AITrajectory, //1
	Trajectory, //2
	TrajectoryEnd, //3
	Hips, //4
	Spine, //5
	Spine1, //6
	Spine2, //7
	LeftShoulder, //8
	LeftArm, //9
	LeftArmRoll, //10
	LeftForeArm, //11
	LeftForeArmRoll, //12
	LeftForeArmRoll1, //13
	LeftHand, //14
	LeftHandMiddle0, //15
	LeftHandMiddle1, //16
	LeftHandMiddle2, //17
	LeftHandMiddle3, //18
	LeftHandMiddle4, //19
	LeftHandRing0, //20
	LeftHandRing1, //21
	LeftHandRing2, //22
	LeftHandRing3, //23
	LeftHandRing4, //24
	LeftHandPinky0, //25
	LeftHandPinky1, //26
	LeftHandPinky2, //27
	LeftHandPinky3, //28
	LeftHandPinky4, //29
	LeftHandIndex0, //30
	LeftHandIndex1, //31
	LeftHandIndex2, //32
	LeftHandIndex3, //33
	LeftHandIndex4, //34
	LeftHandThumb1, //35
	LeftHandThumb2, //36
	LeftHandThumb3, //37
	LeftHandThumb4, //38
	LeftForeArmCloth, //39
	LeftElbowRoll, //40
	LeftArmCloth, //41
	LeftShoulderPhys1, //42
	Neck, //43
	Neck1, //44
	Head, //45
	HeadEnd, //46
	Face, //47
	Offset_Jaw, //48
	Jaw, //49
	Offset_LeftLowerLip, //50
	LeftLowerLip, //51
	Offset_LowerLip, //52
	LowerLip, //53
	Offset_RightLowerLip, //54
	RightLowerLip, //55
	Offset_Tongue, //56
	Tongue, //57
	Offset_TongueTip, //58
	TongueTip, //59
	Offset_Chin, //60
	Chin, //61
	Offset_LeftEye, //62
	LeftEye, //63
	Offset_RightEye, //64
	RightEye, //65
	Offset_LeftUpCheek, //66
	LeftUpCheek, //67
	Offset_LeftUpInnerCheek, //68
	LeftUpInnerCheek, //69
	Offset_RightUpInnerCheek, //70
	RightUpInnerCheek, //71
	Offset_RightUpCheek, //72
	RightUpCheek, //73
	Offset_LeftCheek, //74
	LeftCheek, //75
	Offset_RightCheek, //76
	RightCheek, //77
	Offset_LeftMouth, //78
	LeftMouth, //79
	Offset_LeftUpperLip, //80
	LeftUpperLip, //81
	Offset_UpperLip, //82
	UpperLip, //83
	Offset_RightUpperLip, //84
	RightUpperLip, //85
	Offset_RightMouth, //86
	RightMouth, //87
	Offset_LeftUpEyelid, //88
	LeftUpEyelid, //89
	Offset_RightUpEyelid, //90
	RightUpEyelid, //91
	Offset_LeftLowEyelid, //92
	LeftLowEyelid, //93
	Offset_RightLowEyelid, //94
	RightLowEyelid, //95
	Offset_LeftInnerEyebrow, //96
	LeftInnerEyebrow, //97
	Offset_LeftOuterEyebrow, //98
	LeftOuterEyebrow, //99
	Offset_RightInnerEyebrow, //100
	RightInnerEyebrow, //101
	Offset_RightOuterEyebrow, //102
	RightOuterEyebrow, //103
	Offset_LeftNose, //104
	LeftNose, //105
	Offset_RightNose, //106
	RightNose, //107
	Offset_LeftCrease, //108
	LeftCrease, //109
	Offset_RightCrease, //110
	RightCrease, //111
	Offset_LeftMiddleEyebrow, //112
	LeftMiddleEyebrow, //113
	Offset_RightMiddleEyebrow, //114
	RightMiddleEyebrow, //115
	HeadCloth, //116
	Throat, //117
	Spine2Phys1, //118
	Spine2Cloth, //119
	RightShoulder, //120
	RightArm, //121
	RightArmRoll, //122
	RightForeArm, //123
	RightForeArmRoll, //124
	RightForeArmRoll1, //125
	RightHand, //126
	RightHandMiddle0, //127
	RightHandMiddle1, //128
	RightHandMiddle2, //129
	RightHandMiddle3, //130
	RightHandMiddle4, //131
	RightHandRing0, //132
	RightHandRing1, //133
	RightHandRing2, //134
	RightHandRing3, //135
	RightHandRing4, //136
	RightHandPinky0, //137
	RightHandPinky1, //138
	RightHandPinky2, //139
	RightHandPinky3, //140
	RightHandPinky4, //141
	RightHandIndex0, //142
	RightHandIndex1, //143
	RightHandIndex2, //144
	RightHandIndex3, //145
	RightHandIndex4, //146
	RightHandThumb1, //147
	RightHandThumb2, //148
	RightHandThumb3, //149
	RightHandThumb4, //150
	RightForeArmCloth, //151
	RightElbowRoll, //152
	RightArmCloth, //153
	RightShoulderPhys1, //154
	Wep_Root, //155
	Wep_Extra1, //156
	Wep_Trigger, //157
	Wep_Slide, //158
	Wep_Grenade1, //159
	Wep_Grenade2, //160
	Wep_Mag, //161
	Wep_Mag_Ammo, //162
	Wep_Physic1, //163
	Wep_Physic2, //164
	Wep_Physic3, //165
	Wep_Belt1, //166
	Wep_Belt2, //167
	Wep_Belt3, //168
	Wep_Belt4, //169
	Wep_Belt5, //170
	Wep_Bipod1, //171
	Wep_Bipod2, //172
	Wep_Bipod3, //173
	IK_Joint_LeftHand, //174
	IK_Joint_RightHand, //175
	Wep_Extra2, //176
	Wep_Extra3, //177
	Wep_Aim, //178
	LeftSpine1Phys1, //179
	RightSpine1Phys1, //180
	LeftUpLeg, //181
	LeftUpLegRoll, //182
	LeftLeg, //183
	LeftFoot, //184
	LeftToeBase, //185
	LeftToe, //186
	LeftLegCloth, //187
	LeftKneeRoll, //188
	LeftHipsRoll, //189
	LeftUpLegCloth, //190
	HipsCenterPhys, //191
	HipsCloth, //192
	LeftHipsFrontPhys, //193
	LeftHipsBackPhys, //194
	LeftHipsSidePhys, //195
	RightUpLeg, //196
	RightUpLegRoll, //197
	RightLeg, //198
	RightFoot, //199
	RightToeBase, //200
	RightToe, //201
	RightLegCloth, //202
	RightKneeRoll, //203
	RightHipsRoll, //204
	RightUpLegCloth, //205
	RightHipsFrontPhys, //206
	RightHipsBackPhys, //207
	RightHipsSidePhys, //208
	CameraBase, //209
	CameraJoint, //210
	Connect, //211
	ConnectEnd, //212
	totalBones
};