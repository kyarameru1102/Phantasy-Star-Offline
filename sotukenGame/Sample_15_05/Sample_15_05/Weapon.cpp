#include "stdafx.h"
#include "Weapon.h"



Weapon::Weapon()
{
}


Weapon::~Weapon()
{
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
	return true;
}

void Weapon::Update()
{
	//���W�ݒ�B
	m_skimModelRender->SetPosition(m_position);
	//��]�ݒ�B
	m_skimModelRender->SetRotation(m_rotation);
}
