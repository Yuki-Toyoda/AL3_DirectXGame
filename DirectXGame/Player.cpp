#include "Player.h"
#include "GameScene.h"

/// <summary>
/// コンストラクタ
/// </summary>
Player::Player() {
	
}

/// <summary>
/// デストラクタ
/// </summary>
Player::~Player() { 
	// スプライト解放
	delete sprite2DReticle_; 
}

/// <summary>
/// 初期化処理
/// </summary>
/// <param name="model">3Dモデル</param>
/// <param name="textureHandle">テクスチャハンドル</param>
/// <param name="gameScene">ゲームシーン</param>
void Player::Initialize(Model* model, uint32_t textureHandle, GameScene* gameScene) {

	// シングルトンインスタンスを取得
	input_ = Input::GetInstance();

	// NULLポインタチェック
	assert(model);

	// 引数として受け取ったデータをメンバ変数に記録
	// モデル
	model_ = model;
	// テクスチャ
	textureHandle_ = textureHandle;

	// ワールド座標の初期化
	worldTransform_.Initialize();
	worldTransform_.translation_.z = 50.0f;
	worldTransform3DReticle_.Initialize();

	// 移動ベクトルの初期化
	move = {0.0f, 0.0f, 0.0f};

	// ゲームシーンをセットする
	SetGameScene(gameScene);

	// 射撃間隔初期化
	fireTimer = kFireInterval;

	// レティクル用テクスチャ読み込み
	uint32_t textureReticle = TextureManager::Load("reticle.png");
	sprite2DReticle_ = Sprite::Create(
	    textureReticle, {float(WinApp::kWindowWidth / 2), float(WinApp::kWindowHeight / 2)}, {1.0f, 1.0f, 1.0f, 1.0f}, {0.5f, 0.5f});
	sprite2DReticle_->SetSize({100.0f, 100.0f});

	// コントローラー操作を有効にする
	enableController = true;

}

/// <summary>
/// 更新処理
/// </summary>
/// <param name="viewProjection">ビュープロジェクション</param>
void Player::Update(ViewProjection& viewProjection) {

	// 行列を定数バッファに転送
	worldTransform_.TransferMatrix();
	worldTransform3DReticle_.TransferMatrix();

	// 移動処理呼び出し
	Move();

	// 行列の更新
	worldTransform_.UpdateMatrix();

	// レティクル移動処理呼び出し
	MoveReticle(viewProjection);
	// 行列の更新
	worldTransform3DReticle_.UpdateMatrix();

	// 攻撃処理
	Attack();

	// デバッグ描画
	ImGui::Begin("Player");
	ImGui::SliderFloat3("translate", &worldTransform_.translation_.x, -50.0f, 50.0f);
	ImGui::End();

	ImGui::Begin("enableController");
	ImGui::Checkbox("enable", &enableController);
	ImGui::End();

}

/// <summary>
/// 描画処理
/// </summary>
/// <param name="viewProjection">ビュープロジェクション</param>
void Player::Draw(ViewProjection& viewProjection) {
	// プレイヤーモデル描画
	model_->Draw(worldTransform_, viewProjection, textureHandle_);
	// レティクル描画
	//model_->Draw(worldTransform3DReticle_, viewProjection, textureHandle_);
}

void Player::DrawUI() {
	// スプライト描画
	sprite2DReticle_->Draw();
}

