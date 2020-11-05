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

//モデル用の定数バッファ
cbuffer ModelCb : register(b0){
	float4x4 mWorld;
	float4x4 mView;
	float4x4 mProj;
};

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
	//step ??? 頂点シェーダーからの出力にワールド座標を追加。
	float3 worldPos		: TEXCOORD1;	//ワールド座標。
};


//モデルテクスチャ。
Texture2D<float4> g_texture : register(t0);	
//ボーン行列
StructuredBuffer<float4x4> boneMatrix : register(t1);

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

	psIn.pos = mul(mWorld, vsIn.pos);	//モデルの頂点をワールド座標系に変換。	+
	
	psIn.worldPos = psIn.pos;

	psIn.pos = mul(mView, psIn.pos);	//ワールド座標系からカメラ座標系に変換。
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
	
	psIn.pos = mul(mView, psIn.pos);	//ワールド座標系からカメラ座標系に変換。
	psIn.pos = mul(mProj, psIn.pos);	//カメラ座標系からスクリーン座標系に変換。
	psIn.normal = normalize(mul(mWorld, vsIn.normal));
	psIn.uv = vsIn.uv;

	return psIn;
}

/// <summary>
/// モデル用のピクセルシェーダーのエントリーポイント
/// </summary>
float4 PSMain( SPSIn psIn ) : SV_Target0
{
	//アルベドカラーを出力。
	float4 albedo = g_texture.Sample(g_sampler, psIn.uv);

	float3 lig = 0.0f;

	float t = max(0.0, dot(-light.dirLight.direction, psIn.normal));
	lig += t * light.dirLight.color;

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
	lig += 1.0f;
	albedo.xyz *= lig;
	return albedo;
}
