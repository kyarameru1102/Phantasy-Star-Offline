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
	btCollisionDispatcher*					collisionDispatcher = nullptr;	//衝突解決処理。
	btBroadphaseInterface*					overlappingPairCache = nullptr;	//ブロードフェーズ。衝突判定の枝切り。
	btSequentialImpulseConstraintSolver*	constraintSolver = nullptr;		//コンストレイントソルバー。拘束条件の解決処理。
	btDiscreteDynamicsWorld*				dynamicWorld = nullptr;			//ワールド。
public:
	~PhysicsWorld();
	void Init();
	void Update();
	void Release();
	/// <summary>
	/// ダイナミックワールドを取得。
	/// </summary>
	/// <returns></returns>
	btDiscreteDynamicsWorld* GetDynamicWorld()
	{
		return dynamicWorld;
	}
	/// <summary>
	/// 剛体を登録。
	/// </summary>
	/// <param name="rb"></param>
	void AddRigidBody(RigidBody& rb);
	/// <summary>
	/// 剛体を破棄。
	/// </summary>
	/// <param name="rb"></param>
	void RemoveRigidBody(RigidBody& rb);
	/// <summary>
	/// スウィープテスト。
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
	void ContactTestCol(
		btCollisionObject* colObj,
		std::function<void(const btCollisionObject& contactCollisionObject)> cb
	)
	{
		ContactTest(colObj, cb);
	}
	void ContactTestCharaCon(
		CharacterController& charaCon,
		std::function<void(const btCollisionObject& contactCollisionObject)> cb
	)
	{
		ContactTest(charaCon.GetRigidBody()->GetBody(), cb);
	}
	
	/// <summary>
	/// コリジョンオブジェクトをワールドに登録。
	/// </summary>
	/// <param name="colliObj"></param>
	void AddCollisionObject(btCollisionObject& colliObj)
	{
		dynamicWorld->addCollisionObject(&colliObj);
	}
	/// <summary>
	/// コリジョンオブジェクトをワールドから破棄。
	/// </summary>
	/// <param name="colliObj"></param>
	void RemoveCollisionObject(btCollisionObject& colliObj)
	{
		dynamicWorld->removeCollisionObject(&colliObj);
	}
};

extern PhysicsWorld g_physics;


