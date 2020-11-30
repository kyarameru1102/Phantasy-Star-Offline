#pragma once
class GameCamera;
class Weapon;
#include "Physics/Character/CharacterController.h"
#include "GameCamera.h"
#include "Weapon.h"
#include "PlayerAnimation.h"
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
	/// 攻撃。
	/// </summary>
	void Attack();
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
	/// 向きと移動スピードを設定する。
	/// </summary>
	void SetDirAndSpeed();
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
	Vector3 GetRootPos()
	{
		return m_rootPos;
	}
	bool GetAttackFlag()
	{
		return m_attackFlag;
	}
	/// <summary>
	/// HPを設定。
	/// </summary>
	/// <param name="hp">HP</param>
	void SetHP(const float hp)
	{
		m_playerHP = hp;
	}
	/// <summary>
	/// HPを返す。
	/// </summary>
	/// <returns></returns>
	const float GetHP() const
	{
		return m_playerHP;
	}
private:
	PlayerAnimation* m_playerAnim = nullptr;
	SkinModelRender* m_playerSkinModel = nullptr;
	GameCamera* m_gameCam = nullptr;
	Vector3 m_position = Vector3::Zero;//座標。
	Vector3 m_moveSpeed = Vector3::Zero;//ムーブスピード。
	Quaternion m_rotation = Quaternion::Identity; //回転クォータニオン。
	CharacterController m_charaCon;//キャラコン。
	enum {
		enBladState,
		enSwordState
	};
	bool m_changeAnimFlag = false;
	int m_changeAnimTimer = 0;
	int m_changeAnimTime = 35;//武器を変えるのにかかるフレーム。
	int m_animState = enStay_blad; //アニメーションの状態。
	int m_weaponState = enBladState;//武器の状態。
	bool m_jumpFlag = false;//ジャンプしてるかどうかのフラグ。
	float m_speedY = 0.0f;//Y方向のスピード。
	float m_magnificationSpeed = 5.0f; //速さの倍率。
	float m_complementaryTime = 0.0f;//アニメーション補完時間。
	int jumpStartTimer = 40;
	float m_playerHP = 100.0f;      //HP。

	Weapon* m_weapon[2] = { nullptr, nullptr };
	int m_weapon01Num = 0; //1本目の武器のボーンの番号。
	int m_weapon02Num = 0; //2本目の武器のボーンの番号。
	Vector3 m_weaponPos = Vector3::Zero;          //武器の座標。
	Quaternion m_weaponRot = Quaternion::Identity;//武器の回転。
	Vector3 m_weaponScale = Vector3::One;       //武器のスケール。

	bool m_attackFlag = false;
	int attackTimer = 0;
	int m_weapon03Num = 0; //3本目のボーンの番号。
	Vector3 m_rootPos = Vector3::Zero;
	Quaternion m_rot = Quaternion::Identity;
	Vector3 m_rootScale = Vector3::One;
	Vector3 v = Vector3::Zero;
	Vector3 m_rerootpos = Vector3::Zero;
	bool m_flag = false;
	int m_attackNum = 0;
	int time = 0;
	int m_continuousAttackTime = 0;
	int num = 0;
};

