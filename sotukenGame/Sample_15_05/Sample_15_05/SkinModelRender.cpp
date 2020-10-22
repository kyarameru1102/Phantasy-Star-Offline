#include "stdafx.h"
#include "SkinModelRender.h"

SkinModelRender::SkinModelRender() 
{

}

SkinModelRender::~SkinModelRender()
{

}

void SkinModelRender::Init(const char* tkm, const char* fx)
{
	m_modelInitData.m_tkmFilePath = tkm;
	m_modelInitData.m_fxFilePath = fx;
	m_model.Init(m_modelInitData);
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
		//’ÊíƒŒƒ“ƒ_ƒŠƒ“ƒOB
		if (m_renderOn) {
			auto& renderContext = g_graphicsEngine->GetRenderContext();
			m_model.Draw(renderContext);
		}
	}
}

