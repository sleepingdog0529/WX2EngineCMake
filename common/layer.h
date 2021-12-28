/*********************************************************************
 * @file   layer.h
 * @author Tomomi Murakami
 * @date   2021/12/14 14:20
 * @brief  ���C���[�C���^�[�t�F�C�X
 ********************************************************************/
#pragma once
#include <string>
#include "macro.h"

namespace wx2
{
	/**
	 * @brief ���C���[�̃C���^�[�t�F�C�X�N���X
	 */
	class ILayer
	{
	public:
		/**
		 * @brief  ���C���[���̏�����
		 * @param  layerName ���C���[�̖��O
		 */
		explicit ILayer(std::string layerName)
			: layerName_(std::move(layerName)) {}
		virtual ~ILayer() = default;

		// �R�s�[�ƃ��[�u�̋֎~
		WX2_DISALLOW_COPY(ILayer);
		WX2_DISALLOW_MOVE(ILayer);

		//! @brief ���C���[�X�^�b�N�Ƀv�b�V�����ꂽ�Ƃ��̃R�[���o�b�N
		virtual void OnAttach() {}
		//! @brief ���C���[�X�^�b�N����|�b�v���ꂽ�Ƃ��̃R�[���o�b�N
		virtual void OnDetach() {}

		/**
		 * @brief  ���C���[���̎擾
		 * @return ���C���[��������
		 */
		[[nodiscard]] const std::string& GetName() const noexcept { return layerName_; }

	private:
		//! ���C���[��
		std::string layerName_;
	};
}
