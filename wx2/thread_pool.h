/*********************************************************************
 * @file	thread_pool.h
 * @author	Tomomi Murakami
 * @date	2021/06/27 17:48
 * @brief   �X���b�h�v�[��
*********************************************************************/
#pragma once
#include <deque>
#include <future>
#include <thread>
#include <optional>
#include "macro.h"

namespace wx2
{
	/**
	 * @brief  �X���b�h�v�[���N���X
	 */
	class ThreadPool final
	{
	private:
		// �ғ����
		enum class Status
		{
			Standby, Working, Joining,
		};

	public:
		/**
		 * @brief  ���蓖�Ă�X���b�h�����w�肵�ăX���b�h������������
		 * @param  threadCount ���蓖�Ă�X���b�h��
		 */
		explicit ThreadPool(std::size_t threadCount = std::thread::hardware_concurrency()) noexcept;
		//! @brief  �X���b�h��Join���� 
		~ThreadPool() noexcept;
		
		WX2_DISALLOW_COPY(ThreadPool);
		WX2_DISALLOW_MOVE(ThreadPool);

		/**
		 * @brief  �^�X�N�L���[�Ɋ֐����v�b�V������
		 * @tparam F �^�X�N�֐��^
		 * @tparam Args �����^
		 * @param  function �^�X�N�֐�
		 * @param  args ����
		 * @return ���L��Ԃ�����������
		 */
		template<typename F, typename... Args>
		auto Enqueue(F&& function, Args&&... args) noexcept
			-> std::future<std::invoke_result_t<F, Args...>>
		{
			// �֐��̖߂�l�^
			using TaskReturnType = std::invoke_result_t<F, Args...>;
			// �񓯊����s����֐���o�^�����^
			using TaskType = std::packaged_task<TaskReturnType()>;

			// ���L��Ԃ����������^�X�N���i�[����
			auto task = std::make_shared<TaskType>(std::bind(std::forward<F>(function), std::forward<Args>(args)...));
			// ���L��Ԃ����������ʂ��擾����
			auto result = task->get_future();

			// �^�X�N�L���[�Ƀ^�X�N���v�b�V��
			{
				std::lock_guard<std::mutex> lock(mutex_);
				taskQueue_.emplace_back([task]() { (*task)(); });
			}

			// �X���b�h�̉ғ��ĊJ
			condition_.notify_all();

			return result;
		}

		/**
		 * @brief  �g�p���Ă���X���b�h����Ԃ�
		 * @return �X���b�h��
		 */
		[[nodiscard]] std::size_t NumThread() const { return threadCount_; }

	private:
		//! @brief �X���b�h�Ƀ^�X�N��^����
		void Join() noexcept;

		/**
		 * @brief  �^�X�N���^�X�N�L���[����|�b�v����
		 * @return �^�X�N
		 */
		[[nodiscard]] std::optional<std::function<void()>> Dequeue();

		Status status_;						//! �ғ����
		std::size_t threadCount_;			//! �g�p�X���b�h��
		std::vector<std::thread> threads_;	//! �X���b�h���X�g
		std::mutex mutex_;					//! �r����������b�N����
		std::condition_variable condition_;				//! �^�X�N�L���[�̏��
		std::deque<std::function<void()>> taskQueue_;	//! �^�X�N�L���[
	};

}
