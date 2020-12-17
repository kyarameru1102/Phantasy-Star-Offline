#pragma once
#include "GameObject.h"

class BackGround;
class Player;
class GameCamera;
class IStage : public IGameObject
{
public:
	/// <summary>
	/// 更新関数が呼ばれる前に呼ばれる開始関数。
	/// </summary>
	/// <returns>trueを返すと一度だけ呼ばれる</returns>
	virtual bool Start()override { return 0; };

	/// <summary>
	/// 更新関数。
	/// </summary>
	virtual void Update()override {};
	bool GetsceanChangeOK() const
	{
		return m_sceanChangeOK;
	}
protected:
	BackGround* m_backGround = nullptr;				//ステージのインスタンス。
	//Player* m_player = nullptr;
	//GameCamera* m_gameCam = nullptr;
	int m_downEnemy = 0;	//倒したエネミーの数。
	int m_timer = 0;		//タイマー。
	bool m_sceanChangeOK = false;	//シーンを切り替えていいかどうかのフラグ。
};

