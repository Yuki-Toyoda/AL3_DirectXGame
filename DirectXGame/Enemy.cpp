#include "Enemy.h"
#include "Player.h"
#include "GameScene.h"

Enemy::Enemy() {

}

Enemy::~Enemy() {


}

/// <summary>
/// 初期化処理
/// </summary>
/// <param name="model">3Dモデル</param>
/// <param name="gameScene">ゲームシーン</param>
/// <param name="position">初期座標</param>
/// <param name="velocity">速度</param>
/// /// <param name="player">player</param>
void Enemy::Initialize(
    Model* model, GameScene* gameScene, const Vector3& position, const Vector3& velocity,
    Player* player) {

	// NULLポインタチェック
	assert(model);
	// モデル読み込み
	model_ = model;

	assert(player);
	player_ = player;

	// ポジション初期化
	worldTransform_.Initialize();
	worldTransform_.translation_ = position;

	// テクスチャの読み込み
	textureHandle_ = TextureManager::Load("white1x1.png");

	// デスフラグ
	isDead_ = false;

	// 引数で受け取った速度をメンバ変数に代入する
	velocity_ = velocity;

	// 射撃タイマー初期化
	FireTimerInitialize();

	// ゲームシーンをセットする
	SetGameScene(gameScene);

}

/// <summary>
/// 更新処理
/// </summary>
void Enemy::Update() {

	switch (phase_) {
	case Enemy::Phase::Approach:

		// 接近状態の更新処理
		ApproachUpdate();

		break;
	case Enemy::Phase::Leave:

		// 離脱状態の更新処理
		LeaveUpdate();

		break;
	default:
		break;
	}

	// 行列の更新処理
	worldTransform_.UpdateMatrix();

	if (worldTransform_.translation_.y >= 30.0f) {
		isDead_ = true; 
	}
}

/// <summary>
/// 描画処理
/// </summary>
/// <param name="viewProjection">ビュープロジェクション</param>
void Enemy::Draw(const ViewProjection& viewProjection) {

	if (!isDead_) {
		// モデルの描画
		model_->Draw(worldTransform_, viewProjection, textureHandle_);
	}
}

/// <summary>
/// 敵の現在座標を取得する
/// </summary>
/// <returns>敵の現在座標</returns>
Vector3 Enemy::GetWorldPosition() {
	// 結果格納用
	Vector3 worldPos;
	// ワールド行列の平行移動成分を取得
	worldPos = MyMath::TransformNormal(worldTransform_.translation_, worldTransform_.matWorld_);

	// 結果を返す
	return worldPos;
}

/// <summary>
/// 敵の射撃処理
/// </summary>
void Enemy::Fire() {

	// Nullチェック
	assert(player_);

	// 弾速
	const float kBulletSpeed = 0.75f;

	Vector3 playerTranslation = player_->GetWorldPosition();
	Vector3 enemyTranslation = GetWorldPosition();

	Vector3 vectorDif = playerTranslation - enemyTranslation;
	vectorDif = MyMath::Normalize(vectorDif);

	// 速度ベクトルを自機の向きに合わせて回転させる
	Vector3 velocity = {
	    (vectorDif.x * kBulletSpeed), (vectorDif.y * kBulletSpeed), (vectorDif.z * kBulletSpeed)};

	// 弾の生成と初期化
	EnemyBullet* newBullet = new EnemyBullet();
	newBullet->Initialize(model_, worldTransform_.translation_, velocity);

	// 弾を登録する
	gameScene_->AddEnemyBullet(newBullet);

	fireTimer = kFireInterval;

}

/// <summary>
/// 射撃タイマー初期化
/// </summary>
void Enemy::FireTimerInitialize() {
	// タイマー初期化
	this->fireTimer = this->kFireInterval;
}

/// <summary>
/// 衝突判定関数
/// </summary>
void Enemy::OnCollision() {

	isDead_ = true;

}

/// <summary>
/// 接近状態の更新処理
/// </summary>
void Enemy::ApproachUpdate() {

	// 敵の座標を移動させる
	worldTransform_.translation_ = MyMath::Add(worldTransform_.translation_, velocity_);

	// 指定の位置まで移動したら離脱
	if (worldTransform_.translation_.z < 0.0f) {
		phase_ = Phase::Leave;
	}

	// 発射タイマーカウントダウン
	fireTimer--;
	// 指定時間に達したら
	if (fireTimer <= 0) {
		// 弾を発射
		Fire();
		fireTimer = kFireInterval;
	}

}

void Enemy::LeaveUpdate() {

	// ベクトルの初期化
	velocity_ = {-0.5f, 0.5f, 0.0f};

	// 敵の座標を移動させる
	worldTransform_.translation_ = MyMath::Add(worldTransform_.translation_, velocity_);
}