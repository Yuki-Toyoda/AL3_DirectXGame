#include "MyMath.h"

/// <summary>
/// 3次元ベクトルの加算関数
/// </summary>
/// <param name="v1">ベクトル1</param>
/// <param name="v2">ベクトル2</param>
/// <returns>加算されたベクトルの値</returns>
Vector3 MyMath::Add(Vector3 v1, Vector3 v2) {

	// 結果格納用
	Vector3 result;

	// 計算処理
	result.x = v1.x + v2.x;
	result.y = v1.y + v2.y;
	result.z = v1.z + v2.z;

	return result;
}

/// <summary>
/// 平行移動を無視してスケーリングと回転のみを適用する関数
/// </summary>
/// <param name="v">3次元ベクトル</param>
/// <param name="m">4x4行列</param>
/// <returns>変換されたベクトル</returns>
Vector3 MyMath::TransformNormal(const Vector3& v, const Matrix4x4& m) {
	Vector3 result{
	    v.x * m.m[0][0] + v.y * m.m[1][0] + v.z * m.m[2][0],
	    v.x * m.m[0][1] + v.y * m.m[1][1] + v.z * m.m[2][1],
	    v.x * m.m[0][2] + v.y * m.m[1][2] + v.z * m.m[2][2]};

	return result;
}

// 内積
float MyMath::Dot(const Vector3& v1, const Vector3& v2) {

	// 結果格納用
	float result;

	// 計算処理
	result = (v1.x * v2.x) + (v1.y * v2.y) + (v1.z * v2.z);

	return result;
}

// 長さ
float MyMath::Length(const Vector3& v) {

	// 計算処理
	return sqrtf(MyMath::Dot(v, v));
}

// 正規化
Vector3 MyMath::Normalize(const Vector3& v) {

	// 正規化するベクトルの長さを求める
	float length = sqrtf(Length(v));
	// 結果格納用
	Vector3 result;

	// 計算処理
	if (v.x != 0.0f) {
		result.x = v.x / length;
	} else {
		result.x = 0.0f;
	}
	if (v.y != 0.0f) {
		result.y = v.y / length;
	} else {
		result.y = 0.0f;
	}
	if (v.z != 0.0f) {
		result.z = v.z / length;
	} else {
		result.z = 0.0f;
	}

	return result;
}

