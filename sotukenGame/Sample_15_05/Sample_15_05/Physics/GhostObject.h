#pragma once
#include "ICollider.h"

/// <summary>
/// �S�[�X�g�N���X�B
/// </summary>
class GhostObject
{
public:
	~GhostObject();
	/// <summary>
	/// �����[�X�B
	/// </summary>
	/// ���������Ƃ��ĂԁB
	void Release();

	/// <summary>
	/// �{�b�N�X�^�̃S�[�X�g���쐬����֐��B
	/// </summary>
	/// <param name="pos"></param>
	/// <param name="rot"></param>
	/// <param name="size"></param>
	void CreateBox(Vector3 pos, Quaternion rot, Vector3 size);

	/// <summary>
	/// �����œn���ꂽ�S�[�X�g���������g������B
	/// </summary>
	/// <param name="ghost"></param>
	/// <returns></returns>
	bool IsSelf(const btCollisionObject& ghost) const
	{
		return &ghost == &m_ghostObject;
	}
	/// <summary>
	/// ���W��ݒ肷��֐��B
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
	/// ��]��ݒ肷��֐��B
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
	/// �������̋��ʏ����B
	/// </summary>
	/// <param name="pos"></param>
	/// <param name="rot"></param>
	void CreateCommon(Vector3 pos, Quaternion rot);
private:
	bool						m_isRegistPhysicsWorld = false;	//!<�������[���h�ɓo�^���Ă��邩�ǂ����̃t���O�B
	std::unique_ptr<ICollider>	m_collider;	//!<�R���C�_�[�B
	btGhostObject				m_ghostObject;	//!<�S�[�X�g
};

