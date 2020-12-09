#pragma once
#include "ICollider.h"

/// <summary>
/// ゴーストクラス。
/// </summary>
class GhostObject
{
public:
	~GhostObject();
	/// <summary>
	/// リリース。
	/// </summary>
	/// 消したいとき呼ぶ。
	void Release();

	/// <summary>
	/// ボックス型のゴーストを作成する関数。
	/// </summary>
	/// <param name="pos"></param>
	/// <param name="rot"></param>
	/// <param name="size"></param>
	void CreateBox(Vector3 pos, Quaternion rot, Vector3 size);

	/// <summary>
	/// 引数で渡されたゴーストが自分自身か判定。
	/// </summary>
	/// <param name="ghost"></param>
	/// <returns></returns>
	bool IsSelf(const btCollisionObject& ghost) const
	{
		return &ghost == &m_ghostObject;
	}
	/// <summary>
	/// 座標を設定する関数。
	/// </summary>
	/// <param name="pos"></param>
	void SetPosition(const Vector3& pos)
	{
		auto& btTrans = m_ghostObject.getWorldTransform();
		btVector3 btPos;
		pos.CopyTo(btPos);
		btTrans.setOrigin(btPos);
	}
	/// <summary>
	/// 回転を設定する関数。
	/// </summary>
	/// <param name="rot"></param>
	void SetRotation(const Quaternion& rot)
	{
		auto& btTrans = m_ghostObject.getWorldTransform();
		btQuaternion btRot;
		rot.CopyTo(btRot);
		btTrans.setRotation(btRot);
	}
private:
	/// <summary>
	/// 生成時の共通処理。
	/// </summary>
	/// <param name="pos"></param>
	/// <param name="rot"></param>
	void CreateCommon(Vector3 pos, Quaternion rot);
private:
	bool						m_isRegistPhysicsWorld = false;	//!<物理ワールドに登録しているかどうかのフラグ。
	std::unique_ptr<ICollider>	m_collider;	//!<コライダー。
	btGhostObject				m_ghostObject;	//!<ゴースト
};

