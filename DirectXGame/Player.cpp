#include "Player.h"
#include "GlobalVariables.h"

void Player::Initialize(const std::vector<Model*>& models) {

	// 基底クラス初期化
	BaseCharactor::Initialize(models);

	// 入力情報取得
	input_ = Input::GetInstance();

	// ワールドトランスフォーム初期化
	worldTransform_.Initialize();
	worldTransformBody_.Initialize();
	worldTransformHead_.Initialize();
	worldTransformL_Arm_.Initialize();
	worldTransformR_Arm_.Initialize();
	worldTransformWeapon_.Initialize();

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
	worldTransformWeapon_.translation_.x = -0.35f;
	worldTransformWeapon_.translation_.y = 0.15f;
	worldTransformWeapon_.rotation_.x = (float)std::numbers::pi;
	// 武器をプレイヤーに追従させる
	worldTransformWeapon_.parent_ = &worldTransformR_Arm_;

	// 調整項目クラスのインスタンス取得
	GlobalVariables* globalVariables = GlobalVariables::GetInstance();
	// グループ名設定
	const char* groupName = "Player";
	// 指定した名前でグループ追加
	globalVariables->CreateGroup(groupName);

	// メンバ変数の調整項目をグローバル変数に追加

	globalVariables->AddItem(groupName, "Test", 0.0f);

	globalVariables->AddItem(groupName, "HeadTranslation", worldTransformHead_.translation_);
	globalVariables->AddItem(groupName, "HeadRotation", worldTransformHead_.rotation_);
	globalVariables->AddItem(groupName, "L_ArmTranslation", worldTransformL_Arm_.translation_);
	globalVariables->AddItem(groupName, "R_ArmTranslation", worldTransformR_Arm_.translation_);
	globalVariables->AddItem(groupName, "floatingCycle", floatingCycle_);
	globalVariables->AddItem(groupName, "floatingAmpritude", floatingAmpritude_);
	globalVariables->AddItem(groupName, "swingOverTime", swingOverTime_);
	globalVariables->AddItem(groupName, "attackTime", attackTime_);
	globalVariables->AddItem(groupName, "attackForward", attackForward_);
	globalVariables->AddItem(groupName, "attackWaitTime", attackWaitTime_);
}

void Player::Update() {

	// ふるまいを変更するリクエストがあればTrue
	if (behaviorRequest_) {
		// ふるまい変更
		behavior_ = behaviorRequest_.value();
		// 各振る舞いごとの初期化を実行
		switch (behavior_) {
		case Behavior::kRoot:
			// 通常行動初期化
			BehaviorRootInitialize();
			break;
		case Behavior::kAttack:
			// 攻撃行動初期化
			BehaviorAttackInitialize();
			break;
		}
		// ふるまいリクエストをリセット
		behaviorRequest_ = std::nullopt;
	}

	// 各振る舞いごとの初期化を実行
	switch (behavior_) {
	case Behavior::kRoot:
		// 通常行動初期化
		BehaviorRootUpdate();
		// 調整項目を反映
		ApplyGlobalVariables();
		break;
	case Behavior::kAttack:
		// 攻撃行動初期化
		BehaviorAttackUpdate();
		break;
	}

	// 行列を更新
	worldTransform_.UpdateMatrix();
	worldTransformBody_.UpdateMatrix();
	worldTransformHead_.UpdateMatrix();
	worldTransformL_Arm_.UpdateMatrix();
	worldTransformR_Arm_.UpdateMatrix();
	worldTransformWeapon_.UpdateMatrix();

}

void Player::Draw(ViewProjection viewProjection) { 
	models_[0]->Draw(worldTransformBody_, viewProjection);
	models_[1]->Draw(worldTransformHead_, viewProjection);
	models_[2]->Draw(worldTransformL_Arm_, viewProjection);
	models_[3]->Draw(worldTransformR_Arm_, viewProjection);
	models_[4]->Draw(worldTransformWeapon_, viewProjection);
}

void Player::ApplyGlobalVariables() {
	// 調整項目クラスのインスタンス取得
	GlobalVariables* globalVariables = GlobalVariables::GetInstance();
	// グループ名の設定
	const char* groupName = "Player";

	// メンバ変数の調整項目をグローバル変数に追加
	worldTransformHead_.translation_ = globalVariables->GetVector3Value(groupName, "HeadTranslation");
	worldTransformHead_.rotation_ = globalVariables->GetVector3Value(groupName, "HeadRotation");
	worldTransformL_Arm_.translation_ = globalVariables->GetVector3Value(groupName, "L_ArmTranslation");
	worldTransformR_Arm_.translation_ = globalVariables->GetVector3Value(groupName, "R_ArmTranslation");
	floatingCycle_ = globalVariables->GetIntValue(groupName, "floatingCycle");
	floatingAmpritude_ = globalVariables->GetFloatValue(groupName, "floatingAmpritude");
	swingOverTime_ = globalVariables->GetFloatValue(groupName, "swingOverTime");
	attackTime_ = globalVariables->GetFloatValue(groupName, "attackTime");
	attackForward_ = globalVariables->GetFloatValue(groupName, "attackForward");
	attackWaitTime_ = globalVariables->GetFloatValue(groupName, "attackWaitTime");

}

