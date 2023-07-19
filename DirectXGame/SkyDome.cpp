#include "SkyDome.h"

void SkyDome::Initialize(Model* model) {

	// NULLチェック
	assert(model);

	// 引数の値をメンバ変数に代入
	model_ = (model);

	// ワールドトランスフォーム初期化
	worldTransform_.Initialize();

}

void SkyDome::Update() {

	// 行列を定数バッファに転送
	worldTransform_.TransferMatrix();

}

void SkyDome::Draw(ViewProjection viewProjection) {

	// モデル描画
	model_->Draw(worldTransform_, viewProjection);

}
