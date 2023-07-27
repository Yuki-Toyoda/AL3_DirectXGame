#pragma once
#include <Windows.h>
#include <json.hpp>
#include <variant>
#include <map>
#include <string>
#include <fstream>
#include "MyMath.h"

#ifdef _DEBUG
#include <imgui.h>
#endif // _DEBUG

/// <summary>
/// 調整項目クラス
/// </summary>
class GlobalVariables {
private: // コンストラクタ等を無効

	/// <summary>
	/// コンストラクタ
	/// </summary>
	GlobalVariables();
	/// <summary>
	/// デストラクタ
	/// </summary>
	~GlobalVariables();

public: // コピーコンストラクタ、代入演算子無効

	// コピーコンストラクタ無効
	GlobalVariables(const GlobalVariables& obj) = delete;
	// 代入演算子無効
	GlobalVariables& operator=(const GlobalVariables& obj) = delete;

public: // メンバ関数

	/// <summary>
	/// インスタンス取得
	/// </summary>
	/// <returns>インスタンス</returns>
	static GlobalVariables* GetInstance();

	/// <summary>
	/// 更新処理
	/// </summary>
	void Update();

	/// <summary>
	/// グループの作成関数
	/// </summary>
	/// <param name="groupName">グループ名</param>
	void CreateGroup(const std::string& groupName);

	/// <summary>
	/// ファイルに書き出しを行う関数
	/// </summary>
	/// <param name="groupName">保存するグループ</param>
	void SaveFile(const std::string& groupName);

	/// <summary>
	/// 値のセット関数（int）
	/// </summary>
	/// <param name="groupName">セットするグループ</param>
	/// <param name="key">セットするキー</param>
	/// <param name="value">セットする値</param>
	void SetValue(const std::string& groupName, const std::string& key, int32_t value);
	/// <summary>
	/// 値のセット関数（float）
	/// </summary>
	/// <param name="groupName">セットするグループ</param>
	/// <param name="key">セットするキー</param>
	/// <param name="value">セットする値</param>
	void SetValue(const std::string& groupName, const std::string& key, float value);
	/// <summary>
	/// 値のセット関数（Vector3）
	/// </summary>
	/// <param name="groupName">セットするグループ</param>
	/// <param name="key">セットするキー</param>
	/// <param name="value">セットする値</param>
	void SetValue(const std::string& groupName, const std::string& key, const Vector3& value);

private: // メンバ変数

	// 項目列挙子
	struct Item {
		// 項目の値
		std::variant<int32_t, float, Vector3> value;
	};

	// グループ列挙子
	struct Group {
		std::map<std::string, Item> items;
	};

	// 全データ
	std::map<std::string, Group> datas_;

	// グローバル変数の保存先ファイルパス
	const std::string kDirectorypath = "Resources/GlobalVariables/";

};
