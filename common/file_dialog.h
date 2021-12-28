/*********************************************************************
 * @file   file_dialog.h
 * @author Tomomi Murakami
 * @date   2021/12/03 20:33
 * @brief  �t�@�C���I���_�C�A���O
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
	 * @brief  �t�@�C�����J���_�C�A���O��\������
	 * @param  filter �\������t�@�C���̃t�B���^�[ '\0'�ō��ڂ���؂�'\0'��������2�Ȃ���΂Ȃ�Ȃ�
	 * @return �I�������t�@�C���p�X
	 * @note   https://docs.microsoft.com/en-us/windows/win32/api/commdlg/ns-commdlg-openfilenamea
	 */
	inline std::filesystem::path OpenFileDialog(const std::string_view filter)
	{
		// �Ō�ɊJ�����f�B���N�g���p�X���擾����
		std::string fileDir(MAX_PATH, '\0');
		std::string currentDir(MAX_PATH, '\0');
		GetCurrentDirectory(MAX_PATH, currentDir.data());

		// �t�@�C���_�C�A���O�̐ݒ�
		OPENFILENAME ofn{};
		ofn.lStructSize = sizeof(OPENFILENAME);
		ofn.lpstrInitialDir = currentDir.empty() ? currentDir.data() : nullptr;	// �ŏ��ɊJ���f�B���N�g���p�X
		ofn.lpstrFile = fileDir.data();
		ofn.nMaxFile = static_cast<DWORD>(sizeof(char) * fileDir.size());
		ofn.lpstrFilter = filter.data();	// �t�B���^�[������̃|�C���^
		ofn.nFilterIndex = 1;				// ������ԂőI������t�B���^�̔ԍ�(1����J�E���g)
		ofn.Flags = OFN_PATHMUSTEXIST | OFN_FILEMUSTEXIST | OFN_NOCHANGEDIR;

		if (!GetOpenFileName(&ofn))
			return "";

		return ofn.lpstrFile;
	}

	/**
	 * @brief  �t�@�C����ۑ�����_�C�A���O��\������
	 * @param  filter �\������t�@�C���̃t�B���^�[ '\0'�ō��ڂ���؂�'\0'��������2�Ȃ���΂Ȃ�Ȃ�
	 * @return �쐬 or �㏑����̃t�@�C���p�X
	 * @note   https://docs.microsoft.com/en-us/windows/win32/api/commdlg/ns-commdlg-openfilenamea
	 */
	inline std::filesystem::path SaveFileDialog(const std::string_view filter)
	{
		// �Ō�ɊJ�����f�B���N�g���p�X���擾����
		std::string fileDir(MAX_PATH, '\0');
		std::string currentDir(MAX_PATH, '\0');
		GetCurrentDirectory(MAX_PATH, currentDir.data());

		// �t�@�C���_�C�A���O�̐ݒ�
		OPENFILENAME ofn{};
		ofn.lStructSize = sizeof(OPENFILENAME);
		ofn.lpstrInitialDir = currentDir[0] ? currentDir.data() : nullptr;	// �ŏ��ɊJ���f�B���N�g���p�X
		ofn.lpstrFile = fileDir.data();
		ofn.nMaxFile = static_cast<DWORD>(sizeof(char) * fileDir.size());
		ofn.lpstrFilter = filter.data();	// �t�B���^�[������̃|�C���^
		ofn.nFilterIndex = 1;				// ������ԂőI������t�B���^�̔ԍ�(1����J�E���g)
		ofn.Flags = OFN_PATHMUSTEXIST | OFN_OVERWRITEPROMPT | OFN_NOCHANGEDIR;

		if (!::GetSaveFileName(&ofn))
			return "";

		return ofn.lpstrFile;
	}
}
