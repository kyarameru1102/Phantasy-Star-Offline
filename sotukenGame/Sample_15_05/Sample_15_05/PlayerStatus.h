#pragma once
#include "Player.h"

/// <summary>
/// プレイヤーのステータスクラス。
/// </summary>
class PlayerStatus : public IGameObject
{
public:
	PlayerStatus();
	~PlayerStatus();

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
	Player* m_player = nullptr;					//プレイヤーのインスタンス。
	SpriteRender* m_spriteRender = nullptr;		//スプライトレンダー。
};