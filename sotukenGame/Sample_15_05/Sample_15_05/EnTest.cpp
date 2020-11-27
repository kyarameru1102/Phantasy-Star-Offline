#include "stdafx.h"
#include "EnTest.h"

EnTest::EnTest()
{

}
EnTest::~EnTest()
{

}

bool EnTest::Start()
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
	m_EnTestSkinModel = NewGO<SkinModelRender>(0);
	m_EnTestSkinModel->Init("Assets/modelData/enemy/DragonBoar/Gold/DrBoarGo.tkm", m_animationClip, enAnimationClip_num);
	
	m_rotation.SetRotationDegY(90.0f);

	return true;
}

void EnTest::Update()
{
	changeTimer++;
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
	}
	
	
	m_EnTestSkinModel->SetScale({ 40.0, 40.0, 40.0 });
	m_EnTestSkinModel->SetRotation(m_rotation);
	m_EnTestSkinModel->PlayAnimation(m_animState,0.0f);
}