#pragma once
#include "IStage.h"

class BossBoar;
class Stage3 : public IStage
{
public:
	Stage3();
	~Stage3();

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
	BossBoar* m_bossBoar = nullptr;
};

