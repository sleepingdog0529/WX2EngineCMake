/*********************************************************************
 * @file	log.h
 * @author	Tomomi Murakami
 * @date	2021/09/18 22:35
 * @brief	���O���o�́E�L�^����
 ********************************************************************/
#pragma once
#pragma warning(push, 0)
#include <spdlog/spdlog.h>
#include "macro.h"
#pragma warning(pop)

/**
 * @brief �ǐՃ��O���o�͂���
 * @param �t�H�[�}�b�g�������b�Z�[�W�A����
 */
#define WX2_LOG_TRACE(...)    spdlog::trace(__VA_ARGS__)
/**
 * @brief �ڍ׃��O���o�͂���
 * @param �t�H�[�}�b�g�������b�Z�[�W�A����
 */
#define WX2_LOG_INFO(...)     spdlog::info(__VA_ARGS__)
/**
 * @brief �x�����O���o�͂���
 * @param �t�H�[�}�b�g�������b�Z�[�W�A����
 */
#define WX2_LOG_WARN(...)     spdlog::warn(__VA_ARGS__)
/**
 * @brief �G���[���O���o�͂���
 * @param �t�H�[�}�b�g�������b�Z�[�W�A����
 */
#define WX2_LOG_ERROR(...)    spdlog::error(__VA_ARGS__)
/**
 * @brief �d��ȃG���[�̃��O���o�͂���
 * @param �t�H�[�}�b�g�������b�Z�[�W�A����
 */
#define WX2_LOG_CRITICAL(...) spdlog::critical(__VA_ARGS__)

namespace wx2
{
	/**
	 * @brief ���O�̊Ǘ����s���N���X
	 */
	class Logger final
	{
	private:
		//! ���O�t�@�C���̍ő吔
		static constexpr std::size_t MAX_FILE = 3; 
		//! ���O�t�@�C����u���f�B���N�g��
		static constexpr const char* FILE_DIR = ".\\log";	
		//! ���O�t�@�C���̖����t�H�[�}�b�g
		static constexpr const char* FILE_NAME = "{:%Y-%m-%d-%H-%M-%S}.log";	

	public:
		//! @brief ���K�[�̏������A���O�t�@�C���̊Ǘ����s��
		Logger() noexcept;

		//! @brief ���K�[�̏I������
		~Logger() noexcept;

		WX2_DISALLOW_COPY(Logger);
		WX2_DISALLOW_MOVE(Logger);

	private:
		//! ���K�[�{��
		std::shared_ptr<spdlog::logger> logger_;
	};
}