#include "stdafx.h"
#include "GhostObject.h"
#include "BoxCollider.h"

GhostObject::~GhostObject()
{
	Release();
}

void GhostObject::Release()
{
	if (m_isRegistPhysicsWorld == true) {
		g_physics.RemoveCollisionObject(m_ghostObject);
		m_isRegistPhysicsWorld = false;
	}
}

void GhostObject::CreateBox(Vector3 pos, Quaternion rot, Vector3 size)
{
	Release();
	auto boxCollider = std::make_unique<BoxCollider>();
	boxCollider->Create(size);
	m_collider = move(boxCollider);
	CreateCommon(pos, rot);
}

void GhostObject::CreateCommon(Vector3 pos, Quaternion rot)
{
	m_ghostObject.setCollisionShape(m_collider->GetBody());
	btTransform btTrans;
	btTrans.setOrigin({ pos.x, pos.y, pos.z });
	btTrans.setRotation({ rot.x, rot.y, rot.z, rot.w });
	m_ghostObject.setWorldTransform(btTrans);

	//�����G���W���ɓo�^�B
	g_physics.AddCollisionObject(m_ghostObject);
	m_isRegistPhysicsWorld = true;
}
