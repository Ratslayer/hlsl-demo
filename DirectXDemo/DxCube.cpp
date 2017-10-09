#include "DxCube.h"


DxCube::DxCube()
{
	//this is code taken directly from MS tutorial
	MeshVertex tempVertices[] =
	{
		{ XMFLOAT3(-1.0f, 1.0f, -1.0f), XMFLOAT2(1.0f, 0.0f) },
		{ XMFLOAT3(1.0f, 1.0f, -1.0f), XMFLOAT2(0.0f, 0.0f) },
		{ XMFLOAT3(1.0f, 1.0f, 1.0f), XMFLOAT2(0.0f, 1.0f) },
		{ XMFLOAT3(-1.0f, 1.0f, 1.0f), XMFLOAT2(1.0f, 1.0f) },

		{ XMFLOAT3(-1.0f, -1.0f, -1.0f), XMFLOAT2(0.0f, 0.0f) },
		{ XMFLOAT3(1.0f, -1.0f, -1.0f), XMFLOAT2(1.0f, 0.0f) },
		{ XMFLOAT3(1.0f, -1.0f, 1.0f), XMFLOAT2(1.0f, 1.0f) },
		{ XMFLOAT3(-1.0f, -1.0f, 1.0f), XMFLOAT2(0.0f, 1.0f) },

		{ XMFLOAT3(-1.0f, -1.0f, 1.0f), XMFLOAT2(0.0f, 1.0f) },
		{ XMFLOAT3(-1.0f, -1.0f, -1.0f), XMFLOAT2(1.0f, 1.0f) },
		{ XMFLOAT3(-1.0f, 1.0f, -1.0f), XMFLOAT2(1.0f, 0.0f) },
		{ XMFLOAT3(-1.0f, 1.0f, 1.0f), XMFLOAT2(0.0f, 0.0f) },

		{ XMFLOAT3(1.0f, -1.0f, 1.0f), XMFLOAT2(1.0f, 1.0f) },
		{ XMFLOAT3(1.0f, -1.0f, -1.0f), XMFLOAT2(0.0f, 1.0f) },
		{ XMFLOAT3(1.0f, 1.0f, -1.0f), XMFLOAT2(0.0f, 0.0f) },
		{ XMFLOAT3(1.0f, 1.0f, 1.0f), XMFLOAT2(1.0f, 0.0f) },

		{  XMFLOAT3(-1.0f, -1.0f, -1.0f), XMFLOAT2(0.0f, 1.0f) },
		{ XMFLOAT3(1.0f, -1.0f, -1.0f), XMFLOAT2(1.0f, 1.0f) },
		{ XMFLOAT3(1.0f, 1.0f, -1.0f), XMFLOAT2(1.0f, 0.0f) },
		{ XMFLOAT3(-1.0f, 1.0f, -1.0f), XMFLOAT2(0.0f, 0.0f) },

		{ XMFLOAT3(-1.0f, -1.0f, 1.0f), XMFLOAT2(1.0f, 1.0f) },
		{ XMFLOAT3(1.0f, -1.0f, 1.0f), XMFLOAT2(0.0f, 1.0f) },
		{ XMFLOAT3(1.0f, 1.0f, 1.0f), XMFLOAT2(0.0f, 0.0f) },
		{ XMFLOAT3(-1.0f, 1.0f, 1.0f), XMFLOAT2(1.0f, 0.0f) },
	};
	WORD tempIndices[] =
	{
		3,1,0,
		2,1,3,

		6,4,5,
		7,4,6,

		11,9,8,
		10,9,11,

		14,12,13,
		15,12,14,

		19,17,16,
		18,17,19,

		22,20,21,
		23,20,22
	};
	for (int i = 0; i < 12; i++)
	{
		//get indices
		int i1 = i * 3;
		int i2 = i1 + 1;
		int i3 = i1 + 2;
		//get vertices
		MeshVertex &vertex1 = tempVertices[tempIndices[i1]];
		MeshVertex &vertex2 = tempVertices[tempIndices[i2]];
		MeshVertex &vertex3 = tempVertices[tempIndices[i3]];
		//get positions
		Vector3 v1(vertex1.Pos);
		Vector3 v2(vertex2.Pos);
		Vector3 v3(vertex3.Pos);

		//get uvs
		Vector3 u1(vertex1.Tex);
		Vector3 u2(vertex2.Tex);
		Vector3 u3(vertex3.Tex);
		//get edges
		Vector3 e1 = v2 - v1;
		Vector3 e2 = v3 - v1;
		//get texture edges
		Vector3 s1 = u2 - u1;
		Vector3 s2 = u3 - u1;
		//get values
		Vector3 normal = Vector3::crossProduct(e1, e2);
		normal.normalise();
		vertex1.Normal = vertex2.Normal = vertex3.Normal = normal.ToXMFloat3();
	}
	std::vector<MeshVertex> vertices(24);
	std::vector<WORD> indices(36);
	vertices.assign(tempVertices, tempVertices + 24);
	indices.assign(tempIndices, tempIndices + 36);
	CalculateTangentArray(vertices, indices);
	CreateBuffers(vertices, indices);
}
//This function has been taken from https://gamedev.stackexchange.com/questions/68612/how-to-compute-tangent-and-bitangent-vectors
void DxCube::CalculateTangentArray(std::vector<MeshVertex> &vertices, std::vector<WORD> &indices)
{
	Vector3 *tan1 = new Vector3[vertices.size() * 2];
	Vector3 *tan2 = tan1 + vertices.size();
	ZeroMemory(tan1, vertices.size() * sizeof(Vector3) * 2);

	for (long i = 0; i < indices.size(); i+=3)
	{
		long i1 = indices[i];
		long i2 = indices[i + 1];
		long i3 = indices[i + 2];

		const Vector3& v1 = vertices[i1].Pos;
		const Vector3& v2 = vertices[i2].Pos;
		const Vector3& v3 = vertices[i3].Pos;

		const Vector3& w1 = vertices[i1].Tex;
		const Vector3& w2 = vertices[i2].Tex;
		const Vector3& w3 = vertices[i3].Tex;

		float x1 = v2.x - v1.x;
		float x2 = v3.x - v1.x;
		float y1 = v2.y - v1.y;
		float y2 = v3.y - v1.y;
		float z1 = v2.z - v1.z;
		float z2 = v3.z - v1.z;

		float s1 = w2.x - w1.x;
		float s2 = w3.x - w1.x;
		float t1 = w2.y - w1.y;
		float t2 = w3.y - w1.y;

		float r = 1.0F / (s1 * t2 - s2 * t1);
		Vector3 sdir((t2 * x1 - t1 * x2) * r, (t2 * y1 - t1 * y2) * r,
			(t2 * z1 - t1 * z2) * r);
		Vector3 tdir((s1 * x2 - s2 * x1) * r, (s1 * y2 - s2 * y1) * r,
			(s1 * z2 - s2 * z1) * r);

		tan1[i1] += sdir;
		tan1[i2] += sdir;
		tan1[i3] += sdir;

		tan2[i1] += tdir;
		tan2[i2] += tdir;
		tan2[i3] += tdir;
	}

	for (long a = 0; a < vertices.size(); a++)
	{
		const Vector3& n = vertices[a].Normal;
		const Vector3& t = tan1[a];

		// Gram-Schmidt orthogonalize
		Vector3 tempTangent = (t - n * Vector3::dotProduct(n, t));
		tempTangent.normalise();
		// Calculate handedness
		tempTangent *= (Vector3::dotProduct(Vector3::crossProduct(n, t), tan2[a]) < 0.0F) ? -1.0F : 1.0F;
		
		vertices[a].Tangent = tempTangent.ToXMFloat3();
	}

	delete[] tan1;
}


DxCube::~DxCube()
{
}
