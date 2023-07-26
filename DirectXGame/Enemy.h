#pragma once
#include "BaseCharactor.h"
#include <numbers>
#include "MyMath.h"

#ifdef _DEBUG
#include <imgui.h>
#endif // _DEBUG

/// <summary>
/// 敵クラス
/// </summary>
class Enemy : public BaseCharactor {
public: // メンバ関数

	/// <summary>
	/// 初期化処理
	/// </summary>
	/// <param name="models">モデルデータ配列</param>
	void Initialize(const std::vector<Model*>& models) override;

	/// <summary>
	/// 更新処理
	/// </summary>
	void Update() override;

	/// <summary>
	/// 描画処理
	/// </summary>
	/// <param name="viewProjection">ビュープロジェクション</param>
	void Draw(const ViewProjection viewProjection) override;

private: // メンバ変数

	// ワールドトランスフォーム
	WorldTransform worldTransform_L_Camera_; // 左カメラ
	WorldTransform worldTransform_R_Camera_; // 右カメラ


};
