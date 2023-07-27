#pragma once

#include <memory>
#include <numbers>

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
#include "Enemy.h"
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

	// プレイヤーモデル
	std::unique_ptr<Model> modelFighterBody_; // 体
	std::unique_ptr<Model> modelFighterHead_; // 頭
	std::unique_ptr<Model> modelFighterL_Arm_; // 左腕
	std::unique_ptr<Model> modelFighterR_Arm_; // 右腕

	// プレイヤー武器モデル
	std::unique_ptr<Model> modelFighterWeapon_; // 武器

	// 天球モデル
	std::unique_ptr<Model> modelSkyDome_;
	// 地面モデル
	std::unique_ptr<Model> modelGruond_;

	// 敵モデル
	std::unique_ptr<Model> modelEnemyBody_; // 本体
	std::unique_ptr<Model> modelEnemy_L_Camera_; // 左カメラ
	std::unique_ptr<Model> modelEnemy_R_Camera_; // 右カメラ

	// プレイヤークラス
	std::unique_ptr<Player> player_;
	// 敵
	std::unique_ptr<Enemy> enemy_;
	// 天球クラス
	std::unique_ptr<SkyDome> skyDome_;
	// 地面クラス
	std::unique_ptr<Ground> ground_;
};