/// <summary>
/// 行列の乗算
/// </summary>
/// <param name="m1">乗算する行列1</param>
/// <param name="m2">乗算する行列2</param>
/// <returns>乗算された行列</returns>
Matrix4x4 MyMath::Multiply(Matrix4x4 m1, Matrix4x4 m2) {

	// 結果格納用
	Matrix4x4 result;

	// 計算処理
	result.m[0][0] = (m1.m[0][0] * m2.m[0][0]) + (m1.m[0][1] * m2.m[1][0]) +
	                 (m1.m[0][2] * m2.m[2][0]) + (m1.m[0][3] * m2.m[3][0]);
	result.m[1][0] = (m1.m[1][0] * m2.m[0][0]) + (m1.m[1][1] * m2.m[1][0]) +
	                 (m1.m[1][2] * m2.m[2][0]) + (m1.m[1][3] * m2.m[3][0]);
	result.m[2][0] = (m1.m[2][0] * m2.m[0][0]) + (m1.m[2][1] * m2.m[1][0]) +
	                 (m1.m[2][2] * m2.m[2][0]) + (m1.m[2][3] * m2.m[3][0]);
	result.m[3][0] = (m1.m[3][0] * m2.m[0][0]) + (m1.m[3][1] * m2.m[1][0]) +
	                 (m1.m[3][2] * m2.m[2][0]) + (m1.m[3][3] * m2.m[3][0]);

	result.m[0][1] = (m1.m[0][0] * m2.m[0][1]) + (m1.m[0][1] * m2.m[1][1]) +
	                 (m1.m[0][2] * m2.m[2][1]) + (m1.m[0][3] * m2.m[3][1]);
	result.m[1][1] = (m1.m[1][0] * m2.m[0][1]) + (m1.m[1][1] * m2.m[1][1]) +
	                 (m1.m[1][2] * m2.m[2][1]) + (m1.m[1][3] * m2.m[3][1]);
	result.m[2][1] = (m1.m[2][0] * m2.m[0][1]) + (m1.m[2][1] * m2.m[1][1]) +
	                 (m1.m[2][2] * m2.m[2][1]) + (m1.m[2][3] * m2.m[3][1]);
	result.m[3][1] = (m1.m[3][0] * m2.m[0][1]) + (m1.m[3][1] * m2.m[1][1]) +
	                 (m1.m[3][2] * m2.m[2][1]) + (m1.m[3][3] * m2.m[3][1]);

	result.m[0][2] = (m1.m[0][0] * m2.m[0][2]) + (m1.m[0][1] * m2.m[1][2]) +
	                 (m1.m[0][2] * m2.m[2][2]) + (m1.m[0][3] * m2.m[3][2]);
	result.m[1][2] = (m1.m[1][0] * m2.m[0][2]) + (m1.m[1][1] * m2.m[1][2]) +
	                 (m1.m[1][2] * m2.m[2][2]) + (m1.m[1][3] * m2.m[3][2]);
	result.m[2][2] = (m1.m[2][0] * m2.m[0][2]) + (m1.m[2][1] * m2.m[1][2]) +
	                 (m1.m[2][2] * m2.m[2][2]) + (m1.m[2][3] * m2.m[3][2]);
	result.m[3][2] = (m1.m[3][0] * m2.m[0][2]) + (m1.m[3][1] * m2.m[1][2]) +
	                 (m1.m[3][2] * m2.m[2][2]) + (m1.m[3][3] * m2.m[3][2]);

	result.m[0][3] = (m1.m[0][0] * m2.m[0][3]) + (m1.m[0][1] * m2.m[1][3]) +
	                 (m1.m[0][2] * m2.m[2][3]) + (m1.m[0][3] * m2.m[3][3]);
	result.m[1][3] = (m1.m[1][0] * m2.m[0][3]) + (m1.m[1][1] * m2.m[1][3]) +
	                 (m1.m[1][2] * m2.m[2][3]) + (m1.m[1][3] * m2.m[3][3]);
	result.m[2][3] = (m1.m[2][0] * m2.m[0][3]) + (m1.m[2][1] * m2.m[1][3]) +
	                 (m1.m[2][2] * m2.m[2][3]) + (m1.m[2][3] * m2.m[3][3]);
	result.m[3][3] = (m1.m[3][0] * m2.m[0][3]) + (m1.m[3][1] * m2.m[1][3]) +
	                 (m1.m[3][2] * m2.m[2][3]) + (m1.m[3][3] * m2.m[3][3]);

	return result;
}

