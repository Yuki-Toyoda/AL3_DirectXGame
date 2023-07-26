#include "Enemy.h"

void Enemy::Initialize(const std::vector<Model*>& models) { 
	// 基底クラス初期化
	BaseCharactor::Initialize(models); 

	// ワールドトランスフォーム初期化
	worldTransform_L_Camera_.Initialize();
	worldTransform_R_Camera_.Initialize();

	worldTransform_L_Camera_.translation_.x -= 0.5f;
	worldTransform_L_Camera_.translation_.y += 1.0f;
	worldTransform_L_Camera_.parent_ = &worldTransform_;
	worldTransform_R_Camera_.translation_.x += 0.5f;
	worldTransform_R_Camera_.translation_.y += 1.0f;
	worldTransform_R_Camera_.parent_ = &worldTransform_;


}

void Enemy::Update() {

	// 移動ベクトルを設定
	Vector3 move = {0.0f, 0.0f, 0.2f};

	// 敵を回転させる
	worldTransform_.rotation_.y += 0.05f;
	// 2πを超えたら0に戻す
	worldTransform_.rotation_.y =
	    (float)(std::fmod(worldTransform_.rotation_.y, 2.0f * std::numbers::pi));

	// カメラの角度から回転行列を生成
	Matrix4x4 rotateMat =
	    MyMath::MakeRotateYMatrix(worldTransform_.rotation_.y);
	// 移動ベクトルをカメラの角度に応じて回転させる
	move = MyMath::Transform(move, rotateMat);

	// 向いている方向に移動
	worldTransform_.translation_ = worldTransform_.translation_ + move;

	// カメラを回転させる
	worldTransform_L_Camera_.rotation_.y -= 0.1f;
	worldTransform_R_Camera_.rotation_.y -= 0.1f;

	// 2πを超えたら0に戻す
	worldTransform_L_Camera_.rotation_.y =
	    (float)(std::fmod(worldTransform_L_Camera_.rotation_.y, 2.0f * std::numbers::pi));
	worldTransform_R_Camera_.rotation_.y =
	    (float)(std::fmod(worldTransform_R_Camera_.rotation_.y, 2.0f * std::numbers::pi));

	#ifdef _DEBUG

	// 移動ベクトルのデバック表示
	ImGui::Begin("Enemy");
	ImGui::DragFloat3("translation", &worldTransform_.translation_.x, 0.05f);
	ImGui::DragFloat3("rotation", &worldTransform_.rotation_.x, 0.05f);
	ImGui::End();

#endif // _DEBUG

	// 基底クラス更新処理
	BaseCharactor::Update();

	worldTransform_L_Camera_.UpdateMatrix();
	worldTransform_R_Camera_.UpdateMatrix();

}

void Enemy::Draw(const ViewProjection viewProjection) {
	models_[0]->Draw(worldTransform_, viewProjection);
	models_[1]->Draw(worldTransform_L_Camera_, viewProjection);
	models_[2]->Draw(worldTransform_R_Camera_, viewProjection);
}
