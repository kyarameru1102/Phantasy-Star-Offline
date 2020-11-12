#pragma once
#include "Physics/Character/CharacterController.h"
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
	/// スタート関数。
	/// </summary>
	/// <returns></returns>
	bool Start() override;
	/// <summary>
	/// 更新関数。
	/// </summary>
	void Update() override;
	/// <summary>
	/// プレイヤーの座標を返す。
	/// </summary>
	const Vector3& GetPosition() const
	{
		return m_position;
	}
private:
	SkinModelRender* m_playerSkinModel = nullptr;
	Vector3 m_position = Vector3::Zero;//座標。
	Vector3 m_moveSpeed = Vector3::Zero;//ムーブスピード。
	CharacterController m_charaCon;//キャラコン。
	const enum {
		enStay01,
		enStay02,
		enAnimationClipNum
	};
	int m_animState = enStay01; //アニメーションの状態。
	AnimationClip animClip[enAnimationClipNum];//アニメーションクリップ。
};