/// <summary>
/// 逆行列
/// </summary>
/// <param name="m">計算する行列</param>
/// <returns></returns>
Matrix4x4 MyMath::Inverse(const Matrix4x4& m) {

	// 結果格納用
	Matrix4x4 result = {};

	// 行列式
	float d;

	// 行列式を求める
	d = (m.m[0][0] * m.m[1][1] * m.m[2][2] * m.m[3][3]) +
	    (m.m[0][0] * m.m[1][2] * m.m[2][3] * m.m[3][1]) +
	    (m.m[0][0] * m.m[1][3] * m.m[2][1] * m.m[3][2]) -

	    (m.m[0][0] * m.m[1][3] * m.m[2][2] * m.m[3][1]) -
	    (m.m[0][0] * m.m[1][2] * m.m[2][1] * m.m[3][3]) -
	    (m.m[0][0] * m.m[1][1] * m.m[2][3] * m.m[3][2]) -

	    (m.m[0][1] * m.m[1][0] * m.m[2][2] * m.m[3][3]) -
	    (m.m[0][2] * m.m[1][0] * m.m[2][3] * m.m[3][1]) -
	    (m.m[0][3] * m.m[1][0] * m.m[2][1] * m.m[3][2]) +

	    (m.m[0][3] * m.m[1][0] * m.m[2][2] * m.m[3][1]) +
	    (m.m[0][2] * m.m[1][0] * m.m[2][1] * m.m[3][3]) +
	    (m.m[0][1] * m.m[1][0] * m.m[2][3] * m.m[3][2]) +

	    (m.m[0][1] * m.m[1][2] * m.m[2][0] * m.m[3][3]) +
	    (m.m[0][2] * m.m[1][3] * m.m[2][0] * m.m[3][1]) +
	    (m.m[0][3] * m.m[1][1] * m.m[2][0] * m.m[3][2]) -

	    (m.m[0][3] * m.m[1][2] * m.m[2][0] * m.m[3][1]) -
	    (m.m[0][2] * m.m[1][1] * m.m[2][0] * m.m[3][3]) -
	    (m.m[0][1] * m.m[1][3] * m.m[2][0] * m.m[3][2]) -

	    (m.m[0][1] * m.m[1][2] * m.m[2][3] * m.m[3][0]) -
	    (m.m[0][2] * m.m[1][3] * m.m[2][1] * m.m[3][0]) -
	    (m.m[0][3] * m.m[1][1] * m.m[2][2] * m.m[3][0]) +

	    (m.m[0][3] * m.m[1][2] * m.m[2][1] * m.m[3][0]) +
	    (m.m[0][2] * m.m[1][1] * m.m[2][3] * m.m[3][0]) +
	    (m.m[0][1] * m.m[1][3] * m.m[2][2] * m.m[3][0]);

	// 計算処理
	if (d != 0) {

		result.m[0][0] =
		    (1.0f / d) * (m.m[1][1] * m.m[2][2] * m.m[3][3] + m.m[1][2] * m.m[2][3] * m.m[3][1] +
		                  m.m[1][3] * m.m[2][1] * m.m[3][2] - m.m[1][3] * m.m[2][2] * m.m[3][1] -
		                  m.m[1][2] * m.m[2][1] * m.m[3][3] - m.m[1][1] * m.m[2][3] * m.m[3][2]);
		result.m[0][1] =
		    (1.0f / d) * (-m.m[0][1] * m.m[2][2] * m.m[3][3] - m.m[0][2] * m.m[2][3] * m.m[3][1] -
		                  m.m[0][3] * m.m[2][1] * m.m[3][2] + m.m[0][3] * m.m[2][2] * m.m[3][1] +
		                  m.m[0][2] * m.m[2][1] * m.m[3][3] + m.m[0][1] * m.m[2][3] * m.m[3][2]);
		result.m[0][2] =
		    (1.0f / d) * (+m.m[0][1] * m.m[1][2] * m.m[3][3] + m.m[0][2] * m.m[1][3] * m.m[3][1] +
		                  m.m[0][3] * m.m[1][1] * m.m[3][2] - m.m[0][3] * m.m[1][2] * m.m[3][1] -
		                  m.m[0][2] * m.m[1][1] * m.m[3][3] - m.m[0][1] * m.m[1][3] * m.m[3][2]);
		result.m[0][3] =
		    (1.0f / d) * (-m.m[0][1] * m.m[1][2] * m.m[2][3] - m.m[0][2] * m.m[1][3] * m.m[2][1] -
		                  m.m[0][3] * m.m[1][1] * m.m[2][2] + m.m[0][3] * m.m[1][2] * m.m[2][1] +
		                  m.m[0][2] * m.m[1][1] * m.m[2][3] + m.m[0][1] * m.m[1][3] * m.m[2][2]);

		result.m[1][0] =
		    (1.0f / d) * (-m.m[1][0] * m.m[2][2] * m.m[3][3] - m.m[1][2] * m.m[2][3] * m.m[3][0] -
		                  m.m[1][3] * m.m[2][0] * m.m[3][2] + m.m[1][3] * m.m[2][2] * m.m[3][0] +
		                  m.m[1][2] * m.m[2][0] * m.m[3][3] + m.m[1][0] * m.m[2][3] * m.m[3][2]);
		result.m[1][1] =
		    (1.0f / d) * (m.m[0][0] * m.m[2][2] * m.m[3][3] + m.m[0][2] * m.m[2][3] * m.m[3][0] +
		                  m.m[0][3] * m.m[2][0] * m.m[3][2] - m.m[0][3] * m.m[2][2] * m.m[3][0] -
		                  m.m[0][2] * m.m[2][0] * m.m[3][3] - m.m[0][0] * m.m[2][3] * m.m[3][2]);
		result.m[1][2] =
		    (1.0f / d) * (-m.m[0][0] * m.m[1][2] * m.m[3][3] - m.m[0][2] * m.m[1][3] * m.m[3][0] -
		                  m.m[0][3] * m.m[1][0] * m.m[3][2] + m.m[0][3] * m.m[1][2] * m.m[3][0] +
		                  m.m[0][2] * m.m[1][0] * m.m[3][3] + m.m[0][0] * m.m[1][3] * m.m[3][2]);
		result.m[1][3] =
		    (1.0f / d) * (m.m[0][0] * m.m[1][2] * m.m[2][3] + m.m[0][2] * m.m[1][3] * m.m[2][0] +
		                  m.m[0][3] * m.m[1][0] * m.m[2][2] - m.m[0][3] * m.m[1][2] * m.m[2][0] -
		                  m.m[0][2] * m.m[1][0] * m.m[2][3] - m.m[0][0] * m.m[1][3] * m.m[2][2]);

		result.m[2][0] =
		    (1.0f / d) * (m.m[1][0] * m.m[2][1] * m.m[3][3] + m.m[1][1] * m.m[2][3] * m.m[3][0] +
		                  m.m[1][3] * m.m[2][0] * m.m[3][1] - m.m[1][3] * m.m[2][1] * m.m[3][0] -
		                  m.m[1][1] * m.m[2][0] * m.m[3][3] - m.m[1][0] * m.m[2][3] * m.m[3][1]);
		result.m[2][1] =
		    (1.0f / d) * (-m.m[0][0] * m.m[2][1] * m.m[3][3] - m.m[0][1] * m.m[2][3] * m.m[3][0] -
		                  m.m[0][3] * m.m[2][0] * m.m[3][1] + m.m[0][3] * m.m[2][1] * m.m[3][0] +
		                  m.m[0][1] * m.m[2][0] * m.m[3][3] + m.m[0][0] * m.m[2][3] * m.m[3][1]);
		result.m[2][2] =
		    (1.0f / d) * (m.m[0][0] * m.m[1][1] * m.m[3][3] + m.m[0][1] * m.m[1][3] * m.m[3][0] +
		                  m.m[0][3] * m.m[1][0] * m.m[3][1] - m.m[0][3] * m.m[1][1] * m.m[3][0] -
		                  m.m[0][1] * m.m[1][0] * m.m[3][3] - m.m[0][0] * m.m[1][3] * m.m[3][1]);
		result.m[2][3] =
		    (1.0f / d) * (-m.m[0][0] * m.m[1][1] * m.m[2][3] - m.m[0][1] * m.m[1][3] * m.m[2][0] -
		                  m.m[0][3] * m.m[1][0] * m.m[2][1] + m.m[0][3] * m.m[1][1] * m.m[2][0] +
		                  m.m[0][1] * m.m[1][0] * m.m[2][3] + m.m[0][0] * m.m[1][3] * m.m[2][1]);

		result.m[3][0] =
		    (1.0f / d) * (-m.m[1][0] * m.m[2][1] * m.m[3][2] - m.m[1][1] * m.m[2][2] * m.m[3][0] -
		                  m.m[1][2] * m.m[2][0] * m.m[3][1] + m.m[1][2] * m.m[2][1] * m.m[3][0] +
		                  m.m[1][1] * m.m[2][0] * m.m[3][2] + m.m[1][0] * m.m[2][2] * m.m[3][1]);
		result.m[3][1] =
		    (1.0f / d) * (m.m[0][0] * m.m[2][1] * m.m[3][2] + m.m[0][1] * m.m[2][2] * m.m[3][0] +
		                  m.m[0][2] * m.m[2][0] * m.m[3][1] - m.m[0][2] * m.m[2][1] * m.m[3][0] -
		                  m.m[0][1] * m.m[2][0] * m.m[3][2] - m.m[0][0] * m.m[2][2] * m.m[3][1]);
		result.m[3][2] =
		    (1.0f / d) * (-m.m[0][0] * m.m[1][1] * m.m[3][2] - m.m[0][1] * m.m[1][2] * m.m[3][0] -
		                  m.m[0][2] * m.m[1][0] * m.m[3][1] + m.m[0][2] * m.m[1][1] * m.m[3][0] +
		                  m.m[0][1] * m.m[1][0] * m.m[3][2] + m.m[0][0] * m.m[1][2] * m.m[3][1]);
		result.m[3][3] =
		    (1.0f / d) * (m.m[0][0] * m.m[1][1] * m.m[2][2] + m.m[0][1] * m.m[1][2] * m.m[2][0] +
		                  m.m[0][2] * m.m[1][0] * m.m[2][1] - m.m[0][2] * m.m[1][1] * m.m[2][0] -
		                  m.m[0][1] * m.m[1][0] * m.m[2][2] - m.m[0][0] * m.m[1][2] * m.m[2][1]);
	}

	return result;
}

