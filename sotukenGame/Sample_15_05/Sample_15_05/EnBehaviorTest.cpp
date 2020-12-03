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
	//m_entest = NewGO<EnTest>(0, "EnTest");
	m_drboar = NewGO<DrBoar>(0, "DrBoar");
	return true;
}

void EnBehaviorTest::Update()
{

}