#pragma once
#include "Title.h"

/// <summary>
/// メニュー画面クラス
/// </summary>
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

	Title* m_title = nullptr;
};

