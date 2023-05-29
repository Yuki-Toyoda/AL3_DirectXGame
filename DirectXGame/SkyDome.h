#pragma once
#include <cassert>
#include "Model.h"
#include "WorldTransform.h"
class SkyDome {
public:

	/// <summary>
	/// 初期化処理
	/// </summary>
	void Initialize(Model* model);

	/// <summary>
	/// 更新処理
	/// </summary>
	void Update();

	/// <summary>
	/// 描画処理
	/// </summary>
	void Draw(ViewProjection& viewProjection);

private:

	// ワールド変換データ
	WorldTransform worldTransform_;
	// モデル
	Model* model_ = nullptr;

};
