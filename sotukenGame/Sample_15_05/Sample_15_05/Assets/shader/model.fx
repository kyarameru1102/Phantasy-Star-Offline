/*!
 * @brief	シンプルなモデル表示用のシェーダー。
 */

struct SPointLight {
	float3 position;	//座標。
	float3 color;		//ポイントライトのカラー。
	float  range;		//影響を与える範囲。
};

static const int NUM_POINT_LIGHT = 1000;

//ディレクションライト。
struct DirLight {
	float3 direction;	//方向
	float3 color;		//カラー。
};

//ライト構造体。
struct SLight{
	SPointLight pointsLights[NUM_POINT_LIGHT];
	DirLight dirLight;
};

static const int NUM_CASCADES = 3;



//モデル用の定数バッファ
cbuffer ModelCb : register(b0){
	float4x4 mWorld;
	float4x4 mView;
	float4x4 mProj;
	float4x4 mLightView;
	float4x4 mLightProj;
	float4x4 mLightViewProj[NUM_CASCADES];
	float4 mFarList[NUM_CASCADES];
	int isShadowReciever;
	int shadowMapNumber = 0;
};

/// <summary>
/// シャドウマップ用の定数バッファ。
/// </summary>
cbuffer ShadowMapCb : register(b2) {
	float4x4 lightViewProjMatrix;	//ライトビュープロジェクション行列。
}

cbuffer PointLightCb : register(b1){
	SLight light;
}

//頂点シェーダーへの入力。
struct SVSIn{
	float4 pos 		: POSITION;
	float3 normal	: NORMAL;
	float2 uv 		: TEXCOORD0;
	int4  indices  : BLENDINDICES0;
	float4 weights  : BLENDWEIGHT0;
};
//ピクセルシェーダーへの入力。
struct SPSIn{
	float4 pos 			: SV_POSITION;
	float3 normal		: NORMAL;
	float2 uv 			: TEXCOORD0;
	float3 worldPos		: TEXCOORD1;	//ワールド座標。
	float4 posInCamera  : TEXCOORD2;    //カメラ空間での座標
	float4 posInLVP[NUM_CASCADES]		: TEXCOORD3;	//ライトビュープロジェクション空間での座標

};

//ピクセルシェーダーからの出力
struct SPSOut {
	float4 albedo : SV_Target0;		//アルベド
	float4 normal : SV_Target1;		//法線
	float shadow : SV_Target2;	//シャドウ
};

/// <summary>
/// シャドウマップ用のピクセルシェーダへの入力構造体。
/// </summary>
struct PSInput_ShadowMap {
	float4 Position 			: SV_POSITION;	//座標。
};

//モデルテクスチャ。
Texture2D<float4> g_texture : register(t0);
//法線。
Texture2D<float4> g_normal : register(t1);
//ボーン行列
StructuredBuffer<float4x4> boneMatrix : register(t3);
//シャドウマップ
Texture2D<float4> g_shadowMap : register(t4);
//カスケードシャドウマップ
Texture2D<float4> g_cascadeShadowMap1 : register(t5);
Texture2D<float4> g_cascadeShadowMap2 : register(t6);
Texture2D<float4> g_cascadeShadowMap3 : register(t7);

//サンプラステート。
sampler g_sampler : register(s0);

/// <summary>
/// スキン行列を計算。
/// </summary>
float4x4 CalcSkinMatrix(SVSIn vsIn)
{
	float4x4 skinning = 0;
	float w = 0.0f;
	[unroll]
	for (int i = 0; i < 3; i++)
	{
		skinning += boneMatrix[vsIn.indices[i]] * vsIn.weights[i];
		w += vsIn.weights[i];
	}

	skinning += boneMatrix[vsIn.indices[3]] * (1.0f - w);
	return skinning;
}

