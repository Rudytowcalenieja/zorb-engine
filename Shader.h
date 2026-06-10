#pragma once

#include <GL/glew.h>

#include <glm/matrix.hpp>
#include <glm/gtc/type_ptr.hpp>

#include <string>
#include <fstream>
#include <sstream>
#include <iostream>

namespace ShaderState {
	inline GLuint activeShader_ID = 0;
}

class Shader
{
public:
	unsigned int ID;

	Shader(const char* vertexPath, const char* fragmentPath);
	Shader(const char* vertexPath, const char* fragmentPath, const char* geometryPath);

	void use();

	void SetBool(const std::string &name, bool value) const;
	void SetInt(const std::string& name, int value) const;
	void SetFloat(const std::string& name, float value) const;
	void SetMatrix4(const std::string& name, const glm::mat4& value) const;
	static void SetMatrix4(GLuint id, const std::string& name, const glm::mat4& value);
	void SetVec3(const std::string& name, const glm::vec3& value) const;
	static void SetVec3(GLuint id, const std::string& name, const glm::vec3& value);
	void SetVec4(const std::string& name, const glm::vec4& value) const;

	~Shader();
};

