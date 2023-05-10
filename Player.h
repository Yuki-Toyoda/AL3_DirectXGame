#pragma once
#include <cassert>
#include <list>
#include "MyMath.h"
#include "Model.h"
#include "WorldTransform.h"
#include "Input.h"
#include "ImGuiManager.h"
#include "PlayerBullet.h"

/// <summary>
/// プレイヤークラス
/// </summary>
class Player {
public:
	Player();
	~Player();

	/// <summary>
	/// 初期化処理
	/// </summary>
	/// <param name="model">3Dモデル</param>
	/// <param name="textureHandle">テクスチャハンドル</param>
	void Initialize(Model* model, uint32_t textureHandle);

	/// <summary>
	/// 更新処理
	/// </summary>
	void Update();

	/// <summary>
	/// 描画処理
	/// </summary>
	void Draw(ViewProjection& viewProjection);

	/// <summary>
	/// プレイヤーの攻撃処理
	/// </summary>
	void Attack();

	/// <summary>
	/// プレイヤーのワールド座標のゲッター
	/// </summary>
	/// <returns>プレイヤーのワールド座標</returns>
	Vector3 GetWorldPosition();

	/// <summary>
	/// 衝突判定コールバック関数
	/// </summary>
	void OnCollision();

	/// <summary>
	/// 弾のリストを取得するゲッター
	/// </summary>
	/// <returns>弾のリスト</returns>
	const std::list<PlayerBullet*>& GetBullets() { return bullets_; }

private:

	// キーボード入力
	Input* input_ = nullptr;

	// ワールド変換データ
	WorldTransform worldTransform_;

	// モデル
	Model* model_ = nullptr;

	// テクスチャハンドル
	uint32_t textureHandle_ = 0u;

	// 移動ベクトル
	Vector3 move;

	// 移動限界
	const float kMoveLimitX = 34.0f;
	const float kMoveLimitY = 19.0f;

	// 旋回速さ
	const float kRotSpeed = 0.02f;

	// 弾
	std::list<PlayerBullet*> bullets_;

	// デバッグ用
	float translation[3] = {0.0f, 0.0f, 0.0f};

};
