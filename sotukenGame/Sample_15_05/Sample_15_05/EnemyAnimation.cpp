#include "stdafx.h"
#include "EnemyAnimation.h"

EnemyAnimation::EnemyAnimation()
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
	animClip[enScream].SetLoopFlag(true);
	//�U��
	animClip[enAttack].Load("Assets/animData/DragonBoar/boar_attack.tka");
	animClip[enAttack].SetLoopFlag(true);
	//�p�U��
	animClip[enHornattack].Load("Assets/animData/DragonBoar/boar_hornattack.tka");
	animClip[enHornattack].SetLoopFlag(true);
	//��_��
	animClip[enGethit].Load("Assets/animData/DragonBoar/boar_gethit.tka");
	animClip[enGethit].SetLoopFlag(true);
	//���S
	animClip[enDie].Load("Assets/animData/DragonBoar/boar_die.tka");
	animClip[enDie].SetLoopFlag(true);
}

EnemyAnimation::~EnemyAnimation()
{

}

bool EnemyAnimation::Start()
{
	return true;
}

void EnemyAnimation::Update()
{

}