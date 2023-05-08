﻿#include "Enemy.h"

Enemy::Enemy() {

}

Enemy::~Enemy() {
	
	// 弾の解放
	for (EnemyBullet* bullet : bullets_) {
		delete bullet;
	}

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

	// 射撃タイマー初期化
	FireTimerInitialize();

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

	// 弾の更新処理
	for (EnemyBullet* bullet : bullets_) {
		bullet->Update();
	}

	// 行列の更新処理
	worldTransform_.UpdateMatrix();
}

/// <summary>
/// 描画処理
/// </summary>
/// <param name="viewProjection">ビュープロジェクション</param>
void Enemy::Draw(const ViewProjection& viewProjection) {

	// モデルの描画
	model_->Draw(worldTransform_, viewProjection, textureHandle_);

	// 弾描画
	for (EnemyBullet* bullet : bullets_) {
		bullet->Draw(viewProjection);
	}

}

/// <summary>
/// 敵の射撃処理
/// </summary>
void Enemy::Fire() {

	// 弾速
	const float kBulletSpeed = -1.0f;
	Vector3 velocity(0, 0, kBulletSpeed);

	// 速度ベクトルを自機の向きに合わせて回転させる
	velocity = MyMath::TransformNormal(velocity, worldTransform_.matWorld_);

	// 弾の生成と初期化
	EnemyBullet* newBullet = new EnemyBullet();
	newBullet->Initialize(model_, worldTransform_.translation_, velocity);

	// 弾を登録する
	bullets_.push_back(newBullet);

}

/// <summary>
/// 射撃タイマー初期化
/// </summary>
void Enemy::FireTimerInitialize() {
	// タイマー初期化
	this->fireTimer = this->kFireInterval;
}

/// <summary>
/// 接近状態の更新処理
/// </summary>
void Enemy::ApproachUpdate() {

	// ベクトルの初期化
	velocity_ = {0.0f, 0.0f, -0.25f};

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
		// 発射タイマー初期化
		FireTimerInitialize();
	}

}

void Enemy::LeaveUpdate() {

	// ベクトルの初期化
	velocity_ = {-0.5f, 0.5f, 0.0f};

	// 敵の座標を移動させる
	worldTransform_.translation_ = MyMath::Add(worldTransform_.translation_, velocity_);
}