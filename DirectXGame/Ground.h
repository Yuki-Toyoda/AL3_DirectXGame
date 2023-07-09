#pragma once
#include <cassert>

#include "Model.h"
#include "WorldTransform.h"

/// <summary>
/// 地面クラス
/// </summary>
class Ground {
public: // メンバ関数

	/// <summary>
	/// 初期化関数
	/// </summary>
	/// <param name="model">3Dモデル</param>
	void Initialize(Model* model);

	/// <summary>
	/// 更新関数
	/// </summary>
	void Update();

	/// <summary>
	/// 描画処理
	/// </summary>
	/// <param name="viewProjection">ビュープロジェクション</param>
	void Draw(ViewProjection viewProjection);

private: // メンバ変数

	// ワールドトランスフォーム
	WorldTransform worldTransform_;

	// モデル
	std::unique_ptr<Model> model_;

};
