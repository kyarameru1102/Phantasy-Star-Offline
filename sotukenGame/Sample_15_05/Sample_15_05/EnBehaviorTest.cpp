#include "stdafx.h"
#include "EnBehaviorTest.h"

EnBehaviorTest::EnBehaviorTest()
{
}

EnBehaviorTest::~EnBehaviorTest()
{
}

bool EnBehaviorTest::Start()
{
	//�G�e�X�g�쐬
	//m_entest = NewGO<EnTest>(0, "EnTest");
	m_drboar = NewGO<DrBoar>(0, "DrBoar");
	return true;
}

void EnBehaviorTest::Update()
{

}