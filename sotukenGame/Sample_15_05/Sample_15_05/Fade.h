#pragma once

/// <summary>
/// fade�N���X�B
/// </summary>
class Fade : public IGameObject
{
public:
	Fade();
	~Fade();

	/// <summary>
	/// �X�V�֐����Ă΂��O�ɌĂ΂��J�n�֐��B
	/// </summary>
	/// <returns>true��Ԃ��ƈ�x�����Ă΂��</returns>
	bool Start()override;
	/// <summary>
	/// �X�V�֐��B
	/// </summary>
	void Update()override;

public:
	//�t�F�[�h�̑I����ԁB
	const enum FadeType {
		Fade_In,			//�t�F�[�h�C���B
		Fade_Out,			//�t�F�[�h�A�E�g�B
		Fade_DoNothing		//�������Ȃ��B
	};

	/// <summary>
	/// �t�F�[�h�̐ݒ�B
	/// </summary>
	/// <param name="sprite">�X�v���C�g</param>
	/// <param name="m_State">�t�F�[�h�^�C�v</param>
	/// <param name="m_time">�t�F�[�h����</param>
	void FadeSet(SpriteRender* sprite, const FadeType& m_State, float m_time)
	{
		m_fadeSprite = sprite;
		m_fadeState = m_State;
		m_mulColorAddValue = 1.0f / m_time;
	}

private:
	void FadeIn();		//�t�F�[�h�C���B
	void FadeOut();		//�t�F�[�h�A�E�g�B
	void DoNothing();	//�������Ȃ��B

private:
	SpriteRender* m_fadeSprite = nullptr;		//�t�F�[�h������X�v���C�g�B
	Vector4 m_mulColor = { Vector4::White };	//�t�F�[�h�p�̏�Z�J���[�B
	FadeType m_fadeState = Fade_DoNothing;		//�t�F�[�h�̑I����ԁB

	float m_mulColorAddValue = 0.0f;			//��Z�J���[�ɉ��Z����l�B

	const float FADEIN_FINISHED = 1.0f;			//�t�F�[�h�C�����I��������l�B
	const float FADEOUT_FINISHED = 0.0f;		//�t�F�[�h�A�E�g���I��������l�B

};

