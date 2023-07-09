#include "GameScene.h"
#include "TextureManager.h"
#include <cassert>

GameScene::GameScene() {}

GameScene::~GameScene() {

	// 生成したものの削除
	/*delete model_;
	delete player_;*/

}

void GameScene::Initialize() {

	dxCommon_ = DirectXCommon::GetInstance();
	input_ = Input::GetInstance();
	audio_ = Audio::GetInstance();

	// ワールドトランスフォーム初期化
	worldTransform_.Initialize();
	// ビュープロジェクション初期化
	viewProjection_.Initialize();

	// デバックカメラのインスタンス生成
	debugCamera_ = std::make_unique<DebugCamera>(1280, 720);
	// デバックカメラ無効化
	enableDebugCamera_ = false;

	// 追従カメラのインスタンス生成
	followCamera_ = std::make_unique<FollowCamera>();
	// 追従カメラ初期化
	followCamera_->Initialize();

	// モデル生成
	model_.reset(Model::Create());
	// プレイヤーテクスチャのロード
	texturePlayer_ = TextureManager::Load("PLAYER.png");

	// 天球モデル生成
	modelSkyDome_.reset(Model::CreateFromOBJ("SkyDome", true));
	// 地面モデル生成
	modelGruond_.reset(Model::CreateFromOBJ("Ground", true));

	// プレイヤーのインスタンス生成
	player_ = std::make_unique<Player>();
	player_->Initialize(model_.get(), texturePlayer_);

	// 追従カメラの追従対象をプレイヤーに設定
	followCamera_->SetTarget(player_->GetWorldTransform());

	// プレイヤーにビュープロジェクションをセット
	player_->SetViewProjection(followCamera_->GetViewProjectionAdress());

	// 天球のインスタンス生成
	skyDome_ = std::make_unique<SkyDome>();
	skyDome_->Initialize(modelSkyDome_.get());
	// 地面のインスタンス生成
	ground_ = std::make_unique<Ground>();
	ground_->Initialize(modelGruond_.get());

}

void GameScene::Update() {

	// 更新処理
	player_->Update(); // プレイヤー
	skyDome_->Update(); // 天球
	ground_->Update(); // 地面

	// デバックカメラ有効時
	if (enableDebugCamera_) {
		debugCamera_->Update(); // デバックカメラ

		// ビュープロジェクションをデバックカメラのものに設定する
		viewProjection_.matView = debugCamera_->GetViewProjection().matView;
		viewProjection_.matProjection = debugCamera_->GetViewProjection().matProjection;

		// 行列を定数バッファに転送
		viewProjection_.TransferMatrix();

	} else {
		// viewProjection行列の更新と転送
		followCamera_->Update();
		// ビュープロジェクションを追従カメラのものに設定する
		viewProjection_.matView = followCamera_->GetViewProjection().matView;
		viewProjection_.matProjection = followCamera_->GetViewProjection().matProjection;

		// 行列を定数バッファに転送
		viewProjection_.TransferMatrix();
	}

	// デバックのみ
	#ifdef _DEBUG

	// デバックカメラの有効化と無効化
	ImGui::Begin("camera");
	ImGui::Checkbox("EnableCamera", &enableDebugCamera_);
	ImGui::End();

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

	// 描画
	player_->Draw(viewProjection_); // プレイヤー
	skyDome_->Draw(viewProjection_); // 天球
	ground_->Draw(viewProjection_); // 地面

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
