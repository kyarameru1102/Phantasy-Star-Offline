#pragma once

#include "Physics/MeshCollider.h"
#include "Physics/BoxCollider.h"
#include "Physics/RigidBody.h"

class BackGround : public IGameObject
{
public:
	BackGround();
	~BackGround();
	bool Start()override;
	void Update()override;
private:
	SkinModelRender* m_bgModel = nullptr;
	//BoxCollider m_box;
	MeshCollider m_mesh;
	RigidBody m_rigidBody;
	Vector3 m_position = Vector3::Zero;
	Quaternion m_rotation = Quaternion::Identity;
	Vector3 m_scale = Vector3::One;
};

