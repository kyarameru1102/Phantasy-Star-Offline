#pragma once
#include "Player.h"
#include "GameCamera.h"
#include "BackGround.h"
#include "Menu.h"
#include"DrBoar.h"

#include "Stage1.h"
/// <summary>
/// �Q�[���V�[���B
/// </summary>

class Stage1;
class PlayerStatusUI;
class Game : public IGameObject
{
public:
	/// <summary>
	/// �R���X�g���N�^�B
	/// </summary>
	Game();
	/// <summary>
	/// �f�X�g���N�^�B
	/// </summary>
	~Game();
	/// <summary>
	/// �X�^�[�g�֐��B
	/// </summary>
	/// <returns></returns>
	bool Start() override;
	/// <summary>
	/// �X�V�֐��B
	/// </summary>
	void Update() override;
private:
	SkinModelRender* m_ladySkinModelRender = nullptr;
	Player* m_player = nullptr;
	GameCamera* m_gameCam = nullptr;
	//BackGround* m_bg = nullptr;
	PlayerStatusUI* m_playerStatusUI = nullptr;
	//DrBoar* m_drBoar[3];
	Menu* m_menu = nullptr;				//���j���[�̃C���X�^���X�B

	Stage1* m_stage1 = nullptr;
};

