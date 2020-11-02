#include "stdafx.h"
#include "BoxCollider.h"

BoxCollider::BoxCollider() :
	shape(NULL)
{
}

BoxCollider::~BoxCollider()
{
	delete shape;
}

void BoxCollider::Create(const Vector3& size)
{
	shape = new btBoxShape(btVector3(size.x * 0.5f, size.y * 0.5f, size.z * 0.5f));
}
