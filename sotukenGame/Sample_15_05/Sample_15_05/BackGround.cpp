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
	m_bgModel->Init("Assets/modelData/background.tkm");
	return true;
}

void BackGround::Update()
{
}
