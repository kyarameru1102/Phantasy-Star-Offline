#include "stdafx.h"
#include "RigidBody.h"
#include "ICollider.h"


RigidBody::~RigidBody()
{
	Release();
}
void RigidBody::Release()
{
	delete rigidBody;
	delete myMotionState;
	rigidBody = nullptr;
	myMotionState = nullptr;
}
void RigidBody::Create(RigidBodyInfo& rbInfo)
{

	Release();
	btTransform transform;
	transform.setIdentity();
	transform.setOrigin(btVector3(rbInfo.pos.x, rbInfo.pos.y, rbInfo.pos.z));
	transform.setRotation(btQuaternion(rbInfo.rot.x, rbInfo.rot.y, rbInfo.rot.z, rbInfo.rot.w));
	myMotionState = new btDefaultMotionState;
	myMotionState->setWorldTransform(transform);
	btRigidBody::btRigidBodyConstructionInfo btRbInfo(rbInfo.mass, myMotionState, rbInfo.collider->GetBody(), btVector3(0, 0, 0));
	//���̂��쐬�B
	rigidBody = new btRigidBody(btRbInfo);

}