/// <summary>
/// 移動処理
/// </summary>
void Player::Move() {

	/// プレイヤーの移動処理
	// 移動ベクトル
	move = {0.0f, 0.0f, 0.0f};

	// 移動スピード
	const float kSpeed = 0.2f;

	// コントローラーが有効なら
	if (enableController) {
	
		XINPUT_STATE joyState;

		// ジョイスティックによって移動させる
		if (Input::GetInstance()->GetJoystickState(0, joyState)) {
		
			move.x += (float)joyState.Gamepad.sThumbLX / SHRT_MAX * kSpeed;
			move.y += (float)joyState.Gamepad.sThumbLY / SHRT_MAX * kSpeed;

		}


	} else {
	
		// 押した方向で移動ベクトルを変更する(左右)
		if (input_->PushKey(DIK_LEFT)) {
			move.x -= kSpeed;
		} else if (input_->PushKey(DIK_RIGHT)) {
			move.x += kSpeed;
		}

		// 押した方向で移動ベクトルを変更する(上下)
		if (input_->PushKey(DIK_UP)) {
			move.y += kSpeed;
		} else if (input_->PushKey(DIK_DOWN)) {
			move.y -= kSpeed;
		}

		// プレイヤーの旋回処理
		if (input_->PushKey(DIK_A)) {
			worldTransform_.rotation_.y -= kRotSpeed;
		} else if (input_->PushKey(DIK_D)) {
			worldTransform_.rotation_.y += kRotSpeed;
		}

	}

	// 座標移動(ベクトルの加算)
	worldTransform_.translation_ = MyMath::Add(worldTransform_.translation_, move);

	/// 移動制限処理
	// 範囲を超えない処理
	worldTransform_.translation_.x = max(worldTransform_.translation_.x, -kMoveLimitX);
	worldTransform_.translation_.x = min(worldTransform_.translation_.x, +kMoveLimitX);
	worldTransform_.translation_.y = max(worldTransform_.translation_.y, -kMoveLimitY);
	worldTransform_.translation_.y = min(worldTransform_.translation_.y, +kMoveLimitY);

}

/// <summary>
/// レティクルの移動処理
/// </summary>
void Player::MoveReticle(ViewProjection& viewProjection) {

	if (enableController) {
	
		// スプライトの現在座標を取得
		Vector2 spritePosition = sprite2DReticle_->GetPosition();

		// コントローラーの右スティックを取得
		XINPUT_STATE joyState;

		// ジョイスティックによって移動させる
		if (Input::GetInstance()->GetJoystickState(0, joyState)) {

			spritePosition.x += (float)joyState.Gamepad.sThumbRX / SHRT_MAX * 5.0f;
			spritePosition.y -= (float)joyState.Gamepad.sThumbRY / SHRT_MAX * 5.0f;
		}

		sprite2DReticle_->SetPosition(spritePosition);

		// ビューポート行列の生成
		Matrix4x4 matViewport =
		    MyMath::MakeViewPortMatrix(0, 0, WinApp::kWindowWidth, WinApp::kWindowHeight, 0, 1);

		// ビュー行列とプロジェクション行列、ビューポート行列を合成
		Matrix4x4 matViewProjectionViewport = MyMath::Multiply(
		    MyMath::Multiply(viewProjection.matView, viewProjection.matProjection), matViewport);
		// その逆行列を作る
		Matrix4x4 matInverseVPV = MyMath::Inverse(matViewProjectionViewport);

		// スクリーン座標
		Vector3 posNear = Vector3(spritePosition.x, spritePosition.y, 0);
		Vector3 posFar = Vector3(spritePosition.x, spritePosition.y, 1);

		// スクリーンからワールド座標系に
		posNear = MyMath::Transform(posNear, matInverseVPV);
		posFar = MyMath::Transform(posFar, matInverseVPV);

		// マウスレイの方向
		Vector3 mouseDirection = posFar - posNear;
		mouseDirection = MyMath::Normalize(mouseDirection);

		// カメラから照準オブジェクトの距離
		float kDistanceTestObject = 100;
		mouseDirection = MyMath::Multiply(kDistanceTestObject, mouseDirection);

		// 3Dレティクルの座標を設定
		worldTransform3DReticle_.translation_ = MyMath::Add(mouseDirection, posNear);

	} else {
	
		// マウス座標を取得する
		POINT mousePoint{};
		GetCursorPos(&mousePoint);

		// クライアントエリア座標に変換する
		HWND hwnd = WinApp::GetInstance()->GetHwnd();
		ScreenToClient(hwnd, &mousePoint);

		Vector2 mouseposition = {(float)mousePoint.x, (float)mousePoint.y};
		sprite2DReticle_->SetPosition({mouseposition.x, mouseposition.y});

		// ビューポート行列の生成
		Matrix4x4 matViewport =
		    MyMath::MakeViewPortMatrix(0, 0, WinApp::kWindowWidth, WinApp::kWindowHeight, 0, 1);

		// ビュー行列とプロジェクション行列、ビューポート行列を合成
		Matrix4x4 matViewProjectionViewport = MyMath::Multiply(
		    MyMath::Multiply(viewProjection.matView, viewProjection.matProjection), matViewport);
		// その逆行列を作る
		Matrix4x4 matInverseVPV = MyMath::Inverse(matViewProjectionViewport);

		// スクリーン座標
		Vector3 posNear = Vector3(mouseposition.x, mouseposition.y, 0);
		Vector3 posFar = Vector3(mouseposition.x, mouseposition.y, 1);

		// スクリーンからワールド座標系に
		posNear = MyMath::Transform(posNear, matInverseVPV);
		posFar = MyMath::Transform(posFar, matInverseVPV);

		// マウスレイの方向
		Vector3 mouseDirection = posFar - posNear;
		mouseDirection = MyMath::Normalize(mouseDirection);

		// カメラから照準オブジェクトの距離
		float kDistanceTestObject = 100;
		mouseDirection = MyMath::Multiply(kDistanceTestObject, mouseDirection);

		// 3Dレティクルの座標を設定
		worldTransform3DReticle_.translation_ = MyMath::Add(mouseDirection, posNear);

	}
}

