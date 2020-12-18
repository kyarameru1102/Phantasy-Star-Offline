#pragma once
/// <summary>
/// �^�C�g���V�[���B
/// </summary>
class Title : public IGameObject
{
public:
	/// <summary>
	/// �R���X�g���N�^�B
	/// </summary>
	Title();
	/// <summary>
	/// �f�X�g���N�^�B
	/// </summary>
	~Title();
	/// <summary>
	/// �J�n�֐��B
	/// </summary>
	bool Start()override;
	/// <summary>
	/// �X�V�֐��B
	/// </summary>
	void Update()override;
private:
	//��ԁB
	enum TitleState {
		Title_FadeIn,		//�t�F�[�h�C���B
		Title_Font,			//�^�C�g�����A�{�^���̕\���B
		Title_Select,		//�{�^���I���B
		Title_FadeOut,		//�t�F�[�h�A�E�g�B
	};

	//�I���{�^��
	enum EButton {
		Button_Start,
		Button_Load
	};

private:
	void TitleMoveBackGround();		//�w�i�̈ړ������B

	void TitleFadeIn();				//�t�F�[�h�C���B
	void TitleFont();				//�^�C�g�����A�{�^���̕\���B
	void TitleSelect();				//�{�^���I���B
	void TitleFadeOut();			//�t�F�[�h�A�E�g�B

private:
	std::vector<SpriteRender*> m_spriteRender;		//�X�v���C�g�̓��I�z��
	SpriteRender* m_titleSprite = nullptr;			//�X�v���C�g�����_�[�B
	Vector3	m_spritePosition = Vector3::Zero;		//���W�B
	Quaternion m_rot = Quaternion::Identity;		//��]�B	
	
	TitleState m_titleState = Title_FadeIn;			//��ԁB
	EButton m_buttonState = Button_Start;			//�I�𒆂̃{�^����ԁB
private:

	Vector4 m_spriteMul = Vector4::White;
	const Vector4 FADEIN_FINISHED = { 1.0f,1.0f,1.0f,1.0f };	//�t�F�[�h�C�����I���l�B
	const Vector4 FADEOUT_FINISHED = { 0.0f,0.0f,0.0f,1.0f };	//�t�F�[�h�A�E�g���I���l�B

	//background�֘A
	const float m_backTexXPos = 1280.0f;				//�񖇖ڂ�X���W�̈ʒu�B
	Vector3 m_backTexpos1 = Vector3::Zero;				//�w�i�̍��W1�B
	Vector3 m_backTexpos2 = Vector3::Zero;				//�w�i�̍��W2�B
	const float m_backMove = -0.1f;						//�w�i�̈ړ����x�B

};

