#pragma once
class GameCamera;
#include "Physics/Character/CharacterController.h"
#include "GameCamera.h"
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
	/// プレイヤーの座標を設定する。
	/// </summary>
	/// <param name="pos">座標。</param>
	void SetPosition(const Vector3& pos)
	{
		m_position = pos;
	}
	/// <summary>
	/// プレイヤーの座標を返す。
	/// </summary>
	/// <returns></returns>
	const Vector3& GetPosition() const
	{
		return m_position;
	}
private:
	SkinModelRender* m_playerSkinModel = nullptr;
	GameCamera* m_gameCam = nullptr;
	Vector3 m_position = Vector3::Zero;//座標。
	Vector3 m_moveSpeed = Vector3::Zero;//ムーブスピード。
	Quaternion m_rotation = Quaternion::Identity; //回転クォータニオン。
	CharacterController m_charaCon;//キャラコン。
	const enum {
		enStay01,            //ブレイド状態。
		enStay02,            //ソード状態。
		enChange01,          //ブレイドからソードに変更。
		enChange02,         //ソードからブレイドに変更。
		attackAndChang01,
		attackAndChang02,
		enAnimationClipNum, //アニメーションクリップの数。
		enBladState,
		enSwordState
	};
	bool m_changeAnimFlag = false;
	int m_changeAnimTimer = 0;
	int m_changeAnimTime = 70;//武器を変えるのにかかるフレーム。
	int m_animState = enStay01; //アニメーションの状態。
	int m_weaponState = enBladState;//武器の状態。
	int m_Chang01State = 0;
	int m_Chang02State = 0;
	AnimationClip animClip[enAnimationClipNum];//アニメーションクリップ。
};

