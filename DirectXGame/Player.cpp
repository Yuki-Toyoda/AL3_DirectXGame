#include "Player.h"

void Player::Initialize(Model* modelBody, Model* modelHead, Model* modelL_arm, Model* modelR_arm) {

	// NULLチェック
	assert(modelBody);
	assert(modelHead);
	assert(modelL_arm);
	assert(modelR_arm);

	// 入力情報取得
	input_ = Input::GetInstance();

	// ワールドトランスフォーム初期化
	worldTransform_.Initialize();
	worldTransformBody_.Initialize();
	worldTransformHead_.Initialize();
	worldTransformL_Arm_.Initialize();
	worldTransformR_Arm_.Initialize();

	// 引数の値をメンバ変数に代入
	modelFighterBody_ = (modelBody);
	modelFighterHead_ = (modelHead);
	modelFighterL_Arm_ = (modelL_arm);
	modelFighterR_Arm_ = (modelR_arm);

	// 浮遊ギミック初期化
	InitializeFloatingGimmick();
	// 腕振りギミック初期化
	InitializeArmSwingGimmick();

	// 体をプレイヤー座標に追従させる
	worldTransformBody_.parent_ = &worldTransform_;
	worldTransformHead_.translation_.y += 1.5f;
	worldTransformHead_.parent_ = &worldTransformBody_;
	worldTransformL_Arm_.translation_.x -= 0.35f;
	worldTransformL_Arm_.translation_.y += 1.25f;
	worldTransformL_Arm_.parent_ = &worldTransformBody_;
	worldTransformR_Arm_.translation_.x += 0.35f;
	worldTransformR_Arm_.translation_.y += 1.25f;
	worldTransformR_Arm_.parent_ = &worldTransformBody_;
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
		worldTransform_.rotation_.y = atan2(move.x, move.z);

		#ifdef _DEBUG

		// 移動ベクトルのデバック表示
		ImGui::Begin("move");
		ImGui::DragFloat3("move", &move.x, 0.05f);
		ImGui::End();

		// 移動ベクトルのデバック表示
		ImGui::Begin("translation");
		ImGui::SliderFloat3("translation", &worldTransform_.translation_.x, -30.0f, 30.0f);
		ImGui::DragFloat3("rotation", &worldTransform_.rotation_.x, 0.05f);
		ImGui::DragFloat3("Bodytranslation", &worldTransformBody_.translation_.x, 0.05f);
		ImGui::DragFloat3("Bodyrotation", &worldTransformBody_.rotation_.x, 0.05f);
		ImGui::SliderInt("floatingCycle", reinterpret_cast<int*>(&floatingCycle_), 10, 240);
		ImGui::SliderFloat("floatingAmpritude", &floatingAmpritude_, 0.005f, 1.0f);
		ImGui::SliderInt("armSwingCycle", reinterpret_cast<int*>(&armSwingCycle_), 10, 240);
		ImGui::End();

#endif // _DEBUG

	}

	// 浮遊ギミック更新
	UpdateFloatingGimmick();
	// 腕振りギミック更新
	UpdateArmSwingGimmick();

	// 行列を更新
	worldTransform_.UpdateMatrix();
	worldTransformBody_.UpdateMatrix();
	worldTransformHead_.UpdateMatrix();
	worldTransformL_Arm_.UpdateMatrix();
	worldTransformR_Arm_.UpdateMatrix();

}

void Player::Draw(ViewProjection viewProjection) {
	// 描画
	modelFighterBody_->Draw(worldTransformBody_, viewProjection); // 体
	modelFighterHead_->Draw(worldTransformHead_, viewProjection); // 頭
	modelFighterL_Arm_->Draw(worldTransformL_Arm_, viewProjection); // 左腕
	modelFighterR_Arm_->Draw(worldTransformR_Arm_, viewProjection); // 右腕
}

void Player::InitializeFloatingGimmick() {

	// 浮遊移動サイクル
	floatingCycle_ = 60;
	// 浮遊の振幅
	floatingAmpritude_ = 0.01f;
	// 変数初期化
	floatingParameter_ = 0.0f;

}

void Player::UpdateFloatingGimmick() {

	// 1フレームごとの加算値
	const float step = (float)(2.0f * std::numbers::pi / floatingCycle_);

	// パラメータを1ステップ分加算する
	floatingParameter_ += step;
	// 2πを超えたら0に戻す
	floatingParameter_ = (float)(std::fmod(floatingParameter_, 2.0f * std::numbers::pi));

	// 浮遊を座標に反映させる
	worldTransformBody_.translation_.y = std::sin(floatingParameter_) * floatingAmpritude_;

}

void Player::InitializeArmSwingGimmick() {
	// 腕振りサイクル
	armSwingCycle_ = 60;
	// 腕振りギミック用変数
	armSwingParameter_ = 0.0f;
}

void Player::UpdateArmSwingGimmick() {

	// 1フレームごとの加算値
	const float step = (float)(2.0f * std::numbers::pi / armSwingCycle_);

	// パラメータを1ステップ分加算する
	armSwingParameter_ += step;
	// 2πを超えたら0に戻す
	armSwingParameter_ = (float)(std::fmod(armSwingParameter_, 2.0f * std::numbers::pi));

	// 浮遊を座標に反映させる
	worldTransformL_Arm_.rotation_.x = std::cos(armSwingParameter_) / 2.0f;
	worldTransformR_Arm_.rotation_.x = std::cos(armSwingParameter_) / 2.0f;

}

