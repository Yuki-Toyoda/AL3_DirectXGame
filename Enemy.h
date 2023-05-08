#pragma once
#include <cassert>
#include <Model.h>
#include "MyMath.h"
#include "EnemyBullet.h"

/// <summary>
/// 敵のクラス
/// </summary>
class Enemy {
public:

	Enemy();
	~Enemy();

	/// <summary>
	/// 初期化処理
	/// </summary>
	/// <param name="model">3Dモデル</param>
	/// <param name="position">初期座標</param>
	/// <param name="velocity">速度</param>
	void Initialize(Model* model, const Vector3& position, const Vector3& velocity);

	/// <summary>
	/// 更新処理
	/// </summary>
	void Update();

	/// <summary>
	/// 描画処理
	/// </summary>
	/// <param name="viewProjection">ビュープロジェクション</param>
	void Draw(const ViewProjection& viewProjection);

	/// <summary>
	/// 敵の発射処理
	/// </summary>
	void Fire();

	/// <summary>
	/// 敵の射撃タイマー初期化
	/// </summary>
	void FireTimerInitialize();

private:

	/// <summary>
	/// 接近状態の更新処理
	/// </summary>
	void ApproachUpdate();

	/// <summary>
	/// 離脱状態の更新処理
	/// </summary>
	void LeaveUpdate();

	// ワールド変換データ
	WorldTransform worldTransform_;

	// モデルのポインタ
	Model* model_ = nullptr;

	// テクスチャハンドル
	uint32_t textureHandle_ = 0u;

	// 速度
	Vector3 velocity_;

	// 行動パターン
	enum class Phase {
		Approach, // 接近する
		Leave,	  // 離れる
	};

	Phase phase_ = Phase::Approach;

	// 弾
	std::list<EnemyBullet*> bullets_;

	// 発射間隔
	static const int kFireInterval = 30;
	int32_t fireTimer = 0;

};
