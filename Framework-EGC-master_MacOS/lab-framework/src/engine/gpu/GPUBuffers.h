#pragma once
#include <defines/gl.h>
#include <defines/glm.h>
#include <defines/utils.h>
#include <vector>

#include <engine/gpu/Mesh.h>

class GPUBuffers
{
	public:
		GPUBuffers();

		void CreateBuffers(unsigned int size);
		void ReleaseMemory();

	public:
		GLuint VAO;
		GLuint VBO[6];

	private:
		unsigned short size;
};

namespace UtilsGPU
{

	GPUBuffers UploadData(const std::vector<glm::vec3> &positions,
							const std::vector<glm::vec3> &normals,
							const std::vector<unsigned short>& indices);

	GPUBuffers UploadData(const std::vector<glm::vec3> &positions,
							const std::vector<glm::vec3> &normals,
							const std::vector<glm::vec2> &text_coords,
							const std::vector<unsigned short> &indices);

	GPUBuffers UploadData(const std::vector<VertexFormat> &vertices,
							const std::vector<unsigned short>& indices);
}
