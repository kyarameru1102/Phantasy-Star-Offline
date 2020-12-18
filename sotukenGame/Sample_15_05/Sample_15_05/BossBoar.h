#pragma once

#include "Physics/Character/CharacterController.h"
#include "EnemyAnimation.h"
#include "EnBase.h"
#include "Physics/GhostObject.h"
#include "Physics/CapsuleCollider.h"

class BossBoar : public EnBase
{
public:
	/// <summary>
	/// �R���X�g���N�^�B
	/// </summary>
	BossBoar();
	/// <summary>
	/// �f�X�g���N�^�B
	/// </summary>
	~BossBoar();
	/// <summary>
	/// �X�^�[�g�֐��B
	/// </summary>
	/// <returns></returns>
	bool Start();
	/// <summary>
	/// �X�V�֐��B
	/// </summary>
	/// <returns></returns>
	void Update();

	/// <summary>
	/// �v���C���[�Ɍ������Ă����֐��B
	/// </summary>
	void Move();
	/// <summary>
	/// �v���C���[�̕����ɑ̂�������֐��B
	/// </summary>
	void Turn();
	/// <summary>
	/// �U���֐��B
	/// </summary>
	void Attack();
	/// <summary>
	/// ���B
	/// </summary>
	void Die();
	void ReceiveDamage(int damage) override
	{
		m_hp -= damage;
		m_status = GetDamage_state;
	}
private:
	/// <summary>
	/// �G�l�~�[�̃X�e�[�g�B
	/// </summary>
	enum {
		Idle_state,
		Walk_state,
		Run_state,
		Attack_state,
		GetDamage_state,
		Die_state
	};
	int					m_status = Idle_state;			//��ԁB
	int					changeTimer = 0;				//�A�j���[�V�����ύX�^�C�}�[�B
	float				m_speedY = 0.0f;				//Y�����̃X�s�[�h�B
	int					m_animState = enIdle;			//�A�j���[�V�����̏�ԁB
	int					m_appearcolor = 0;				//�z�FNo
	EnemyAnimation*		m_enemyAnim = nullptr;			//�A�j���[�V�����̃��[�h�B
	std::vector<int>	boarcolor = { 1,2,3,4 };		//�z�F����B
	bool				m_isAttack = false;				//�U�����Ă��邩�B
	bool				m_ATKoff = false;				//���̍U���Ń_���[�W����񂾂�����邽�߂̃t���O�B
	int					m_count = 0;					//�U��������܂ł̃J�E���g�B
	GhostObject			m_ghostObj;						//�S�[�X�g�B
	//CharacterController m_charaConFace;						//�L�����R��2�߁B
	Vector3 dir, ghostPos, facePos;
};

