#pragma once
/// <summary>
/// �G�̌Q��𐶐�����N���X
/// </summary>
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
};

