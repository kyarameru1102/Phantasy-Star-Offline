#include "stdafx.h"
#include "CapsuleCollider.h"


CapsuleCollider::~CapsuleCollider()
{
	delete shape;
}