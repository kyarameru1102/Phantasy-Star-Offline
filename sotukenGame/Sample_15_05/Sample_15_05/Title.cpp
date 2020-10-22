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
	//Unityちゃんのモデルの初期化。
	m_ladySkinModelRender = NewGO<SkinModelRender>(0,"UnityChan");
	m_ladySkinModelRender->Init("Assets/modelData/unityChan.tkm");
	//背景モデル初期化。
	m_bgSkinModelRender = NewGO<SkinModelRender>(0, "backGround");
	m_bgSkinModelRender->Init("Assets/modelData/bg.tkm");
	return true;
}

void Title::Update()
{

}
