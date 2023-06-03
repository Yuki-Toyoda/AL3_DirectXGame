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

	/// <summary>
	/// 全ての当たり判定を検証する関数
	/// </summary>
	void CheckAllCollisions();

	/// <summary>
	/// 敵弾を追加する関数
	/// </summary>
	/// <param name="enemyBullet">敵弾</param>
	void AddPlayerBullet(PlayerBullet* playerBullet);

	/// <summary>
	/// 敵弾を追加する関数
	/// </summary>
	/// <param name="enemyBullet">敵弾</param>
	void AddEnemyBullet(EnemyBullet* enemyBullet);

	/// <summary>
	/// 敵をスポーンさせる関数
	/// </summary>
	void SpawnEnemy();

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
	// プレイヤー弾
	std::list<PlayerBullet*> playerBullets_;

	// 敵のリスト
	std::list<Enemy*> enemies_;
	// 敵弾
	std::list<EnemyBullet*> enemyBullets_;

	// スポーン間隔
	static const int32_t kSpawnTime = 60;
	// 敵のスポーンタイマー
	int32_t spawnTimer_ = kSpawnTime;

	// 天球
	Model* modelSkyDome_ = nullptr;

	// スカイドーム
	SkyDome* skyDome_ = nullptr;

};