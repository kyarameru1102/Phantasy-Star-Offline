#include "stdafx.h"
#include "BackGround.h"

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
	m_box.Create(Vector3(100.0f, 100.0f, 100.0f));
	return true;
}

void BackGround::Update()
{
}
