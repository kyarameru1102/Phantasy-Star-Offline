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
	//���f���̏������B
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
	//�S�[�X�g�쐬�B
	m_nextAttackNum = m_player->GetAttackNum();
	m_ghostObj.CreateBox(
		m_position,
		m_rotation,
		{ 100.0f, 20.0f, 20.0f }
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
	//���W�Ƀ��[�u�X�s�[�h�����Z�B

	m_position += m_player->GetWeaponMoveSpeed();
	//���W�ݒ�B
	m_skimModelRender->SetPosition(m_position);
	//��]�ݒ�B
	m_skimModelRender->SetRotation(weaponRot);

	m_ghostObj.SetPosition(m_position);
	m_ghostObj.SetRotation(weaponRot);

	//�G�Ƃ̓����蔻����Ƃ�O�ɁA
	//�G�����邩�ǂ����𒲂ׂ�B
	QueryGOs<DrBoar>("drBoar", [&](DrBoar * drBoar)->bool {
		if (m_player->GetAttackFlag() != false) {
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
		}
		return true;
		});
}
