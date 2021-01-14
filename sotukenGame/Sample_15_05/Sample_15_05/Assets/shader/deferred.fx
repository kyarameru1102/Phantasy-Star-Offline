
cbuffer cb : register(b0){
	float4x4 mvp;	
	float4 mulColor;
};

cbuffer DirectionLight : register(b1){
	float3 ligDirection;	//ライトの方向。
	float3 ligColor;		//ライトのカラー

};
struct VSInput{
	float4 pos : POSITION;
	float2 uv  : TEXCOORD0;
};

struct PSInput{
	float4 pos : SV_POSITION;
	float2 uv  : TEXCOORD0;
};

Texture2D<float4> albedoTexture : register(t0);	//アルベド。
Texture2D<float4> normalTexture : register(t1);	//法線。
Texture2D<float4> shadowTexture : register(t2); //シャドウ

sampler Sampler : register(s0);

PSInput VSMain(VSInput In) 
{
	PSInput psIn;
	psIn.pos = mul( mvp, In.pos );
	psIn.uv = In.uv;
	return psIn;
}
float4 PSMain(PSInput In) : SV_Target0
{
	float4 albedo = albedoTexture.Sample(Sampler, In.uv);
	float3 normal = normalTexture.Sample(Sampler, In.uv).xyz;
	float shadow = shadowTexture.Sample(Sampler, In.uv);
	normal = (normal * 2.0f)-1.0f;
	//ライトを計算。
	float3 lig = 0.0f;
	float t = max( 0.0f, dot( normal, ligDirection) * -1.0f);
	lig = ligColor * t;
	lig += 1.0f;
	//lig *= shadow;
	float4 finalColor = float4(0.0f, 0.0f, 0.0f, 1.0f);
	finalColor = albedo;
	//finalColor.xyz = normal;
	//finalColor = float4(1.0f, 0.0f, 0.0f, 1.0f);
	//finalColor.xyz = world;
	finalColor.xyz *= lig;
	finalColor.xyz *= shadow;
	return finalColor;
}