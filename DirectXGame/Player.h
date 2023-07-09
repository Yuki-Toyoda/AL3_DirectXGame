#pragma once
#include <cassert>
#include <numbers>
#include "Input.h"
#include "Model.h"
#include "WorldTransform.h"
#include "ViewProjection.h"
#include "math/MyMath.h"

#ifdef _DEBUG
#include <imgui.h>
#endif // _DEBUG


/// <summary>
/// プレイヤークラス
/// </summary>
class Player {
public: // メンバ関数

	/// <summary>
	/// 初期化関数
	/// </summary>
	/// <param name="modelBody">体モデル</param>
	/// <param name="modelHead">頭モデル</param>
	/// <param name="modelL_arm">左腕モデル</param>
	/// <param name="modelR_arm">右腕モデル</param>
	void Initialize(Model* modelBody, Model* modelHead, Model* modelL_arm, Model* modelR_arm);

	/// <summary>
	/// 更新処理
	/// </summary>
	void Update();

	/// <summary>
	/// 描画処理
	/// </summary>
	/// <param name="viewProjection">ビュープロジェクション</param>
	void Draw(ViewProjection viewProjection);

	#pragma region アクセッサ等

	/// <summary>
	/// ワールドトランスフォームのゲッター
	/// </summary>
	/// <returns>ワールドトランスフォーム</returns>
	WorldTransform* GetWorldTransform() { return &worldTransform_; }

	/// <summary>
	/// ビュープロジェクションのセッター
	/// </summary>
	/// <param name="viewProjection">ビュープロジェクション</param>
	void SetViewProjection(const ViewProjection* viewProjection) {
		viewProjection_ = viewProjection;
	}

#pragma endregion

	/// <summary>
	/// 浮遊ギミック初期化関数
	/// </summary>
	void InitializeFloatingGimmick();

	/// <summary>
	/// 浮遊ギミック更新関数
	/// </summary>
	void UpdateFloatingGimmick();

private: // メンバ変数

	// 入力情報
	Input* input_ = nullptr;

	// ワールドトランスフォーム
	WorldTransform worldTransform_;

	// プレイヤーモデル
	std::unique_ptr<Model> modelFighterBody_;  // 体
	std::unique_ptr<Model> modelFighterHead_;  // 頭
	std::unique_ptr<Model> modelFighterL_Arm_; // 左腕
	std::unique_ptr<Model> modelFighterR_Arm_; // 右腕
	// モデルトランスフォーム
	WorldTransform worldTransformBody_;
	WorldTransform worldTransformHead_;
	WorldTransform worldTransformL_Arm_;
	WorldTransform worldTransformR_Arm_;

	// テクスチャ
	uint32_t textureHandle_ = 0u;

	// カメラのビュープロジェクションを格納する変数
	const ViewProjection* viewProjection_ = nullptr;

	// 浮遊ギミック用媒介変数
	float floatingParameter_ = 0.0f;

};
