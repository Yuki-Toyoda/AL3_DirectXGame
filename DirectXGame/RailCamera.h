#pragma once
#include <imgui.h>
#include "WorldTransform.h"
#include "ViewProjection.h"
#include "MyMath.h"

class RailCamera {
public:

	/// <summary>
	/// 初期化処理
	/// </summary>
	/// <param name="translation">ワールド座標</param>
	/// <param name="rotate">回転角</param>
	void Initialize(Vector3 translation_, Vector3 rotate);

	/// <summary>
	/// 更新処理
	/// </summary>
	void Update();

	#pragma region アクセッサ等

	/// <summary>
	/// ビュープロジェクションを取得
	/// </summary>
	/// <returns>ビュープロジェクション</returns>
	ViewProjection GetViewProjection() { return viewProjection_; }

	WorldTransform& GetWorldMatrix() { return worldTransform_; }

#pragma endregion


private:

	// ワールド変換データ
	WorldTransform worldTransform_;

	// ビュープロジェクション
	ViewProjection viewProjection_;

	// デバック用座標
	float translation[3];
	// デバック用角度
	float rotation[3];

};
