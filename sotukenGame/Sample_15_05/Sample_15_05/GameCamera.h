#pragma once
#include "Player.h"
class GameCamera : public IGameObject
{
public:
	/// <summary>
	/// コンストラクタ。
	/// </summary>
	GameCamera();
	/// <summary>
	/// デストラクタ。
	/// </summary>
	~GameCamera();
	/// <summary>
	/// スタート関数。
	/// </summary>
	/// <returns></returns>
	bool Start() override;
	/// <summary>
	/// 更新関数。
	/// </summary>
	void Update() override;
private:
	Player* m_player = nullptr;
	Vector3 m_position = Vector3::Zero;
	Vector3 m_traget = Vector3::Zero;
	Vector3 m_toPlayerVec = { 0.0f, 200.0f, 600.0f };//カメラからプレイヤーに向かって伸びるベクトル。
	float m_angleAxisX = 0.0f;//X軸回転の角度。
	float m_angleAxisY = 0.0f;//Y軸回転の角度。

};

