/*********************************************************************
 * @file   timer.h
 * @author Tomomi Murakami
 * @date   2021/11/28 10:17
 * @brief  �^�C�}�[
*********************************************************************/
#pragma once
#include <chrono>
#include "macro.h"

namespace wx2
{
	template <class Units = std::chrono::milliseconds>
	class Timer final
	{
	public:
		Timer() noexcept
			: start_(std::chrono::system_clock::now())
		{
		}

		~Timer() = default;

		WX2_DISALLOW_COPY(Timer);
		WX2_DISALLOW_MOVE(Timer);

		void Start() noexcept
		{
			start_ = std::chrono::system_clock::now();
		}

		[[nodiscard]] long long ElapcedTime() const noexcept
		{
			return std::chrono::duration_cast<Units>(
				std::chrono::system_clock::now() - start_).count();
		}

	private:
		std::chrono::time_point<std::chrono::system_clock> start_{};
	};
}
