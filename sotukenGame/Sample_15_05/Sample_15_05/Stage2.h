#pragma once
#include "IStage.h"

/// <summary>
/// �X�e�[�W2�B
/// </summary>
class DrBoar;
class Stage2 : public IStage
{
public:
	Stage2();
	~Stage2();

	/// <summary>
	/// �X�V�֐����Ă΂��O�ɌĂ΂��J�n�֐��B
	/// </summary>
	/// <returns>true��Ԃ��ƈ�x�����Ă΂��</returns>
	bool Start()override;

	/// <summary>
	/// �X�V�֐��B
	/// </summary>
	void Update()override;
private:
	enum {
		ENEMY_NUM = 2		//�G�l�~�[�̐��B
	};
	DrBoar* m_drBoar[ENEMY_NUM] = { nullptr };		//�h���S���{�A(�G)�̃C���X�^���X�B
};

