#include "stdafx.h"
#include "Weapon.h"



Weapon::Weapon()
{
}


Weapon::~Weapon()
{
	DeleteGO(m_skimModelRender);
}

bool Weapon::Start()
{
	//モデルの初期化。
	m_skimModelRender = NewGO<SkinModelRender>(0);
	m_skimModelRender->Init(
		"Assets/modelData/player/weapon/weapon01.tkm",
		nullptr,
		0,
		"Assets/shader/model.fx",
		SkinModelRender::YUp
	);
	m_skimModelRender->SetPosition(m_position);
	m_skimModelRender->SetRotation(m_rotation);
	m_player = FindGO<Player>("player");
	//ゴースト作成。
	m_nextAttackNum = m_player->GetAttackNum();
	m_ghostObj.CreateBox(
		m_position,
		m_rotation,
		{ 1.0f, 1.0f, 1.0f }
	);
	return true;
}

void Weapon::Update()
{
	m_player->GetPlayerSkinModelRemder().GetModel().GetSkeleton().GetBone(m_boneNum)->CalcWorldTRS(
		m_position,
		m_rotation,
		m_scale
	);
	Quaternion weaponRot = Quaternion::Identity;
	weaponRot.SetRotationDegX(90.0f);
	weaponRot.Multiply(m_rotation);
	//座標にムーブスピードを加算。

	m_position += m_player->GetWeaponMoveSpeed();
	//座標設定。
	m_skimModelRender->SetPosition(m_position);
	//回転設定。
	m_skimModelRender->SetRotation(weaponRot);

	m_ghostObj.SetPosition(m_position);
	m_ghostObj.SetRotation(weaponRot);

	//敵との当たり判定をとる前に、
	//敵がいるかどうかを調べる。
	if (m_player->GetAttackFlag() != false) {
		QueryGOs<DrBoar>("drBoar", [&](DrBoar * drBoar)->bool {
			CharacterController& charaCon = *drBoar->GetCharaCon();
			g_physics.ContactTestCharaCon(charaCon, [&](const btCollisionObject & collisionObject) {
				if (m_ghostObj.IsSelf(collisionObject) == true) {
					drBoar->GetHit(10);
				}
			});
			/*if (m_player->GetAttackFlag() != false) {
				if (m_nextAttackNum == m_player->GetAttackNum()) {
					Vector3 v = drBoar->GetPosition() - m_position;
					if (v.Length() <= 300.0f) {
						drBoar->GetHit(5);
					}
					m_nextAttackNum++;
				}
			}
			else {
				m_nextAttackNum = m_player->GetAttackNum();
			}*/
			return true;
		});
	}
}
