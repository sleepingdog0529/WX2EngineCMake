/*********************************************************************
 * @file   safe_release.h
 * @author Tomomi Murakami
 * @date   2021/11/29 15:34
 * @brief  null�`�F�b�N�̏���
 ********************************************************************/
#pragma once

namespace wx2
{
	namespace detail
	{
		//! �A�b�p�[�P�[�X��Release�֐��������Ă��邩���肷��
		template <class T>
		concept HasReleaseUpperCase = requires (T x)
		{
			x.Release();
		};

		//! ���[���[�P�[�X��release�֐��������Ă��邩���肷��
		template <class T>
		concept HasReleaseLowerCase = requires (T x)
		{
			x.release();
		};
	}

	/**
	 * @brief  null�`�F�b�N���s���������ŃA�b�p�[�P�[�X��Release�֐����Ăяo���������
	 * @tparam T ����Ώۂ̌^
	 * @param  x ����Ώ�
	 */
	template <detail::HasReleaseUpperCase T>
	inline void SafeRelease(T*& x) noexcept
	{
		if (x)
		{
			x->Release();
			x = nullptr;
		}
	}

	/**
	 * @brief  null�`�F�b�N���s���������Ń��[���[�P�[�X��release�֐����Ăяo���������
	 * @tparam T ����Ώۂ̌^
	 * @param  x ����Ώ�
	 */
	template <detail::HasReleaseLowerCase T>
	inline void SafeRelease(T*& x) noexcept
	{
		if (x)
		{
			x->release();
			x = nullptr;
		}
	}

	template<typename T = void>
	struct SafeDeleter
	{
		void operator()(T* x) const
		{
			SafeRelease(x);
		}
	};
}
