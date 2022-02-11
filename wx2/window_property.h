/*********************************************************************
 * @file	window_property.h
 * @author	Tomomi Murakami
 * @date	2021/09/20 19:19
 * @brief	�E�B���h�E���
 ********************************************************************/
#pragma once
#pragma warning(push, 0)
#include <cereal/cereal.hpp>
#include <cereal/archives/json.hpp>
#pragma warning(pop)

namespace wx2 
{
	/**
	 * @brief �E�B���h�E���
	 */
	struct WindowProperty
	{
	public:
		std::string title;		//! �E�B���h�E�̃^�C�g��
		int x, y;				//! �E�B���h�E����̍��W
		int width, height;		//! �E�B���h�E�̕�
		unsigned long style;	//! �E�B���h�E�X�^�C���̃t���O
		unsigned long exStyle;	//! �g���E�B���h�E�X�^�C���̃t���O
		bool maximized;			//! �ő剻����Ă��邩
		bool fullscreen;		//! �S��ʉ�����Ă��邩

		/**
		 * @brief  �E�B���h�E�̃A�X�y�N�g���Ԃ�
		 * @return �A�X�y�N�g��
		 */
		[[nodiscard]] float AspectRatio() const noexcept
		{
			return static_cast<float>(width) / static_cast<float>(height);
		}

	private:
		// �V���A�������C�u�����̃A�N�Z�X������
		friend cereal::access;

		//! @brief �V���A���C�Y�p���\�b�h
		template <class Archive>
		void serialize(Archive& archive) noexcept
		{
			archive(
				CEREAL_NVP(title),
				CEREAL_NVP(x),
				CEREAL_NVP(y),
				CEREAL_NVP(width),
				CEREAL_NVP(height),
				CEREAL_NVP(style),
				CEREAL_NVP(exStyle),
				CEREAL_NVP(maximized),
				CEREAL_NVP(fullscreen));
		}
	};
}