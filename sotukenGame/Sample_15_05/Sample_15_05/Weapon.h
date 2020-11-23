#pragma once
#include "Player.h"
class Weapon : public IGameObject
{
public:
	/// <summary>
	/// コンストラクタ。
	/// </summary>
	Weapon();
	/// <summary>
	/// デストラクタ。
	/// </summary>
	~Weapon();
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
	/// 座標を設定する。
	/// </summary>
	/// <param name="pos"></param>
	void SetPosition(const Vector3& pos)
	{
		m_position = pos;
	}
	/// <summary>
	/// 回転を設定する。
	/// </summary>
	/// <param name="rot"></param>
	void SetRtation(const Quaternion& rot)
	{
		m_rotation = rot;
	}
private:
	Player* m_player = nullptr; //プレイヤーのインスタンス。
	SkinModelRender* m_skimModelRender = nullptr; //スキンモデルレンダー。
	Vector3 m_position = Vector3::Zero;//座標。
	Quaternion m_rotation = Quaternion::Identity;//回転。
};