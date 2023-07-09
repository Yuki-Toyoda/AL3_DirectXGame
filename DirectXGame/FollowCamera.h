#pragma once
#include "ViewProjection.h"
#include "WorldTransform.h"
#include "input/input.h"
#include "math/MyMath.h"

/// <summary>
/// 追従カメラ
/// </summary>
class FollowCamera {
public: // メンバ関数

	/// <summary>
	/// 初期化関数
	/// </summary>
	void Initialize();

	/// <summary>
	/// 更新処理
	/// </summary>
	void Update();

	#pragma region アクセッサ等

	/// <summary>
	/// ビュープロジェクションゲッター
	/// </summary>
	/// <returns>ビュープロジェクション</returns>
	ViewProjection* GetViewProjectionAdress() { return &viewProjection_; }

	/// <summary>
	/// ビュープロジェクションゲッター
	/// </summary>
	/// <returns>ビュープロジェクション</returns>
	ViewProjection GetViewProjection() { return viewProjection_; }

	/// <summary>
	/// カメラの追従対象セッター
	/// </summary>
	/// <param name="target">追従対象</param>
	void SetTarget(const WorldTransform* target) { target_ = target; }

#pragma endregion


private: // メンバ変数

	// ビュープロジェクション
	ViewProjection viewProjection_;

	// 追従対象のワールド座標
	const WorldTransform* target_ = nullptr;

};
