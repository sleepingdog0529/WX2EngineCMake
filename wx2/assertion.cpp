#include "assertion.h"
#include <format>
#include "log.h"

// �f�o�b�O���̂ݒ�`
#if !defined(NDEBUG)

// BOOST_ASSERT���̓�����`
namespace boost
{
	void assertion_failed(
		const char* expr,
		const char* function,
		const char* file,
		const long line)
	{
		// �o�͗p���b�Z�[�W
		auto out = std::format(
			"\n"
			"==============< Assertion failed ! >==============\n"
			"Expression: {}\n"
			"File: {}\n"
			"Function: {}\n"
			"Line: {}\n"
			"==================================================\n",
			expr, file, function, line);

		// VisualStudio��ɏo��
		OutputDebugString(out.c_str());

		// �G���[���O�ɏo��
		WX2_LOG_ERROR("\n{}", out);

		// �u���[�N�|�C���g�𔭐�������
		__debugbreak();
	}

	void assertion_failed_msg(
		char const* expr,
		char const* msg,
		char const* function,
		char const* file,
		const long line)
	{
		// �o�͗p���b�Z�[�W
		auto out = std::format(
			"\n"
			"==============< Assertion failed ! >==============\n"
			"Expression: {}\n"
			"Message: {}\n"
			"File: {}\n"
			"Function: {}\n"
			"Line: {}\n"
			"==================================================\n",
			expr, msg, file, function, line);

		// VisualStudio��ɏo��
		OutputDebugString(out.c_str());

		// �G���[���O�ɏo��
		WX2_LOG_ERROR("\n{}", out);

		// �u���[�N�|�C���g�𔭐�������
		__debugbreak();
	}
}

#endif