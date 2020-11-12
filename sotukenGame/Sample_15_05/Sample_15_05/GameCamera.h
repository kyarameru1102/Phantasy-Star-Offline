#pragma once
#include "Player.h"
class GameCamera : public IGameObject
{
public:
	/// <summary>
	/// �R���X�g���N�^�B
	/// </summary>
	GameCamera();
	/// <summary>
	/// �f�X�g���N�^�B
	/// </summary>
	~GameCamera();
	/// <summary>
	/// �X�^�[�g�֐��B
	/// </summary>
	/// <returns></returns>
	bool Start() override;
	/// <summary>
	/// �X�V�֐��B
	/// </summary>
	void Update() override;
private:
	Player* m_player = nullptr;
	Vector3 m_position = Vector3::Zero;
	Vector3 m_traget = Vector3::Zero;
	Vector3 m_toPlayerVec = { 0.0f, 200.0f, 600.0f };//�J��������v���C���[�Ɍ������ĐL�т�x�N�g���B


};

