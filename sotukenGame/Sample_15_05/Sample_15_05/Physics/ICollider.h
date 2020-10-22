#pragma once

class btCollisionShape;

/// <summary>
/// コライダーのインターフェース。
/// </summary>
class ICollider {
public:
	virtual btCollisionShape* GetBody() const = 0;
};
