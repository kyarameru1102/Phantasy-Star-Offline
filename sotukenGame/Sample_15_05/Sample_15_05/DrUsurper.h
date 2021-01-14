#pragma once
#include "Physics/Character/CharacterController.h"
#include "EnBase.h"
#include "Physics/GhostObject.h"
class DrUsurper : public EnBase
{
public:
	/// <summary>
	/// �R���X�g���N�^
	/// </summary>
	DrUsurper();
	/// <summary>
	/// �f�X�g���N�^
	/// </summary>
	~DrUsurper();
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

};

