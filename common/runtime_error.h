/*********************************************************************
 * @file   runtime_error.h
 * @author Tomomi Murakami
 * @date   2021/11/23 02:01
 * @brief  ���s���̗�O
 ********************************************************************/
#pragma once
#include <format>
#include <source_location>

/**
 * @brief �������莮���U�ł������Ȃ烉���^�C���G���[���X���[����
 * @param expr ���莮
 * @param __VA_ARGS__ �t�H�[�}�b�g���b�Z�[�W
 */
#define WX2_RUNTIME_ERROR_IF_FAILED(expr, ...)	\
	do											\
	{											\
		if (!(expr))							\
		{										\
			throw wx2::RuntimeError(			\
				#expr,							\
				std::format(__VA_ARGS__));		\
		}										\
	} while(0)

namespace wx2
{
	class RuntimeError
	{
	public:
		/**
		 * @brief �����^�C���G���[�̏�����
		 * @param expr ���莮������
		 * @param msg �G���[���
		 * @param location �\�[�X��̃G���[�����ʒu ���K���f�t�H���g�������g�p���邱��
		 */
		RuntimeError(
			const std::string& expr,
			const std::string& msg,
			const std::source_location& location = std::source_location::current()) noexcept
		{
			// �G���[���b�Z�[�W
			what_ = std::format(
				"\n"
				"==============< Exception thrown ! >==============\n"
				"Message: {}\n"
				"Expression: {}\n"
				"File: {}\n"
				"Function: {}\n"
				"Line: {}\n"
				"==================================================\n",
				msg,						// �w�肵�����b�Z�[�W
				expr,						// �G���[�̔��莮
				location.file_name(),		// �G���[�����������t�@�C����
				location.function_name(),	// �G���[�����������֐���
				location.line());			// �G���[�����������s
		}

		/**
		 * @brief  ��O�̃G���[���b�Z�[�W���擾
		 * @return �G���[���b�Z�[�W
		 */
		[[nodiscard]] const std::string& what() const noexcept
		{
			return what_;
		}

	private:
		//! ��O�̏ڍ�
		std::string what_{};
	};
}