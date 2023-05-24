#pragma once
#include <cassert>
#include <WorldTransform.h>
#include <Model.h>
#include "MyMath.h"
class EnemyBullet {
public:
	EnemyBullet();
	~EnemyBullet();

	/// <summary>
	/// 初期化処理
	/// </summary>
	/// <param name="model">弾のモデル</param>
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
	/// 弾が消滅するかどうかを取得するゲッター
	/// </summary>
	/// <returns></returns>
	bool IsDead() const { return isDead_; }

	/// <summary>
	/// 衝突判定コールバック関数
	/// </summary>
	void OnCollision();

	/// <summary>
	/// 敵弾のワールド座標のゲッター
	/// </summary>
	/// <returns>敵弾のワールド座標</returns>
	Vector3 GetWorldPosition();

private:

	// ワールド変換データ
	WorldTransform worldTransform_;

	// モデルのポインタ
	Model* model_ = nullptr;

	// テクスチャハンドル
	uint32_t textureHandle_ = 0u;

	// 速度
	Vector3 velocity_;

	// 存在する時間
	static const int32_t kLifeTime = 60 * 5;

	// デスタイマー
	int32_t deathTimer_ = kLifeTime;
	// デスフラグ
	bool isDead_ = false;

};
