#include "GlobalVariables.h"

#pragma region private

GlobalVariables::GlobalVariables() {}
GlobalVariables::~GlobalVariables() {}

#pragma endregion

using namespace nlohmann;

GlobalVariables* GlobalVariables::GetInstance() { 
	static GlobalVariables instance;
	return &instance;
}

void GlobalVariables::Update() { 
	// メニューバーが使用可能なウィンドウを開く
	if (!ImGui::Begin("Global Variables", nullptr, ImGuiWindowFlags_MenuBar)) {
		ImGui::End();
		return;
	}
	if (!ImGui::BeginMenuBar())
		return;

	// 全てのグループを取得
	for (std::map<std::string, Group>::iterator itGroup = datas_.begin(); itGroup != datas_.end();
	     itGroup++) {
		// グループ名(キー)を取得
		const std::string& groupName = itGroup->first;
		// グループの参照(値)を取得
		Group& group = itGroup->second;

		if (!ImGui::BeginMenu(groupName.c_str()))
			continue;

		// 各項目を取得
		for (std::map<std::string, Item>::iterator itItem = group.items.begin();
		     itItem != group.items.end(); itItem++) {
			// 項目名(キー)を取得
			const std::string& itemName = itItem->first;
			// 項目の参照(値)を取得
			Item& item = itItem->second;

			// int型の値を保持している場合
			if (std::holds_alternative<int32_t>(item.value)) {
				// int32_t型の値を取得
				int32_t* ptr = std::get_if<int32_t>(&item.value);
				// ImGuiのUIを出す
				ImGui::SliderInt(itemName.c_str(), ptr, 0, 100);
			} 
			// float型の値を保持している場合
			else if (std::holds_alternative<float>(item.value)) {
				// float型の値を取得
				float* ptr = std::get_if<float>(&item.value);
				// ImGuiのUIを出す
				ImGui::SliderFloat(itemName.c_str(), ptr, -100.0f, 100.0f);
			}
			// Vector3型の値を保持している場合
			else if (std::holds_alternative<Vector3>(item.value)) {
				// Vector3型の値を取得
				Vector3* ptr = std::get_if<Vector3>(&item.value);
				// ImGuiのUIを出す
				ImGui::SliderFloat3(itemName.c_str(), reinterpret_cast<float*>(ptr), -100.0f, 100.0f);
			}
		}

		// 改行する
		ImGui::Text("\n");
		// セーブするボタンを出す
		if (ImGui::Button("Save")) {
			// ファイル保存を行う
			SaveFile(groupName);
			// セーブが完了したことをメッセージボックスで出す
			std::string message = std::format("{}.json saved.", groupName);
			MessageBoxA(nullptr, message.c_str(), "GlobalVariables", 0);
		}

		ImGui::EndMenu();
	}

	ImGui::EndMenuBar();
	ImGui::End();
}

void GlobalVariables::CreateGroup(const std::string& groupName) { 
	// 引数名のオブジェクトがなければ追加する
	datas_[groupName]; 
}

void GlobalVariables::SaveFile(const std::string& groupName) {
	// 指定されたグループが登録されているか検索
	std::map<std::string, Group>::iterator itGroup = datas_.find(groupName);
	// 未登録だった場合はassertでゲームを落とす
	assert(itGroup != datas_.end());
	
	// json型のインスタンスを生成
	json root;
	// コンテナを作成（std::map のようなもの）
	root = json::object();
	// 1グループ分のjsonオブジェクトを登録
	root[groupName] = json::object();

	for (std::map<std::string, Item>::iterator itItem = itGroup->second.items.begin();
	     itItem != itGroup->second.items.end(); itItem++) {
		// 項目名(キー)を取得
		const std::string& itemName = itItem->first;
		// 項目の参照(値)を取得
		Item& item = itItem->second;

		// int型の値を保持している場合
		if (std::holds_alternative<int32_t>(item.value)) {
			// int32_t型の値を登録
			root[groupName][itemName] = std::get<int32_t>(item.value);
		}
		// float型の値を保持している場合
		else if (std::holds_alternative<float>(item.value)) {
			// float型の値を登録
			root[groupName][itemName] = std::get<float>(item.value);
		}
		// Vector3型の値を保持している場合
		else if (std::holds_alternative<Vector3>(item.value)) {
			// Vector3型の値を登録
			Vector3 value = std::get<Vector3>(item.value);
			// jsonの配列でVector3の要素一つ一つを格納する
			root[groupName][itemName] = json::array({value.x, value.y, value.z});
		}
	}

	// ディレクトリがなければ新規で作成する
	std::filesystem::path dir(kDirectorypath);
	if (!std::filesystem::exists(kDirectorypath)) {
		std::filesystem::create_directory(kDirectorypath);
	}

	// 書き込むJsonファイルのフルパスを合成して生成
	std::string filePath = kDirectorypath + groupName + ".json";
	// 書き込む用のファイルストリーム
	std::ofstream ofs;
	// ファイルを書き込み用に開く
	ofs.open(filePath);

	// ファイルオープンが失敗した場合ログを出して停止
	if (ofs.fail()) {
		// 読み込み失敗メッセージ
		std::string message = "Failed open data file for write.";
		// メッセージボックスを出す
		MessageBoxA(nullptr, message.c_str(), "GlobalVariables", 0);
		// ゲーム停止
		assert(0);
		return;
	}

	// ファイルにjson文字列を書き込む インデント幅4
	ofs << std::setw(4) << root << std::endl;
	// ファイルを閉じる
	ofs.close();
}

void GlobalVariables::SetValue(
    const std::string& groupName, const std::string& key, int32_t value) {
	// グループの参照を取得する
	Group& group = datas_[groupName];
	// 新しい項目のデータを設定
	Item newItem{};
	newItem.value = value;
	// 設定を行った項目をデータコンテナに追加
	group.items[key] = newItem;
}

void GlobalVariables::SetValue(const std::string& groupName, const std::string& key, float value) {
	// グループの参照を取得する
	Group& group = datas_[groupName];
	// 新しい項目のデータを設定
	Item newItem{};
	newItem.value = value;
	// 設定を行った項目をデータコンテナに追加
	group.items[key] = newItem;
}

void GlobalVariables::SetValue(
    const std::string& groupName, const std::string& key, const Vector3& value) {
	// グループの参照を取得する
	Group& group = datas_[groupName];
	// 新しい項目のデータを設定
	Item newItem{};
	newItem.value = value;
	// 設定を行った項目をデータコンテナに追加
	group.items[key] = newItem;
}
