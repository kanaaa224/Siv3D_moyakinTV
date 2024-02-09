#pragma once

#include <string>
#include <Siv3D.hpp>
#include "PMD.hpp"

namespace mmd
{
	class Model
	{
	public:
		Model();
		virtual ~Model();

		// ���f���̐���
		// filename : PMD�t�@�C�����w��
		bool Create(const FilePath& filename);
		// �X�V
		void Update();
		// �`��
		void Draw();


	private:
		PMD m_Pmd;
	};
}
