#pragma once
/// <summary>
/// �G�����m�F�N���X
/// </summary>
#include "EnTest.h"

class EnBehaviorTest : public IGameObject
{
public:
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
	EnTest* m_entest = nullptr;
};

