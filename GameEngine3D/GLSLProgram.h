#pragma once

#include <string>
#include <GL/glew.h>

namespace GameEngine3D {

	struct ShaderProgramSource {
		std::string VertexSource;
		std::string FragmentSource;
	};

	class GLSLProgram
	{
	public:
		GLSLProgram();

		//Read shaders from file and compile it
		void compileShaders(const std::string& shaderFilePath);

		//Link the shaders
		void linkShaders();

		void addAttribute(const std::string& attributeName);

		GLint getUniformLocation(const std::string& uniformName);

		void useProgram();

		void unuseProgram();

	private:
		void compileShader(const std::string& source, GLuint id);
		void createShaders(const std::string& vertexShader, const std::string& fragmentShader);
		ShaderProgramSource readShaderFile(const std::string& filePath);

		//ID of the whole program
		GLuint _programID;

		GLuint _vertexShaderID;
		GLuint _fragmentShaderID;

		//Count the number of attributes
		int _numAttributes;
	};

}