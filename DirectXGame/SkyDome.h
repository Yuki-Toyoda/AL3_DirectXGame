#pragma once
#include <cassert>
#include "Model.h"
#include "WorldTransform.h"

/// <summary>
/// 天球クラス
/// </summary>
class SkyDome {

public: // メンバ関数

	/// <summary>
	/// 初期化処理
	/// </summary>
	/// <param name="model">3Dモデル</param>
	void Initialize(Model* model);

	/// <summary>
	/// 更新関数
	/// </summary>
	void Update();

	/// <summary>
	/// 描画関数
	/// </summary>
	/// <param name="viewProjection">ビュープロジェクション</param>
	void Draw(ViewProjection viewProjection);

private: // メンバ変数

	// ワールドトランスフォーム
	WorldTransform worldTransform_;

	// モデル
	Model* model_ = nullptr;

};
