#include "Shader.h"

Shader::Shader(const char* vertexPath, const char* fragmentPath) {
	std::string vertexCode;
	std::string fragmentCode;

	std::ifstream vertexShaderFile;
	std::ifstream fragmentShaderFile;

	vertexShaderFile.exceptions(std::ifstream::failbit | std::ifstream::badbit);
	fragmentShaderFile.exceptions(std::ifstream::failbit | std::ifstream::badbit);

	try {
		vertexShaderFile.open(vertexPath);
		fragmentShaderFile.open(fragmentPath);

		std::stringstream vertexShaderStream;
		std::stringstream fragmentShaderStream;

		vertexShaderStream << vertexShaderFile.rdbuf();
		fragmentShaderStream << fragmentShaderFile.rdbuf();

		vertexShaderFile.close();
		fragmentShaderFile.close();

		vertexCode = vertexShaderStream.str();
		fragmentCode = fragmentShaderStream.str();
	} catch (std::ifstream::failure &e) {
		std::cout << "Failed to read shader file. Exception: " << e.what() << ".\n";
	}

	const char* vertexShaderCode = vertexCode.c_str();
	const char* fragmentShaderCode = fragmentCode.c_str();

	unsigned int vertexShader = glCreateShader(GL_VERTEX_SHADER);

	glShaderSource(vertexShader, 1, &vertexShaderCode, nullptr);
	glCompileShader(vertexShader);

	this -> checkCompileErrors(vertexShader, "Vertex");

	unsigned int fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);

	glShaderSource(fragmentShader, 1, &fragmentShaderCode, nullptr);
	glCompileShader(fragmentShader);

	this -> checkCompileErrors(fragmentShader, "Fragment");

	this -> ID = glCreateProgram();

	glAttachShader(this -> ID, vertexShader);
	glAttachShader(this -> ID, fragmentShader);

	glLinkProgram(this -> ID);

	this -> checkCompileErrors(this -> ID, "Program");

	glDeleteShader(vertexShader);
	glDeleteShader(fragmentShader);
}

Shader::~Shader() {

}

void Shader::use() {
	glUseProgram(this -> ID);
}

void Shader::setInt(const std::string &name, int value) const {
	glUniform1i(glGetUniformLocation(this -> ID, name.c_str()), value);
}

void Shader::setBool(const std::string &name, bool value) const {
	glUniform1i(glGetUniformLocation(this -> ID, name.c_str()), (int) value);
}

void Shader::setFloat(const std::string &name, float value) const {
	glUniform1f(glGetUniformLocation(this -> ID, name.c_str()), value);
}

void Shader::setVec2(const std::string &name, float x, float y) const {
	glUniform2f(glGetUniformLocation(this -> ID, name.c_str()), x, y);
}

void Shader::setVec2(const std::string &name, const glm::vec2 &value) const {
	glUniform2fv(glGetUniformLocation(this -> ID, name.c_str()), 1, &value[0]);
}

void Shader::setVec3(const std::string &name, float x, float y, float z) const {
	glUniform3f(glGetUniformLocation(this -> ID, name.c_str()), x, y, z);
}

void Shader::setVec3(const std::string &name, const glm::vec3 &value) const {
	glUniform3fv(glGetUniformLocation(this -> ID, name.c_str()), 1, &value[0]);
}

void Shader::setVec4(const std::string &name, float x, float y, float z, float w) const {
	glUniform4f(glGetUniformLocation(this -> ID, name.c_str()), x, y, z, w);
}

void Shader::setVec4(const std::string &name, const glm::vec4 &value) const {
	glUniform4fv(glGetUniformLocation(this -> ID, name.c_str()), 1, &value[0]);
}

void Shader::setMat2(const std::string &name, const glm::mat2 &value) const {
	glUniformMatrix2fv(glGetUniformLocation(this -> ID, name.c_str()), 1, GL_FALSE, &value[0][0]);
}

void Shader::setMat3(const std::string &name, const glm::mat3 &value) const {
	glUniformMatrix3fv(glGetUniformLocation(this -> ID, name.c_str()), 1, GL_FALSE, &value[0][0]);
}

void Shader::setMat4(const std::string &name, const glm::mat4 &value) const {
	glUniformMatrix4fv(glGetUniformLocation(this -> ID, name.c_str()), 1, GL_FALSE, &value[0][0]);
}

void Shader::checkCompileErrors(unsigned int obj, std::string type) {
	char infoLog[1024];
	int success;

	if (type != "Program") {
		glGetShaderiv(obj, GL_COMPILE_STATUS, &success);

		if (!success) {
			glGetShaderInfoLog(obj, 1024, nullptr, infoLog);

			std::cout << "A " << type << " Shader Compilation Error Occurred. Info Log:\n" << infoLog << "\n";
		}
	} else {
		glGetProgramiv(obj, GL_LINK_STATUS, &success);

		if (!success) {
			glGetShaderInfoLog(obj, 1024, nullptr, infoLog);

			std::cout << "A Program Linking Error Occurred. Info Log:\n" << infoLog << "\n";
		}
	}
}
