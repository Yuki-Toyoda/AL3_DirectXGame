#include "FollowCamera.h"

void FollowCamera::Initialize() {
	// ビュープロジェクションの初期化
	viewProjection_.Initialize();
}

void FollowCamera::Update() {

	// ゲームパッドの状態を得る変数
	XINPUT_STATE joyState;

	if (Input::GetInstance()->GetJoystickState(0, joyState)) {

		// 旋回速度
		const float speed = 0.05f;

		// スティックの横移動に対してカメラを旋回
		viewProjection_.rotation_.y += (float)joyState.Gamepad.sThumbRX / SHRT_MAX * speed;

#ifdef _DEBUG

		

#endif // _DEBUG
	}

	// 追従対象が存在すれば
	if (target_) {
		// 追従対象からカメラまでのオフセットを設定
		Vector3 offset = {0.0f, 2.0f, -10.0f};

		// カメラの角度から回転行列を生成
		Matrix4x4 rotateMat = MyMath::MakeRotateXYZMatrix(viewProjection_.rotation_);

		// オフセットをカメラの回転に合わせて回転させる
		offset = MyMath::Transform(offset, rotateMat);

		// 座標コピーからオフセット分ずらす
		viewProjection_.translation_ = target_->translation_ + offset;
	}

	// ビュープロジェクション行列の
	viewProjection_.UpdateMatrix(); // 更新
	viewProjection_.TransferMatrix(); // 転送
}
