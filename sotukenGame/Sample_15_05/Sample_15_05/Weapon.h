#pragma once
#include "Player.h"
class Weapon : public IGameObject
{
public:
	Weapon();
	~Weapon();

	bool Start() override;

	void Update() override;

	void SetPosition(const Vector3& pos)
	{
		m_position = pos;
	}
	void SetRtation(const Quaternion& rot)
	{
		m_rotation = rot;
	}
private:
	Player* m_player = nullptr;
	SkinModelRender* m_skimModelRender = nullptr;
	Vector3 m_position = Vector3::Zero;
	Quaternion m_rotation = Quaternion::Identity;
	Vector3 m_asix = Vector3::One;
};