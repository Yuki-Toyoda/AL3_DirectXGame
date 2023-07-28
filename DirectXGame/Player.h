#pragma once
#include "BaseCharactor.h"
#include <cassert>
#include <numbers>
#include <optional>
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
	/// 調整項目の適用関数
	/// </summary>
	void ApplyGlobalVariables();

	/// <summary>
	/// 通常時の行動初期化
	/// </summary>
	void BehaviorRootInitialize();
	/// <summary>
	/// 通常時の行動更新関数
	/// </summary>
	void BehaviorRootUpdate();

	/// <summary>
	/// 通常時の行動初期化
	/// </summary>
	void BehaviorAttackInitialize();
	/// <summary>
	/// 攻撃時の行動更新関数
	/// </summary>
	void BehaviorAttackUpdate();

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
	// 武器用トランスフォーム
	WorldTransform worldTransformWeapon_;

	// テクスチャ
	uint32_t textureHandle_ = 0u;

	// カメラのビュープロジェクションを格納する変数
	const ViewProjection* viewProjection_ = nullptr;

	// 浮遊移動サイクル
	int32_t floatingCycle_ = 60;
	// 浮遊の振幅
	float floatingAmpritude_ = 0.01f;
	// 浮遊ギミック用媒介変数
	float floatingParameter_ = 0.0f;

	// 腕振りサイクル
	int32_t armSwingCycle_ = 60;
	// 腕振りギミック用変数
	float armSwingParameter_ = 0.0f;

	// ふるまい列挙子
	enum Behavior {
		kRoot, // 通常状態
		kAttack // 攻撃状態
	};
	// ふるまい初期設定
	Behavior behavior_ = Behavior::kRoot;

	// ふるまいリクエスト
	std::optional<Behavior> behaviorRequest_ = std::nullopt;

	// 攻撃状態列挙子
	enum AttackState {
		SwingOver, // 振りかぶり
		Attack, // 攻撃動作
		Wait, // 硬直
	};
	// 現在の攻撃状態
	int32_t attackState_ = SwingOver;

	// 攻撃演出用t
	float t_ = 0.0f;

	// 振りかぶり秒数
	float swingOverTime_ = 0.5f;
	// 攻撃秒数
	float attackTime_ = 0.25f;
	// 攻撃の時どれだけ前に進むか
	float attackForward_ = 10.0f;
	// 攻撃後硬直秒数
	float attackWaitTime_ = 0.5f;

	// 振りかぶり初期角度
	float swingOverStartAngle_ = (float)std::numbers::pi + (float) std::numbers::pi / 2.0f;
	// 振りかぶり終端角度
	float swingOverEndAngle_ = (float)std::numbers::pi - (float)std::numbers::pi / 3.0f;

	// 振り降ろし終端角度
	float attackEndAngle_ = (float)std::numbers::pi + (float)std::numbers::pi / 1.75f;

	// 攻撃開始地点
	Vector3 attackStartPos_ = {0.0f, 0.0f, 0.0f};
	// 攻撃終端地点
	Vector3 attackEndPos_ = {0.0f, 0.0f, 0.0f};

};
