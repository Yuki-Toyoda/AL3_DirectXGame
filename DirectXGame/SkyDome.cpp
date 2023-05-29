#include "SkyDome.h"

/// <summary>
/// 初期化処理
/// </summary>
void SkyDome::Initialize(Model* model) {

	// NULLポインタチェック
	assert(model);

	// 引数として受け取ったデータをメンバ変数に記録
	// モデル
	model_ = model;

	// ワールド座標の初期化
	worldTransform_.Initialize();
	worldTransform_.translation_ = {0.0f, 0.0f, 0.0f};

}

/// <summary>
/// 更新処理
/// </summary>
void SkyDome::Update() {

	worldTransform_.UpdateMatrix();

}

/// <summary>
/// 描画処理
/// </summary>
void SkyDome::Draw(ViewProjection& viewProjection) {

	// モデル描画
	model_->Draw(worldTransform_, viewProjection);

}
