#pragma once

/// <summary>
/// 2次元ベクトル
/// </summary>
struct Vector2 final {
	float x;
	float y;

	// 演算子のオーバーロード
	Vector2 operator+(const Vector2 v1) {
		// 結果格納用
		Vector2 result;

		// 計算処理
		result.x = x + v1.x;
		result.y = y + v1.y;

		// 計算結果を返す
		return result;
	}

	Vector2 operator-(const Vector2 v1) {
		// 結果格納用
		Vector2 result;

		// 計算処理
		result.x = x - v1.x;
		result.y = y - v1.y;

		// 計算結果を返す
		return result;
	}

	Vector2 operator*(const Vector2 v1) {
		// 結果格納用
		Vector2 result;

		// 計算処理
		result.x = x * v1.x;
		result.y = y * v1.y;

		// 計算結果を返す
		return result;
	}

};
