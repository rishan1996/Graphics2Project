#include "GLSLProgram.h"
#include "Errors.h"

#include <fstream>
#include <sstream>
#include <vector>

namespace GameEngine3D {

	GLSLProgram::GLSLProgram() : _programID(0), _vertexShaderID(0), _fragmentShaderID(0), _numAttributes(0)
	{
	}



	void GLSLProgram::compileShaders(const std::string& shaderFilePath) {
		_programID = glCreateProgram();

		//Create Vertex Shader
		_vertexShaderID = glCreateShader(GL_VERTEX_SHADER);

		//Error checking on vertex shader id
		if (_vertexShaderID == 0)
			fatalError("Vertex shader failed to be created!");

		//Create Fragment Shader
		_fragmentShaderID = glCreateShader(GL_FRAGMENT_SHADER);

		//Error checking on fragment shader id
		if (_fragmentShaderID == 0)
			fatalError("Fragment shader failed to be created!");

		ShaderProgramSource source = readShaderFile(shaderFilePath);

		compileShader(source.VertexSource, _vertexShaderID); 
		compileShader(source.FragmentSource, _fragmentShaderID);
	}

	void GLSLProgram::linkShaders() {
		//Attach our shaders to our program
		glAttachShader(_programID, _vertexShaderID);
		glAttachShader(_programID, _fragmentShaderID);

		//Link our program
		glLinkProgram(_programID);
		glValidateProgram(_programID);

		//Note the different functions here: glGetProgram* instead of glGetShader*.
		GLint isLinked = 0;
		glGetProgramiv(_programID, GL_LINK_STATUS, (int *)&isLinked);
		if (isLinked == GL_FALSE)
		{
			GLint maxLength = 0;
			glGetProgramiv(_programID, GL_INFO_LOG_LENGTH, &maxLength);

			//The maxLength includes the NULL character
			std::vector<char> infoLog(maxLength);
			glGetProgramInfoLog(_programID, maxLength, &maxLength, &(infoLog[0]));


			//We don't need the program anymore.
			glDeleteProgram(_programID);
			//Don't leak shaders either.
			glDeleteShader(_vertexShaderID);
			glDeleteShader(_fragmentShaderID);

			std::printf("%s\n", &(infoLog[0]));
			fatalError("Shaders failed to link");
		}

		//Always detach shaders after a successful link.
		glDetachShader(_programID, _vertexShaderID);
		glDetachShader(_programID, _fragmentShaderID);
	}

	void GLSLProgram::addAttribute(const std::string& attributeName) {
		glBindAttribLocation(_programID, _numAttributes++, attributeName.c_str());
	}

	GLint GLSLProgram::getUniformLocation(const std::string& uniformName) {
		GLint location = glGetUniformLocation(_programID, uniformName.c_str());

		//Error checking
		if (location == GL_INVALID_INDEX)
			fatalError("Uniform " + uniformName + " not found in shader!");

		return location;
	}

	void GLSLProgram::useProgram() {
		glUseProgram(_programID);
		for (int i = 0; i < _numAttributes; i++)
			glEnableVertexAttribArray(i);
	}

	void GLSLProgram::unuseProgram() {
		glUseProgram(0);
		for (int i = 0; i < _numAttributes; i++)
			glDisableVertexAttribArray(i);
	}

	void GLSLProgram::compileShader(const std::string& source, GLuint id) {
		const char* contentsPtr = source.c_str();

		glShaderSource(id, 1, &contentsPtr, nullptr);

		//Compile the shader
		glCompileShader(id);

		//Error handling
		GLint success = 0;
		glGetShaderiv(id, GL_COMPILE_STATUS, &success);

		if (success == GL_FALSE) {
			GLint maxLength = 0;
			glGetShaderiv(id, GL_INFO_LOG_LENGTH, &maxLength);

			//The maxLength includes the NULL character
			std::vector<char> errorLog(maxLength);
			glGetShaderInfoLog(id, maxLength, &maxLength, &errorLog[0]);

			//Exit with failure
			glDeleteShader(id);

			std::printf("%s\n", &(errorLog[0]));
			fatalError("Shaders failed to compile");
		}

	}

	void GLSLProgram::createShaders(const std::string & vertexShader, const std::string & fragmentShader)
	{

	}

	ShaderProgramSource GLSLProgram::readShaderFile(const std::string& filePath)
	{
		std::ifstream shaderFile(filePath);

		//Error check if shaders opened
		if (shaderFile.fail()) {
			perror(filePath.c_str());
			fatalError("Failed to open " + filePath);
		}

		std::string line;
		std::stringstream ss[2]; ///< String stream for vertex and fragment shader

		enum class ShaderMode {
			NONE = -1, VERTEX = 0, FRAGMENT = 1
		};

		ShaderMode shaderMode = ShaderMode::NONE;

		while (std::getline(shaderFile, line)) { ///< Read the vertex and fragment shader from the shader file
			if (line.find("#shader") != std::string::npos) { ///< Check if it is the beginning of the shader file
				if (line.find("vertex") != std::string::npos) { ///< Check if it the vertex file, if so set to vertex mode
					shaderMode = ShaderMode::VERTEX;
				}
				else if (line.find("fragment") != std::string::npos) { ///< Check if it the fragment file, if so set to fragment mode
					shaderMode = ShaderMode::FRAGMENT;
				}
			}
			else {
				ss[int(shaderMode)] << line << "\n";
			}

		}

		//Close the file
		shaderFile.close();

		return{ ss[0].str(), ss[1].str() };
	}

}