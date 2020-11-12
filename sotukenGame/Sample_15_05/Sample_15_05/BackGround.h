#pragma once

#include "Physics/MeshCollider.h"
#include "Physics/BoxCollider.h"

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
};

