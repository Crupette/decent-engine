#ifndef SHADERHANDLER_H
#define SHADERHANDLER_H

#include <SDL2/SDL.h>
#include <GL/glew.h>

#include <string>
#include <vector>

#include "Logger.h"

namespace DecentEngine {

class ShaderHandler {
	static Logger m_logger;

	GLuint m_program = 0;
	GLuint m_numAttributes = 0;

	std::vector<std::pair<GLenum, std::string>> tmp_shaders;

	/**
	 * @brief Compiles the shader into it's id and type
	 *
	 * @param type Type of shader to compile
	 * @param path Path of said shader
	 *
	 * @return Shader ID and type
	 */
	std::pair<GLuint, GLenum> compileShader(GLenum type, const std::string& path);
public:
	/**
	 * @brief Use this program as a pointer
	 */
	ShaderHandler() {}
	~ShaderHandler();
	/**
	 * @brief Builds the program with all of the shaders and attributes added by each respective function.
	 */
	void buildProgram();
	/**
	 * @brief Adds the shader to be compiled and added to the program by the [buildProgram] function.
	 *
	 * @param type Enum specifying the type of shader
	 * @param path Path to the shader file
	 */
	void addShader(GLenum type, const std::string& path);
	/**
	 * @brief Adds the attribute to be added to the program. Must be called after the [buildProgram] function.
	 *
	 * @param name Name of the attribute as specified in the shader.
	 */
	void addAttribute(const std::string& name);
	/**
	 * @brief Returns the location of a uniform
	 *
	 * @param name Name of the uniform as specified in the shader
	 *
	 * @return Integer location of the uniform.
	 */
	GLuint getUniformLocation(const std::string& name);

	/**
	 * @brief Specifies the shader program to be used for graphics processing
	 */
	void use();
	/**
	 * @brief Stops using the shader program
	 */
	void unuse();
};
}

#endif
