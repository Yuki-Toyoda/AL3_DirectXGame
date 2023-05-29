#include "Player.h"

/// <summary>
/// コンストラクタ
/// </summary>
Player::Player() {
	
}

/// <summary>
/// デストラクタ
/// </summary>
Player::~Player() {

	// 弾の解放
	for (PlayerBullet* bullet : bullets_) {
		delete bullet;
	}

}

/// <summary>
/// 初期化処理
/// </summary>
/// <param name="model">3Dモデル</param>
/// <param name="textureHandle">テクスチャハンドル</param>
void Player::Initialize(Model* model, uint32_t textureHandle) {

	// シングルトンインスタンスを取得
	input_ = Input::GetInstance();

	// NULLポインタチェック
	assert(model);

	// 引数として受け取ったデータをメンバ変数に記録
	// モデル
	model_ = model;
	// テクスチャ
	textureHandle_ = textureHandle;

	// ワールド座標の初期化
	worldTransform_.Initialize();
	worldTransform_.translation_.z = 50.0f;

	// 移動ベクトルの初期化
	move = {0.0f, 0.0f, 0.0f};

}

/// <summary>
/// 更新処理
/// </summary>
void Player::Update() {

	// 行列を定数バッファに転送
	worldTransform_.TransferMatrix();

	/// プレイヤーの移動処理

	// 移動ベクトル
	move = {0.0f, 0.0f, 0.0f};

	// 移動スピード
	const float kSpeed = 0.2f;

	// 押した方向で移動ベクトルを変更する(左右)
	if (input_->PushKey(DIK_LEFT)) {
		move.x -= kSpeed;
	} else if (input_->PushKey(DIK_RIGHT)) {
		move.x += kSpeed;
	}

	// 押した方向で移動ベクトルを変更する(上下)
	if (input_->PushKey(DIK_UP)) {
		move.y += kSpeed;
	} else if (input_->PushKey(DIK_DOWN)) {
		move.y -= kSpeed;
	}

	// プレイヤーの旋回処理
	if (input_->PushKey(DIK_A)) {
		worldTransform_.rotation_.y -= kRotSpeed;
	}
	else if(input_->PushKey(DIK_D)) {
		worldTransform_.rotation_.y += kRotSpeed;
	}

	// 座標移動(ベクトルの加算)
	worldTransform_.translation_ = MyMath::Add(worldTransform_.translation_, move);
	
	/// 移動制限処理
	// 範囲を超えない処理
	worldTransform_.translation_.x = max(worldTransform_.translation_.x, -kMoveLimitX);
	worldTransform_.translation_.x = min(worldTransform_.translation_.x, +kMoveLimitX);
	worldTransform_.translation_.y = max(worldTransform_.translation_.y, -kMoveLimitY);
	worldTransform_.translation_.y = min(worldTransform_.translation_.y, +kMoveLimitY);

	// 行列の更新
	worldTransform_.UpdateMatrix();

	// 攻撃処理
	Attack();

	// 弾の更新処理
	for (PlayerBullet* bullet : bullets_) {
		bullet->Update();
	}

	// デスフラグの立った弾を削除
	bullets_.remove_if([](PlayerBullet* bullet) {
		if (bullet->IsDead()) {
			delete bullet;
			return true;
		}
		return false;
	});

	// デバック用の値を変える
	translation[0] = worldTransform_.translation_.x;
	translation[1] = worldTransform_.translation_.y;
	translation[2] = worldTransform_.translation_.z;

	// デバッグ描画
	ImGui::Begin("Player");
	ImGui::SliderFloat3("Player", translation, -100.0f, 100.0f);
	ImGui::End();

}

/// <summary>
/// 描画処理
/// </summary>
/// <param name="viewProjection">ビュープロジェクション</param>
void Player::Draw(ViewProjection& viewProjection) {
	// 3Dモデル描画
	model_->Draw(worldTransform_, viewProjection, textureHandle_);

	// 弾描画
	for (PlayerBullet* bullet : bullets_) {
		bullet->Draw(viewProjection);
	}

}

/// <summary>
/// 
/// </summary>
void Player::Attack() {
	if (input_->TriggerKey(DIK_SPACE)) {

		// 弾速
		const float kBulletSpeed = 1.0f;
		Vector3 velocity(0, 0, kBulletSpeed);

		// 速度ベクトルを自機の向きに合わせて回転させる
		velocity = MyMath::TransformNormal(velocity, worldTransform_.matWorld_);

		// 弾の生成と初期化
		PlayerBullet* newBullet = new PlayerBullet();
		newBullet->Initialize(model_, GetWorldPosition(), velocity);

		// 弾を登録する
		bullets_.push_back(newBullet);
	}

}

Vector3 Player::GetWorldPosition() {

	// 結果格納用
	Vector3 worldPos;
	// ワールド行列の平行移動成分を取得
	worldPos.x = worldTransform_.matWorld_.m[3][0];
	worldPos.y = worldTransform_.matWorld_.m[3][1];
	worldPos.z = worldTransform_.matWorld_.m[3][2];

	// 結果を返す
	return worldPos;
}

/// <summary>
/// 衝突判定関数
/// </summary>
void Player::OnCollision() {
	
}

/// <summary>
/// 親子関係をセットするセッター
/// </summary>
/// <param name="parent">親</param>
void Player::SetParent(const WorldTransform* parent) {
	// 親子関係を結ぶ
	worldTransform_.parent_ = parent;
}