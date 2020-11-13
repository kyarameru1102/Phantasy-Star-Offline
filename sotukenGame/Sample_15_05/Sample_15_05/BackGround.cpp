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
	//���s�ړ��s����쐬�B
	mTranse.MakeTranslation(m_position);
	//��]�s����쐬�B
	mRot.MakeRotationFromQuaternion(m_rotation);
	//�g��s����쐬�B
	mScale.MakeScaling(m_scale);
	//���[���h�s����쐬�B
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