/// <summary>
/// 平行移動行列
/// </summary>
/// <param name="translate">三次元ベクトル</param>
/// <returns>平行移動した後の行列</returns>
Matrix4x4 MyMath::MakeTranslateMatrix(Vector3 translate) {

	// 結果格納用
	Matrix4x4 result;

	// 生成処理
	result.m[0][0] = 1.0f;
	result.m[0][1] = 0.0f;
	result.m[0][2] = 0.0f;
	result.m[0][3] = 0.0f;

	result.m[1][0] = 0.0f;
	result.m[1][1] = 1.0f;
	result.m[1][2] = 0.0f;
	result.m[1][3] = 0.0f;

	result.m[2][0] = 0.0f;
	result.m[2][1] = 0.0f;
	result.m[2][2] = 1.0f;
	result.m[2][3] = 0.0f;

	result.m[3][0] = translate.x;
	result.m[3][1] = translate.y;
	result.m[3][2] = translate.z;
	result.m[3][3] = 1.0f;

	return result;
}

/// <summary>
/// 拡大縮小行列
/// </summary>
/// <param name="scale">三次元ベクトル</param>
/// <returns>拡大縮小行列</returns>
Matrix4x4 MyMath::MakeScaleMatrix(Vector3 scale) {

	// 結果格納用
	Matrix4x4 result;

	// 生成処理
	result.m[0][0] = scale.x;
	result.m[0][1] = 0.0f;
	result.m[0][2] = 0.0f;
	result.m[0][3] = 0.0f;

	result.m[1][0] = 0.0f;
	result.m[1][1] = scale.y;
	result.m[1][2] = 0.0f;
	result.m[1][3] = 0.0f;

	result.m[2][0] = 0.0f;
	result.m[2][1] = 0.0f;
	result.m[2][2] = scale.z;
	result.m[2][3] = 0.0f;

	result.m[3][0] = 0.0f;
	result.m[3][1] = 0.0f;
	result.m[3][2] = 0.0f;
	result.m[3][3] = 1.0f;

	return result;
}

