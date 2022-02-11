#include "layer_stack.h"
#include <algorithm>

namespace wx2
{
	void LayerStack::PopLayer(const LayerPtr& layer)
	{
		// ���C���[�X�^�b�N�̒ʏ탌�C���[�͈̔͂���Ώۃ��C���[�̃C�e���[�^��T��
		const auto itr = std::find(layers_.begin(), layers_.begin() + layerInsertIndex_, layer);
		if (itr != layers_.begin() + layerInsertIndex_)
		{
			// �Ώۃ��C���[�̃|�b�v���̃R�[���o�b�N���Ăяo��
			itr->get()->OnDetach();

			// ���C���[�X�^�b�N����|�b�v
			layers_.erase(itr);

			// �ʏ탌�C���[�̑}���ʒu���f�N�������g
			--layerInsertIndex_;
		}
	}

	void LayerStack::PopOverlay(const LayerPtr& overlay)
	{
		// ���C���[�X�^�b�N�̃I�[�o�[���C���C���[�͈̔͂���Ώۃ��C���[�̃C�e���[�^��T��
		const auto itr = std::find(layers_.begin() + layerInsertIndex_, layers_.end(), overlay);
		if (itr != layers_.begin() + layerInsertIndex_)
		{
			// �Ώۃ��C���[�̃|�b�v���̃R�[���o�b�N���Ăяo��
			itr->get()->OnDetach();

			// ���C���[�X�^�b�N����|�b�v
			layers_.erase(itr);
		}
	}
}
