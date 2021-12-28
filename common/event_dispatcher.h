/*********************************************************************
 * @file   event_dispatcher.h
 * @author Tomomi Murakami
 * @date   2021/12/12 15:10
 * @brief  �C�x���g�f�B�X�p�b�`���[�p�^�[��
 ********************************************************************/
#pragma once
#include <algorithm>
#include <functional>
#include <unordered_map>
#include <unordered_set>

namespace wx2
{
	// �O���錾
	template <typename EventType, typename... Args>
	class EventDispatcher;

	/**
	 * @brief  �C�x���g���X�i�[
	 * @tparam EventType �C�x���g�̎�ނ𔻕ʂ��邽�߂̃L�[�̌^
	 * @tparam CallbackArgsType �R�[���o�b�N�ɓn���������̌^
	 */
	template <typename EventType, typename... CallbackArgsType>
	class EventListener final
	{
		//! �Ή������C�x���g���s�N���X�̌^
		using EventDispatcherType = EventDispatcher<EventType, CallbackArgsType...>;
		//! �R�[���o�b�N�֐��^
		using CallbackFunc = std::function<void(CallbackArgsType ...)>;

		//! �C�x���g���s�N���X�̃A�N�Z�X������
		friend class EventDispatcherType;

	public:
		EventListener() = default;
		/**
		 * @brief �R�[���o�b�N�֐����Z�b�g����
		 * @param callback �R�[���o�b�N�֐�
		 */
		explicit EventListener(CallbackFunc callback) noexcept
			: callback_(std::move(callback)) {}

		~EventListener() = default;

		// ���[�u�ƃR�s�[������
		EventListener(const EventListener& other) = default;
		EventListener& operator=(const EventListener& other) = default;
		EventListener(EventListener&& other) = default;
		EventListener& operator=(EventListener&& other) = default;

		/**
		 * @brief �R�[���o�b�N�֐����Z�b�g����
		 * @param callback �R�[���o�b�N�֐�
		 */
		void SetCallback(const CallbackFunc& callback) noexcept
		{
			callback_ = callback;
		}

		/**
		 * @brief ����������
		 */
		void Clear() noexcept
		{
			callback_ = {};
		}

		/**
		 * @brief  �R�[���o�b�N�֐����Ăяo���\�����ׂ�
		 * @return �Ăяo���\��
		 */
		[[nodiscard]] bool HasCallback() const noexcept
		{
			return static_cast<bool>(callback_);
		}

	private:
		/**
		 * @brief �R�[���o�b�N���Ăяo��
		 * @param args �R�[���o�b�N�̈���
		 */
		void OnDispatch(const CallbackArgsType&... args) const
		{
			if (HasCallback())
			{
				callback_(args...);
			}
		}

		//! �R�[���o�b�N�֐�
		CallbackFunc callback_{};
	};

	/**
	 * @brief  �C�x���g���s�@
	 * @tparam EventType �C�x���g�̎�ނ𔻒肷�邽�߂̃L�[�̌^
	 * @tparam CallbackArgsType �R�[���o�b�N�ɓn���������̌^
	 */
	template <typename EventType, typename... CallbackArgsType>
	class EventDispatcher
	{
		//! �C�x���g���X�i�[�̌^
		using EventListenerType = EventListener<EventType, CallbackArgsType...>;

	public:
		EventDispatcher() = default;
		virtual ~EventDispatcher() = default;

		// ���[�u�ƃR�s�[������
		EventDispatcher(const EventDispatcher& other) = default;
		EventDispatcher& operator=(const EventDispatcher& other) = default;
		EventDispatcher(EventDispatcher&& other) = default;
		EventDispatcher& operator=(EventDispatcher&& other) = default;

		/**
		 * @brief �C�x���g�𔭍s����
		 * @param event �C�x���g�̎��
		 * @param args �R�[���o�b�N�ɓn������
		 */
		void Dispatch(EventType event, const CallbackArgsType&... args)
		{
			if (listeners_.empty()) 
				return;

			auto [itr, end] = listeners_.equal_range(event);
			for (; itr != end; ++itr)
			{
				if (itr->second)
					itr->second->OnDispatch(args...);
				else
					itr = listeners_.erase(itr);
			}
		}

		/**
		 * @brief �C�x���g���X�i�[��o�^����
		 * @param event �C�x���g�̎��
		 * @param eventListener �o�^����C�x���g���X�i�[
		 */
		void AppendListener(EventType event, EventListenerType& eventListener)
		{
			listeners_.emplace(event, &eventListener);
		}

		/**
		 * @brief �w�肵���C�x���g�̃C�x���g���X�i�[��o�^��������
		 * @param event �o�^��������C�x���g�̎��
		 * @param eventListener �o�^��������C�x���g���X�i�[
		 */
		void RemoveListener(EventType event, EventListenerType& eventListener)
		{
			if (listeners_.empty())
				return;
			
			std::erase_if(
				listeners_,
				[&](const auto& x)
				{
					return x.first == event && x.second == &eventListener;
				});
		}

		/**
		 * @brief �C�x���g���X�i�[��S�ēo�^����
		 */
		void Clear()
		{
			listeners_.clear();
		}

	private:
		//! �C�x���g���X�i�[�̘A�z�z��
		std::unordered_multimap<EventType, EventListenerType*> listeners_{};
	};
}
