#pragma once
/// <summary>
/// プレイヤークラス。
/// </summary>
class Player : public IGameObject
{
public:
	/// <summary>
	/// コンストラクタ。
	/// </summary>
	Player();
	/// <summary>
	/// デストラクタ。
	/// </summary>
	~Player();
	/// <summary>
	/// 更新関数。
	/// </summary>
	void Update() override;

	SkinModelRender* m_playerSkinModel = nullptr;

	const enum {
		enStay01,
		enStay02,
		enAnimationClipNum
	};
	int m_animState = enStay01; //アニメーションの状態。
	AnimationClip animClip[enAnimationClipNum];//アニメーションクリップ。
};

