#pragma once
#include "Player.h"
#include "GameCamera.h"
#include "BackGround.h"
/// <summary>
/// �Q�[���V�[���B
/// </summary>

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
	BackGround* m_bg = nullptr;
	PlayerStatusUI* m_playerStatusUI = nullptr;
};

