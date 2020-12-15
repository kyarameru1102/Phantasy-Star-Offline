#include "stdafx.h"
#include "GameCamera.h"


GameCamera::GameCamera()
{
}


GameCamera::~GameCamera()
{
}
bool GameCamera::Start()
{
	m_player = FindGO<Player>("player");
	return true;
}

void GameCamera::Update()
{
	Vector3 toPlayerVecOld = m_toPlayerVec;
	//カメラの座標にプレイヤーの座標を代入。
	m_position = m_player->GetPosition();
	//Y軸回転の角度を更新。
	m_angleAxisY = g_pad[0]->GetRStickXF() * 2.0f;
	//X軸回転の角度を更新。
	m_angleAxisX = g_pad[0]->GetRStickYF() * 2.0f;

	//Y軸回転をカメラからプレイヤーに向かって伸びるベクトルに適応させる。
	Quaternion rot;
	rot.SetRotationDeg(Vector3::AxisY, m_angleAxisY);
	rot.Apply(m_toPlayerVec);

	//Y軸とm_toPlayerVecの外積を求めてX軸を計算する。
	Vector3 AxisX = Vector3::AxisY;
	AxisX.Cross(m_toPlayerVec);
	AxisX.Normalize();
	//X軸回転をカメラからプレイヤーに向かって伸びるベクトルに適応させる。
	rot = Quaternion::Identity;
	rot.SetRotationDeg(AxisX, m_angleAxisX);
	rot.Apply(m_toPlayerVec);
	Vector3 toPosDir = m_toPlayerVec;
	toPosDir.Normalize();
	if (toPosDir.y < -0.5f) {
		m_toPlayerVec = toPlayerVecOld;
	}
	if (toPosDir.y > 0.8f) {
		m_toPlayerVec = toPlayerVecOld;
	}
	//ターゲットをプレイヤーにする。
	m_target = m_player->GetPosition();
	m_target.y += 100.0f;
	//ターゲットを設定。
	g_camera3D->SetTarget(m_target);
	//座標を更新。
	m_position = m_target + m_toPlayerVec;
	//座標を設定。
	g_camera3D->SetPosition(m_position);
	
}