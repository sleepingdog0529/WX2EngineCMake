#include "log.h"
#include <filesystem>
#include <ranges>
#include <chrono>
#pragma warning(push, 0) 
#include <spdlog/sinks/stdout_color_sinks.h>
#include <spdlog/sinks/basic_file_sink.h>
#pragma warning(pop)

namespace wx2
{
	Logger::Logger() noexcept
	{
		namespace fs = std::filesystem;
		namespace vs = std::views;
		namespace ch = std::chrono;

		// ���O���i�[����f�B���N�g��
		const fs::path dir(FILE_DIR);
		if (!fs::is_directory(dir))
		{
			WX2_LOG_INFO("�w�肳�ꂽ���O�i�[�p�̃f�B���N�g���͑��݂��܂���B�V���ɍ쐬���܂��B�p�X: {}", dir.string());
			fs::create_directory(dir);
		}

		// �f�B���N�g�����̃��O�t�@�C�������܂������ɕۂ�
		if (std::vector logFiles(fs::directory_iterator(dir), {}); logFiles.size() >= MAX_FILE)
		{
			// �w�萔��胍�O�t�@�C����������ΌÂ����ɏ���
			for (const auto& f : vs::counted(logFiles.begin(), logFiles.size() - (MAX_FILE - 1)))
			{
				fs::remove(f);
			}
		}

		// �����̌��ݎ������擾
		const auto now = ch::system_clock::now();
		const ch::sys_seconds nowSec = ch::floor<ch::seconds>(now);
		const ch::zoned_time zonedTime{ "Asia/Tokyo", nowSec };

		// ���O�t�@�C���̐�����p�X
		const fs::path path = dir / std::format(FILE_NAME, zonedTime);

		// ���O�̏o�͐��ݒ�
		std::vector<spdlog::sink_ptr> loggerSink;
		loggerSink.emplace_back(std::make_shared<spdlog::sinks::stdout_color_sink_mt>());
		loggerSink.emplace_back(std::make_shared<spdlog::sinks::basic_file_sink_mt>(path.string(), true));

		// ���K�[���쐬
		logger_ = std::make_shared<spdlog::logger>("logger", loggerSink.begin(), loggerSink.end());
		logger_->set_level(spdlog::level::trace);
		logger_->flush_on(spdlog::level::trace);

		// �f�t�H���g�Ɏw�肵�ČĂяo����e�Ղɂ���
		set_default_logger(logger_);
	}

	Logger::~Logger() noexcept
	{
		// ���K�[���I��������
		spdlog::shutdown();
	}
}