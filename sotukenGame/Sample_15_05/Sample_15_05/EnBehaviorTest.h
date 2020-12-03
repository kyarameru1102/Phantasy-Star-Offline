#pragma once
/// <summary>
/// �G�����m�F�N���X
/// </summary>
#include "EnTest.h"
#include "DrBoar.h"
#include "BackGround.h";
#include "Player.h"
#include "GameCamera.h"
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
	DrBoar* m_drboar = nullptr;
	BackGround* m_bg = nullptr;
	Player* m_player = nullptr;
	GameCamera* m_gameCam = nullptr;
};

