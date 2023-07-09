#include "Ground.h"

void Ground::Initialize(Model* model) {

	// NULLチェック
	assert(model);

	// 引数の値をメンバ変数に代入
	model_ = model;

	// ワールドトランスフォーム初期化
	worldTransform_.Initialize();

}

void Ground::Update() {

	// 行列を定数バッファに転送
	worldTransform_.TransferMatrix();

}

void Ground::Draw(ViewProjection viewProjection) {

	// 描画処理
	model_->Draw(worldTransform_, viewProjection);

}
