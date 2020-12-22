#pragma once
#define _USE_MATH_DEFINES
class GameCamera;
class Weapon;
#include <math.h>
#include "Physics/Character/CharacterController.h"
#include "GameCamera.h"
#include "Weapon.h"
#include "PlayerAnimation.h"
#include "PlayerStatusUI.h"
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
	/// プレイヤーが経験値を取得する。ゲッターじゃないよ！！
	/// </summary>
	/// <param name="experiencePoint">倒した敵の経験値。</param>
	void GetExperiencePoint(const float experiencePoint);
	void AttackFlag(int attackTime01_blad, int attackAnimNum, int attackTime01_sword);
	/// 攻撃終了関数。
	/// </summary>
	void AttackEnd();
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
	/// プレイヤーのレベルを返す。
	/// </summary>
	/// <returns></returns>
	const int GetPlayerLevel() const
	{
		return m_playerLevel;
	}
	/// <summary>
	/// HPを減らす。
	/// </summary>
	void ReceiveDamage(int damage)
	{
		m_playerHP -= damage;
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
	/// 攻撃力を返す。
	/// </summary>
	/// <returns></returns>
	const int GetmAtaackPow() const
	{
		return m_ataackPow;
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
		return m_attackAnimationFlag;
	}
	/// <summary>
	/// 攻撃番号を返す。
	/// </summary>
	/// <returns></returns>
	const int GetAttackNum() const
	{
		return m_attackNum;
	}
	/// <summary>
	/// プレイヤーのキャラコンを返す。
	/// </summary>
	/// <returns></returns>
	CharacterController* GetCharacterController()
	{
		return &m_charaCon;
	}
private:
	PlayerAnimation* m_playerAnim = nullptr;
	SkinModelRender* m_playerSkinModel = nullptr;
	GameCamera* m_gameCam = nullptr;
	PlayerStatusUI* m_playerStatusUI = nullptr;
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
	int m_ataackPow = 10; //攻撃力。

	Weapon* m_weapon[2] = { nullptr, nullptr };

	bool m_attackAnimationFlag = false;
	int attackTimer = 0;
	int m_attackNum = 0; //攻撃番号。
	int m_totalAttackAnimationTime = 0; //攻撃アニメーションの合計の時間。
	int m_continuousAttackTime = 0;  //連撃する際のアニメーションの合計の時間。
	int m_attackAnimationTimeNum = 0; //攻撃アニメーションの時間を入れた配列の番号。
	int m_attackAnimNum = 0; //XボタンかYボタンの攻撃アニメーションの数。
	float m_angle = 0.0f;//回転角度。
	bool m_attackAngleFlag = false;
	Vector3 m_weaponMoveSpeed = Vector3::Zero; //武器のムーブスピード。
	Vector3 m_oldPosition = Vector3::Zero; //前の座標。

	bool m_kaihiFlag = false; //回避フラグ。
	int m_kaihiTimer = 0;

	int m_playerLevel = 1; //プレイヤーのレベル。
	float m_experiencePoint = 0.0f;  //経験値。
	float m_nextExperiencePoint = 10.0f; //次に必要な経験値。

	Vector3 m_dir = Vector3::Zero;

	int ATTACK_ANIM_NUM_X = 1;//Xボタンの攻撃アニメーションの数。
	int ATTACK_ANIM_NUM_Y = 1;//Yボタンの攻撃アニメーションの数。
	bool m_attackFlag = false; //攻撃しているフラグ。

	bool m_doNothingFlag = false; //何もしていないフラグ。
};

