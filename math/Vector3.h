#pragma once

/// <summary>
/// 3次元ベクトル
/// </summary>
struct Vector3 final {
	float x;
	float y;
	float z;

	// 演算子のオーバーロード
	Vector3 operator+(Vector3 v1) {

		// 計算結果格納用
		Vector3 result;

		// 計算処理
		result.x = x + v1.x;
		result.y = y + v1.y;
		result.z = z + v1.z;

		return result;

	}

	Vector3 operator-(Vector3 v1) {

		// 計算結果格納用
		Vector3 result;

		// 計算処理
		result.x = x - v1.x;
		result.y = y - v1.y;
		result.z = z - v1.z;

		return result;
	}

	Vector3 operator*(Vector3 v1) {

		// 計算結果格納用
		Vector3 result;

		// 計算処理
		result.x = x * v1.x;
		result.y = y * v1.y;
		result.z = z * v1.z;

		return result;
	}

};