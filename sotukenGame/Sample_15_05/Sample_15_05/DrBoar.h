#pragma once
#include "Physics/Character/CharacterController.h"
#include "EnemyAnimation.h"
/// <summary>
/// �h���S���{�A�N���X
/// </summary>
class Player;
class DrBoar : public IGameObject
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

	void Move();
	void Turn();

	/// <summary>
	/// �v���C���[�̍��W��Ԃ��B
	/// </summary>
	/// <returns></returns>
	const Vector3& GetPosition() const
	{
		return m_position;
	}
private:
	enum {
		Idle_state,
		Attack_state
	};
	int m_status = Attack_state;    //���
	SkinModelRender* m_DrBoarSkinModel = nullptr;
	Vector3 m_position = Vector3::Zero;  //���W
	Vector3 m_scale = Vector3::One;      //�g�嗦
	Quaternion m_rotation = Quaternion::Identity; //��]
	Vector3 m_movespeed = Vector3::Zero;  //�ړ����x
	int changeTimer = 0;       //�A�j���[�V�����ύX�^�C�}�[
	float m_speedY = 0.0f;//Y�����̃X�s�[�h�B
	int m_animState = enIdle; //�A�j���[�V�����̏�ԁB
	

	Player* m_player = nullptr;
	CharacterController m_charaCon;//�L�����R���B
	EnemyAnimation* m_enemyAnim = nullptr;
};

