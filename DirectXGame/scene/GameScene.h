#pragma once

#include "Audio.h"
#include "RailCamera.h"
#include "DebugCamera.h"
#include "DirectXCommon.h"
#include "Enemy.h"
#include "Input.h"
#include "Model.h"
#include "Player.h"
#include "SkyDome.h"
#include "SafeDelete.h"
#include "Sprite.h"
#include "ViewProjection.h"
#include "WorldTransform.h"

/// <summary>
/// ゲームシーン
/// </summary>
class GameScene {

public: // メンバ関数
	/// <summary>
	/// コンストクラタ
	/// </summary>
	GameScene();

	/// <summary>
	/// デストラクタ
	/// </summary>
	~GameScene();

	/// <summary>
	/// 初期化
	/// </summary>
	void Initialize();

	/// <summary>
	/// 毎フレーム処理
	/// </summary>
	void Update();

	/// <summary>
	/// 描画
	/// </summary>
	void Draw();

private: // メンバ変数
	DirectXCommon* dxCommon_ = nullptr;
	Input* input_ = nullptr;
	Audio* audio_ = nullptr;

	/// <summary>
	/// ゲームシーン用
	/// </summary>

	// テクスチャハンドル
	uint32_t textureHandle_ = 0;

	// デバックカメラ
	DebugCamera* debugCamera_ = nullptr;
	// デバックカメラを有効
	bool isDebugCameraActive_ = false;

	// レールカメラ
	RailCamera* railCamera = nullptr;

	// 3Dモデル
	Model* model = nullptr;

	// ビュープロジェクション
	ViewProjection viewProjection_;

	// プレイヤー
	Player* player_ = nullptr;

	// 敵
	Enemy* enemy_ = nullptr;

	// 天球
	Model* modelSkyDome_ = nullptr;

	// スカイドーム
	SkyDome* skyDome_ = nullptr;

};