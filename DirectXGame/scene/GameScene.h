#pragma once

#include <memory>
#include <imgui.h>

#include "Audio.h"
#include "DirectXCommon.h"
#include "Input.h"
#include "Model.h"
#include "SafeDelete.h"
#include "Sprite.h"
#include "ViewProjection.h"
#include "WorldTransform.h"

#include "DebugCamera.h"
#include "Player.h"
#include "SkyDome.h"

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

	// ワールドトランスフォーム
	WorldTransform worldTransform_;
	// ビュープロジェクション
	ViewProjection viewProjection_;

	// デバックカメラ
	std::unique_ptr<DebugCamera> debugCamera_;
	// デバックカメラを有効にするか
	bool enableDebugCamera_;

	// モデル
	std::unique_ptr<Model> model_;
	// プレイヤーテクスチャ
	uint32_t texturePlayer_ = 0;

	// 天球モデル
	std::unique_ptr<Model> modelSkyDome_;

	// プレイヤークラス
	std::unique_ptr<Player> player_;
	// 天球クラス
	std::unique_ptr<SkyDome> skyDome_;
};
