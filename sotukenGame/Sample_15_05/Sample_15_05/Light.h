#pragma once


//ディレクションライト。
struct DirectionLight {
	Vector4 direction;		//ライトの方向。
	Vector4 color;			//ライトの色。
};

//ライト。
struct AllLight {
	DirectionLight dirLig;
};

