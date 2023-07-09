#include "Player.h"

void Player::Initialize(Model* model, uint32_t textureHandle) {
	// NULLチェック
	assert(model);

	// 入力情報取得
	input_ = Input::GetInstance();

	// ワールドトランスフォーム初期化
	worldTransform_.Initialize();

	// 引数の値をメンバ変数に代入する
	model_ = model;
	textureHandle_ = textureHandle;
}

void Player::Update() {

	// ゲームパッドの状態を得る変数
	XINPUT_STATE joyState;

	if (Input::GetInstance()->GetJoystickState(0, joyState)) {
		
		// 移動速度
		const float speed = 0.3f;

		// スティックの入力に応じて移動
		Vector3 move = {
		    (float)joyState.Gamepad.sThumbLX / SHRT_MAX, 
			0.0f,
		    (float)joyState.Gamepad.sThumbLY / SHRT_MAX
		};

		// 移動量を正規化、スピードを加算
		move = MyMath::Normalize(move) * speed;

		// カメラの角度から回転行列を生成
		Matrix4x4 rotateMat = MyMath::MakeRotateXYZMatrix(viewProjection_->rotation_);
		// 移動ベクトルをカメラの角度に応じて回転させる
		move = MyMath::Transform(move, rotateMat);

		// 移動
		worldTransform_.translation_ = worldTransform_.translation_ + move;

		// 移動方向にオブジェクトの向きを合わせる
		worldTransform_.rotation_.y = -(atan2(move.z, move.x));

		#ifdef _DEBUG

		// 移動ベクトルのデバック表示
		ImGui::Begin("move");
		ImGui::DragFloat3("move", &move.x, 0.05f);
		ImGui::End();

		// 移動ベクトルのデバック表示
		ImGui::Begin("translation");
		ImGui::DragFloat3("move", &worldTransform_.translation_.x, 0.05f);
		ImGui::End();

#endif // _DEBUG

	}

	// 行列を更新
	worldTransform_.matWorld_ = MyMath::MakeAffineMatrix(
	    worldTransform_.scale_, worldTransform_.rotation_, worldTransform_.translation_);

	// 行列を定数バッファに転送する
	worldTransform_.TransferMatrix();

}

void Player::Draw(ViewProjection viewProjection) {
	// 描画
	model_->Draw(worldTransform_, viewProjection, textureHandle_);
}
