#pragma once
#include <cassert>
#include <WorldTransform.h>
#include <Model.h>
#include "MyMath.h"
/// <summary>
/// プレイヤーの弾のクラス
/// </summary>
class PlayerBullet {
public:
	PlayerBullet();
	~PlayerBullet();

	/// <summary>
	/// 初期化処理
	/// </summary>
	/// <param name="model">弾のモデル</param>
	/// <param name="position">初期座標</param>
	void Initialize(Model* model, const Vector3& position);

	/// <summary>
	/// 更新処理
	/// </summary>
	void Update();

	/// <summary>
	/// 描画処理
	/// </summary>
	/// <param name="viewProjection">ビュープロジェクション</param>
	void Draw(const ViewProjection& viewProjection);

private:

	// ワールド変換データ
	WorldTransform worldTransform_;

	// モデルのポインタ
	Model* model_ = nullptr;

	// テクスチャハンドル
	uint32_t textureHandle_ = 0u;

};
