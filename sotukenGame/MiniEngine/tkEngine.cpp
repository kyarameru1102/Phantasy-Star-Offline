#include "stdafx.h"
#include "tkEngine.h"
#include "GraphicsEngine.h"

TkEngine* g_engine = nullptr;

TkEngine::~TkEngine()
{
	if (g_graphicsEngine) {
		delete m_graphicsEngine;
	}
}
void TkEngine::Init(HWND hwnd, UINT frameBufferWidth, UINT frameBufferHeight)
{
	//�O���t�B�b�N�G���W���̏������B
	g_graphicsEngine = new GraphicsEngine();
	g_graphicsEngine->Init(hwnd, frameBufferWidth, frameBufferHeight);
	//�Q�[���p�b�h�̏������B
	for (int i = 0; i < GamePad::CONNECT_PAD_MAX; i++) {
		g_pad[i] = &m_pad[i];
	}
}
void TkEngine::BeginFrame()
{
	g_graphicsEngine->BeginRender();
	for (auto& pad : m_pad) {
		pad.BeginFrame();
		pad.Update();
	}
	
}
void TkEngine::EndFrame()
{
	g_graphicsEngine->EndRender();
}