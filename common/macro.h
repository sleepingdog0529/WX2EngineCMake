/*********************************************************************
 * @file	macro.h
 * @author	Tomomi Murakami
 * @date	2021/09/19 1:37
 * @brief	�}�N���錾
 ********************************************************************/
#pragma once

/**
 * @brief �f�t�H���g�R�s�[�R���X�g���N�^�Ƒ�����Z�q���`����
 * @param name �N���X��
 */
#define WX2_COPYABLE(name)					\
	name(const name&) = default;			\
	name& operator = (const name&) = default

 /**
  * @brief �f�t�H���g���[�u�R���X�g���N�^�ƈړ�������Z�q���`����
  * @param name �N���X��
  */
#define WX2_MOVEABLE(name)					\
	name(name&&) = default;					\
	name& operator = (name&&) = default

/**
 * @brief �R�s�[�R���X�g���N�^�Ƒ�����Z�q�̌Ăяo�����֎~����
 * @param name �N���X��
 */
#define WX2_DISALLOW_COPY(name)				\
	name(const name&) = delete;				\
	name& operator = (const name&) = delete

/**
 * @brief ���[�u�R���X�g���N�^�ƈړ�������Z�q�̌Ăяo�����֎~����
 * @param name �N���X��
 */
#define WX2_DISALLOW_MOVE(name)				\
	name(name&&) = delete;					\
	name& operator = (name&&) = delete