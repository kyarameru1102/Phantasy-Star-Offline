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
	void Attack();
	void Die();
	/// <summary>
	/// �h���S���{�A�̍��W��Ԃ��B
	/// </summary>
	/// <returns></returns>
	const Vector3& GetPosition() const
	{
		return m_position;
	}
	/// <summary>
	/// �h���S���{�A��HP��Ԃ��B
	/// </summary>
	/// <returns></returns>
	const int& GetHP() const
	{
		return m_hp;
	}
	/// <summary>
	/// �h���S���{�A��HP�����炷�B
	/// </summary>
	int GetHit(int damage) 
	{
		m_hp -= damage;
		return true;
	}
private:
	enum {
		Idle_state,
		Attack_state,
		Die_state
	};
	
	int m_status = Attack_state;    //���
	SkinModelRender* m_DrBoarSkinModel = nullptr; //�X�L�����f��
	Vector3 m_position = Vector3::Zero;  //���W
	Vector3 m_scale = Vector3::One;      //�g�嗦
	Quaternion m_rotation = Quaternion::Identity; //��]
	Vector3 m_movespeed = Vector3::Zero;  //�ړ����x
	int changeTimer = 0;       //�A�j���[�V�����ύX�^�C�}�[
	float m_speedY = 0.0f;//Y�����̃X�s�[�h�B
	int m_animState = enIdle; //�A�j���[�V�����̏�ԁB
	int m_appearcolor = 0;  //�z�FNo
	int m_hp = 50;  //HP

	Player* m_player = nullptr;
	CharacterController m_charaCon;//�L�����R���B
	EnemyAnimation* m_enemyAnim = nullptr;  //�A�j���[�V�����̃��[�h
	std::vector<int> boarcolor = { 1,2,3,4 }; //�z�F����
};

