#include "stdafx.h"
#include "EnemyAnimation.h"

EnemyAnimation::EnemyAnimation()
{
	//アニメーションロード。
	//待機
	animClip[enIdle].Load("Assets/animData/DragonBoar/boar_idle.tka");
	animClip[enIdle].SetLoopFlag(true);
	//歩き
	animClip[enWalk].Load("Assets/animData/DragonBoar/boar_walk.tka");
	animClip[enWalk].SetLoopFlag(true);
	//走り
	animClip[enRun].Load("Assets/animData/DragonBoar/boar_run.tka");
	animClip[enRun].SetLoopFlag(true);
	//咆哮
	animClip[enScream].Load("Assets/animData/DragonBoar/boar_scream.tka");
	//攻撃
	animClip[enAttack].Load("Assets/animData/DragonBoar/boar_attack.tka");
	//角攻撃
	animClip[enHornattack].Load("Assets/animData/DragonBoar/boar_hornattack.tka");
	//被ダメ
	animClip[enGethit].Load("Assets/animData/DragonBoar/boar_gethit.tka");
	//死亡
	animClip[enDie].Load("Assets/animData/DragonBoar/boar_die.tka");
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