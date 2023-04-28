#pragma once
#include <cassert>
#include <Model.h>
#include "MyMath.h"

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
	/// 引数で指定したぶんだけ敵を動かす関数
	/// </summary>
	/// <param name="vector">移動量のベクトル</param>
	void MoveEnemy(const Vector3& vector);

	/// <summary>
	/// 敵の現在座標を返すゲッター
	/// </summary>
	/// <returns>敵の現在座標</returns>
	Vector3 GetEnemyTranslation() { return worldTransform_.translation_; }

private:

	/// <summary>
	/// 接近状態の更新処理
	/// </summary>
	void ApproachUpdate();

	/// <summary>
	/// 離脱状態の更新処理
	/// </summary>
	void LeaveUpdate();

	BaseEnemyState* State;

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

};

/// <summary>
/// 敵の行動管理クラス
/// </summary>
class BaseEnemyState {
public:
	/// <summary>
	/// 更新処理(仮想関数)
	/// </summary>
	virtual void Update();
};

class EnemyStateApproach : public BaseEnemyState {
public:
	/// <summary>
	/// 更新処理
	/// </summary>
	void Update();
};

class EnemyStateLeave : public BaseEnemyState {
public:
	/// <summary>
	/// 更新処理
	/// </summary>
	void Update();
};
