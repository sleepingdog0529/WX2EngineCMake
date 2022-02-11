/*********************************************************************
 * @file   string_helper.h
 * @author Tomomi Murakami
 * @date   2021/09/19 2:57
 * @brief  ������^�̃w���p�[
*********************************************************************/
#pragma once

namespace wx2
{
	/**
	 * @brief  string_view��string�ɕϊ�����
	 * @param  strv ������r���[
	 * @return �ϊ���̕�����
	 */
	inline std::string ToString(std::string_view strv) noexcept
	{
		return { strv.data(), strv.size() };
	}

	/**
	 * @brief  �}���`�o�C�g����������C�h������ɕϊ�����
	 * @param  str �ϊ��Ώۂ̃}���`�o�C�g������
	 * @return �ϊ����ꂽ���C�h������
	 */
	inline std::wstring Utf8ToUtf16(const std::string_view str) noexcept
	{
		// �ϊ��Ώۂ̕����񂪋�̏ꍇ
		if (str.empty() || str[0] == '\0')
			return {};

		// �ϊ��ɕK�v�ȃT�C�Y���m��
		std::wstring out(str.size() * sizeof(char), '\0');

		// ���C�h������ւ̕ϊ�
		if (::mbstowcs_s(nullptr, out.data(), out.size() + 1, str.data(), _TRUNCATE) != 0)
			return {};

		// �I�[������̕s�v�ȕ��������
		out.resize(std::char_traits<wchar_t>::length(out.data()));

		return out;
	}

	/**
	 * @brief  ���C�h��������}���`�o�C�g������ɕϊ�����
	 * @param  wstr �ϊ��Ώۂ̃��C�h������
	 * @return �ϊ����ꂽ�}���`�o�C�g������
	 */
	inline std::string Utf16ToUtf8(const std::wstring_view wstr) noexcept
	{
		// �ϊ��Ώۂ̕����񂪋�̏ꍇ
		if (wstr.empty() || wstr[0] == L'\0')
			return {};

		// �ϊ��ɕK�v�ȃT�C�Y���m��
		std::string out(wstr.size() * sizeof(wchar_t), '\0');

		// �}���`�o�C�g������ւ̕ϊ�
		if (::wcstombs_s(nullptr, out.data(), out.size() + 1, wstr.data(), _TRUNCATE) != 0)
			return {};

		// �I�[������̕s�v�ȕ��������
		out.resize(std::char_traits<char>::length(out.data()));

		return out;
	}
}