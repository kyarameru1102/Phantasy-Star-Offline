#include "stdafx.h"
#include "SpriteRender.h"

void SpriteRender::Init(const char* dds,float height,float width,const char* fx)
{
	m_spriteInitData.m_height = height;
	m_spriteInitData.m_width = width;
	m_spriteInitData.m_fxFilePath = fx;
	m_spriteInitData.m_ddsFilePath[0] = dds;
	m_sprite.Init(m_spriteInitData);
}

bool SpriteRender::Start()
{
	return true;
}

void SpriteRender::Update()
{
	m_sprite.Update(m_position,m_rotation,m_scale, m_pivot);
}

void SpriteRender::Render2D()
{
	auto& renderContext = g_graphicsEngine->GetRenderContext();
	m_sprite.Draw(renderContext);
}
