#pragma once
#include "ICollider.h"

class BoxCollider : public ICollider
{
public:
	/*!
	 * @brief	�R���X�g���N�^�B
	 */
	BoxCollider();
	/*!
	 * @brief	�f�X�g���N�^�B
	 */
	~BoxCollider();
	/*!
	 * @brief	�{�b�N�X�R���C�_�[���쐬�B
	 */
	void Create(const Vector3& size);
	btCollisionShape* GetBody() const override
	{
		return shape;
	}
private:
	btBoxShape* shape;
};

