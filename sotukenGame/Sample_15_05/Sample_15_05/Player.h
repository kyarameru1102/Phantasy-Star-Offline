#pragma once
class GameCamera;
#include "Physics/Character/CharacterController.h"
#include "GameCamera.h"
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
		enStay01,            //�u���C�h��ԁB
		enStay02,            //�\�[�h��ԁB
		enChange01,          //�u���C�h����\�[�h�ɕύX�B
		enChange02,         //�\�[�h����u���C�h�ɕύX�B
		attackAndChang01,
		attackAndChang02,
		enAnimationClipNum, //�A�j���[�V�����N���b�v�̐��B
		enBladState,
		enSwordState
	};
	bool m_changeAnimFlag = false;
	int m_changeAnimTimer = 0;
	int m_changeAnimTime = 70;//�����ς���̂ɂ�����t���[���B
	int m_animState = enStay01; //�A�j���[�V�����̏�ԁB
	int m_weaponState = enBladState;//����̏�ԁB
	int m_Chang01State = 0;
	int m_Chang02State = 0;
	AnimationClip animClip[enAnimationClipNum];//�A�j���[�V�����N���b�v�B
};

