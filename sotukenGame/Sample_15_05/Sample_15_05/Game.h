#pragma once
#include "Player.h"
#include "GameCamera.h"
#include "BackGround.h"
#include "Menu.h"
#include "DrBoar.h"


/// <summary>
/// ゲームシーン。
/// </summary>

class Stage1;
class Stage2;
class Stage3;
class PlayerStatusUI;
class Game : public IGameObject
{
public:
	/// <summary>
	/// コンストラクタ。
	/// </summary>
	Game();
	/// <summary>
	/// デストラクタ。
	/// </summary>
	~Game();
	/// <summary>
	/// スタート関数。
	/// </summary>
	/// <returns></returns>
	bool Start() override;
	/// <summary>
	/// 更新関数。
	/// </summary>
	void Update() override;
private:
	SkinModelRender* m_ladySkinModelRender = nullptr;
	Player* m_player = nullptr;
	GameCamera* m_gameCam = nullptr;
	//BackGround* m_bg = nullptr;
	PlayerStatusUI* m_playerStatusUI = nullptr;
	//DrBoar* m_drBoar[3];
	Menu* m_menu = nullptr;				//メニューのインスタンス。

	Stage1* m_stage1 = nullptr;
	Stage2* m_stage2 = nullptr;
	Stage3* m_stage3 = nullptr;
};

