#include "PMD.hpp"

mmd::PMD::PMD()
	:m_Mesh(NULL)
{
}

mmd::PMD::~PMD()
{
	delete m_Mesh;
}

bool mmd::PMD::Create(BinaryReader& reader)
{
	std::string magic;
	magic.resize(3);
	reader.read(&magic[0], 3);
	if (magic != "Pmd") return false;

	// �w�b�_�ǂݍ���.
	reader.read(m_Version);
	m_ModelName.resize(20);
	reader.read(&m_ModelName[0], 20);
	m_Comment.resize(256);
	reader.read(&m_Comment[0], 256);

	// ���_���X�g�ǂݍ���.
	uint32 count;
	reader.read(count);

	MeshData data;
	data.vertices.resize(count);
	for (uint32 i = 0; i < count; i++)
	{
		MeshVertex& vertex = data.vertices[i];

		reader.read(vertex.position.x);
		reader.read(vertex.position.y);
		reader.read(vertex.position.z);
		reader.read(vertex.normal.x);
		reader.read(vertex.normal.y);
		reader.read(vertex.normal.z);
		reader.read(vertex.texcoord.x);
		reader.read(vertex.texcoord.y);
		// �{�[���n�A�G�b�W�Ɋւ����񂪑���.
		// �ǂݔ�΂�.
		reader.skip(6);
	}

	// �ʒ��_���X�g�ǂݍ���.
	reader.read(count);
	data.indices.resize(count);
	for (uint32 i = 0; i < count; i++)
	{
		short indice;
		reader.read(indice);
		data.indices[i] = indice;
	}

	// �ގ����X�g�ǂݍ���.
	reader.read(count);
	m_Materials.resize(count);
	for (uint32 i = 0; i < count; i++)
	{
		m_Materials[i].Create(reader);
	}
	m_Mesh = new Mesh(data);
	return true;
}

void mmd::PMD::Draw()
{
	int indicesCount = 0;
	for (size_t i = 0; i < m_Materials.size(); i++)
	{
		mmd::Material& material = m_Materials[i];
		if (TextureAsset::IsRegistered(material.m_Texture))
		{
			m_Mesh->drawSubset(indicesCount, material.m_IndicesCount, TextureAsset(material.m_Texture), material.m_Material.diffuse);
		}
		else
		{
			m_Mesh->drawSubset(indicesCount, material.m_IndicesCount, material.m_Material.diffuse);
		}
		indicesCount += material.m_IndicesCount;
	}
}
