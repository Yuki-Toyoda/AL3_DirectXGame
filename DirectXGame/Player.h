#pragma once
#include <cassert>
#include <list>
#include "MyMath.h"
#include "Model.h"
#include "Sprite.h"
#include "WorldTransform.h"
#include "Input.h"
#include "ImGuiManager.h"
#include "PlayerBullet.h"

// ゲームシーンクラスの前方宣言
class GameScene;

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
	/// <param name="gameScene">ゲームシーン</param>
	void Initialize(Model* model, uint32_t textureHandle, GameScene* gameScene);

	/// <summary>
	/// 更新処理
	/// </summary>
	/// <param name="viewProjection">ビュープロジェクション</param>
	void Update(ViewProjection& viewProjection);

	/// <summary>
	/// 描画処理
	/// </summary>
	void Draw(ViewProjection& viewProjection);

	/// <summary>
	/// UIの描画処理
	/// </summary>
	void DrawUI();

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
	/// 親子関係をセットするセッター
	/// </summary>
	/// <param name="parent">親</param>
	void SetParent(const WorldTransform* parent);

	/// <summary>
	/// ゲームシーンのセッター
	/// </summary>
	/// <param name="gameScene"></param>
	void SetGameScene(GameScene* gameScene) { gameScene_ = gameScene; }

private:

	// キーボード入力
	Input* input_ = nullptr;

	// ワールド変換データ
	WorldTransform worldTransform_;
	// 3Dレティクル用ワールド変換データ
	WorldTransform worldTransform3DReticle_;

	// スプライト
	Sprite* sprite2DReticle_ = nullptr;

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

	// ゲームシーン
	GameScene* gameScene_ = nullptr;

};
