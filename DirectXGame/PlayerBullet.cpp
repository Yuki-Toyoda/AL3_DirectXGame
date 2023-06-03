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
/// <param name="velocity">速度</param>
void PlayerBullet::Initialize(Model* model, const Vector3& position, const Vector3& velocity) {

	// NULLポインタチェック
	assert(model);

	// モデル読み込み
	model_ = model;

	// ポジション初期化
	worldTransform_.Initialize();
	worldTransform_.translation_ = position;

	// 引数で受け取った速度をメンバ変数に代入する
	velocity_ = velocity;

	// テクスチャの読み込み
	textureHandle_ = TextureManager::Load("Arrow.png");

}

/// <summary>
/// 更新処理
/// </summary>
void PlayerBullet::Update() {

	// ワールドトランスフォームの更新
	worldTransform_.UpdateMatrix();

	// 弾の座標を移動させる
	worldTransform_.translation_ = MyMath::Add(worldTransform_.translation_, velocity_);

	// 時間経過で消滅
	if (--deathTimer_ <= 0) {
		isDead_ = true;
	}

}

/// <summary>
/// 描画処理
/// </summary>
void PlayerBullet::Draw(const ViewProjection& viewProjection) {

	// モデルの描画
	model_->Draw(worldTransform_, viewProjection, textureHandle_);

}

/// <summary>
/// 敵弾のワールド座標のゲッター
/// </summary>
/// <returns>敵弾のワールド座標</returns>
Vector3 PlayerBullet::GetWorldPosition() {
	// 結果格納用
	Vector3 worldPos;
	// ワールド行列の平行移動成分を取得
	worldPos = MyMath::TransformNormal(worldTransform_.translation_, worldTransform_.matWorld_);

	// 結果を返す
	return worldPos;
}

/// <summary>
/// 衝突判定関数
/// </summary>
void PlayerBullet::OnCollision() {
	// 死亡フラグをTrueにする
	isDead_ = true;
}