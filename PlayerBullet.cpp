#include "PlayerBullet.h"

PlayerBullet::PlayerBullet() {

}
PlayerBullet::~PlayerBullet() {

}

/// <summary>
/// 初期化処理
/// </summary>
/// <param name="model">弾のモデル</param>
/// <param name="position">初期座標</param>
void PlayerBullet::Initialize(Model* model, const Vector3& position) {

	// NULLポインタチェック
	assert(model);

	// モデル読み込み
	model_ = model;

	// ポジション初期化
	worldTransform_.Initialize();
	worldTransform_.translation_ = position;

	// テクスチャの読み込み
	textureHandle_ = TextureManager::Load("white1x1.png");

}

/// <summary>
/// 更新処理
/// </summary>
void PlayerBullet::Update() {

	// ワールドトランスフォームの更新
	worldTransform_.UpdateMatrix();


}

/// <summary>
/// 描画処理
/// </summary>
void PlayerBullet::Draw(const ViewProjection& viewProjection) {

	// モデルの描画
	model_->Draw(worldTransform_, viewProjection, textureHandle_);

}