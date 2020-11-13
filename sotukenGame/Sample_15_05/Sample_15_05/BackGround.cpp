#include "stdafx.h"
#include "BackGround.h"
#include "Physics/CollisionAttr.h"

BackGround::BackGround()
{
}

BackGround::~BackGround()
{
}

bool BackGround::Start()
{
	m_bgModel = NewGO<SkinModelRender>(0);
	m_bgModel->Init("Assets/modelData/background.tkm",nullptr,0, "Assets/shader/model.fx",SkinModelRender::YUp);
	Matrix mTranse, mRot, mScale, mWorld;
	//平行移動行列を作成。
	mTranse.MakeTranslation(m_position);
	//回転行列を作成。
	mRot.MakeRotationFromQuaternion(m_rotation);
	//拡大行列を作成。
	mScale.MakeScaling(m_scale);
	//ワールド行列を作成。
	mWorld.Multiply(mScale, mRot);
	mWorld.Multiply(mWorld, mTranse);
	//m_mesh.CreateFromModel(m_bgModel->GetModel(), &mWorld);
	m_box.Create(m_scale);
	RigidBodyInfo rbi;
	rbi.collider = &m_box;
	rbi.mass = 0.0f;
	m_rigidBody.Create(rbi);
	m_rigidBody.GetBody()->setUserIndex(enCollisionAttr_ground);

	g_physics.AddRigidBody(m_rigidBody);

	return true;
}

void BackGround::Update()
{
	m_bgModel->SetPosition(m_position);
}
