#pragma once

class btCollisionShape;

/// <summary>
/// �R���C�_�[�̃C���^�[�t�F�[�X�B
/// </summary>
class ICollider {
public:
	virtual btCollisionShape* GetBody() const = 0;
};
