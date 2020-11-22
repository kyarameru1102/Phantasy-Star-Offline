#pragma once
class GameCamera;
class Weapon;
#include "Physics/Character/CharacterController.h"
#include "GameCamera.h"
#include "Weapon.h"
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
	/// Y方向の移動。ジャンプや落下時の処理。
	/// </summary>
	void YDirMove();
	/// <summary>
	/// 武器変更。
	/// </summary>
	void WeaponChange();
	/// <summary>
	/// 武器の座標、回転を設定する。
	/// </summary>
	void SetWeaponTR();
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
		enStay_blad,            //ブレイド状態。
		enStay_sword,            //ソード状態。
		enWalk_blad,           //ブレイド状態で歩く。
		enWalk_sword,           //ソード状態で歩く。
		enRun_blad,            //ブレイド状態で走る。
		enRun_sword,            //ソード状態で走る。
		enJumpStart_blad,       //ブレイド状態でジャンプする。
		enJumpStart_sword,      //ソード状態でジャンプする。
		enStayInTheAir_blad,   //ブレイド状態で滞空。
		enStayInTheAir_sword,  //ソード状態で滞空。
		enJumpEnd_blad,       //ブレイド状態でジャンプ終了。
		enJumpEnd_sword,      //ソード状態でジャンプ終了。
		enChange_blad,          //ブレイドからソードに変更。
		enChange_sword,         //ソードからブレイドに変更。
		enAnimationClipNum, //アニメーションクリップの数。
		enBladState,
		enSwordState
	};
	bool m_changeAnimFlag = false;
	int m_changeAnimTimer = 0;
	int m_changeAnimTime = 70;//武器を変えるのにかかるフレーム。
	int m_animState = enStay_blad; //アニメーションの状態。
	int m_weaponState = enBladState;//武器の状態。
	AnimationClip animClip[enAnimationClipNum];//アニメーションクリップ。
	bool m_jumpFlag = false;//ジャンプしてるかどうかのフラグ。
	float m_speedY = 0.0f;//Y方向のスピード。
	float m_magnificationSpeed = 5.0f; //速さの倍率。

	int jumpStartTimer = 40;

	Weapon* m_weapon[2] = { nullptr, nullptr };
	int m_weapon01Num = 0; //1本目の武器のボーンの番号。
	int m_weapon02Num = 0; //2本目の武器のボーンの番号。
	Vector3 m_weaponPos = Vector3::Zero;          //武器の座標。
	Quaternion m_weaponRot = Quaternion::Identity;//武器の回転。
	Vector3 m_weaponScale = Vector3::One;       //武器のスケール。

};

