#pragma once
/// <summary>
/// プレイヤーステータスのUIクラス。
/// </summary>
class PlayerStatusUI : public IGameObject
{
public:
	PlayerStatusUI();
	~PlayerStatusUI();

	/// <summary>
	/// 更新関数が呼ばれる前に呼ばれる開始関数。
	/// </summary>
	/// <returns>trueを返すと一度だけ呼ばれる。</returns>
	bool Start()override;

	/// <summary>
	/// 更新関数。
	/// </summary>
	void Update()override;

	/// <summary>
	/// 現在のプレイヤーHPを設定。
	/// </summary>
	/// <param name="currentHP">現在のプレイヤーのHPを設定</param>
	void SetCurrentPlayerHP(const float& currentHP)
	{
		m_currentPlayerHP = currentHP;
	}

	/// <summary>
	/// 現在のプレイヤーHPを取得。
	/// </summary>
	/// <returns>現在のプレイヤーのHP</returns>
	const float& GetCurrentPlayerHP() const
	{
		return m_currentPlayerHP;
	}

private:

	const enum {
		en_playerUIHP,			//プレイヤーHPのUI。
		en_playerUIPP,			//プレイヤーPPのUI。
		en_playerUIHPBer,		//HPBerのUI。
		en_playerUIPPBer,		//PPBerのUI。
		en_playerUIStatus,		//ステータスのUI。
		en_playerUINum			//プレイヤーUIの数。
	};

	SpriteRender* m_statusSprite = nullptr;		//プレイヤーステータスのスプライトレンダー。
	SpriteRender* m_hpSprite =  nullptr;		//プレイヤーHPのスプライトレンダー。
	SpriteRender* m_ppSprite = nullptr;			//プレイヤーPPのスプライトレンダー。
	SpriteRender* m_hpBerSprite = nullptr;		//HPBerのスプライトレンダー。
	SpriteRender* m_ppBerSprite = nullptr;		//PPBerのスプライトレンダー。

	Vector3 m_spritePosition[en_playerUINum] = { Vector3::Zero };	//スプライトの座標。
	Vector3 m_spriteScale[en_playerUINum] = { Vector3::One };		//スプライトの拡大率。
	Vector2 m_spritePivot[en_playerUINum] = { { 0.5f, 0.5f } };		//スプライトのピボット。

	float m_currentPlayerHP = 0.0f;		//プレイヤーの現在のHP。
	float m_hp = 0.0f;					//プレイヤーの現在のHPを保存する変数。

	int c = 0;
};