/// <summary>
/// x軸方向の回転行列を作成する関数
/// </summary>
/// <param name="radian">回転角度</param>
/// <returns>回転後の行列</returns>
Matrix4x4 MyMath::MakeRotateXMatrix(float radian) {

	// 結果格納用
	Matrix4x4 result;

	result.m[0][0] = 1.0f;
	result.m[0][1] = 0.0f;
	result.m[0][2] = 0.0f;
	result.m[0][3] = 0.0f;

	result.m[1][0] = 0.0f;
	result.m[1][1] = std::cosf(radian);
	result.m[1][2] = std::sinf(radian);
	result.m[1][3] = 0.0f;

	result.m[2][0] = 0.0f;
	result.m[2][1] = -(std::sinf(radian));
	result.m[2][2] = std::cosf(radian);
	result.m[2][3] = 0.0f;

	result.m[3][0] = 0.0f;
	result.m[3][1] = 0.0f;
	result.m[3][2] = 0.0f;
	result.m[3][3] = 1.0f;

	return result;
}

/// <summary>
/// y軸方向の回転行列を作成する関数
/// </summary>
/// <param name="radian">回転角度</param>
/// <returns>回転後の行列</returns>
Matrix4x4 MyMath::MakeRotateYMatrix(float radian) {

	// 結果格納用
	Matrix4x4 result;

	result.m[0][0] = std::cosf(radian);
	result.m[0][1] = 0.0f;
	result.m[0][2] = -(std::sinf(radian));
	result.m[0][3] = 0.0f;

	result.m[1][0] = 0.0f;
	result.m[1][1] = 1.0f;
	result.m[1][2] = 0.0f;
	result.m[1][3] = 0.0f;

	result.m[2][0] = std::sinf(radian);
	result.m[2][1] = 0.0f;
	result.m[2][2] = std::cosf(radian);
	result.m[2][3] = 0.0f;

	result.m[3][0] = 0.0f;
	result.m[3][1] = 0.0f;
	result.m[3][2] = 0.0f;
	result.m[3][3] = 1.0f;

	return result;
}

