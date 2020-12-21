#pragma once

/// <summary>
/// fadeクラス。
/// </summary>
class Fade : public IGameObject
{
public:
	Fade();
	~Fade();

	/// <summary>
	/// 更新関数が呼ばれる前に呼ばれる開始関数。
	/// </summary>
	/// <returns>trueを返すと一度だけ呼ばれる</returns>
	bool Start()override;
	/// <summary>
	/// 更新関数。
	/// </summary>
	void Update()override;

public:
	//フェードの選択状態。
	const enum FadeType {
		Fade_In,			//フェードイン。
		Fade_Out,			//フェードアウト。
		Fade_DoNothing		//何もしない。
	};

	/// <summary>
	/// フェードの設定。
	/// </summary>
	/// <param name="sprite">スプライト</param>
	/// <param name="m_State">フェードタイプ</param>
	/// <param name="m_time">フェード時間</param>
	void FadeSet(SpriteRender* sprite, const FadeType& m_State, float m_time)
	{
		m_fadeSprite = sprite;
		m_fadeState = m_State;
		m_mulColorAddValue = 1.0f / (m_time * 100);
	}

private:
	void FadeIn();		//フェードイン。
	void FadeOut();		//フェードアウト。
	void DoNothing();	//何もしない。

private:
	SpriteRender* m_fadeSprite = nullptr;		//フェードさせるスプライト。
	Vector4 m_mulColor = { Vector4::White };	//フェード用の乗算カラー。
	FadeType m_fadeState = Fade_DoNothing;		//フェードの選択状態。

	float m_mulColorAddValue = 0.0f;			//乗算カラーに加算する値。

	const float FADEIN_FINISHED = 1.0f;			//フェードインを終了させる値。
	const float FADEOUT_FINISHED = 0.0f;		//フェードアウトを終了させる値。

};

