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

	void AttackFlag(int attackTime01_blad, int attackAnimNum, int attackTime01_sword);
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
	/// 移動スピードを設定する。
	/// </summary>
	void SetSpeed();
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
	/// <summary>
	/// プレイヤーのスキンモデルレンダーのインスタンスを返す。
	/// </summary>
	/// <returns></returns>
	SkinModelRender& GetPlayerSkinModelRemder()
	{
		return *m_playerSkinModel;
	}
	/// <summary>
	/// 武器のムーブスピードを返す。
	/// </summary>
	/// <returns></returns>
	const Vector3& GetWeaponMoveSpeed() const
	{
		return m_weaponMoveSpeed;
	}
	/// <summary>
	/// 攻撃フラグを返す。
	/// </summary>
	/// <returns></returns>
	const bool GetAttackFlag() const
	{
		return m_attackFlag;
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
	float m_complementaryFlame = 10.0f;//アニメーション補完時間。フレーム数。
	int jumpStartTimer = 40;
	float m_playerHP = 100.0f;      //HP。

	Weapon* m_weapon[2] = { nullptr, nullptr };

	bool m_attackFlag = false;
	int attackTimer = 0;
	int m_attackNum = 0;
	int m_totalAttackAnimationTime = 0; //攻撃アニメーションの合計の時間。
	int m_continuousAttackTime = 0;  //連撃する際のアニメーションの合計の時間。
	int m_attackAnimationTimeNum = 0; //攻撃アニメーションの時間を入れた配列の番号。
	int m_attackAnimNum = 0; //XボタンかYボタンの攻撃アニメーションの数。
	float m_angle = 0.0f;//回転角度。
	bool m_attackAngleFlag = false;
	Vector3 m_weaponMoveSpeed = Vector3::Zero; //武器のムーブスピード。
	Vector3 m_oldPosition = Vector3::Zero; //前の座標。
};

