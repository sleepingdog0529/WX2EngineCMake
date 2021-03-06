/*********************************************************************
 * @file   file_dialog.h
 * @author Tomomi Murakami
 * @date   2021/12/03 20:33
 * @brief  ファイル選択ダイアログ
 ********************************************************************/
#pragma once

#include <filesystem>
#include <string_view>
#define STRICT
#define WIN32_LEAN_AND_MEAN
#define NOMINMAX
#include <Windows.h>
#include <commdlg.h>

namespace wx2
{
	/**
	 * @brief  ファイルを開くダイアログを表示する
	 * @param  filter 表示するファイルのフィルター '\0'で項目を区切り'\0'が末尾に2つなければならない
	 * @return 選択したファイルパス
	 * @note   https://docs.microsoft.com/en-us/windows/win32/api/commdlg/ns-commdlg-openfilenamea
	 */
	inline std::filesystem::path OpenFileDialog(const std::string_view filter)
	{
		// 最後に開いたディレクトリパスを取得する
		std::string fileDir(MAX_PATH, '\0');
		std::string currentDir(MAX_PATH, '\0');
		GetCurrentDirectory(MAX_PATH, currentDir.data());

		// ファイルダイアログの設定
		OPENFILENAME ofn{};
		ofn.lStructSize = sizeof(OPENFILENAME);
		ofn.lpstrInitialDir = currentDir.empty() ? currentDir.data() : nullptr;	// 最初に開くディレクトリパス
		ofn.lpstrFile = fileDir.data();
		ofn.nMaxFile = static_cast<DWORD>(sizeof(char) * fileDir.size());
		ofn.lpstrFilter = filter.data();	// フィルター文字列のポインタ
		ofn.nFilterIndex = 1;				// 初期状態で選択するフィルタの番号(1からカウント)
		ofn.Flags = OFN_PATHMUSTEXIST | OFN_FILEMUSTEXIST | OFN_NOCHANGEDIR;

		if (!GetOpenFileName(&ofn))
			return "";

		return ofn.lpstrFile;
	}

	/**
	 * @brief  ファイルを保存するダイアログを表示する
	 * @param  filter 表示するファイルのフィルター '\0'で項目を区切り'\0'が末尾に2つなければならない
	 * @return 作成 or 上書き先のファイルパス
	 * @note   https://docs.microsoft.com/en-us/windows/win32/api/commdlg/ns-commdlg-openfilenamea
	 */
	inline std::filesystem::path SaveFileDialog(const std::string_view filter)
	{
		// 最後に開いたディレクトリパスを取得する
		std::string fileDir(MAX_PATH, '\0');
		std::string currentDir(MAX_PATH, '\0');
		GetCurrentDirectory(MAX_PATH, currentDir.data());

		// ファイルダイアログの設定
		OPENFILENAME ofn{};
		ofn.lStructSize = sizeof(OPENFILENAME);
		ofn.lpstrInitialDir = currentDir[0] ? currentDir.data() : nullptr;	// 最初に開くディレクトリパス
		ofn.lpstrFile = fileDir.data();
		ofn.nMaxFile = static_cast<DWORD>(sizeof(char) * fileDir.size());
		ofn.lpstrFilter = filter.data();	// フィルター文字列のポインタ
		ofn.nFilterIndex = 1;				// 初期状態で選択するフィルタの番号(1からカウント)
		ofn.Flags = OFN_PATHMUSTEXIST | OFN_OVERWRITEPROMPT | OFN_NOCHANGEDIR;

		if (!::GetSaveFileName(&ofn))
			return "";

		return ofn.lpstrFile;
	}
}
