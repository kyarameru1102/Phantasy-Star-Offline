#pragma once
#include "Physics/Character/CharacterController.h"
#include "NightmareAnimation.h"
#include "EnBase.h"
#include "Physics/GhostObject.h"
class DrNightmare : public EnBase
{
	/// <summary>
	/// �R���X�g���N�^
	/// </summary>
	DrNightmare();
	/// <summary>
	/// �f�X�g���N�^
	/// </summary>
	~DrNightmare();
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

	//�i�C�g���A�̃X�e�[�g
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
	int					m_animState = enIdle01;			//�A�j���[�V�����̏�ԁB
	int					m_appearcolor = 0;				//�z�FNo
	NightmareAnimation* m_nightmAnim = nullptr;         //�A�j���[�V�����̃��[�h�B
	std::vector<int>	boarcolor = { 1,2,3,4 };		//�z�F����B
	bool				m_isAttack = false;				//�U�����Ă��邩�B
	bool				m_ATKoff = false;				//���̍U���Ń_���[�W����񂾂�����邽�߂̃t���O�B
	int					m_count = 0;					//�U��������܂ł̃J�E���g�B
	GhostObject			m_ghostObj;						//�S�[�X�g�B
	int					m_deathCount = 0;				//���񂾂Ƃ��̃J�E���g�B
};

