#pragma once

#include <memory>

#include "Audio.h"
#include "DirectXCommon.h"
#include "Input.h"
#include "Model.h"
#include "SafeDelete.h"
#include "Sprite.h"
#include "ViewProjection.h"
#include "WorldTransform.h"

#include "DebugCamera.h"
#include "FollowCamera.h"
#include "Player.h"
#include "SkyDome.h"
#include "Ground.h"

#ifdef _DEBUG
#include <imgui.h>
#endif // _DEBUG

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

	// 追従カメラ
	std::unique_ptr<FollowCamera> followCamera_;

	// モデル
	std::unique_ptr<Model> model_;
	// プレイヤーモデル
	std::unique_ptr<Model> modelFighterBody_; // 体
	std::unique_ptr<Model> modelFighterHead_; // 頭
	std::unique_ptr<Model> modelFighterL_Arm_; // 左腕
	std::unique_ptr<Model> modelFighterR_Arm_; // 右腕
	// プレイヤーテクスチャ
	uint32_t texturePlayer_ = 0;

	// 天球モデル
	std::unique_ptr<Model> modelSkyDome_;
	// 地面モデル
	std::unique_ptr<Model> modelGruond_;

	// プレイヤークラス
	std::unique_ptr<Player> player_;
	// 天球クラス
	std::unique_ptr<SkyDome> skyDome_;
	// 地面クラス
	std::unique_ptr<Ground> ground_;
};
