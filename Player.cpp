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

}

/// <summary>
/// 描画処理
/// </summary>
/// <param name="viewProjection">ビュープロジェクション</param>
void Player::Draw(ViewProjection& viewProjection) {
	// 3Dモデル描画
	model_->Draw(worldTransform_, viewProjection, textureHandle_);
}
