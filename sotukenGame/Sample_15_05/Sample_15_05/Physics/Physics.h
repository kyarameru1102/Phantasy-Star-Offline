#pragma once
#include "Character/CharacterController.h"

class RigidBody;

class PhysicsWorld
{
	struct MyContactResultCallback : public btCollisionWorld::ContactResultCallback {
		using ContantTestCallback = std::function<void(const btCollisionObject& contactCollisionObject)>;
		ContantTestCallback  m_cb;
		btCollisionObject* m_me = nullptr;
		virtual	btScalar	addSingleResult(btManifoldPoint& cp, const btCollisionObjectWrapper* colObj0Wrap, int partId0, int index0, const btCollisionObjectWrapper* colObj1Wrap, int partId1, int index1) override
		{
			if (m_me == colObj0Wrap->getCollisionObject()) {
				m_cb(*colObj1Wrap->getCollisionObject());
			}
			return 0.0f;
		}
	};

	btDefaultCollisionConfiguration*		collisionConfig = nullptr;
	btCollisionDispatcher*					collisionDispatcher = nullptr;	//�Փˉ��������B
	btBroadphaseInterface*					overlappingPairCache = nullptr;	//�u���[�h�t�F�[�Y�B�Փ˔���̎}�؂�B
	btSequentialImpulseConstraintSolver*	constraintSolver = nullptr;		//�R���X�g���C���g�\���o�[�B�S�������̉��������B
	btDiscreteDynamicsWorld*				dynamicWorld = nullptr;			//���[���h�B
public:
	~PhysicsWorld();
	void Init();
	void Update();
	void Release();
	/// <summary>
	/// �_�C�i�~�b�N���[���h���擾�B
	/// </summary>
	/// <returns></returns>
	btDiscreteDynamicsWorld* GetDynamicWorld()
	{
		return dynamicWorld;
	}
	/// <summary>
	/// ���̂�o�^�B
	/// </summary>
	/// <param name="rb"></param>
	void AddRigidBody(RigidBody& rb);
	/// <summary>
	/// ���̂�j���B
	/// </summary>
	/// <param name="rb"></param>
	void RemoveRigidBody(RigidBody& rb);
	/// <summary>
	/// �X�E�B�[�v�e�X�g�B
	/// </summary>
	/// <param name="castShape"></param>
	/// <param name="convexFromWorld"></param>
	/// <param name="convexToWorld"></param>
	/// <param name="resultCallback"></param>
	/// <param name="allowedCcdPenetration"></param>
	void ConvexSweepTest(
		const btConvexShape* castShape,
		const btTransform& convexFromWorld,
		const btTransform& convexToWorld,
		btCollisionWorld::ConvexResultCallback& resultCallback,
		btScalar allowedCcdPenetration = 0.0f
	)
	{
		dynamicWorld->convexSweepTest(castShape, convexFromWorld, convexToWorld, resultCallback, allowedCcdPenetration);
	}

	void ContactTest(
		btCollisionObject* colObj,
		std::function<void(const btCollisionObject& contactCollisionObject)> cb
	) {
		MyContactResultCallback myContactResultCallback;
		myContactResultCallback.m_cb = cb;
		myContactResultCallback.m_me = colObj;
		dynamicWorld->contactTest(colObj, myContactResultCallback);
	}
	void ContactTest(
		btCollisionObject* colObj,
		btCollisionWorld::ContactResultCallback& resultCallback
	)
	{
		dynamicWorld->contactTest(colObj, resultCallback);
	}
	void ContactTestCharaCon(
		CharacterController& charaCon,
		btCollisionWorld::ContactResultCallback& resultCallback
	)
	{
		ContactTest(charaCon.GetRigidBody()->GetBody(), resultCallback);
	}
	
	/// <summary>
	/// �R���W�����I�u�W�F�N�g�����[���h�ɓo�^�B
	/// </summary>
	/// <param name="colliObj"></param>
	void AddCollisionObject(btCollisionObject& colliObj)
	{
		dynamicWorld->addCollisionObject(&colliObj);
	}
	/// <summary>
	/// �R���W�����I�u�W�F�N�g�����[���h����j���B
	/// </summary>
	/// <param name="colliObj"></param>
	void RemoveCollisionObject(btCollisionObject& colliObj)
	{
		dynamicWorld->removeCollisionObject(&colliObj);
	}
};

extern PhysicsWorld g_physics;


