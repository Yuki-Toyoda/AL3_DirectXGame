#pragma once

/// <summary>
/// 3次元ベクトル
/// </summary>
struct Vector3 final {
	float x;
	float y;
	float z;
};

// 加算
Vector3 Add(const Vector3& v1, const Vector3& v2) {

	// 結果格納用
	Vector3 result;

	// 計算処理
	result.x = v1.x + v2.x;
	result.y = v1.y + v2.y;
	result.z = v1.z + v2.z;

	return result;
}