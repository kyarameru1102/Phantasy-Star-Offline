#pragma once
#include "Physics/Character/CharacterController.h"
#include "EnemyAnimation.h"
/// <summary>
/// ドラゴンボアクラス
/// </summary>
class Player;
class DrBoar : public IGameObject
{
public:
	/// <summary>
	/// コンストラクタ
	/// </summary>
	DrBoar();
	/// <summary>
	/// デストラクタ
	/// </summary>
	~DrBoar();
	/// <summary>
	/// スタート関数。
	/// </summary>
	/// <returns></returns>
	bool Start();
	/// <summary>
	/// 更新関数。
	/// </summary>
	/// <returns></returns>
	void Update();

	void Move();
	void Turn();
	void Attack();
	void Die();
	/// <summary>
	/// ドラゴンボアの座標を返す。
	/// </summary>
	/// <returns></returns>
	const Vector3& GetPosition() const
	{
		return m_position;
	}
	/// <summary>
	/// ドラゴンボアのHPを返す。
	/// </summary>
	/// <returns></returns>
	const int& GetHP() const
	{
		return m_hp;
	}
	/// <summary>
	/// ドラゴンボアのHPを減らす。
	/// </summary>
	int GetHit(int damage) 
	{
		m_hp -= damage;
		return true;
	}
private:
	enum {
		Idle_state,
		Attack_state,
		Die_state
	};
	
	int m_status = Attack_state;    //状態
	SkinModelRender* m_DrBoarSkinModel = nullptr; //スキンモデル
	Vector3 m_position = Vector3::Zero;  //座標
	Vector3 m_scale = Vector3::One;      //拡大率
	Quaternion m_rotation = Quaternion::Identity; //回転
	Vector3 m_movespeed = Vector3::Zero;  //移動速度
	int changeTimer = 0;       //アニメーション変更タイマー
	float m_speedY = 0.0f;//Y方向のスピード。
	int m_animState = enIdle; //アニメーションの状態。
	int m_appearcolor = 0;  //配色No
	int m_hp = 50;  //HP

	Player* m_player = nullptr;
	CharacterController m_charaCon;//キャラコン。
	EnemyAnimation* m_enemyAnim = nullptr;  //アニメーションのロード
	std::vector<int> boarcolor = { 1,2,3,4 }; //配色決定
};

