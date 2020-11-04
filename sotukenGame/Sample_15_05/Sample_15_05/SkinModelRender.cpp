#include "stdafx.h"
#include "SkinModelRender.h"


SkinModelRender::SkinModelRender() 
{

}

SkinModelRender::~SkinModelRender()
{

}

void SkinModelRender::Init(const char* filePath, AnimationClip* animationClips, int numAnimationClips, const char* fx)
{
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
		m_numAnimationClips = numAnimationClips;
		m_animation.Init(m_model, m_animationClip, m_numAnimationClips);
		m_model.BindSkeleton(m_model.GetSkeleton());
		m_isInitAnimation = true;
	}

}



bool SkinModelRender::Start()
{
	return true;
}

void SkinModelRender::Update()
{
	m_model.UpdateWorldMatrix(m_position, m_rotation, m_scale);
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

