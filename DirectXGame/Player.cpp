#include "Player.h"

void Player::Initialize(Model* model, uint32_t textureHandle) {
	// NULLチェック
	assert(model);

	// ワールドトランスフォーム初期化
	worldTransform_.Initialize();

	// 引数の値をメンバ変数に代入する
	model_ = model;
	textureHandle_ = textureHandle;
}

void Player::Update() {

	// 行列を定数バッファに転送する
	worldTransform_.TransferMatrix();
}

void Player::Draw(ViewProjection viewProjection) {
	// 描画
	model_->Draw(worldTransform_, viewProjection, textureHandle_);
}
