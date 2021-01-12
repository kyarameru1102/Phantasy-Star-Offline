#pragma once
#include "Title.h"
#include "PlayerStatus.h"

/// <summary>
/// メニュー画面クラス
/// </summary>
class Game;
class Menu : public IGameObject
{
public:
	Menu();
	~Menu();

	/// <summary>
	/// 更新関数が呼ばれる前に呼ばれる開始関数。
	/// </summary>
	/// <returns>trueを返すと一度だけ呼ばれる</returns>
	bool Start()override;

	/// <summary>
	/// 更新関数。
	/// </summary>
	void Update()override;

	/// <summary>
	/// 矢印を動かす処理。
	/// </summary>
	void ArrowButtonMove();

	/// <summary>
	/// メニューの項目を選択する処理。
	/// </summary>
	void MenuSelect();

private:
	const enum {
		en_menuUIMenu,				//メニュー画面のUI。
		en_menuUIArrowButton,		//矢印のUI。
		en_menuUIReturnTitle,		//タイトルに戻る文字のUI。
		en_menuUIStatusMoji,		//ステータス文字のUI。
		en_menuUINum				//メニューUIの数。
	};

	SpriteRender* m_spriteRender[en_menuUINum] = { nullptr };		//スプライトレンダー。
	Vector3 m_spritePosition[en_menuUINum] = { Vector3::Zero };		//スプライトの座標。

	PlayerStatus* m_playerStatus = nullptr;		//プレイヤーステータスのインスタンス。
	Title* m_title = nullptr;					//タイトルのインスタンス。
	Game* m_game = nullptr;						//ゲームのインスタンス。
};