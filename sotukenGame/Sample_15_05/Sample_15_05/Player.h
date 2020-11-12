#pragma once
#include "Physics/Character/CharacterController.h"
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
	/// �v���C���[�̍��W��Ԃ��B
	/// </summary>
	const Vector3& GetPosition() const
	{
		return m_position;
	}
private:
	SkinModelRender* m_playerSkinModel = nullptr;
	Vector3 m_position = Vector3::Zero;//���W�B
	Vector3 m_moveSpeed = Vector3::Zero;//���[�u�X�s�[�h�B
	CharacterController m_charaCon;//�L�����R���B
	const enum {
		enStay01,
		enStay02,
		enAnimationClipNum
	};
	int m_animState = enStay01; //�A�j���[�V�����̏�ԁB
	AnimationClip animClip[enAnimationClipNum];//�A�j���[�V�����N���b�v�B
};

