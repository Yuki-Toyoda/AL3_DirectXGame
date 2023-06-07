#include "RailCamera.h"

/// <summary>
/// 初期化処理
/// </summary>
/// <param name="translation">ワールド座標</param>
/// <param name="rotate">回転角</param>
void RailCamera::Initialize(Vector3 translation_, Vector3 rotate) {
	// ワールド座標の初期化
	//worldTransform_.Initialize();
	// 引数の値をメンバ変数に代入
	worldTransform_.translation_ = translation_;
	worldTransform_.rotation_ = rotate;

	// ビュープロジェクションの初期化
	viewProjection_.Initialize();

}

/// <summary>
/// 更新処理
/// </summary>
void RailCamera::Update() {

	// ワールド座標を加算する
	worldTransform_.translation_.z += 0.01f;

	// スケール、回転、平行移動を合成して行列を計算する
	worldTransform_.matWorld_ = MyMath::Vector3MakeAffineMatrix(worldTransform_.scale_, worldTransform_.rotation_, worldTransform_.translation_);

	viewProjection_.matView = MyMath::Inverse(worldTransform_.matWorld_);

	// デバックウィンドウ表示
	ImGui::Begin("Camera");

	ImGui::SliderFloat3("translate", &worldTransform_.translation_.x, -100.0f, 100.0f);
	ImGui::SliderFloat3("rotation", &worldTransform_.rotation_.x, 0.0f, 6.0f);

	ImGui::End();

}