SPSIn VSMain(SVSIn vsIn, uniform bool hasSkin)
{
	SPSIn psIn;

	float4 worldPos = mul(mWorld, vsIn.pos);			//モデルの頂点をワールド座標系に変換。

	psIn.pos = worldPos;	
	
	psIn.worldPos = psIn.pos;

	if (isShadowReciever == 1) {
		//ライトビュープロジェクション座標に変換
		for (int i = 0; i < NUM_CASCADES; i++) {
			psIn.posInLVP[i] = mul(mLightViewProj[i], worldPos);
		}
	}

	psIn.pos = mul(mView, psIn.pos);	//ワールド座標系からカメラ座標系に変換。
	psIn.posInCamera = psIn.pos;
	psIn.pos = mul(mProj, psIn.pos);	//カメラ座標系からスクリーン座標系に変換。
	psIn.normal = normalize(mul(mWorld, vsIn.normal));
	psIn.uv = vsIn.uv;

	return psIn;
}

/// <summary>
/// スキンありモデル用の頂点シェーダーのエントリーポイント。
/// </summary>
SPSIn VSMainSkin(SVSIn vsIn)
{
	SPSIn psIn;

	float4x4 skinning = CalcSkinMatrix(vsIn);
	float4 worldPos = mul(skinning, vsIn.pos);
	
	psIn.pos = worldPos;
	
	psIn.worldPos = psIn.pos.xyz;
	
	if (isShadowReciever == 1) {
		//ライトビュープロジェクション座標に変換
		for (int i = 0; i < NUM_CASCADES; i++) {
			psIn.posInLVP[i] = mul(mLightViewProj[i], worldPos);
		}
	}

	psIn.pos = mul(mView, psIn.pos);	//ワールド座標系からカメラ座標系に変換。
	psIn.posInCamera = psIn.pos;
	psIn.pos = mul(mProj, psIn.pos);	//カメラ座標系からスクリーン座標系に変換。
	psIn.normal = normalize(mul(mWorld, vsIn.normal));
	psIn.uv = vsIn.uv;


	return psIn;
}

/// <summary>
/// モデル用のピクセルシェーダーのエントリーポイント
/// </summary>
SPSOut PSMain( SPSIn psIn ) : SV_Target0
{
	//アルベドカラーを出力。
	float4 albedo = g_texture.Sample(g_sampler, psIn.uv);

	SPSOut spsOut;
	spsOut.albedo = albedo;
	spsOut.normal.xyz = psIn.normal;
	spsOut.normal.w = 1.0f;


	spsOut.shadow = 1.0f;
	//spsOut.shadow = color.x;
		//シャドウレシーバー。
	if (isShadowReciever == 1) {
		for (int i = 0; i < NUM_CASCADES; i++) {
			if (mFarList[i].x > psIn.posInCamera.z) {
				//LVP空間から見た時の最も手前の深度値をシャドウマップから取得する。
			//プロジェクション行列をシャドウマップのUV座標に変換している
				float2 shadowMapUV = psIn.posInLVP[i].xy / psIn.posInLVP[i].w;
				shadowMapUV *= float2(0.5f, -0.5f);
				shadowMapUV += 0.5f;
				//spsOut.shadow = shadowMapUV.x;
				//シャドウマップのUV座標範囲内かどうかを判定する。
				if (shadowMapUV.x < 1.0f
					&& shadowMapUV.x > 0.0f
					&& shadowMapUV.y < 1.0f
					&& shadowMapUV.y > 0.0f
					) {
					///LVP空間での深度値を計算。
					float zInLVP = psIn.posInLVP[i].z / psIn.posInLVP[i].w;
					float zInShadowMap;
					//シャドウマップに書き込まれている深度値を取得。
					if (i == 0) {
						zInShadowMap = g_cascadeShadowMap1.Sample(g_sampler, shadowMapUV);
					}
					else if (i == 1) {
						zInShadowMap = g_cascadeShadowMap2.Sample(g_sampler, shadowMapUV);
					}
					else if (i == 2) {
						zInShadowMap = g_cascadeShadowMap3.Sample(g_sampler, shadowMapUV);
					}

					if (zInLVP > zInShadowMap + 0.0001f * (NUM_CASCADES - i)) {
						//影が落ちているので、光を弱くする
						spsOut.shadow = 0.5f;
						//	spsOut.shadow = zInShadowMap;
							//spsOut.shadow = zInLVP;
							//spsOut.shadow = psIn.pos.z / psIn.pos.w;

					}
					break;
				}
			}
		}
	}

	/*float3 lig = 0.0f;

	float t = max(0.0, dot(-light.dirLight.direction, psIn.normal));
	lig += t * light.dirLight.color;*/

	//ポイントライトから光によるランバート拡散反射を計算。
	/*for( int i = 0; i < NUM_POINT_LIGHT; i++){
		//１．光源からサーファイスに入射するベクトルを計算。
		float3 ligDir = normalize( psIn.worldPos - light.pointsLights[i].position);
		//２．光源からサーフェイスまでの距離を計算。
		float distance = length( psIn.worldPos - light.pointsLights[i].position );
		//３．光の入射ベクトルとサーフェイスの法線で内積を取って反射の強さを計算する。
		float t = max( 0.0f, dot( -ligDir , psIn.normal ) );
		//４．影響率を計算する。影響率は0.0～1.0の範囲で、
		//    指定した距離(pointsLights[i].range)を超えたら、影響率は0.0になる。
		float affect = 1.0f - min( 1.0f, distance / light.pointsLights[i].range );
		lig += light.pointsLights[i].color * t * affect;
	}*/ 
	//環境光を加算。
	//lig += 1.0f;
	//albedo.xyz *= lig;
	return spsOut;
}

