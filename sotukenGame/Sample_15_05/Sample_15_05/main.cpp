#include "stdafx.h"
#include "system/system.h"
#include <random>
#include "util/stopwatch.h"
#include "Physics/Physics.h"
#include "Title.h"
#include "EnBehaviorTest.h"
//�֐��錾
void InitRootSignature(RootSignature& rs);


///////////////////////////////////////////////////////////////////
// �E�B���h�E�v���O�����̃��C���֐��B
///////////////////////////////////////////////////////////////////
int WINAPI wWinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPWSTR lpCmdLine, int nCmdShow)
{
	//�Q�[���̏������B
	InitGame(hInstance, hPrevInstance, lpCmdLine, nCmdShow, TEXT("Game"));
	
	//�R�}���h�v�����v�g��FPS�\���B
	{
		::AllocConsole();               // �R�}���h�v�����v�g���\�������
		freopen("CON", "w", stdout);    // �W���o�͂̊��蓖��

		auto fhandle = GetStdHandle(STD_OUTPUT_HANDLE);
		SMALL_RECT rc;
			
		rc.Top = 0;
		rc.Left = 0;
		rc.Bottom = 1;
		rc.Right = 30;
		::SetConsoleWindowInfo(fhandle, TRUE, &rc);
	}
	//////////////////////////////////////
	// �������珉�������s���R�[�h���L�q����B
	//////////////////////////////////////
	std::random_device seed_gen;
	std::mt19937 random(seed_gen());
	//�J���������ݒ�B
	g_camera3D->SetPosition({ 0.0f, 0.0, 400.0f });
	g_camera3D->SetTarget({ 0.0f, 0.0f, 0.0f });
	g_camera3D->SetFar(30000.0f);

	//���[�g�V�O�l�`�����쐬�B
	RootSignature rootSignature;
	InitRootSignature(rootSignature);

	//////////////////////////////////////
	// ���������s���R�[�h�������̂͂����܂ŁI�I�I
	//////////////////////////////////////
	auto& renderContext = g_graphicsEngine->GetRenderContext();

	Stopwatch sw;
	NewGO<Title>(0, "Title");

	// ��������Q�[�����[�v�B
	while (DispatchWindowMessage())
	{
		sw.Start();
		//�����_�����O�J�n�B
		g_engine->BeginFrame();
		//PhysicsWorld�̍X�V�B
		g_physics.Update();
		//GemeObjectManager��Update�֐��B
		gameObjectManager().Update();

		//�����_�����O�I���B
		g_engine->EndFrame();
		sw.Stop();
		//fps�\���B
		printf("fps = %0.2f\n", 1.0f / sw.GetElapsed() );
	}

	::FreeConsole();
	return 0;
}


//���[�g�V�O�l�`���̏������B
void InitRootSignature(RootSignature& rs)
{
	rs.Init(D3D12_FILTER_MIN_MAG_MIP_LINEAR,
		D3D12_TEXTURE_ADDRESS_MODE_WRAP,
		D3D12_TEXTURE_ADDRESS_MODE_WRAP,
		D3D12_TEXTURE_ADDRESS_MODE_WRAP);
}

