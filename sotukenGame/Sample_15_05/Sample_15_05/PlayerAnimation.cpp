#include "stdafx.h"
#include "PlayerAnimation.h"



PlayerAnimation::PlayerAnimation()
{
	//アニメーションロード。
	//プレイヤーのスキンモデルを初期化するより先にロードしたいから、
	//コンストラクタでロードする。
	//待機状態。
	animClip[enStay_blad].Load("Assets/animData/player/blad/stay_01.tka");
	animClip[enStay_blad].SetLoopFlag(true);
	animClip[enStay_sword].Load("Assets/animData/player/sword/stay_02.tka");
	animClip[enStay_sword].SetLoopFlag(true);
	//武器変更。
	animClip[enChange_blad].Load("Assets/animData/player/blad/change_01.tka");
	animClip[enChange_blad].SetLoopFlag(true);
	animClip[enChange_sword].Load("Assets/animData/player/sword/change_02.tka");
	animClip[enChange_sword].SetLoopFlag(true);
	//歩く。
	animClip[enWalk_blad].Load("Assets/animData/player/blad/walk_01.tka");
	animClip[enWalk_blad].SetLoopFlag(true);
	animClip[enWalk_sword].Load("Assets/animData/player/sword/walk_02.tka");
	animClip[enWalk_sword].SetLoopFlag(true);
	//走る。
	animClip[enRun_blad].Load("Assets/animData/player/blad/run_01.tka");
	animClip[enRun_blad].SetLoopFlag(true);
	animClip[enRun_sword].Load("Assets/animData/player/sword/run_02.tka");
	animClip[enRun_sword].SetLoopFlag(true);
	//ジャンプスタート。
	animClip[enJumpStart_blad].Load("Assets/animData/player/blad/jumpStart_01.tka");
	animClip[enJumpStart_blad].SetLoopFlag(true);
	animClip[enJumpStart_sword].Load("Assets/animData/player/sword/jumpStart_02.tka");
	animClip[enJumpStart_sword].SetLoopFlag(true);
	//滞空中。
	animClip[enStayInTheAir_blad].Load("Assets/animData/player/blad/stayInTheAir_01.tka");
	animClip[enStayInTheAir_blad].SetLoopFlag(true);
	animClip[enStayInTheAir_sword].Load("Assets/animData/player/sword/stayInTheAir_02.tka");
	animClip[enStayInTheAir_sword].SetLoopFlag(true);
	//攻撃1
	animClip[enAttack_blad].Load("Assets/animData/player/blad/attack_01_2.tka");
	animClip[enAttack_blad].SetLoopFlag(true);
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