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
	if (bullet_) {
		bullet_->Update();
	}

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
	if (bullet_) {
		bullet_->Draw(viewProjection);
	}

}

/// <summary>
/// 
/// </summary>
void Player::Attack() {
	if (input_->TriggerKey(DIK_SPACE)) {
		// 弾の生成と初期化
		PlayerBullet* newBullet = new PlayerBullet();
		newBullet->Initialize(model_, worldTransform_.translation_);

		// 弾を登録する
		bullet_ = newBullet;
	}

}
