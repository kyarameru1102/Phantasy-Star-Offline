#include "stdafx.h"
#include "EnTest.h"

EnTest::EnTest()
{

}
EnTest::~EnTest()
{

}

bool EnTest::Start()
{
	//モデルの初期化
	m_EnTestSkinModel = NewGO<SkinModelRender>(0);
	m_EnTestSkinModel->Init("Assets/modelData/enemy/DragonBoar/Blue/DrBoarBl.tkm");
	return true;
}