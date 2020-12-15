#include "stdafx.h"
#include "system/system.h"
#include <random>
#include "util/stopwatch.h"
#include "Physics/Physics.h"
#include "Title.h"
#include "EnBehaviorTest.h"
//関数宣言
void InitRootSignature(RootSignature& rs);


///////////////////////////////////////////////////////////////////
// ウィンドウプログラムのメイン関数。
///////////////////////////////////////////////////////////////////
int WINAPI wWinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPWSTR lpCmdLine, int nCmdShow)
{
	//ゲームの初期化。
	InitGame(hInstance, hPrevInstance, lpCmdLine, nCmdShow, TEXT("Game"));
	
	//コマンドプロンプトでFPS表示。
	{
		::AllocConsole();               // コマンドプロンプトが表示される
		freopen("CON", "w", stdout);    // 標準出力の割り当て

		auto fhandle = GetStdHandle(STD_OUTPUT_HANDLE);
		SMALL_RECT rc;
			
		rc.Top = 0;
		rc.Left = 0;
		rc.Bottom = 3;
		rc.Right = 30;
		::SetConsoleWindowInfo(fhandle, TRUE, &rc);
	}
	//////////////////////////////////////
	// ここから初期化を行うコードを記述する。
	//////////////////////////////////////
	std::random_device seed_gen;
	std::mt19937 random(seed_gen());
	//カメラ初期設定。
	g_camera3D->SetPosition({ 0.0f, 0.0, 400.0f });
	g_camera3D->SetTarget({ 0.0f, 0.0f, 0.0f });
	g_camera3D->SetFar(30000.0f);

	//ルートシグネチャを作成。
	RootSignature rootSignature;
	InitRootSignature(rootSignature);

	//////////////////////////////////////
	// 初期化を行うコードを書くのはここまで！！！
	//////////////////////////////////////
	auto& renderContext = g_graphicsEngine->GetRenderContext();

	Stopwatch sw;
	NewGO<Title>(0, "Title");

	// ここからゲームループ。
	while (DispatchWindowMessage())
	{
		sw.Start();
		//レンダリング開始。
		g_engine->BeginFrame();
		//PhysicsWorldの更新。
		g_physics.Update();
		//GemeObjectManagerのUpdate関数。
		gameObjectManager().Update();

		//レンダリング終了。
		g_engine->EndFrame();
		sw.Stop();
		//fps表示。
		printf("fps = %0.2f\n", 1.0f / sw.GetElapsed() );
	}

	::FreeConsole();
	return 0;
}


//ルートシグネチャの初期化。
void InitRootSignature(RootSignature& rs)
{
	rs.Init(D3D12_FILTER_MIN_MAG_MIP_LINEAR,
		D3D12_TEXTURE_ADDRESS_MODE_WRAP,
		D3D12_TEXTURE_ADDRESS_MODE_WRAP,
		D3D12_TEXTURE_ADDRESS_MODE_WRAP);
}

