/*!
 * @brief	tkエクスポーターの共通処理。
 */
 
--オブジェクトパラメータ。
struct ObjectParam(
	objName,
	isShadowCaster,
	isShadowReceiver,

	numIntParam,
	intParams,

	numFloatParam,
	floatParams,

	numStringParam,
	stringParamLength,
	stringParams,

	numVec3Param,
	vec3Params,
	
	bindPose,	
	invBindPose,
	parentId,
	n
)

--オブジェクトパラメータの配列。
g_objectParams = #()
/*
*  出力するノードの情報を構築。
*/
fn BuildOutputNodeInfo n parentId= 
(
	objParam = ObjectParam "" true true 0 #() 0 #() 0 #() #() 0 #() Matrix3 Matrix3 -1 Node
	objParam.objName = n.name
	objParam.bindPose = n.transform
	if n.modifiers[maxPlugin] != undefined then(
		objParam.isShadowCaster = n.modifiers[maxPlugin].caster
		objParam.isShadowReceiver = n.modifiers[maxPlugin].receiver

		--int型のカスタムパラメータ出力
		objParam.numIntParam = n.modifiers[maxPlugin].intList.count
		for i = 1 to objParam.numIntParam do (
			append objParam.intParams n.modifiers[maxPlugin].intList[i]	
		)

		--float型のカスタムパラメータ出力
		objParam.numFloatParam = n.modifiers[maxPlugin].floatList.count
		for i = 1 to objParam.numFloatParam do (
			append objParam.floatParams n.modifiers[maxPlugin].floatList[i]	
		)

		--string型のカスタムパラメータ出力
		objParam.numStringParam = n.modifiers[maxPlugin].strList.count
		for i = 1 to objParam.numStringParam do (
			append objParam.stringParamLength n.modifiers[maxPlugin].strList[i].count
			append objParam.stringParams n.modifiers[maxPlugin].strList[i]	
		)

		--Vector3型のカスタムパラメータ出力
		objParam.numVec3Param = n.modifiers[maxPlugin].vec3List.count
		for i = 1 to objParam.numVec3Param do (
			append objParam.Vec3Params n.modifiers[maxPlugin].vec3List[i]	
		)

	)else(
		objParam.isShadowCaster = false
		objParam.isShadowReceiver = false
	)

	objParam.invBindPose = inverse n.transform
	objParam.n = n
	if n.parent == undefined then(
		--親がいない
		objParam.parentId = -1
	)else(
		--親がいる
		objParam.parentId = parentId
	)

	append g_objectParams objParam
	parentId = g_objectParams.count-1
	--子供も。
	for child in n.children do(
		BuildOutputNodeInfo child parentId
	)
)

/*!
 * ボーンインデックスを取得する。
 * この関数を呼び出すには、BuildOutputNodeInfoを実行して
 * スケルトン情報を構築済みである必要があります。
*/
fn GetBoneIndex boneName =
(
	boneNo = 0
	for op in g_objectParams do(
		if op.objName == boneName then(
			--見つけた
			return boneNo
		)
		boneNo += 1
	)
)
/*
*  スキンモディファイアが設定されているノードがあったら、そのノードに割り当てられているスケルトンのルートを取得。
*/
fn GetSkeletonRoot nodes =
(
	for p in nodes do
	(
		--スキンモディファイアを取得。
		skinMod = p.modifiers[skin]
		
		if skinMod != undefined then(
			--スキンを見つけた。
			max modify mode
			
			modPanel.setCurrentObject skinMod
			numBone = skinOps.GetNumberBones( skinMod )
			if numBone > 0 then(
				--bone発見したぞいぞい
				boneName = skinOps.GetBoneName skinMod 1 1 
				--名前からノードを選択
				boneNode = getNodebyName(boneName)
				if boneNode != undefined  then (
					--スケルトンのルートを検索するぞ
					while boneNode.parent != undefined  do(
						boneNode = boneNode.parent
					)
					--ルートを返すん。
					return boneNode
				)
			)
		)
	)
	return undefined
)
/*
*  マテリアルが貼られていないノードがないかチェックを行う。
*/
fn CheckMaterial nodes =
(
	for p in nodes do
	(
		meshCount = GetTriMeshFaceCount(p)
		if classof( p ) == BoneGeometry do(
			--こいつはボーン
			meshCount[1] = 0
			meshCount[2] = 0
		)
		if meshCount[1] > 0 do
		(
			--メッシュがある。
			if p.material == undefined do
			(
				--マテリアルが張られていない。
				errorMessage = "エラー\n " + p.name + "にマテリアルが割り当てられていないため出力できません。\n"+ "マテリアルを割り当ててください。\n"
				messagebox errorMessage
				return false				
			)
		)
	)
	return true
)