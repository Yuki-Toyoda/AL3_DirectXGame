#pragma once

/// <summary>
/// 3次元ベクトル
/// </summary>
struct Vector3 final {
	float x;
	float y;
	float z;

	Vector3 operator+(const Vector3 v1) {
		// 結果格納用
		Vector3 result;

		// 計算処理
		result.x = x + v1.x;
		result.y = y + v1.y;
		result.z = z + v1.z;

		// 計算結果の返却
		return result;
	}

	Vector3 operator-(const Vector3 v1) {
		// 結果格納用
		Vector3 result;

		// 計算処理
		result.x = x - v1.x;
		result.y = y - v1.y;
		result.z = z - v1.z;

		// 計算結果の返却
		return result;
	}

	Vector3 operator*(const Vector3 v1) {
		// 結果格納用
		Vector3 result;

		// 計算処理
		result.x = x * v1.x;
		result.y = y * v1.y;
		result.z = z * v1.z;

		// 計算結果の返却
		return result;
	}

};