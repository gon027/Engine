#pragma once
#include <memory>

namespace engine {

	struct GlyphData {
		int cellIncX;            // �����S�̂̕�
		int height;              // �����S�̂̍���
		int ascent;              // �����̃x�[�X���C�������ԏ�܂� 
		int descent;             // �����̃x�[�X���C�������ԉ��܂� 
		int glyphOriginX;        // �����̊J�n�ʒu��X���W	    
		int glyphOriginY;        // �����̊J�n�ʒu��Y���W
		unsigned int blackBoxX;  // �����̉���
		unsigned int blackBoxY;  // �����̏c��
		unsigned char* ptr;      // �f�[�^
	};

}