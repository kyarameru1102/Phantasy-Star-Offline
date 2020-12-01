#include "stdafx.h"
#include "DrBoar.h"

DrBoar::DrBoar()
{
}

DrBoar::~DrBoar()
{
	DeleteGO(m_DrBoarSkinModel);
}

bool DrBoar::Start()
{
	//アニメーションクリップのロード
	m_animationClip[enIdle].Load("Assets/animData/DragonBoar/boar_idle.tka");
	m_animationClip[enIdle].SetLoopFlag(true);
	m_animationClip[enWalk].Load("Assets/animData/DragonBoar/boar_walk.tka");
	m_animationClip[enWalk].SetLoopFlag(true);
	m_animationClip[enRun].Load("Assets/animData/DragonBoar/boar_run.tka");
	m_animationClip[enRun].SetLoopFlag(true);
	m_animationClip[enDie].Load("Assets/animData/DragonBoar/boar_die.tka");
	m_animationClip[enDie].SetLoopFlag(true);
	//モデルの初期化
	m_DrBoarSkinModel = NewGO<SkinModelRender>(0);
	m_DrBoarSkinModel->Init("Assets/modelData/enemy/DragonBoar/Gold/DrBoarGo.tkm", m_animationClip, enAnimationClip_num);

	m_rotation.SetRotationDegY(90.0f);
	return true;
}

void DrBoar::Update()
{
	/*changeTimer++;
	if (changeTimer == 30)
	{
		m_animState = enWalk;
	}
	if (changeTimer == 50)
	{
		m_animState = enRun;
	}
	if (changeTimer == 70)
	{
		m_animState = enDie;
	}*/


	m_DrBoarSkinModel->SetScale({ 40.0, 40.0, 40.0 });
	m_DrBoarSkinModel->SetRotation(m_rotation);
	m_DrBoarSkinModel->SetPosition(m_position);
	m_DrBoarSkinModel->PlayAnimation(m_animState, 0.0f);
}