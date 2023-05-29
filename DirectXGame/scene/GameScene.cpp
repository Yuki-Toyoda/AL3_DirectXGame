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
	delete enemy_;

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

	// デバックカメラの生成
	debugCamera_ = new DebugCamera(1280, 720);

	// レールカメラの生成
	railCamera = new RailCamera();
	railCamera->Initialize({0.0f, 0.0f, -100.0f}, {0.0f, 0.0f, 0.0f});

	// プレイヤーの生成
	player_ = new Player();
	// プレイヤーの初期化
	player_->Initialize(model, textureHandle_);
	// 親子関係を設定
	player_->SetParent(&railCamera->GetWorldMatrix());

	// 敵の生成
	enemy_ = new Enemy();
	// 敵の初期化
	enemy_->Initialize(model, {0.0f, 1.0f, 50.0f}, {0.0f, 0.0f, -0.5f});

	// 敵キャラに時キャラのポインタを渡す
	enemy_->SetPlayer(player_);

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

	// 敵の更新
	enemy_->Update();

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
	enemy_->Draw(viewProjection_);
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