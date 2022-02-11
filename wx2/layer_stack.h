/*********************************************************************
 * @file   layer_stack.h
 * @author Tomomi Murakami
 * @date   2021/12/14 15:07
 * @brief  ���C���[�X�^�b�N
 ********************************************************************/
#pragma once
#include "layer.h"
#include <vector>
#include <memory>

namespace wx2
{
	/**
	 * @brief ���C���[�X�^�b�N�N���X
	 */
	class LayerStack final
	{
		//! ���C���[�̋��L�|�C���^
		using LayerPtr = std::shared_ptr<ILayer>;

	public:
		LayerStack() = default;
		~LayerStack() = default;

		WX2_DISALLOW_COPY(LayerStack);
		WX2_DISALLOW_MOVE(LayerStack);

		/**
		 * @brief  ���C���[���X�^�b�N���ɒ��ڍ\�z����
		 * @tparam LayerType ���C���[�^
		 * @tparam Args �R���X�g���N�^�����^
		 * @param  layerName ���C���[�̖��O
		 * @param  args �R���X�g���N�^����
		 * @return �\�z���ꂽ���C���[�̋��L�|�C���^
		 */
		template <class LayerType, typename... Args>
		std::shared_ptr<LayerType> EmplaceLayer(const std::string& layerName, Args&&... args)
		{
			// �ʏ탌�C���[�̑}���ʒu�Ƀ��C���[�𒼐ڍ\�z
			const auto itr = layers_.emplace(
				layers_.begin() + layerInsertIndex_,
				std::make_shared<LayerType>(layerName, std::forward<Args>(args)...));

			// �ʏ탌�C���[�̑}���ʒu���C���N�������g
			++layerInsertIndex_;

			// �\�z�������C���[�̋��L�|�C���^��Ԃ�
			return *itr;
		}

		/**
		 * @brief  �I�[�o�[���C���C���[���X�^�b�N���ɒ��ڍ\�z����
		 * @tparam OverlayType ���C���[�^
		 * @tparam Args �R���X�g���N�^�����^
		 * @param  layerName ���C���[�̖��O
		 * @param  args �R���X�g���N�^����
		 * @return �\�z���ꂽ���C���[�̋��L�|�C���^
		 */
		template <class OverlayType, typename... Args>
		std::shared_ptr<OverlayType> EmplaceOverlay(const std::string& layerName, Args&&... args)
		{
			// ���C���[���X�g�����Ƀ��C���[�𒼐ڍ\�z
			const auto itr = layers_.emplace_back(
				std::make_shared<OverlayType>(layerName, std::forward<Args>(args)...));

			// �\�z�������C���[�̋��L�|�C���^��Ԃ�
			return *itr;
		}

		/**
		 * @brief  ���C���[�����C���[�X�^�b�N����|�b�v����
		 * @param  layer ������郌�C���[�̋��L�|�C���^
		 */
		void PopLayer(const LayerPtr& layer);

		/**
		 * @brief  �I�[�o�[���C���C���[�����C���[�X�^�b�N����|�b�v����
		 * @param  overlay ������郌�C���[�̋��L�|�C���^
		 */
		void PopOverlay(const LayerPtr& overlay);

	private:
		//! ���C���[�X�^�b�N
		std::vector<LayerPtr> layers_{};
		//! �ʏ탌�C���[�̑}���ʒu
		std::size_t layerInsertIndex_{};
	};	
}
