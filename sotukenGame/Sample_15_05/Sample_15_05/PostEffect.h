#pragma once
#include "Primitive.h"

class PostEffect
{
public:
	/// <summary>
	/// ������
	/// </summary>
	void Init();
	/// <summary>
	/// �`��
	/// </summary>
	/// <param name="rc"></param>
	void Render(RenderContext& rc);
private:
	Primitive m_quadPrimitive;		//�l�p�`�v���~�e�B�u
};

