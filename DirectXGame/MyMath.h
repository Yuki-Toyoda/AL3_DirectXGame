#pragma once
#include <cmath>
#include <ctime>
#include <Vector3.h>
#include <Matrix4x4.h>

class MyMath {
public:
	
	// srandセット関数
	// 返り値：なし
	// 引数なし
	// 指定された範囲内のランダムな値を返す関数(int型)
	static void SetSrand();

	// ランダム関数（int型）
	// 返り値：ランダムの値（int型）
	// 引数：
	// min ... 最小値
	// max ... 最大値
	// 指定された範囲内のランダムな値を返す関数(int型)
	static int Random(int min, int max);

	// ランダム関数（float型）
	// 返り値：ランダムの値（float型）
	// 引数：
	// min ... 最小値
	// max ... 最大値
	// num ... 少数点何桁まで表示するか
	// 指定された桁数で、範囲内のランダムな値を返す関数(float型)
	static float RandomF(float min, float max, int num);

	/// <summary>
	/// 3次元ベクトルの加算関数
	/// </summary>
	/// <param name="v1">ベクトル1</param>
	/// <param name="v2">ベクトル2</param>
	/// <returns>加算されたベクトルの値</returns>
	static Vector3 Add(Vector3 v1, const Vector3 v2);

	/// <summary>
	/// 平行移動を無視してスケーリングと回転のみを適用する関数
	/// </summary>
	/// <param name="v">3次元ベクトル</param>
	/// <param name="m">4x4行列</param>
	/// <returns>変換されたベクトル</returns>
	static Vector3 TransformNormal(const Vector3& v, const Matrix4x4& m);

	// 内積
	static float Dot(const Vector3& v1, const Vector3& v2);

	// 長さ
	static float Length(const Vector3& v);

	// 正規化
	static Vector3 Normalize(const Vector3& v);

	/// <summary>
	/// 行列の乗算
	/// </summary>
	/// <param name="m1">乗算する行列1</param>
	/// <param name="m2">乗算する行列2</param>
	/// <returns>乗算された行列</returns>
	static Matrix4x4 Multiply(Matrix4x4 m1, Matrix4x4 m2);

	/// <summary>
	/// 逆行列
	/// </summary>
	/// <param name="m">逆行列する行列</param>
	/// <returns>逆行列</returns>
	static Matrix4x4 Inverse(const Matrix4x4& m);

	/// <summary>
	/// 平行移動行列
	/// </summary>
	/// <param name="translate">三次元ベクトル</param>
	/// <returns>平行移動した後の行列</returns>
	static Matrix4x4 MakeTranslateMatrix(Vector3 translate);

	/// <summary>
	/// 拡大縮小行列
	/// </summary>
	/// <param name="scale">三次元ベクトル</param>
	/// <returns></returns>
	static Matrix4x4 MakeScaleMatrix(Vector3 scale);

	/// <summary>
	/// x軸方向の回転行列を作成する関数
	/// </summary>
	/// <param name="radian">回転角度</param>
	/// <returns>回転後の行列</returns>
	static Matrix4x4 MakeRotateXMatrix(float radian);

	/// <summary>
	/// y軸方向の回転行列を作成する関数
	/// </summary>
	/// <param name="radian">回転角度</param>
	/// <returns>回転後の行列</returns>
	static Matrix4x4 MakeRotateYMatrix(float radian);

	/// <summary>
	/// z軸方向の回転行列を作成する関数
	/// </summary>
	/// <param name="radian">回転角度</param>
	/// <returns>回転後の行列</returns>
	static Matrix4x4 MakeRotateZMatrix(float radian);

	/// <summary>
	/// 全ての軸の回転行列を作成する関数
	/// </summary>
	/// <param name="rotate">回転角</param>
	/// <returns>全ての軸の回転行列</returns>
	static Matrix4x4 MakeRotateXYZMatrix(Vector3 rotate);

	/// <summary>
	/// 3次元ベクトルからアフィン変換行列を生成する関数
	/// </summary>
	/// <param name="scale">拡大縮小行列</param>
	/// <param name="rotate">回転行列</param>
	/// <param name="translate">平行移動行列</param>
	/// <returns>アフィン変換された行列</returns>
	static Matrix4x4 Vector3MakeAffineMatrix(Vector3 scale, Vector3 rotate, Vector3 translate);

	/// <summary>
	/// 行列からアフィン変換行列を生成する関数
	/// </summary>
	/// <param name="scale"></param>
	/// <param name="rotate"></param>
	/// <param name="translate"></param>
	/// <returns></returns>
	static Matrix4x4 MakeAffineMatrix(
	    Matrix4x4 scale, Matrix4x4 rotate, Matrix4x4 translate) {

		// 結果格納用
		Matrix4x4 result;

		// 計算処理
		Matrix4x4 S = scale;
		Matrix4x4 R = rotate;
		Matrix4x4 T = translate;

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

};
