#pragma once

#include "Physics/MeshCollider.h"

class BackGround : public IGameObject
{
public:
	BackGround();
	~BackGround();
	bool Start()override;
	void Update()override;
private:
	SkinModelRender* m_bgModel = nullptr;
	//MeshCollider m_mesh;
};

