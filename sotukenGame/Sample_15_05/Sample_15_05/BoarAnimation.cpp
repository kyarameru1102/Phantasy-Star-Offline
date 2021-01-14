#include "stdafx.h"
#include "BoarAnimation.h"

BoarAnimation::BoarAnimation()
{
	//�A�j���[�V�������[�h�B
	//�ҋ@
	animClip[enIdle].Load("Assets/animData/DragonBoar/boar_idle.tka");
	animClip[enIdle].SetLoopFlag(true);
	//����
	animClip[enWalk].Load("Assets/animData/DragonBoar/boar_walk.tka");
	animClip[enWalk].SetLoopFlag(true);
	//����
	animClip[enRun].Load("Assets/animData/DragonBoar/boar_run.tka");
	animClip[enRun].SetLoopFlag(true);
	//���K
	animClip[enScream].Load("Assets/animData/DragonBoar/boar_scream.tka");
	//�U��
	animClip[enAttack].Load("Assets/animData/DragonBoar/boar_attack.tka");
	//�p�U��
	animClip[enHornattack].Load("Assets/animData/DragonBoar/boar_hornattack.tka");
	//��_��
	animClip[enGethit].Load("Assets/animData/DragonBoar/boar_gethit.tka");
	//���S
	animClip[enDie].Load("Assets/animData/DragonBoar/boar_die.tka");
}

BoarAnimation::~BoarAnimation()
{

}

bool BoarAnimation::Start()
{
	return true;
}

void BoarAnimation::Update()
{

}