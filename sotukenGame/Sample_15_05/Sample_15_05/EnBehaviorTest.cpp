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
	m_entest = NewGO<EnTest>(0, "EnTest");
	return true;
}

void EnBehaviorTest::Update()
{

}