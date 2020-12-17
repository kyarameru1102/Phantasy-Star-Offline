#pragma once
#include "Game.h"
#include "BackGround.h"
#include "DrBoar.h"
#include "Title.h"

class Stage1 : public IGameObject
{
public:
	Stage1();
	~Stage1();

	/// <summary>
	/// 更新関数が呼ばれる前に呼ばれる開始関数。
	/// </summary>
	/// <returns>trueを返すと一度だけ呼ばれる</returns>
	bool Start()override;

	/// <summary>
	/// 更新関数。
	/// </summary>
	void Update()override;

private:
	enum {
		ENEMY_NUM = 2		//エネミーの数。
	};

	Game* m_game = nullptr;
	BackGround* m_backGround = nullptr;				//ステージのインスタンス。
	DrBoar* m_drBoar[ENEMY_NUM] = { nullptr };		//ドラゴンボア(敵)のインスタンス。
	Title* m_title = nullptr;						//タイトルのインスタンス。

	int m_downEnemy = 0;	//倒したエネミーの数。
	int m_timer = 0;		//タイマー。
};

