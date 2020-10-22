#pragma once

class ICollider;

/// <summary>
/// ���̏��B
/// </summary>
struct RigidBodyInfo {

	Vector3 pos = Vector3::Zero;			//���W�B
	Quaternion rot = Quaternion::Identity;	//��]�B
	Vector3 scl = Vector3::One;

	ICollider* collider = nullptr;				//�R���C�_�[�B
	float mass = 0.0f;							//���ʁB

};

/// <summary>
/// ���́B
/// </summary>
class RigidBody
{
	btRigidBody* rigidBody = nullptr;		//���́B
	btDefaultMotionState* myMotionState = nullptr;	//���[�V�����X�e�[�g�B
public:
	~RigidBody();
	void Release();
	void Create(RigidBodyInfo& rbInfo);
	btRigidBody* GetBody()
	{
		return rigidBody;
	}

};

