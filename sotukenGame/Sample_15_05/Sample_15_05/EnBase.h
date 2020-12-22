#pragma once
#include "Physics/Character/CharacterController.h"

/// <summary>
/// 敵基底クラス
/// </summary>
class Player;
class EnBase : public IGameObject
{
public:
	/// <summary>
	/// コンストラクタ
	/// </summary>
	EnBase();
	/// <summary>
	/// デストラクタ
	/// </summary>
	~EnBase();
	/// <summary>
	/// 座標を返す。
	/// </summary>
	/// <returns></returns>
	const Vector3& GetPosition() const
	{
		return m_position;
	}
	/// <summary>
	/// HPを返す。
	/// </summary>
	/// <returns></returns>
	const int& GetHP() const
	{
		return m_hp;
	}
	/// <summary>
	/// ダメージを受けてHPを減らす関数。
	/// </summary>
	/// <param name="damage">int ダメージ量</param>
	virtual void ReceiveDamage(int damage)
	{
		m_hp -= damage;
	}
	/// <summary>
	/// HPを与える関数。
	/// 主に回復等で使う。
	/// </summary>
	/// <param name="hp">int 回復量</param>
	void ReceiveHP(int hp)
	{
		m_hp += hp;
	}

	/// <summary>
	/// キャラコンを返す。
	/// </summary>
	CharacterController* GetCharaCon()
	{
		return &m_charaCon;
	}
	void SetPosition(Vector3 pos)
	{
		m_position = pos;
	}
	bool GetDeath()const
	{
		return m_death;
	}
	Vector3 GetDirection()const
	{
		return m_dir;
	}

protected:
	SkinModelRender*	m_skinModelRender = nullptr;			//スキンモデル
	Vector3				m_position = Vector3::Zero;				//座標
	Vector3				m_scale = Vector3::One;					//拡大率
	Quaternion			m_rotation = Quaternion::Identity;		//回転
	Vector3				m_movespeed = Vector3::Zero;			//移動速度
	CharacterController m_charaCon;								//キャラコン。
	int					m_hp = 50;								//HP
	Player*				m_player = nullptr;						//プレイヤー。
	Vector3				m_toPlayer = Vector3::Zero;				//プレイヤーまでのベクトル。
	bool				m_death = false;
	Vector3				m_dir, m_ghostPos;
};


