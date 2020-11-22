#include "stdafx.h"
#include "PlayerAnimation.h"



PlayerAnimation::PlayerAnimation()
{
	animClip[enStay_blad].Load("Assets/animData/player/blad/stay_01.tka");
	animClip[enStay_sword].Load("Assets/animData/player/sword/stay_02.tka");
	animClip[enChange_blad].Load("Assets/animData/player/blad/change_01.tka");
	animClip[enChange_sword].Load("Assets/animData/player/sword/change_02.tka");
	animClip[enWalk_sword].Load("Assets/animData/player/sword/walk_02.tka");
	animClip[enRun_sword].Load("Assets/animData/player/sword/run_02.tka");

	animClip[enJumpStart_sword].Load("Assets/animData/player/sword/jumpStart_02.tka");
	animClip[enStayInTheAir_sword].Load("Assets/animData/player/sword/stayInTheAir_02.tka");
	animClip[enJumpEnd_sword].Load("Assets/animData/player/sword/jumpEnd_02.tka");

	animClip[enStay_blad].SetLoopFlag(true);
	animClip[enStay_sword].SetLoopFlag(true);
	animClip[enChange_blad].SetLoopFlag(true);
	animClip[enChange_sword].SetLoopFlag(true);
	animClip[enWalk_sword].SetLoopFlag(true);
	animClip[enRun_sword].SetLoopFlag(true);

	animClip[enJumpStart_sword].SetLoopFlag(true);
	animClip[enStayInTheAir_sword].SetLoopFlag(true);
	animClip[enJumpEnd_sword].SetLoopFlag(true);
}


PlayerAnimation::~PlayerAnimation()
{
}

bool PlayerAnimation::Start()
{
	return true;
}

void PlayerAnimation::Update()
{

}