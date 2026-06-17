#include "Instanced.h"

Instanced::Instanced() {
	VAO = 0, VBO = 0, IBO = 0, instancedVBO = 0;
}

void Instanced::CreateMesh(GLfloat* vertices, GLuint verticesCount, GLuint* indices, GLuint indicesCount) {
	count = indicesCount;

	// printf("--- Instanced ---\n");
	// printf("Indices count: %d\n", count);
	// printf("Vertices count: %d\n", verticesCount);
	// printf("--- Instanced ---\n");

	// Gen
	glGenVertexArrays(1, &VAO);
	glGenBuffers(1, &VBO);
	glGenBuffers(1, &IBO);

	// Bind
	glBindVertexArray(VAO);

	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices[0]) * verticesCount, vertices, GL_STATIC_DRAW);

	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, IBO);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices[0]) * indicesCount, indices, GL_STATIC_DRAW);

	// Attribs
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(vertices[0]), (void*)0);
	glEnableVertexAttribArray(0);

	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(vertices[0]), (void*)(3 * sizeof(vertices[0])));
	glEnableVertexAttribArray(1);

	glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, 8 * sizeof(vertices[0]), (void*)(6 * sizeof(vertices[0])));
	glEnableVertexAttribArray(2);

	glBindBuffer(GL_ARRAY_BUFFER, 0);
	// glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
	glBindVertexArray(0);
}

void Instanced::CreateInstanced(glm::vec3* vectors, size_t size) {
	transform_size = size;
	transform = new glm::vec3[size];
	for (int i = 0; i < size; i++) {
		transform[i] = vectors[i];
	}

	glBindVertexArray(VAO);

	glGenBuffers(1, &instancedVBO);
	glBindBuffer(GL_ARRAY_BUFFER, instancedVBO);
	glBufferData(GL_ARRAY_BUFFER, size * sizeof(glm::vec3), transform, GL_STATIC_DRAW);

	glEnableVertexAttribArray(3);
	glVertexAttribPointer(3, 3, GL_FLOAT, GL_FALSE, sizeof(glm::vec3), (void*)0);
	glVertexAttribDivisor(3, 1);

	glBindVertexArray(0);
	glBindBuffer(GL_ARRAY_BUFFER, 0);
	delete[] transform;
}

void Instanced::Transform(glm::vec3 position) {
	this->position = position;
}

void Instanced::Render(const GLuint shaderID) {
	model = glm::mat4(1.0f);
	model = glm::translate(model, position);
	Shader::SetMatrix4(shaderID, "model", model);

	glBindVertexArray(VAO);
	glDrawElementsInstanced(GL_TRIANGLES, count, GL_UNSIGNED_INT, 0, transform_size);
	glBindVertexArray(0);
}

Instanced::~Instanced() {
	glDeleteVertexArrays(1, &VAO);
	glDeleteBuffers(1, &VBO);

	if (VAO) VAO = 0;
	if (VBO) VBO = 0;
	if (IBO) IBO = 0;
	if (instancedVBO) instancedVBO = 0;
}