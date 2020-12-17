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
		{ 500.0f, 50.0f, 50.0f }
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

	if (m_player->GetAttackFlag() != false) {
		//�v���C���[���U�����Ă���B
		if (m_nextAttackNum == m_player->GetAttackNum()) {
			//�U���t���O�������Ă���ԁA���t���[���_���[�W��^���Ȃ��悤�ɂ���B
			//�G�Ƃ̓����蔻����Ƃ�O�ɁA�G�����邩�ǂ����𒲂ׂ�B
			QueryGOs<EnBase>("drBoar", [&](EnBase * drBoar)->bool {
				//�G�̃L�����R�����擾�B
				CharacterController& charaCon = *drBoar->GetCharaCon();
				g_physics.ContactTestCharaCon(charaCon, [&](const btCollisionObject & collisionObject) {
					if (m_ghostObj.IsSelf(collisionObject) == true) {
						//�������Ă�����A�_���[�W��^����B
						drBoar->ReceiveDamage(m_ataackPow);
					}
				});
				return true;
			});
			QueryGOs<EnBase>("drBoar2", [&](EnBase* drBoar)->bool {
				//�G�̃L�����R�����擾�B
				CharacterController& charaCon = *drBoar->GetCharaCon();
				g_physics.ContactTestCharaCon(charaCon, [&](const btCollisionObject& collisionObject) {
					if (m_ghostObj.IsSelf(collisionObject) == true) {
						//�������Ă�����A�_���[�W��^����B
						drBoar->ReceiveDamage(m_ataackPow);
					}
					});
				return true;
				});
			m_nextAttackNum++;
		}
	}
	else {
		m_nextAttackNum = m_player->GetAttackNum();
	}
}
