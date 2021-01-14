#pragma once
#define _USE_MATH_DEFINES
class GameCamera;
class Weapon;
class PlayerStatusUI;
class PlayerAttackAnimation;
#include <math.h>
#include "Physics/Character/CharacterController.h"
#include "PlayerAnimation.h"

enum {
	//����̏�ԁB
	enBladState,//�u���C�h��ԁB
	enSwordState,//�\�[�h��ԁB
	//�ʏ�U���B�U���̏�Ԃ𒲂ׂ�̂Ɏg���B
	enNormalState,
	//���{�^���ōU�����Ă��邩�B
	noAttack,//�U�����Ă��Ȃ��B
	attackX,//X�{�^���B
	attackY,//Y�{�^���B
	attackS//����U���B
};

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
	/// ��]�B
	/// </summary>
	void Rotation();
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
	/// �U���A�j���[�V�����t���O��ݒ肷��B
	/// </summary>
	/// <param name="flag">�t���O�B</param>
	void SetAttackAnimationFlag(const bool flag)
	{
		m_attackAnimationFlag = flag;
	}
	/// <summary>
	/// �U���A�j���[�V�����t���O��Ԃ��B
	/// </summary>
	/// <returns></returns>
	const bool GetAttackAnimationFlag() const
	{
		return m_attackAnimationFlag;
	}
	/// <summary>
	/// �v���C���[�̃L�����R����Ԃ��B
	/// </summary>
	/// <returns></returns>
	CharacterController* GetCharacterController()
	{
		return &m_charaCon;
	}
	/// <summary>
	/// ���S�t���O��Ԃ��B
	/// </summary>
	/// <returns></returns>
	const bool GetDeathFlag() const
	{
		return m_deathFlag;
	}
	/// <summary>
	/// ����̏�Ԃ�ݒ肷��B
	/// false�Ȃ�u���C�h��Ԃɂ���B
	/// true�Ȃ�\�[�h��Ԃɂ���B
	/// </summary>
	/// <param name="falseOrTrue"></param>
	void SetWeaponState(const bool falseOrTrue)
	{
		if (falseOrTrue != true) {
			m_weaponState = enBladState;
		}
		else {
			m_weaponState = enSwordState;
		}
	}
	/// <summary>
	/// ����̏�Ԃ�Ԃ��B
	/// </summary>
	/// <returns></returns>
	const int GetWeaponState() const
	{
		return m_weaponState;
	}
	/// <summary>
	/// �U�����Ă���t���O��ݒ肷��B
	/// </summary>
	/// <param name="flag"></param>
	void SetAttackFlag(const bool flag)
	{
		m_attackFlag = flag;
	}
	/// <summary>
	/// �U�����Ă���t���O��Ԃ��B
	/// </summary>
	/// <returns></returns>
	const bool GetAttackFlag() const
	{
		return m_attackFlag;
	}
	/// <summary>
	/// �U�����A�v���C���[�̌�����ς���t���O��ݒ肷��B
	/// </summary>
	/// <param name="flag"></param>
	void SetAttackAngleFlag(const bool flag)
	{
		m_attackAngleFlag = flag;
	}
	/// <summary>
	/// �A�j���[�V�����ԍ���ݒ肷��B
	/// </summary>
	/// <param name="animState">�A�j���[�V�����ԍ��B</param>
	void SetAnimState(const int animState)
	{
		m_animState = animState;
	}
	/// <summary>
	/// �A�j���[�V�����ԍ���Ԃ��B
	/// </summary>
	/// <returns></returns>
	const int GetAnimState() const
	{
		return m_animState;
	}
	/// <summary>
	/// ���[�u�X�s�[�h��ݒ肷��B
	/// </summary>
	/// <param name="moveSpeed"></param>
	void SetMoveSpeed(Vector3 moveSpeed)
	{
		m_moveSpeed = moveSpeed;
	}
	/// <summary>
	/// ���[�u�X�s�[�h��Ԃ��B
	/// </summary>
	/// <returns></returns>
	const Vector3& GetMoveSpeed() const
	{
		return m_moveSpeed;
	}
	/// <summary>
	/// ������Ԃ��B
	/// </summary>
	/// <returns></returns>
	const Vector3& GetDir() const
	{
		return m_dir;
	}
	/// <summary>
	/// �Ȃ�̍U���{�^��������������ݒ肷��B
	/// </summary>
	/// <param name="AXY"></param>
	void SetAttackXOrY(const int AXY)
	{
		m_attackXOrY = AXY;
	}
	/// <summary>
	/// �Ȃ�̍U���{�^��������������Ԃ��B
	/// </summary>
	/// <returns></returns>
	const int GetAttackXOrY() const
	{
		return m_attackXOrY;
	}
	/// <summary>
	/// ����U���̃t���O��ݒ肷��B
	/// </summary>
	/// <param name="flag">�t���O�B</param>
	void SetSpecialAttackFlag(const bool flag)
	{
		m_specialAttackFlag = flag;
	}
	/// <summary>
	/// ����U���̃t���O��Ԃ��B
	/// </summary>
	/// <returns></returns>
	const bool GetSpecialAttackFlag() const
	{
		return m_specialAttackFlag;
	}
	void SetSpecialAttackState(const int attackState)
	{
		m_specialAttackState = attackState;
	}
	const int GetSpecialAttackState() const
	{
		return m_specialAttackState;
	}