/// <summary>
/// z軸方向の回転行列を作成する関数
/// </summary>
/// <param name="radian">回転角度</param>
/// <returns>回転後の行列</returns>
Matrix4x4 MyMath::MakeRotateZMatrix(float radian) {

	// 結果格納用
	Matrix4x4 result;

	result.m[0][0] = std::cosf(radian);
	result.m[0][1] = std::sinf(radian);
	result.m[0][2] = 0.0f;
	result.m[0][3] = 0.0f;

	result.m[1][0] = -(std::sinf(radian));
	result.m[1][1] = std::cosf(radian);
	result.m[1][2] = 0.0f;
	result.m[1][3] = 0.0f;

	result.m[2][0] = 0.0f;
	result.m[2][1] = 0.0f;
	result.m[2][2] = 1.0f;
	result.m[2][3] = 0.0f;

	result.m[3][0] = 0.0f;
	result.m[3][1] = 0.0f;
	result.m[3][2] = 0.0f;
	result.m[3][3] = 1.0f;

	return result;
}

/// <summary>
/// 全ての軸の回転行列を作成する関数
/// </summary>
/// <param name="rotate">回転角</param>
/// <returns>全ての軸の回転行列</returns>
Matrix4x4 MyMath::MakeRotateXYZMatrix(Vector3 rotate) {

	// 結果格納用
	Matrix4x4 result{};

	// 計算一時保存用
	Matrix4x4 tempXMatrix = MyMath::MakeRotateXMatrix(rotate.x);
	Matrix4x4 tempYMatrix = MyMath::MakeRotateYMatrix(rotate.y);
	Matrix4x4 tempZMatrix = MyMath::MakeRotateZMatrix(rotate.z);

	// 計算処理
	result = MyMath::Multiply(tempXMatrix, MyMath::Multiply(tempYMatrix, tempZMatrix));

	return result;
}

/// <summary>
/// 3次元ベクトルからアフィン変換行列を生成する関数
/// </summary>
/// <param name="scale">拡大縮小行列</param>
/// <param name="rotate">回転行列</param>
/// <param name="translate">平行移動行列</param>
/// <returns>アフィン変換された行列</returns>
Matrix4x4 MyMath::Vector3MakeAffineMatrix(Vector3 scale, Vector3 rotate, Vector3 translate) {

	// 結果格納用
	Matrix4x4 result;

	// 計算処理
	Matrix4x4 S = MakeScaleMatrix(scale);
	Matrix4x4 R = MakeRotateXYZMatrix(rotate);
	Matrix4x4 T = MakeTranslateMatrix(translate);

	result.m[0][0] = S.m[0][0] * R.m[0][0];
	result.m[0][1] = S.m[0][0] * R.m[0][1];
	result.m[0][2] = S.m[0][0] * R.m[0][2];
	result.m[0][3] = 0.0f;

	result.m[1][0] = S.m[1][1] * R.m[1][0];
	result.m[1][1] = S.m[1][1] * R.m[1][1];
	result.m[1][2] = S.m[1][1] * R.m[1][2];
	result.m[1][3] = 0.0f;

	result.m[2][0] = S.m[2][2] * R.m[2][0];
	result.m[2][1] = S.m[2][2] * R.m[2][1];
	result.m[2][2] = S.m[2][2] * R.m[2][2];
	result.m[2][3] = 0.0f;

	result.m[3][0] = T.m[3][0];
	result.m[3][1] = T.m[3][1];
	result.m[3][2] = T.m[3][2];
	result.m[3][3] = 1.0f;

	return result;
}