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

	model_ = model;
	// テクスチャの読み込み
	textureHandle_ = TextureManager::Load("block.png");

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

}