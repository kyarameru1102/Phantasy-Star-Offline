#include "stdafx.h"
#include "Title.h"

Title::Title()
{
	
}

Title::~Title()
{
}

bool Title::Start()
{
	//Unity�����̃��f���̏������B
	m_ladySkinModelRender = NewGO<SkinModelRender>(0,"UnityChan");
	m_ladySkinModelRender->Init("Assets/modelData/unityChan.tkm");
	//�w�i���f���������B
	m_bgSkinModelRender = NewGO<SkinModelRender>(0, "backGround");
	m_bgSkinModelRender->Init("Assets/modelData/bg.tkm");
	return true;
}

void Title::Update()
{

}
