#pragma once
#include <cassert>
#include "MyMath.h"
#include "Model.h"
#include "WorldTransform.h"
#include "Input.h"
#include "ImGuiManager.h"

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

	Vector3 GetPlayerTranslation() { return worldTransform_.translation_; } 

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

	// デバッグ用
	float translation[3] = {0.0f, 0.0f, 0.0f};

};
