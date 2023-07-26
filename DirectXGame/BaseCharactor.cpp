#include "BaseCharactor.h"

void BaseCharactor::Initialize(const std::vector<Model*>& models) {
	// 引数の値をメンバ変数に代入する
	models_ = models;
	// ワールドトランスフォーム初期化
	worldTransform_.Initialize();
}

void BaseCharactor::Update() {
	// ワールドトランスフォーム更新
	worldTransform_.UpdateMatrix();
}

void BaseCharactor::Draw(const ViewProjection viewProjection) {
	// モデル描画
	for (Model* model : models_) {
		model->Draw(worldTransform_, viewProjection);
	}
}
