#pragma once
//�G�����m�F�N���X
class EnBehaviorTest : public IGameObject
{
	/// <summary>
	/// �R���X�g���N�^�B
	/// </summary>
	EnBehaviorTest();
	/// <summary>
	/// �f�X�g���N�^�B
	/// </summary>
	~EnBehaviorTest();
	/// <summary>
	/// �X�^�[�g�֐��B
	/// </summary>
	/// <returns></returns>
	bool Start() override;
	/// <summary>
	/// �X�V�֐��B
	/// </summary>
	void Update() override;
};