void Player::BehaviorRootInitialize() {
	// 浮遊ギミック初期化
	InitializeFloatingGimmick();
	// 腕振りギミック初期化
	InitializeArmSwingGimmick();
}

void Player::BehaviorRootUpdate() {
	// ゲームパッドの状態を得る変数
	XINPUT_STATE joyState;

	if (Input::GetInstance()->GetJoystickState(0, joyState)) {

		// 移動速度
		const float speed = 0.3f;

		// スティックの入力に応じて移動
		Vector3 move = {
		    (float)joyState.Gamepad.sThumbLX / SHRT_MAX, 0.0f,
		    (float)joyState.Gamepad.sThumbLY / SHRT_MAX};

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

		// リクエスト状態が攻撃行動でなければ
		if (behaviorRequest_ != kAttack) {
			// Ｘボタンが入力されたら
			if (joyState.Gamepad.wButtons & XINPUT_GAMEPAD_X) {
				// 次の行動を攻撃行動に
				behaviorRequest_ = kAttack;
			}
		}
	}

	// 武器座標をありえないほど遠くに
	worldTransformWeapon_.translation_.x = -100000.0f;
	worldTransformWeapon_.translation_.y = -100000.0f;
	// 浮遊ギミック更新
	UpdateFloatingGimmick();
	// 腕振りギミック更新
	UpdateArmSwingGimmick();
}

void Player::BehaviorAttackInitialize() {
	// 攻撃状態初期化
	attackState_ = SwingOver;
	// t初期化
	t_ = 0.0f;

	// 武器を腕の方に持ってくる
	worldTransformWeapon_.translation_.x = -0.35f;
	worldTransformWeapon_.translation_.y = 0.15f;

}

void Player::BehaviorAttackUpdate() {
	// 現在の攻撃状態によって遷移
	switch (attackState_) {
	case Player::SwingOver:
		// イージングによって振りかぶる動作を行う
		if (t_ <= swingOverTime_) {
			// イージングで腕の角度を調整
			worldTransformR_Arm_.rotation_.x =
			    MyMath::EaseOutF(t_, swingOverStartAngle_, swingOverEndAngle_, swingOverTime_);
			worldTransformL_Arm_.rotation_.x =
			    MyMath::EaseOutF(t_, swingOverStartAngle_, swingOverEndAngle_, swingOverTime_);
			// t加算
			t_ += 1.0f / 60.0f;
		} else {
			// 演出用tリセット
			t_ = 0.0f;

			// 攻撃開始地点を設定
			attackStartPos_ = worldTransform_.translation_;
			// 攻撃終端地点を設定
			// スティックの入力に応じて移動
			Vector3 move = {
			    0.0f, 0.0f, 1.0f};

			// 移動量を正規化、スピードを加算
			move = MyMath::Normalize(move) * attackForward_;

			// カメラの角度から回転行列を生成
			Matrix4x4 rotateMat = MyMath::MakeRotateXYZMatrix(worldTransform_.rotation_);
			// 移動ベクトルをカメラの角度に応じて回転させる
			move = MyMath::Transform(move, rotateMat);

			// 攻撃終端地点を設定
			attackEndPos_ = attackStartPos_ + move;

			// 次の段階へ
			attackState_++;
		}
		break;
	case Player::Attack:
		// イージングによって攻撃動作を行う
		if (t_ <= attackTime_) {
			// イージングで腕の角度を調整
			worldTransformR_Arm_.rotation_.x =
			    MyMath::EaseOutF(t_, swingOverEndAngle_, attackEndAngle_, attackTime_);
			worldTransformL_Arm_.rotation_.x =
			    MyMath::EaseOutF(t_, swingOverEndAngle_, attackEndAngle_, attackTime_);

			// イージングでプレイヤーを移動
			worldTransform_.translation_.x =
			    MyMath::EaseOutF(t_, attackStartPos_.x, attackEndPos_.x, attackTime_);
			worldTransform_.translation_.y =
			    MyMath::EaseOutF(t_, attackStartPos_.y, attackEndPos_.y, attackTime_);
			worldTransform_.translation_.z =
			    MyMath::EaseOutF(t_, attackStartPos_.z, attackEndPos_.z, attackTime_);

			// t加算
			t_ += 1.0f / 60.0f;
		} else {
			// 演出用tリセット
			t_ = 0.0f;
			// 次の段階へ
			attackState_++;
		}
		break;
	case Player::Wait:
		// 待機
		if (t_ <= attackWaitTime_) {
			// t加算
			t_ += 1.0f / 60.0f;
		} else {
			// 通常行動に戻すように命令
			behaviorRequest_ = kRoot;
		}
		// 演出終了
		break;
	default:
		break;
	}
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