/// <summary>
/// スキン無しシャドウマップ生成用の頂点シェーダー
/// </summary>
PSInput_ShadowMap VSMain_ShadowMap(SVSIn In)
{
	PSInput_ShadowMap psInput = (PSInput_ShadowMap)0;
	float4 pos = mul(mWorld, In.pos);
	pos = mul(mLightView, pos);
	pos = mul(mLightProj, pos);
	//pos = mul(mView, pos);
	//pos = mul(mProj, pos);
	psInput.Position = pos;
	return psInput;
}
/// <summary>
/// スキン有りシャドウマップ生成用の頂点シェーダー
/// </summary>
PSInput_ShadowMap VSMainSkin_ShadowMap(SVSIn In)
{
	PSInput_ShadowMap psInput = (PSInput_ShadowMap)0;
	float4x4 skinning = CalcSkinMatrix(In);
	float4 pos = mul(skinning, In.pos);
	pos = mul(mLightView, pos);
	pos = mul(mLightProj, pos);
	//pos = mul(mView, pos);
	//pos = mul(mProj, pos);
	psInput.Position = pos;
	return psInput;
}

/// <summary>
/// スキン無しカスケードシャドウマップ生成用の頂点シェーダー
/// </summary>
PSInput_ShadowMap VSMain_CascadeShadowMap(SVSIn In)
{
	PSInput_ShadowMap psInput = (PSInput_ShadowMap)0;
	float4 pos = mul(mWorld, In.pos);
	pos = mul(mLightViewProj[shadowMapNumber], pos);
	psInput.Position = pos;
	return psInput;
}

/// <summary>
/// スキン有りカスケードシャドウマップ生成用の頂点シェーダー
/// </summary>
PSInput_ShadowMap VSMainSkin_CascadeShadowMap(SVSIn In)
{
	PSInput_ShadowMap psInput = (PSInput_ShadowMap)0;
	float4x4 skinning = CalcSkinMatrix(In);
	float4 pos = mul(skinning, In.pos);
	pos = mul(mLightViewProj[shadowMapNumber], pos);
	psInput.Position = pos;
	return psInput;
}

/// <summary>
/// シャドウマップ生成用のピクセルシェーダー
/// </summary>
float4 PSMain_ShadowMap(PSInput_ShadowMap In) : SV_Target0
{
	//射影空間でのZ値を返す
	return In.Position.z / In.Position.w;
//return 0.1f;
}