private:
	PlayerAnimation* m_playerAnim = nullptr;
	SkinModelRender* m_playerSkinModel = nullptr;
	GameCamera* m_gameCam = nullptr;
	PlayerStatusUI* m_playerStatusUI = nullptr;
	PlayerAttackAnimation* m_playerAttackAnim = nullptr;
	Vector3 m_position = Vector3::Zero;//���W�B
	Vector3 m_moveSpeed = Vector3::Zero;//���[�u�X�s�[�h�B
	Quaternion m_rotation = Quaternion::Identity; //��]�N�H�[�^�j�I���B
	CharacterController m_charaCon;//�L�����R���B
	bool m_changeAnimFlag = false;
	int m_changeAnimTimer = 0;
	int m_changeAnimTime = 35;//�����ς���̂ɂ�����t���[���B
	int m_animState = enStay_blad; //�A�j���[�V�����̏�ԁB
	int m_weaponState = enBladState;//����̏�ԁB
	bool m_jumpFlag = false;//�W�����v���Ă邩�ǂ����̃t���O�B
	float m_speedY = 0.0f;//Y�����̃X�s�[�h�B
	float m_magnificationSpeed = 5.0f; //���[�u�X�s�[�h�̔{���B
	float m_complementaryFlame = 10.0f;//�A�j���[�V�����⊮���ԁB�t���[�����B
	int jumpStartTimer = 40;
	float m_playerHP = 100.0f;      //HP�B
	float m_beforeHp = 0.0f;
	int m_ataackPow = 10; //�U���́B
	Weapon* m_weapon[2] = { nullptr, nullptr };
	bool m_attackAnimationFlag = false;
	float m_angle = 0.0f;//��]�p�x�B
	bool m_attackAngleFlag = false;
	Vector3 m_weaponMoveSpeed = Vector3::Zero; //����̃��[�u�X�s�[�h�B
	Vector3 m_oldPosition = Vector3::Zero; //�O�̍��W�B
	bool m_kaihiFlag = false; //����t���O�B
	int m_kaihiTimer = 0;
	int m_playerLevel = 1; //�v���C���[�̃��x���B
	float m_experiencePoint = 0.0f;  //�o���l�B
	float m_nextExperiencePoint = 10.0f; //���ɕK�v�Ȍo���l�B
	Vector3 m_dir = Vector3::Zero; //�����Ă�������B
	int m_attackAnimNumX = 1;//X�{�^���̍U���A�j���[�V�����̐��B
	int m_attackAnimNumY = 1;//Y�{�^���̍U���A�j���[�V�����̐��B
	bool m_attackFlag = false; //�U�����Ă���t���O�B
	bool m_doNothingFlag = false; //�������Ă��Ȃ��t���O�B
	bool m_deathFlag = false;
	int m_attackXOrY = noAttack;
	bool m_specialAttackFlag = false;
	int m_specialAttackState = enNormalState;
};

