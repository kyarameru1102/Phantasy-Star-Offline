#pragma once
/// <summary>
/// �^�C�g���V�[���B
/// </summary>
class Title : public GameObject
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
	SkinModelRender* m_ladySkinModelRender = nullptr;
	SkinModelRender* m_bgSkinModelRender = nullptr;
};

