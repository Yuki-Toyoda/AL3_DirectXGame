#pragma once
#include "Model.h"
#include "ViewProjection.h"

/// <summary>
/// キャラクター基底クラス
/// </summary>
class BaseCharactor {
public: // メンバ関数

	/// <summary>
	/// 初期化処理
	/// </summary>
	/// <param name="models">モデルデータ配列</param>
	virtual void Initialize(const std::vector<Model*>& models);

	/// <summary>
	/// 更新処理
	/// </summary>
	virtual void Update();

	/// <summary>
	/// 描画処理
	/// </summary>
	/// <param name="viewProjection">ビュープロジェクション</param>
	virtual void Draw(const ViewProjection viewProjection);

	/// <summary>
	/// ワールドトランスフォームのゲッター
	/// </summary>
	/// <returns>ワールドトランスフォーム</returns>
	const WorldTransform& GetWorldTransform() { return worldTransform_; }

	/// <summary>
	/// 座標セッター
	/// </summary>
	/// <param name="translation">セットする座標</param>
	void SetTranslation(Vector3 translation) { worldTransform_.translation_ = translation; }

	/// <summary>
	/// 回転角セッター
	/// </summary>
	/// <param name="rotation">セットする回転角</param>
	void SetRotation(Vector3 rotation) { worldTransform_.rotation_ = rotation; }

	/// <summary>
	/// 拡縮セッター
	/// </summary>
	/// <param name="scale">セットするサイズ</param>
	void SetScale(Vector3 scale) { worldTransform_.scale_ = scale; }

protected: // メンバ変数

	// モデルデータの配列
	std::vector<Model*> models_;

	// ワールドトランスフォーム
	WorldTransform worldTransform_;

};
