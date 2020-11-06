#include "stdafx.h"
#include "SkinModelRender.h"


SkinModelRender::SkinModelRender() 
{

}

SkinModelRender::~SkinModelRender()
{

}

void SkinModelRender::Init(const char* filePath, AnimationClip* animationClips, int numAnimationClips, const char* fx, Up up)
{
	//Z�����ՂȂ��]�B
	if (up == ZUp) {
		m_rotation.SetRotationDegX(90.0f);
	}

	m_filePath = filePath;

	//���f���̏������B
	ModelInitData initData;
	initData.m_tkmFilePath = filePath;
	initData.m_fxFilePath = fx;

	
	m_model.Init(initData);
	

	//�A�j���[�V�����̏�����
	InitAnimation(animationClips, numAnimationClips);
}

void SkinModelRender::InitAnimation(AnimationClip* animationClips, int numAnimationClips)
{
	//�A�j���[�V�����̏�����
	if (m_isInitAnimation) {
		return;
	}

	//�A�j���[�V�����N���b�v���ݒ肳��Ă���
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
		//�A�j���[�V�������Đ��B
		m_animation.Progress(1/60.0f);
	}

	m_model.UpdateWorldMatrix(m_position, m_rotation, m_scale);

	m_renderOK = true;
}

void SkinModelRender::Render()
{
	if (m_renderOK) {
		//�ʏ탌���_�����O�B
		if (m_renderOn) {
			auto& renderContext = g_graphicsEngine->GetRenderContext();
			m_model.Draw(renderContext);
		}
	}
}

