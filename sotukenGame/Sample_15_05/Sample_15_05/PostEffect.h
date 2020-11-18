#pragma once
#include "Primitive.h"

class PostEffect
{
public:
	/// <summary>
	/// 初期化
	/// </summary>
	void Init();
	/// <summary>
	/// 描画
	/// </summary>
	/// <param name="rc"></param>
	void Render(RenderContext& rc);
private:
	Primitive m_quadPrimitive;		//四角形プリミティブ
};

