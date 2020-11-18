#pragma once
/// <summary>
/// 敵テストクラス
/// </summary>
class EnTest : public IGameObject
{
public:
	EnTest();
	~EnTest();
	bool Start() override;
	void Update() override;
private:
	SkinModelRender* m_EnTestSkinModel = nullptr;
	Quaternion m_rotation = Quaternion::Identity;
	enum EnAnimationClip {
		enIdle,
		enAnimationClip_num
	};
	int m_animState = enIdle; //アニメーションの状態。
	AnimationClip m_animationClip[enAnimationClip_num];
};

