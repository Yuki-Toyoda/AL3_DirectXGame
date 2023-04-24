#include "Enemy.h"

Enemy::Enemy() {

}

Enemy::~Enemy() {
	
}

/// <summary>
/// 初期化処理
/// </summary>
/// <param name="model">3Dモデル</param>
/// <param name="position">初期座標</param>
/// <param name="velocity">速度</param>
void Enemy::Initialize(Model* model, const Vector3& position, const Vector3& velocity) {

	// NULLポインタチェック
	assert(model);
	// モデル読み込み
	model_ = model;

	// ポジション初期化
	worldTransform_.Initialize();
	worldTransform_.translation_ = position;

	// テクスチャの読み込み
	textureHandle_ = TextureManager::Load("white1x1.png");

	// 引数で受け取った速度をメンバ変数に代入する
	velocity_ = velocity;

}

/// <summary>
/// 更新処理
/// </summary>
void Enemy::Update() {

	// 行列の更新処理
	worldTransform_.UpdateMatrix();

	// 敵の座標を移動させる
	worldTransform_.translation_ = MyMath::Add(worldTransform_.translation_, velocity_);

}

/// <summary>
/// 描画処理
/// </summary>
/// <param name="viewProjection">ビュープロジェクション</param>
void Enemy::Draw(const ViewProjection& viewProjection) {

	// モデルの描画
	model_->Draw(worldTransform_, viewProjection, textureHandle_);

}