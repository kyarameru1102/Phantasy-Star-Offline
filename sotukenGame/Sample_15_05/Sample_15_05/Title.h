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
	SkinModelRender* m_ladySkinModelRender = nullptr;
	SkinModelRender* m_bgSkinModelRender = nullptr;
	SpriteRender* m_spriteRender = nullptr;
	Vector3	m_spritePosition = Vector3::Zero;
	Quaternion m_rot = Quaternion::Identity;
	float addRot = 0.0f;
	bool m_ok = false;
};

