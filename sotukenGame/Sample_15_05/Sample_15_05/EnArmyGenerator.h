#pragma once
#include "Random.h"
/// <summary>
/// �G�̌Q��𐶐�����N���X
/// </summary>
class Random;
class EnArmyGenerator : public IGameObject
{
public:
	/// <summary>
	/// �R���X�g���N�^�B
	/// </summary>
	EnArmyGenerator();
	/// <summary>
	/// �f�X�g���N�^�B
	/// </summary>
	~EnArmyGenerator();
	void Update()override;
	Random m_random;
};

