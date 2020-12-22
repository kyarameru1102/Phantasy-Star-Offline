#pragma once

/// <summary>
 /// レンダリングモード。
 /// </summary>
enum EnRenderMode {
	enRenderMode_Invalid,			//不正なレンダリングモード。
	enRenderMode_CreateShadowMap,	//シャドウマップ生成。
	enRenderMode_CreateCascadeShadowMap,	//カスケードシャドウマップの生成
	enRenderMode_Normal,			//通常レンダリング。
	enRenderMode_Num,				//レンダリングモードの数。
};
