#include "stdafx.h"
#include "NightmareAnimation.h"

NightmareAnimation::NightmareAnimation()
{
	//ƒAƒjƒ[ƒVƒ‡ƒ“ƒ[ƒhB
	//‘Ò‹@‚P
	animClip[enIdle01].Load("Assets/animData/DragonNightmare/Nm_idle01.tka");
	animClip[enIdle01].SetLoopFlag(true);
	//‘Ò‹@‚Q
	animClip[enIdle02].Load("Assets/animData/DragonNightmare/Nm_idle02.tka");
	animClip[enIdle02].SetLoopFlag(true);
	//•à‚«
	animClip[enWalk].Load("Assets/animData/DragonNightmare/Nm_walk.tka");
	animClip[enWalk].SetLoopFlag(true);
	//Œã‚ë•à‚«
	animClip[enWalkBack].Load("Assets/animData/DragonNightmare/Nm_walkback.tka");
	animClip[enWalkBack].SetLoopFlag(true);
	//¶•à‚«
	animClip[enWalkLeft].Load("Assets/animData/DragonNightmare/Nm_walkleft.tka");
	animClip[enWalkLeft].SetLoopFlag(true);
	//‰E•à‚«
	animClip[enWalkRight].Load("Assets/animData/DragonNightmare/Nm_walkright.tka");
	animClip[enWalkRight].SetLoopFlag(true);
	//‘–‚è
	animClip[enRun].Load("Assets/animData/DragonNightmare/Nm_run.tka");
	animClip[enRun].SetLoopFlag(true);
	//™ôšK
	animClip[enScream].Load("Assets/animData/DragonNightmare/Nm_scream.tka");
	//ƒWƒƒƒ“ƒv
	animClip[enJump].Load("Assets/animData/DragonNightmare/Nm_jump.tka");
	//’ÊíUŒ‚
	animClip[enBasicAttack].Load("Assets/animData/DragonNightmare/Nm_basicattack.tka");
	//’ÜUŒ‚
	animClip[enClawAttack].Load("Assets/animData/DragonNightmare/Nm_clawattack.tka");
	//ŠpUŒ‚
	animClip[enHornAttack].Load("Assets/animData/DragonNightmare/Nm_hornattack.tka");
	//”íƒ_ƒ
	animClip[enGetHit].Load("Assets/animData/DragonNightmare/Nm_gethit.tka");
	//–hŒä
	animClip[enDefend].Load("Assets/animData/DragonNightmare/Nm_defend.tka");
	//‡–°
	animClip[enSleep].Load("Assets/animData/DragonNightmare/Nm_sleep.tka");
	animClip[enSleep].SetLoopFlag(true);
	//€–S
	animClip[enDie].Load("Assets/animData/DragonNightmare/Nm_die.tka");
}

NightmareAnimation::~NightmareAnimation()
{

}

bool NightmareAnimation::Start()
{
	return true;
}

void NightmareAnimation::Update()
{

}