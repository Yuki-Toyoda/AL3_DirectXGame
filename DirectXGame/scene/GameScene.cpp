#include "GameScene.h"
#include "AxisIndicator.h"
#include "ImGuiManager.h"
#include "PrimitiveDrawer.h"
#include "TextureManager.h"
#include <cassert>

GameScene::GameScene() {}

GameScene::~GameScene() {

	// 3Dモデルの削除
	delete model;
	delete modelSkyDome_;

	// カメラの削除
	delete debugCamera_;

	// プレイヤーの解放
	delete player_;

	// 敵の解放
	for (Enemy* enemy : enemies_) {
		delete enemy;
	}

	// プレイヤー弾の解放
	for (PlayerBullet* bullet : playerBullets_) {
		delete bullet;
	}

	// 敵弾の解放
	for (EnemyBullet* bullet : enemyBullets_) {
		delete bullet;
	}

	// 天球の削除
	delete skyDome_;

}

void GameScene::Initialize() {

	dxCommon_ = DirectXCommon::GetInstance();
	input_ = Input::GetInstance();
	audio_ = Audio::GetInstance();

	// テクスチャ読み込み
	textureHandle_ = TextureManager::Load("sample.png");

	// 3Dモデルの読み込み
	model = Model::Create();

	// ビュープロジェクションの初期化
	viewProjection_.Initialize();

	// 軸方向表示を有効にする
	AxisIndicator::GetInstance()->SetVisible(true);
	// 軸方向が参照するビュープロジェクションを指定する
	AxisIndicator::GetInstance()->SetTargetViewProjection(&viewProjection_);

	// セットランド
	MyMath::SetSrand();

	// デバックカメラの生成
	debugCamera_ = new DebugCamera(1280, 720);

	// レールカメラの生成
	railCamera = new RailCamera();
	railCamera->Initialize({0.0f, 0.0f, -100.0f}, {0.0f, 0.0f, 0.0f});

	// プレイヤーの生成
	player_ = new Player();
	// プレイヤーの初期化
	player_->Initialize(model, textureHandle_, this);
	// 親子関係を設定
	player_->SetParent(&railCamera->GetWorldMatrix());

	// 天球モデルの生成
	modelSkyDome_ = Model::CreateFromOBJ("SkyDome", true);

	// 天球の初期化
	skyDome_ = new SkyDome();
	skyDome_->Initialize(modelSkyDome_);

}

void GameScene::Update() {

	// レールカメラ更新
	railCamera->Update();

	// プレイヤーの更新
	player_->Update();

	// プレイヤー弾の更新処理
	for (PlayerBullet* bullet : playerBullets_) {
		bullet->Update();
	}

	// 敵の更新
	for (Enemy* enemy : enemies_) {
		enemy->Update();
	}

	// 敵のスポーン処理
	if (spawnTimer_ <= 0) {

		SpawnEnemy();

		spawnTimer_ = kSpawnTime;


	} else {
		// スポーンタイマーカウントダウン
		spawnTimer_--;
	}

	// 敵弾の更新処理
	for (EnemyBullet* bullet : enemyBullets_) {
		bullet->Update();
	}

	// デスフラグが立った敵を削除
	enemies_.remove_if([](Enemy* enemy) {
		if (enemy->GetIsDead()) {
			delete enemy;
			return true;
		}
		return false;
	});

	// デスフラグの立った弾を削除
	enemyBullets_.remove_if([](EnemyBullet* bullet) {
		if (bullet->IsDead()) {
			delete bullet;
			return true;
		}
		return false;
	});

	// デスフラグの立ったプレイヤー弾を削除
	playerBullets_.remove_if([](PlayerBullet* bullet) {
		if (bullet->IsDead()) {
			delete bullet;
			return true;
		}
		return false;
	});

	// 当たり判定の検証
	CheckAllCollisions();

	// 天球の更新
	skyDome_->Update();

	// カメラの処理
	if (isDebugCameraActive_) {
		debugCamera_->Update();

		viewProjection_.matView = debugCamera_->GetViewProjection().matView;
		viewProjection_.matProjection = debugCamera_->GetViewProjection().matProjection;

		viewProjection_.TransferMatrix();

	} else {

		// ビュープロジェクションをレールカメラにする
		viewProjection_.matView = railCamera->GetViewProjection().matView;
		viewProjection_.matProjection = railCamera->GetViewProjection().matProjection;
		viewProjection_.TransferMatrix();
	}

#ifdef _DEBUG

	if (input_->TriggerKey(DIK_E)) {
		if (isDebugCameraActive_ == false) {
			isDebugCameraActive_ = true;
		} else {
			isDebugCameraActive_ = false;
		}
	}

#endif // _DEBUG
}

