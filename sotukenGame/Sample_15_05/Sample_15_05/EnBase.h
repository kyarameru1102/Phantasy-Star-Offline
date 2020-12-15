#pragma once
#include "Physics/Character/CharacterController.h"

/// <summary>
/// �G���N���X
/// </summary>
class Player;
class EnBase : public IGameObject
{
public:
	/// <summary>
	/// �R���X�g���N�^
	/// </summary>
	EnBase();
	/// <summary>
	/// �f�X�g���N�^
	/// </summary>
	~EnBase();
	/// <summary>
	/// ���W��Ԃ��B
	/// </summary>
	/// <returns></returns>
	const Vector3& GetPosition() const
	{
		return m_position;
	}
	/// <summary>
	/// HP��Ԃ��B
	/// </summary>
	/// <returns></returns>
	const int& GetHP() const
	{
		return m_hp;
	}
	/// <summary>
	/// �_���[�W���󂯂�HP�����炷�֐��B
	/// </summary>
	/// <param name="damage">int �_���[�W��</param>
	virtual void ReceiveDamage(int damage)
	{
		m_hp -= damage;
	}
	/// <summary>
	/// HP��^����֐��B
	/// ��ɉ񕜓��Ŏg���B
	/// </summary>
	/// <param name="hp">int �񕜗�</param>
	void ReceiveHP(int hp)
	{
		m_hp += hp;
	}

	/// <summary>
	/// �L�����R����Ԃ��B
	/// </summary>
	CharacterController* GetCharaCon()
	{
		return &m_charaCon;
	}
protected:
	SkinModelRender*	m_skinModelRender = nullptr;			//�X�L�����f��
	Vector3				m_position = Vector3::Zero;				//���W
	Vector3				m_scale = Vector3::One;					//�g�嗦
	Quaternion			m_rotation = Quaternion::Identity;		//��]
	Vector3				m_movespeed = Vector3::Zero;			//�ړ����x
	CharacterController m_charaCon;								//�L�����R���B
	int					m_hp = 50;								//HP
	Player*				m_player = nullptr;						//�v���C���[�B
	Vector3				m_toPlayer = Vector3::Zero;				//�v���C���[�܂ł̃x�N�g���B
};

