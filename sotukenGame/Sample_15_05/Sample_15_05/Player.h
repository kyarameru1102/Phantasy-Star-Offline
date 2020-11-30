#pragma once
class GameCamera;
class Weapon;
#include "Physics/Character/CharacterController.h"
#include "GameCamera.h"
#include "Weapon.h"
#include "PlayerAnimation.h"
/// <summary>
/// �v���C���[�N���X�B
/// </summary>
class Player : public IGameObject
{
public:
	/// <summary>
	/// �R���X�g���N�^�B
	/// </summary>
	Player();
	/// <summary>
	/// �f�X�g���N�^�B
	/// </summary>
	~Player();
	/// <summary>
	/// �U���B
	/// </summary>
	void Attack();
	/// <summary>
	/// Y�����̈ړ��B�W�����v�◎�����̏����B
	/// </summary>
	void YDirMove();
	/// <summary>
	/// ����ύX�B
	/// </summary>
	void WeaponChange();
	/// <summary>
	/// ����̍��W�A��]��ݒ肷��B
	/// </summary>
	void SetWeaponTR();
	/// <summary>
	/// �����ƈړ��X�s�[�h��ݒ肷��B
	/// </summary>
	void SetDirAndSpeed();
	/// <summary>
	/// �X�^�[�g�֐��B
	/// </summary>
	/// <returns></returns>
	bool Start() override;
	/// <summary>
	/// �X�V�֐��B
	/// </summary>
	void Update() override;
	/// <summary>
	/// �v���C���[�̍��W��ݒ肷��B
	/// </summary>
	/// <param name="pos">���W�B</param>
	void SetPosition(const Vector3& pos)
	{
		m_position = pos;
	}
	/// <summary>
	/// �v���C���[�̍��W��Ԃ��B
	/// </summary>
	/// <returns></returns>
	const Vector3& GetPosition() const
	{
		return m_position;
	}
	Vector3 GetRootPos()
	{
		return m_rootPos;
	}
	bool GetAttackFlag()
	{
		return m_attackFlag;
	}
	/// <summary>
	/// HP��ݒ�B
	/// </summary>
	/// <param name="hp">HP</param>
	void SetHP(const float hp)
	{
		m_playerHP = hp;
	}
	/// <summary>
	/// HP��Ԃ��B
	/// </summary>
	/// <returns></returns>
	const float GetHP() const
	{
		return m_playerHP;
	}
private:
	PlayerAnimation* m_playerAnim = nullptr;
	SkinModelRender* m_playerSkinModel = nullptr;
	GameCamera* m_gameCam = nullptr;
	Vector3 m_position = Vector3::Zero;//���W�B
	Vector3 m_moveSpeed = Vector3::Zero;//���[�u�X�s�[�h�B
	Quaternion m_rotation = Quaternion::Identity; //��]�N�H�[�^�j�I���B
	CharacterController m_charaCon;//�L�����R���B
	enum {
		enBladState,
		enSwordState
	};
	bool m_changeAnimFlag = false;
	int m_changeAnimTimer = 0;
	int m_changeAnimTime = 35;//�����ς���̂ɂ�����t���[���B
	int m_animState = enStay_blad; //�A�j���[�V�����̏�ԁB
	int m_weaponState = enBladState;//����̏�ԁB
	bool m_jumpFlag = false;//�W�����v���Ă邩�ǂ����̃t���O�B
	float m_speedY = 0.0f;//Y�����̃X�s�[�h�B
	float m_magnificationSpeed = 5.0f; //�����̔{���B
	float m_complementaryTime = 0.0f;//�A�j���[�V�����⊮���ԁB
	int jumpStartTimer = 40;
	float m_playerHP = 100.0f;      //HP�B

	Weapon* m_weapon[2] = { nullptr, nullptr };
	int m_weapon01Num = 0; //1�{�ڂ̕���̃{�[���̔ԍ��B
	int m_weapon02Num = 0; //2�{�ڂ̕���̃{�[���̔ԍ��B
	Vector3 m_weaponPos = Vector3::Zero;          //����̍��W�B
	Quaternion m_weaponRot = Quaternion::Identity;//����̉�]�B
	Vector3 m_weaponScale = Vector3::One;       //����̃X�P�[���B

	bool m_attackFlag = false;
	int attackTimer = 0;
	int m_weapon03Num = 0; //3�{�ڂ̃{�[���̔ԍ��B
	Vector3 m_rootPos = Vector3::Zero;
	Quaternion m_rot = Quaternion::Identity;
	Vector3 m_rootScale = Vector3::One;
	Vector3 v = Vector3::Zero;
	Vector3 m_rerootpos = Vector3::Zero;
	bool m_flag = false;
	int m_attackNum = 0;
	int time = 0;
	int m_continuousAttackTime = 0;
	int num = 0;
};

