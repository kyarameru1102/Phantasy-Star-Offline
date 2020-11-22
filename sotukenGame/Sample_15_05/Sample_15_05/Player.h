#pragma once
class GameCamera;
class Weapon;
#include "Physics/Character/CharacterController.h"
#include "GameCamera.h"
#include "Weapon.h"
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
private:
	SkinModelRender* m_playerSkinModel = nullptr;
	GameCamera* m_gameCam = nullptr;
	Vector3 m_position = Vector3::Zero;//���W�B
	Vector3 m_moveSpeed = Vector3::Zero;//���[�u�X�s�[�h�B
	Quaternion m_rotation = Quaternion::Identity; //��]�N�H�[�^�j�I���B
	CharacterController m_charaCon;//�L�����R���B
	const enum {
		enStay_blad,            //�u���C�h��ԁB
		enStay_sword,            //�\�[�h��ԁB
		enWalk_blad,           //�u���C�h��Ԃŕ����B
		enWalk_sword,           //�\�[�h��Ԃŕ����B
		enRun_blad,            //�u���C�h��Ԃő���B
		enRun_sword,            //�\�[�h��Ԃő���B
		enJumpStart_blad,       //�u���C�h��ԂŃW�����v����B
		enJumpStart_sword,      //�\�[�h��ԂŃW�����v����B
		enStayInTheAir_blad,   //�u���C�h��Ԃő؋�B
		enStayInTheAir_sword,  //�\�[�h��Ԃő؋�B
		enJumpEnd_blad,       //�u���C�h��ԂŃW�����v�I���B
		enJumpEnd_sword,      //�\�[�h��ԂŃW�����v�I���B
		enChange_blad,          //�u���C�h����\�[�h�ɕύX�B
		enChange_sword,         //�\�[�h����u���C�h�ɕύX�B
		enAnimationClipNum, //�A�j���[�V�����N���b�v�̐��B
		enBladState,
		enSwordState
	};
	bool m_changeAnimFlag = false;
	int m_changeAnimTimer = 0;
	int m_changeAnimTime = 70;//�����ς���̂ɂ�����t���[���B
	int m_animState = enStay_blad; //�A�j���[�V�����̏�ԁB
	int m_weaponState = enBladState;//����̏�ԁB
	AnimationClip animClip[enAnimationClipNum];//�A�j���[�V�����N���b�v�B
	bool m_jumpFlag = false;//�W�����v���Ă邩�ǂ����̃t���O�B
	float m_speedY = 0.0f;//Y�����̃X�s�[�h�B
	float m_magnificationSpeed = 5.0f; //�����̔{���B

	int jumpStartTimer = 40;

	Weapon* m_weapon[2] = { nullptr, nullptr };
	int m_weapon01Num = 0; //1�{�ڂ̕���̃{�[���̔ԍ��B
	int m_weapon02Num = 0; //2�{�ڂ̕���̃{�[���̔ԍ��B
	Vector3 m_weaponPos = Vector3::Zero;          //����̍��W�B
	Quaternion m_weaponRot = Quaternion::Identity;//����̉�]�B
	Vector3 m_weaponScale = Vector3::One;       //����̃X�P�[���B

};

