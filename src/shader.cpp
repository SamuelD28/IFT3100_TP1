#include <shader.hpp>

namespace shader
{
	shader_error::shader_error(std::string message)
	{
		this->message = message;
	}

	// Shader stuff
	std::ostream &operator<<(std::ostream &os, const shader &shader)
	{
		os << "(COMPILED SHADER) id:" << shader.id << " - path:" << shader.path << " - program id:" << shader.programId;
		return os;
	}

	// Does the file gets freed if an error occurs?
	std::string load(std::string location)
	{
		auto file = std::ifstream{location};
		if (!file.is_open())
		{
			throw shader_error("could not open file at location: " + location);
		}

		std::string source{};
		while (file)
		{
			std::string line;
			std::getline(file, line);
			source = source.append(line) + "\n"; // need to keep return line for compilation
		}

		file.close();
		return source;
	}

	unsigned int compile(std::string source, unsigned int type)
	{
		const char *sourcePointer = source.c_str();

		if (sourcePointer == "")
		{
			throw new shader_error("source is empty. make sure to load the resource before compiling");
		}

		GLuint shaderId = glCreateShader(type);

		glShaderSource(shaderId, 1, &sourcePointer, NULL);
		glCompileShader(shaderId);

		// Look for cleaner way to handle errors
		GLint isCompiled{};
		glGetShaderiv(shaderId, GL_COMPILE_STATUS, &isCompiled);
		if (isCompiled == GL_FALSE)
		{
			GLint maxLength{};
			glGetShaderiv(shaderId, GL_INFO_LOG_LENGTH, &maxLength);
			auto errorLog = std::vector<GLchar>(maxLength);
			glGetShaderInfoLog(shaderId, maxLength, &maxLength, &errorLog[0]);
			glDeleteShader(shaderId);

			auto errorMessage = std::string(errorLog.begin(), errorLog.end());
			throw shader_error(errorMessage);
		}

		return shaderId;
	}

	// Program stuff
	unsigned int initProgram()
	{
		return glCreateProgram();
	}

	bool attachProgram(unsigned int programId, unsigned int shaderId)
	{
		glAttachShader(programId, shaderId);
		return true;
	}

	unsigned int buildProgram(std::vector<shader> &shaders)
	{
		unsigned int programId = initProgram();

		for (auto &shader : shaders)
		{
			shader.source = load(shader.path);
			shader.id = compile(shader.source, shader.type);
			attachProgram(programId, shader.id);
			shader.programId = programId;
		}

		glLinkProgram(programId);

		GLint success{};
		char infoLog[512];
		glGetProgramiv(programId, GL_LINK_STATUS, &success);
		if (!success)
		{
			glGetProgramInfoLog(programId, 512, NULL, infoLog);
			throw new shader_error(infoLog);
		}

		for (auto &shader : shaders)
		{
			glDeleteShader(shader.id);
		}

		return programId;
	}
}