void GameScene::Draw() {

	// コマンドリストの取得
	ID3D12GraphicsCommandList* commandList = dxCommon_->GetCommandList();

#pragma region 背景スプライト描画
	// 背景スプライト描画前処理
	Sprite::PreDraw(commandList);

	/// <summary>
	/// ここに背景スプライトの描画処理を追加できる
	/// </summary>

	// スプライト描画後処理
	Sprite::PostDraw();
	// 深度バッファクリア
	dxCommon_->ClearDepthBuffer();
#pragma endregion

#pragma region 3Dオブジェクト描画
	// 3Dオブジェクト描画前処理
	Model::PreDraw(commandList);

	/// <summary>
	/// ここに3Dオブジェクトの描画処理を追加できる
	/// </summary>

	// 描画処理
	player_->Draw(viewProjection_);
	// プレイヤー弾描画
	for (PlayerBullet* bullet : playerBullets_) {
		bullet->Draw(viewProjection_);
	}

	// 敵描画
	for (Enemy* enemy : enemies_) {
		enemy->Draw(viewProjection_);
	}
	// 敵弾描画
	for (EnemyBullet* bullet : enemyBullets_) {
		bullet->Draw(viewProjection_);
	}
	skyDome_->Draw(viewProjection_);

	// 3Dオブジェクト描画後処理
	Model::PostDraw();
#pragma endregion

#pragma region 前景スプライト描画
	// 前景スプライト描画前処理
	Sprite::PreDraw(commandList);

	/// <summary>
	/// ここに前景スプライトの描画処理を追加できる
	/// </summary>

	// スプライト描画後処理
	Sprite::PostDraw();

#pragma endregion
}

/// <summary>
/// 全ての当たり判定を検証する関数
/// </summary>
void GameScene::CheckAllCollisions() {

	// ポジション格納用
	Vector3 posA, posB;

	// プレイヤー座標の取得
	posA = player_->GetWorldPosition();

	// 敵の弾とプレイヤーの当たり判定を検証
	for (EnemyBullet* bullet : enemyBullets_) {
	
		// ポジションを取得
		posB = bullet->GetWorldPosition();

		// 敵弾とプレイヤーの距離を求める
		float distance;
		distance = float(std::pow((posB.x - posA.x), 2) + std::pow((posB.y - posA.y), 2) + std::pow((posB.z - posA.z), 2));

		// 球の判定同士が衝突していれば
		if (distance <= 10 + 10) {
			// プレイヤーの衝突関数を呼び出す
			player_->OnCollision();
			// 敵の衝突関数を呼び出す
			bullet->OnCollision();
		}

	}

	// 全ての敵と自弾の当たり判定を検証
	for (Enemy* enemy : enemies_) {

		// 敵座標の取得
		posA = enemy->GetWorldPosition();

		for (PlayerBullet* bullet : playerBullets_) {
		
			// プレイヤー弾の取得
			posB = bullet->GetWorldPosition();

			// 自弾と敵の当たり判定
			float distance;
			distance = float(std::pow((posB.x - posA.x), 2) + std::pow((posB.y - posA.y), 2) + std::pow((posB.z - posA.z), 2));

			// 球の判定同士が衝突していれば
			if (distance <= 10 + 10) {
				// プレイヤーの衝突関数を呼び出す
				enemy->OnCollision();
				// 敵の衝突関数を呼び出す
				bullet->OnCollision();
			}

		}
	}

}

/// <summary>
/// 敵弾を追加する関数
/// </summary>
/// <param name="enemyBullet">敵弾</param>
void GameScene::AddPlayerBullet(PlayerBullet* playerBullet) {
	// リストに登録する
	playerBullets_.push_back(playerBullet);
}

/// <summary>
/// 敵弾を追加する関数
/// </summary>
/// <param name="enemyBullet">敵弾</param>
void GameScene::AddEnemyBullet(EnemyBullet* enemyBullet) {
	// リストに登録する
	enemyBullets_.push_back(enemyBullet);
}

/// <summary>
/// 敵をスポーンさせる関数
/// </summary>
void GameScene::SpawnEnemy() {

	// 敵を作る
	Enemy* newEnemy = new Enemy();
	// 作った敵を初期化
	newEnemy->Initialize(
	    model, this, {MyMath::RandomF(-10.0f, 10.0f, 0), MyMath::RandomF(-10.0f, 10.0f, 0), 100.0f},
	    {0.0f, 0.0f, -0.05f}, player_);
	// 敵をリストに登録
	enemies_.push_back(newEnemy);

}