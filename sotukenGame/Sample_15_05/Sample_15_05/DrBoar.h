#pragma once
#include "Physics/Character/CharacterController.h"
#include "EnemyAnimation.h"
#include "EnBase.h"

/// <summary>
/// �h���S���{�A�N���X
/// </summary>
class DrBoar : public EnBase
{
public:
	/// <summary>
	/// �R���X�g���N�^
	/// </summary>
	DrBoar();
	/// <summary>
	/// �f�X�g���N�^
	/// </summary>
	~DrBoar();
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
	
private:
	/// <summary>
	/// �G�l�~�[�̃X�e�[�g�B
	/// </summary>
	enum {
		Idle_state,
		Move_state,
		Attack_state,
		Die_state
	};
	int					m_status = Idle_state;			//��ԁB
	int					changeTimer = 0;				//�A�j���[�V�����ύX�^�C�}�[�B
	float				m_speedY = 0.0f;				//Y�����̃X�s�[�h�B
	int					m_animState = enIdle;			//�A�j���[�V�����̏�ԁB
	int					m_appearcolor = 0;				//�z�FNo
	EnemyAnimation*		m_enemyAnim = nullptr;			//�A�j���[�V�����̃��[�h�B
	std::vector<int>	boarcolor = { 1,2,3,4 };		//�z�F����B
	bool				isAttack = false;				//�U�����Ă��邩�B
};

