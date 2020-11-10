#pragma once
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
	/// �X�V�֐��B
	/// </summary>
	void Update() override;

	SkinModelRender* m_playerSkinModel = nullptr;

	const enum {
		enStay01,
		enStay02,
		enAnimationClipNum
	};
	int m_animState = enStay01; //�A�j���[�V�����̏�ԁB
	AnimationClip animClip[enAnimationClipNum];//�A�j���[�V�����N���b�v�B
};

