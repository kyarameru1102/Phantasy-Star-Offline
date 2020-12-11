#pragma once

/// <summary>
/// コリジョンの属性。
/// </summary>
enum EnCollisionAttr{
	enCollisionAttr_map,
	enCollisionAttr_Character,
	enCollisionAttr_User,
	enCollisionAttr_ground,				//地面。
	enCollisionAttr_obstacle,			//カメラの判定から外したいときにこの属性を入れる。
	enCollisionAttr_Ghost,				//ゴースト。
};