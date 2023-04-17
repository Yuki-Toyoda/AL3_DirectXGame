#include "GameScene.h"
#include "TextureManager.h"
#include "ImGuiManager.h"
#include "PrimitiveDrawer.h"
#include "AxisIndicator.h"
#include <cassert>

GameScene::GameScene() {}

GameScene::~GameScene() {

	// スプライト削除
	delete sprite_;

	// モデル削除
	delete model_;

	// デバックカメラ削除
	delete debugCamera_;

}

void GameScene::Initialize() {

	dxCommon_ = DirectXCommon::GetInstance();
	input_ = Input::GetInstance();
	audio_ = Audio::GetInstance();

	// フォルダ指定してテクスチャの読み込み
	textureHandle_ = TextureManager::Load("sample.png");

	// スプライトの生成
	sprite_ = Sprite::Create(textureHandle_, {100, 50});

	// 3Dモデルの読み込み
	model_ = Model::Create();

	// ワールドランスフォームの初期化
	worldTransform_.Initialize();
	// ビュープロジェクションの初期化
	viewProjection_.Initialize();

	// サウンドデータの読み込み
	soundDataHundle_ = audio_->LoadWave("mokugyo.wav");
	// 音声の再生
	audio_->PlayWave(soundDataHundle_);

	// 音声再生
	voiceHundle_ = audio_->PlayWave(soundDataHundle_, true);

	// デバックカメラ生成
	debugCamera_ = new DebugCamera(1280, 720);

	// ライン描画が参照するビュープロジェクションを指定する(アドレス渡し)
	PrimitiveDrawer::GetInstance()->SetViewProjection(&debugCamera_->GetViewProjection());

	// 軸方向表示を有効にする
	AxisIndicator::GetInstance()->SetVisible(true);
	// 軸方向が参照するビュープロジェクションを指定する
	AxisIndicator::GetInstance()->SetTargetViewProjection(&debugCamera_->GetViewProjection());

}

void GameScene::Update() {

	// スプライトの座標を取得する
	Vector2 spritePosition = sprite_->GetPosition();

	// 座標を{ 2, 1 }分移動させ続ける
	spritePosition.x += 2.0f;
	spritePosition.y += 1.0f;

	// 移動した座標をスプライトに反映する
	sprite_->SetPosition(spritePosition);

	if (input_->TriggerKey(DIK_SPACE)) {
		audio_->StopWave(voiceHundle_);
	}

	// デバックテキストの表示
	ImGui::Text("Toyoda Yuki %d.%d.%d", 2023, 04, 17);

	// ウィンドウ作成
	ImGui::Begin("Debug1");
	// デバックテキストの表示
	ImGui::Text("Toyoda Yuki %d.%d.%d", 2023, 04, 17);

	// float3入力ボックス
	ImGui::InputFloat3("InputFloat3", inputFloat3);
	// float3スライダー
	ImGui::SliderFloat3("SliderFloat3", inputFloat3, 0.0f, 1.0f);

	ImGui::End();

	// デモウィンドウ表示
	ImGui::ShowDemoWindow();

	// デバックカメラ更新
	debugCamera_->Update();

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

	// スプライト描画
	sprite_->Draw();

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

	// 3Dモデルの描画
	model_->Draw(worldTransform_, debugCamera_->GetViewProjection(), textureHandle_);

	// ラインを描画する
	PrimitiveDrawer::GetInstance()->DrawLine3d({0, 0, 0}, {0, 10, 0}, {1.0f, 0.0f, 0.0f, 1.0f});

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
