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
	//モデルの初期化
	m_EnTestSkinModel = NewGO<SkinModelRender>(0);
	m_EnTestSkinModel->Init("Assets/modelData/enemy/DragonBoar/Blue/DrBoarBl.tkm", m_animationClip, enAnimationClip_num);
	
	m_rotation.SetRotation(Vector3::AxisX, (90.0f, 0.0f, 0.0f));
	m_rotation.SetRotationDegY(90.0f);

	return true;
}

void EnTest::Update()
{
	m_EnTestSkinModel->SetScale({ 40.0, 40.0, 40.0 });
	m_EnTestSkinModel->SetRotation(m_rotation);
	//m_EnTestSkinModel->PlayAnimation(m_animState,0.0f);
}