#include "stdafx.h"
#include "GhostObject.h"
#include "BoxCollider.h"
#include "CollisionAttr.h"

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
	m_ghostObject.setUserIndex(enCollisionAttr_Ghost);
	//ï®óùÉGÉìÉWÉìÇ…ìoò^ÅB
	g_physics.AddCollisionObject(m_ghostObject);
	m_isRegistPhysicsWorld = true;
}
