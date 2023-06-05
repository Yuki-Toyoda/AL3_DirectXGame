#include "Player.h"
#include "GameScene.h"

/// <summary>
/// コンストラクタ
/// </summary>
Player::Player() {
	
}

/// <summary>
/// デストラクタ
/// </summary>
Player::~Player() { 
	// スプライト解放
	delete sprite2DReticle_; 
}

/// <summary>
/// 初期化処理
/// </summary>
/// <param name="model">3Dモデル</param>
/// <param name="textureHandle">テクスチャハンドル</param>
/// <param name="gameScene">ゲームシーン</param>
void Player::Initialize(Model* model, uint32_t textureHandle, GameScene* gameScene) {

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
	worldTransform3DReticle_.Initialize();

	// 移動ベクトルの初期化
	move = {0.0f, 0.0f, 0.0f};

	// ゲームシーンをセットする
	SetGameScene(gameScene);

	// レティクル用テクスチャ読み込み
	uint32_t textureReticle = TextureManager::Load("reticle.png");
	sprite2DReticle_ = Sprite::Create(
	    textureReticle, {float(WinApp::kWindowWidth / 2), float(WinApp::kWindowHeight / 2)}, {1.0f, 1.0f, 1.0f, 1.0f}, {0.5f, 0.5f});
	sprite2DReticle_->SetSize({100.0f, 100.0f});
}

/// <summary>
/// 更新処理
/// </summary>
/// <param name="viewProjection">ビュープロジェクション</param>
void Player::Update(ViewProjection& viewProjection) {

	// 行列を定数バッファに転送
	worldTransform_.TransferMatrix();
	worldTransform3DReticle_.TransferMatrix();

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
	} else if (input_->PushKey(DIK_D)) {
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

	// プレイヤーからレティクルまでの距離
	const float kDistancePlayerTo3DReticle = 50.0f;
	// プレイヤーからレティクルへのオフセット
	Vector3 offset = {0.0f, 0.0f, 1.0f};
	// 自機のワールド行列の回転を反映
	offset = MyMath::TransformNormal(offset, worldTransform_.matWorld_);
	// ベクトルの長さを正規化する
	offset = MyMath::Multiply(kDistancePlayerTo3DReticle, MyMath::Normalize(offset));
	// 3Dレティクルの座標を設定
	worldTransform3DReticle_.translation_ = GetWorldPosition() + offset;

	worldTransform3DReticle_.UpdateMatrix();

	// レティクルのワールド座標を取得
	Vector3 ReticleWorldPos;
	ReticleWorldPos.x = worldTransform3DReticle_.matWorld_.m[3][0];
	ReticleWorldPos.y = worldTransform3DReticle_.matWorld_.m[3][1];
	ReticleWorldPos.z = worldTransform3DReticle_.matWorld_.m[3][2];

	// 3Dレティクルのワールド座標を取得
	Vector3 positionReticle = ReticleWorldPos;

	// ビューポート行列の生成
	Matrix4x4 matViewport =
	    MyMath::MakeViewPortMatrix(0, 0, WinApp::kWindowWidth, WinApp::kWindowHeight, 0, 1);

	// ビュー行列とプロジェクション行列、ビューポート行列を合成
	Matrix4x4 matViewProjectionViewport = MyMath::Multiply(
	    MyMath::Multiply(viewProjection.matView, viewProjection.matProjection), matViewport);

	// ワールド座標からスクリーン座標系に変換
	positionReticle = MyMath::Transform(positionReticle, matViewProjectionViewport);

	//// スプライトの座標にセット
	sprite2DReticle_->SetPosition({positionReticle.x, positionReticle.y});

	// 攻撃処理
	Attack();

	// デバッグ描画
	ImGui::Begin("Player");
	ImGui::SliderFloat3("translate", &worldTransform_.translation_.x, -50.0f, 50.0f);
	ImGui::End();

}

/// <summary>
/// 描画処理
/// </summary>
/// <param name="viewProjection">ビュープロジェクション</param>
void Player::Draw(ViewProjection& viewProjection) {
	// プレイヤーモデル描画
	model_->Draw(worldTransform_, viewProjection, textureHandle_);
	// レティクル描画
	//model_->Draw(worldTransform3DReticle_, viewProjection, textureHandle_);
}

void Player::DrawUI() {

	// スプライト描画
	sprite2DReticle_->Draw();

}

/// <summary>
/// 
/// </summary>
void Player::Attack() {
	if (input_->TriggerKey(DIK_SPACE)) {

		// 弾速
		const float kBulletSpeed = 0.25f;
		Vector3 velocity(0, 0, kBulletSpeed);

		// 速度ベクトルを自機の向きに合わせて回転させる

		Vector3 ReticleWorldPos;
		ReticleWorldPos.x = worldTransform3DReticle_.matWorld_.m[3][0];
		ReticleWorldPos.y = worldTransform3DReticle_.matWorld_.m[3][1];
		ReticleWorldPos.z = worldTransform3DReticle_.matWorld_.m[3][2];

		velocity = ReticleWorldPos - GetWorldPosition();
		velocity = MyMath::Multiply(kBulletSpeed, MyMath::Normalize(velocity));
		//velocity = MyMath::TransformNormal(velocity, worldTransform_.matWorld_);

		// 弾の生成と初期化
		PlayerBullet* newBullet = new PlayerBullet();
		newBullet->Initialize(model_, GetWorldPosition(), velocity);

		// 弾を登録する
		gameScene_->AddPlayerBullet(newBullet);

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