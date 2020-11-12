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
	m_position = m_player->GetPosition() + m_toPlayerVec;

	//カメラのターゲットをプレイヤーに固定する。
	m_traget = m_player->GetPosition();
	//座標を設定。
	g_camera3D->SetPosition(m_position);
	//ターゲットを設定。
	g_camera3D->SetTarget(m_traget);
}