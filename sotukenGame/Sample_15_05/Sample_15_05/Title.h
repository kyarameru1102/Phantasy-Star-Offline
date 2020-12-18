#pragma once
/// <summary>
/// タイトルシーン。
/// </summary>
class Title : public IGameObject
{
public:
	/// <summary>
	/// コンストラクタ。
	/// </summary>
	Title();
	/// <summary>
	/// デストラクタ。
	/// </summary>
	~Title();
	/// <summary>
	/// 開始関数。
	/// </summary>
	bool Start()override;
	/// <summary>
	/// 更新関数。
	/// </summary>
	void Update()override;
private:
	//状態。
	enum TitleState {
		Title_FadeIn,		//フェードイン。
		Title_Font,			//タイトル名、ボタンの表示。
		Title_Select,		//ボタン選択。
		Title_FadeOut,		//フェードアウト。
	};

	//選択ボタン
	enum EButton {
		Button_Start,
		Button_Load
	};

private:
	void TitleMoveBackGround();		//背景の移動処理。

	void TitleFadeIn();				//フェードイン。
	void TitleFont();				//タイトル名、ボタンの表示。
	void TitleSelect();				//ボタン選択。
	void TitleFadeOut();			//フェードアウト。

private:
	std::vector<SpriteRender*> m_spriteRender;		//スプライトの動的配列
	SpriteRender* m_titleSprite = nullptr;			//スプライトレンダー。
	Vector3	m_spritePosition = Vector3::Zero;		//座標。
	Quaternion m_rot = Quaternion::Identity;		//回転。	
	
	TitleState m_titleState = Title_FadeIn;			//状態。
	EButton m_buttonState = Button_Start;			//選択中のボタン状態。
private:

	Vector4 m_spriteMul = Vector4::White;
	const Vector4 FADEIN_FINISHED = { 1.0f,1.0f,1.0f,1.0f };	//フェードインが終わる値。
	const Vector4 FADEOUT_FINISHED = { 0.0f,0.0f,0.0f,1.0f };	//フェードアウトが終わる値。

	//background関連
	const float m_backTexXPos = 1280.0f;				//二枚目のX座標の位置。
	Vector3 m_backTexpos1 = Vector3::Zero;				//背景の座標1。
	Vector3 m_backTexpos2 = Vector3::Zero;				//背景の座標2。
	const float m_backMove = -0.1f;						//背景の移動速度。

};

