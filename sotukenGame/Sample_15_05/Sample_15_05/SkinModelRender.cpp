#include "stdafx.h"
#include "SkinModelRender.h"
#include "shadow/CascadeShadowMap.h"


SkinModelRender::SkinModelRender() 
{

}

SkinModelRender::~SkinModelRender()
{

}

void SkinModelRender::Init(const char* filePath, AnimationClip* animationClips, int numAnimationClips, const char* fx, Up up)
{
	//Zあっぷなら回転。
	if (up == ZUp) {
		m_rotation.SetRotationDegX(90.0f);
	}

	m_filePath = filePath;

	//モデルの初期化。
	ModelInitData initData;
	initData.m_tkmFilePath = filePath;
	initData.m_fxFilePath = fx;

	
	m_model.Init(initData);
	

	//アニメーションの初期化
	InitAnimation(animationClips, numAnimationClips);
}

void SkinModelRender::InitAnimation(AnimationClip* animationClips, int numAnimationClips)
{
	//アニメーションの初期化
	if (m_isInitAnimation) {
		return;
	}

	//アニメーションクリップが設定されてたら
	if (animationClips != nullptr) {
		m_animationClip = animationClips;
		m_animationClip[0].SetLoopFlag(true);
		m_numAnimationClips = numAnimationClips;
		m_animation.Init(m_model, m_animationClip, m_numAnimationClips);
		
		m_isInitAnimation = true;
	}

}



bool SkinModelRender::Start()
{
	return true;
}

void SkinModelRender::Update()
{

	if (m_animation.IsInited()) {
		//アニメーションを再生。
		m_animation.Progress(1/60.0f);
	}

	m_model.UpdateWorldMatrix(m_position, m_rotation, m_scale);

	SetShadowCaster(true);
	if (m_model.GetShadowCaster()) {
		g_graphicsEngine->GetShadowMap()->RegistShadowCaster(&m_model);
		g_graphicsEngine->GetCascadeShadowMap()->RegistShadowCaster(&m_model);
	}

	m_renderOK = true;
}

void SkinModelRender::Render()
{
	if (m_renderOK) {
		//通常レンダリング。
		if (m_renderOn) {
			auto& renderContext = g_graphicsEngine->GetRenderContext();
			m_model.Draw(renderContext);
		}
	}
}

