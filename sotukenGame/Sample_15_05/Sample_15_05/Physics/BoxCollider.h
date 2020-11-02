#pragma once
#include "ICollider.h"

class BoxCollider : public ICollider
{
public:
	/*!
	 * @brief	コンストラクタ。
	 */
	BoxCollider();
	/*!
	 * @brief	デストラクタ。
	 */
	~BoxCollider();
	/*!
	 * @brief	ボックスコライダーを作成。
	 */
	void Create(const Vector3& size);
	btCollisionShape* GetBody() const override
	{
		return shape;
	}
private:
	btBoxShape* shape;
};

