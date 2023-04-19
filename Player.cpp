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

}

/// <summary>
/// 更新処理
/// </summary>
void Player::Update() {

	// 行列を定数バッファに転送
	worldTransform_.TransferMatrix();

	/// プレイヤーの移動処理

	// 移動ベクトル
	Vector3 move = {0, 0, 0};

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
		move.y -= kSpeed;
	} else if (input_->PushKey(DIK_DOWN)) {
		move.y += kSpeed;
	}

	// 座標移動(ベクトルの加算)
	Add(worldTransform_.translation_, move);
}

/// <summary>
/// 描画処理
/// </summary>
/// <param name="viewProjection">ビュープロジェクション</param>
void Player::Draw(ViewProjection& viewProjection) {
	// 3Dモデル描画
	model_->Draw(worldTransform_, viewProjection, textureHandle_);
}
