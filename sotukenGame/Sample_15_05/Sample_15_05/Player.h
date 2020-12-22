#pragma once
#define _USE_MATH_DEFINES
class GameCamera;
class Weapon;
#include <math.h>
#include "Physics/Character/CharacterController.h"
#include "GameCamera.h"
#include "Weapon.h"
#include "PlayerAnimation.h"
#include "PlayerStatusUI.h"
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
	/// �v���C���[���o���l���擾����B�Q�b�^�[����Ȃ���I�I
	/// </summary>
	/// <param name="experiencePoint">�|�����G�̌o���l�B</param>
	void GetExperiencePoint(const float experiencePoint);
	void AttackFlag(int attackTime01_blad, int attackAnimNum, int attackTime01_sword);
	/// �U���I���֐��B
	/// </summary>
	void AttackEnd();
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
	/// �ړ��X�s�[�h��ݒ肷��B
	/// </summary>
	void SetSpeed();
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
	/// <summary>
	/// �v���C���[�̃��x����Ԃ��B
	/// </summary>
	/// <returns></returns>
	const int GetPlayerLevel() const
	{
		return m_playerLevel;
	}
	/// <summary>
	/// HP�����炷�B
	/// </summary>
	void ReceiveDamage(int damage)
	{
		m_playerHP -= damage;
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
	/// <summary>
	/// �U���͂�Ԃ��B
	/// </summary>
	/// <returns></returns>
	const int GetmAtaackPow() const
	{
		return m_ataackPow;
	}
	/// <summary>
	/// �v���C���[�̃X�L�����f�������_�[�̃C���X�^���X��Ԃ��B
	/// </summary>
	/// <returns></returns>
	SkinModelRender& GetPlayerSkinModelRemder()
	{
		return *m_playerSkinModel;
	}
	/// <summary>
	/// ����̃��[�u�X�s�[�h��Ԃ��B
	/// </summary>
	/// <returns></returns>
	const Vector3& GetWeaponMoveSpeed() const
	{
		return m_weaponMoveSpeed;
	}
	/// <summary>
	/// �U���t���O��Ԃ��B
	/// </summary>
	/// <returns></returns>
	const bool GetAttackFlag() const
	{
		return m_attackAnimationFlag;
	}
	/// <summary>
	/// �U���ԍ���Ԃ��B
	/// </summary>
	/// <returns></returns>
	const int GetAttackNum() const
	{
		return m_attackNum;
	}
	/// <summary>
	/// �v���C���[�̃L�����R����Ԃ��B
	/// </summary>
	/// <returns></returns>
	CharacterController* GetCharacterController()
	{
		return &m_charaCon;
	}
private:
	PlayerAnimation* m_playerAnim = nullptr;
	SkinModelRender* m_playerSkinModel = nullptr;
	GameCamera* m_gameCam = nullptr;
	PlayerStatusUI* m_playerStatusUI = nullptr;
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
	float m_complementaryFlame = 10.0f;//�A�j���[�V�����⊮���ԁB�t���[�����B
	int jumpStartTimer = 40;
	float m_playerHP = 100.0f;      //HP�B
	int m_ataackPow = 10; //�U���́B

	Weapon* m_weapon[2] = { nullptr, nullptr };

	bool m_attackAnimationFlag = false;
	int attackTimer = 0;
	int m_attackNum = 0; //�U���ԍ��B
	int m_totalAttackAnimationTime = 0; //�U���A�j���[�V�����̍��v�̎��ԁB
	int m_continuousAttackTime = 0;  //�A������ۂ̃A�j���[�V�����̍��v�̎��ԁB
	int m_attackAnimationTimeNum = 0; //�U���A�j���[�V�����̎��Ԃ���ꂽ�z��̔ԍ��B
	int m_attackAnimNum = 0; //X�{�^����Y�{�^���̍U���A�j���[�V�����̐��B
	float m_angle = 0.0f;//��]�p�x�B
	bool m_attackAngleFlag = false;
	Vector3 m_weaponMoveSpeed = Vector3::Zero; //����̃��[�u�X�s�[�h�B
	Vector3 m_oldPosition = Vector3::Zero; //�O�̍��W�B

	bool m_kaihiFlag = false; //����t���O�B
	int m_kaihiTimer = 0;

	int m_playerLevel = 1; //�v���C���[�̃��x���B
	float m_experiencePoint = 0.0f;  //�o���l�B
	float m_nextExperiencePoint = 10.0f; //���ɕK�v�Ȍo���l�B

	Vector3 m_dir = Vector3::Zero;

	int ATTACK_ANIM_NUM_X = 1;//X�{�^���̍U���A�j���[�V�����̐��B
	int ATTACK_ANIM_NUM_Y = 1;//Y�{�^���̍U���A�j���[�V�����̐��B
	bool m_attackFlag = false; //�U�����Ă���t���O�B

	bool m_doNothingFlag = false; //�������Ă��Ȃ��t���O�B
};