/// <summary>
/// 攻撃処理
/// </summary>
void Player::Attack() {

	// コントローラーの右トリガーを取得
	XINPUT_STATE joyState;

	if (!Input::GetInstance()->GetJoystickState(0, joyState)) {
		return;
	}

	if (enableController) {
		// 指定時間に達したら
		if (fireTimer <= 0) {
			
			if (joyState.Gamepad.wButtons & XINPUT_GAMEPAD_RIGHT_SHOULDER) {

				// 弾速
				const float kBulletSpeed = 1.0f;
				Vector3 velocity(0, 0, kBulletSpeed);

				// 速度ベクトルを自機の向きに合わせて回転させる

				Vector3 ReticleWorldPos;
				ReticleWorldPos.x = worldTransform3DReticle_.matWorld_.m[3][0];
				ReticleWorldPos.y = worldTransform3DReticle_.matWorld_.m[3][1];
				ReticleWorldPos.z = worldTransform3DReticle_.matWorld_.m[3][2];

				velocity = ReticleWorldPos - GetWorldPosition();
				velocity = MyMath::Multiply(kBulletSpeed, MyMath::Normalize(velocity));
				// velocity = MyMath::TransformNormal(velocity, worldTransform_.matWorld_);

				// 弾の生成と初期化
				PlayerBullet* newBullet = new PlayerBullet();
				newBullet->Initialize(model_, GetWorldPosition(), velocity);

				// 弾を登録する
				gameScene_->AddPlayerBullet(newBullet);

				// 発射間隔初期化
				fireTimer = kFireInterval;

			}

		} else {
			// 発射タイマーカウントダウン
			fireTimer--;
		}

	} else {
		if (input_->TriggerKey(DIK_SPACE)) {

			// 弾速
			const float kBulletSpeed = 1.0f;
			Vector3 velocity(0, 0, kBulletSpeed);

			// 速度ベクトルを自機の向きに合わせて回転させる

			Vector3 ReticleWorldPos;
			ReticleWorldPos.x = worldTransform3DReticle_.matWorld_.m[3][0];
			ReticleWorldPos.y = worldTransform3DReticle_.matWorld_.m[3][1];
			ReticleWorldPos.z = worldTransform3DReticle_.matWorld_.m[3][2];

			velocity = ReticleWorldPos - GetWorldPosition();
			velocity = MyMath::Multiply(kBulletSpeed, MyMath::Normalize(velocity));
			// velocity = MyMath::TransformNormal(velocity, worldTransform_.matWorld_);

			// 弾の生成と初期化
			PlayerBullet* newBullet = new PlayerBullet();
			newBullet->Initialize(model_, GetWorldPosition(), velocity);

			// 弾を登録する
			gameScene_->AddPlayerBullet(newBullet);
		}
	}

}

Vector3 Player::GetWorldPosition() {

	// 結果格納用
	Vector3 worldPos;
	// ワールド行列の平行移動成分を取得
	worldPos.x = worldTransform_.matWorld_.m[3][0];
	worldPos.y = worldTransform_.matWorld_.m[3][1];
	worldPos.z = worldTransform_.matWorld_.m[3][2];

	// 結果を返す
	return worldPos;
}

/// <summary>
/// 衝突判定関数
/// </summary>
void Player::OnCollision() {
	
}

/// <summary>
/// 親子関係をセットするセッター
/// </summary>
/// <param name="parent">親</param>
void Player::SetParent(const WorldTransform* parent) {
	// 親子関係を結ぶ
	worldTransform_.parent_ = parent;
}