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

	// 行動状態の設定
	state = new EnemyStateApproach();

}

/// <summary>
/// 更新処理
/// </summary>
void Enemy::Update() {

	//switch (phase_) {
	//case Enemy::Phase::Approach:

	//	// 接近状態の更新処理
	//	ApproachUpdate();

	//	break;
	//case Enemy::Phase::Leave:

	//	// 離脱状態の更新処理
	//	LeaveUpdate();

	//	break;
	//default:
	//	break;
	//}

	// 行動の更新処理
	state->Update(this);

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

}

/// <summary>
/// 敵の行動状態を変更する関数
/// </summary>
/// <param name="enemyState">次の敵の行動状態</param>
void Enemy::ChangeEnemyState(BaseEnemyState* enemyState) { 
	
	// NULLチェック
	assert(enemyState);
	// 元のステートを削除
	delete state;
	// ステートを新規作成
	state = new EnemyStateLeave;
	// 行動状態セット
	state = enemyState; 

}

/// <summary>
/// 接近状態の更新処理
/// </summary>
void Enemy::ApproachUpdate() {

	// ベクトルの初期化
	velocity_ = {0.0f, 0.0f, -0.5f};

	// 敵の座標を移動させる
	worldTransform_.translation_ = MyMath::Add(worldTransform_.translation_, velocity_);

	// 指定の位置まで移動したら離脱
	if (worldTransform_.translation_.z < 0.0f) {
		phase_ = Phase::Leave;
	}

}

void Enemy::LeaveUpdate() {

	// ベクトルの初期化
	velocity_ = {-0.5f, 0.5f, 0.0f};

	// 敵の座標を移動させる
	worldTransform_.translation_ = MyMath::Add(worldTransform_.translation_, velocity_);
}

void Enemy::MoveEnemy(const Vector3& velocity) {

	// ベクトルの初期化
	velocity_ = velocity;

	// 敵の座標を移動させる
	worldTransform_.translation_ = MyMath::Add(worldTransform_.translation_, velocity_);

}

void BaseEnemyState::Update(Enemy* enemy) {
	// 敵の現在座標の取得
	translation = enemy->GetEnemyTranslation();
}

void EnemyStateApproach::Update(Enemy* enemy) {

	// 敵の現在座標の取得
	translation = enemy->GetEnemyTranslation();

	// 移動処理
	enemy->MoveEnemy({0.0f, 0.0f, -0.5f});
	if (translation.z < 0.0f) {
		// 敵の行動状態
		enemy->ChangeEnemyState(new EnemyStateLeave());
	}

}

void EnemyStateLeave::Update(Enemy* enemy) {

	// 敵の現在座標の取得
	translation = enemy->GetEnemyTranslation();

	// 移動処理
	enemy->MoveEnemy({-0.5f, 0.5f, 0.0f});

}