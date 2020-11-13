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
	//“GƒeƒXƒgì¬
	m_entest = NewGO<EnTest>(0, "EnTest");
	return true;
}

void EnBehaviorTest::Update()
{

}