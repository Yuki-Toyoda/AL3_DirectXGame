#pragma once
#include "BaseCharactor.h"
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
class Player : public BaseCharactor{
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

	/// <summary>
	/// 腕振りギミック初期化
	/// </summary>
	void InitializeArmSwingGimmick();

	/// <summary>
	/// 腕振りギミック更新処理
	/// </summary>
	void UpdateArmSwingGimmick();

private: // メンバ変数

	// 入力情報
	Input* input_ = nullptr;

	// モデルトランスフォーム
	WorldTransform worldTransformBody_;
	WorldTransform worldTransformHead_;
	WorldTransform worldTransformL_Arm_;
	WorldTransform worldTransformR_Arm_;

	// テクスチャ
	uint32_t textureHandle_ = 0u;

	// カメラのビュープロジェクションを格納する変数
	const ViewProjection* viewProjection_ = nullptr;

	// 浮遊移動サイクル
	uint16_t floatingCycle_ = 60;
	// 浮遊の振幅
	float floatingAmpritude_ = 0.01f;
	// 浮遊ギミック用媒介変数
	float floatingParameter_ = 0.0f;

	// 腕振りサイクル
	uint16_t armSwingCycle_ = 60;
	// 腕振りギミック用変数
	float armSwingParameter_ = 0.0f;

};
