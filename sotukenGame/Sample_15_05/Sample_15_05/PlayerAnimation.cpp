#include "stdafx.h"
#include "PlayerAnimation.h"



PlayerAnimation::PlayerAnimation()
{
}
PlayerAnimation::~PlayerAnimation()
{
}
void PlayerAnimation::InitAnimation()
{
	//‘Ò‹@ó‘ÔB
	animClip[enStay_blad].Load("Assets/animData/player/blad/stay_01.tka");
	animClip[enStay_blad].SetLoopFlag(true);
	animClip[enStay_sword].Load("Assets/animData/player/sword/stay_02.tka");
	animClip[enStay_sword].SetLoopFlag(true);
	//•Ší•ÏXB
	animClip[enChange_blad].Load("Assets/animData/player/blad/change_01.tka");
	animClip[enChange_blad].SetLoopFlag(true);
	animClip[enChange_sword].Load("Assets/animData/player/sword/change_02.tka");
	animClip[enChange_sword].SetLoopFlag(true);
	//•à‚­B
	animClip[enWalk_blad].Load("Assets/animData/player/blad/walk_01.tka");
	animClip[enWalk_blad].SetLoopFlag(true);
	animClip[enWalk_sword].Load("Assets/animData/player/sword/walk_02.tka");
	animClip[enWalk_sword].SetLoopFlag(true);
	//‘–‚éB
	animClip[enRun_blad].Load("Assets/animData/player/blad/run_01.tka");
	animClip[enRun_blad].SetLoopFlag(true);
	animClip[enRun_sword].Load("Assets/animData/player/sword/run_02.tka");
	animClip[enRun_sword].SetLoopFlag(true);
	//ƒWƒƒƒ“ƒvƒXƒ^[ƒgB
	animClip[enJumpStart_blad].Load("Assets/animData/player/blad/jumpStart_01.tka");
	animClip[enJumpStart_blad].SetLoopFlag(true);
	animClip[enJumpStart_sword].Load("Assets/animData/player/sword/jumpStart_02.tka");
	animClip[enJumpStart_sword].SetLoopFlag(true);
	//‘Ø‹ó’†B
	animClip[enStayInTheAir_blad].Load("Assets/animData/player/blad/stayInTheAir_01.tka");
	animClip[enStayInTheAir_blad].SetLoopFlag(true);
	animClip[enStayInTheAir_sword].Load("Assets/animData/player/sword/stayInTheAir_02.tka");
	animClip[enStayInTheAir_sword].SetLoopFlag(true);
	//‰ñ”ğB
	animClip[enKaihi_blad].Load("Assets/animData/player/blad/kaihi_01.tka");
	animClip[enKaihi_sword].Load("Assets/animData/player/sword/kaihi_02.tka");
	//‹¯‚ŞB
	animClip[enHit_blad].Load("Assets/animData/player/blad/hit_01.tka");
	animClip[enHit_sword].Load("Assets/animData/player/sword/hit_02.tka");
	//€–SB
	animClip[enDeath_blad].Load("Assets/animData/player/blad/death_01.tka");
	animClip[enDeath_sword].Load("Assets/animData/player/sword/death_02.tka");
	//UŒ‚1
	animClip[enAttack01_blad].Load("Assets/animData/player/blad/attack_blad_01.tka");
	animClip[enAttack01_blad].SetLoopFlag(true);
	animClip[enAttack01_sword].Load("Assets/animData/player/sword/attack_sword_01.tka");
	animClip[enAttack01_sword].SetLoopFlag(true);
	//UŒ‚2
	animClip[enAttack02_blad].Load("Assets/animData/player/blad/attack_blad_02.tka");
	animClip[enAttack02_blad].SetLoopFlag(true);
	animClip[enAttack02_sword].Load("Assets/animData/player/sword/attack_sword_02.tka");
	animClip[enAttack02_sword].SetLoopFlag(true);
	//UŒ‚3
	animClip[enAttack03_blad].Load("Assets/animData/player/blad/attack_blad_03.tka");
	animClip[enAttack03_blad].SetLoopFlag(true);
	animClip[enAttack03_sword].Load("Assets/animData/player/sword/attack_sword_03.tka");
	animClip[enAttack03_sword].SetLoopFlag(true);
	//UŒ‚4
	animClip[enAttack04_blad].Load("Assets/animData/player/blad/attack_blad_04.tka");
	animClip[enAttack04_blad].SetLoopFlag(true);
	animClip[enAttack04_sword].Load("Assets/animData/player/sword/attack_sword_04.tka");
	animClip[enAttack04_sword].SetLoopFlag(true);
	//UŒ‚5
	animClip[enAttack05_blad].Load("Assets/animData/player/blad/attack_blad_05.tka");
	animClip[enAttack05_blad].SetLoopFlag(true);
	animClip[enAttack05_sword].Load("Assets/animData/player/sword/attack_sword_05.tka");
	animClip[enAttack05_sword].SetLoopFlag(true);
	//UŒ‚6
	animClip[enAttack06_blad].Load("Assets/animData/player/blad/attack_blad_06.tka");
	animClip[enAttack06_blad].SetLoopFlag(true);
	animClip[enAttack06_sword].Load("Assets/animData/player/sword/attack_sword_06.tka");
	animClip[enAttack06_sword].SetLoopFlag(true);
	//UŒ‚7
	animClip[enAttack07_blad].Load("Assets/animData/player/blad/attack_blad_07.tka");
	animClip[enAttack07_blad].SetLoopFlag(true);
	animClip[enAttack07_sword].Load("Assets/animData/player/sword/attack_sword_07.tka");
	animClip[enAttack07_sword].SetLoopFlag(true);
	//UŒ‚8
	animClip[enAttack08_blad].Load("Assets/animData/player/blad/attack_blad_08.tka");
	animClip[enAttack08_blad].SetLoopFlag(true);
	animClip[enAttack08_sword].Load("Assets/animData/player/sword/attack_sword_08.tka");
	animClip[enAttack08_sword].SetLoopFlag(true);
	//UŒ‚9
	animClip[enAttack09_blad].Load("Assets/animData/player/blad/attack_blad_09.tka");
	animClip[enAttack09_blad].SetLoopFlag(true);
	animClip[enAttack09_sword].Load("Assets/animData/player/sword/attack_sword_09.tka");
	animClip[enAttack09_sword].SetLoopFlag(true);

	//“ÁêUŒ‚
	animClip[enSpecialAttack_01_blad].Load("Assets/animData/player/blad/attack_blad_special_1.tka");
	animClip[enSpecialAttack_02_blad].Load("Assets/animData/player/blad/attack_blad_special_2.tka");
	animClip[enSpecialAttack_02_blad].SetLoopFlag(true);
	animClip[enSpecialAttack_03_blad].Load("Assets/animData/player/blad/attack_blad_special_3.tka");
}
bool PlayerAnimation::Start()
{
	return true;
}

void PlayerAnimation::Update()
{

}