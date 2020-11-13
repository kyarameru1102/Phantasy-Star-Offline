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
	BoxCollider m_box;
	MeshCollider m_mesh;
	RigidBody m_rigidBody;
	Vector3 m_position = Vector3(0.0f,-50.0f,0.0f);
	Quaternion m_rotation = Quaternion::Identity;
	Vector3 m_scale = Vector3(1000.0f,100.0f,1000.0f);
};

