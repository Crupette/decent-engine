#include "ShaderHandler.h"

#include <fstream>
#include <iostream>
#include <sstream>

namespace DecentEngine {

ShaderHandler::~ShaderHandler(){
	if(m_program != 0) glDeleteProgram(m_program);
}

void ShaderHandler::buildProgram(){
	m_program = glCreateProgram();

	std::vector<std::pair<GLuint, GLenum>> shaders;
	for(auto& it : tmp_shaders){
		shaders.push_back(compileShader(it.first, it.second));
	}

	glLinkProgram(m_program);

	GLint linked = 0;
	glGetProgramiv(m_program, GL_LINK_STATUS, &linked);
	if(linked == GL_FALSE){
		GLint errorlen = 0;
		glGetProgramiv(m_program, GL_INFO_LOG_LENGTH, &errorlen);

		std::vector<GLchar> errorLog(errorlen);
		glGetProgramInfoLog(m_program, errorlen, &errorlen, &errorLog[0]);

		//TODO: Add logger message with [ERROR] tag
		printf("Failed to link program.\nError is as follows:\n%s\n", (char*)(&errorLog[0]));
		
		glDeleteProgram(m_program);

		for(auto& it : shaders){
			glDeleteShader(it.first);
		}

		SDL_Quit();
		exit(6);
	}

	for(auto& it : shaders){
		glDetachShader(m_program, it.first);
		glDeleteShader(it.first);
	}

	tmp_shaders.clear();
}

void ShaderHandler::addShader(GLenum type, const std::string& path){
	tmp_shaders.push_back(std::make_pair(type, path));
	//TODO: Add logger message with [DEBUG] tag
}

void ShaderHandler::addAttribute(const std::string& name){
	glBindAttribLocation(m_program, m_numAttributes++, name.c_str());
	//TODO: Add logger message with [DEBUG] tag
}

GLuint ShaderHandler::getUniformLocation(const std::string& name){
	GLint location = glGetUniformLocation(m_program, name.c_str());
	if(location == -1){
		//TODO: Add logger message with [ERROR] tag
		printf("Failed to retrieve uniform location.\nError is as follows:\nUniform not found\n");
		SDL_Quit();
		exit(4);
	}
	return (GLuint)location;
}

void ShaderHandler::use(){
	glUseProgram(m_program);
}

void ShaderHandler::unuse(){
	glUseProgram(0);
}

std::pair<GLuint, GLenum> ShaderHandler::compileShader(GLenum type, const std::string& path){
	GLuint id = glCreateShader(type);

	std::ifstream file(path, std::ios::binary);
	if(file.fail()){
		//TODO: Add logger message with [ERROR] tag
		printf("Failed to compile shader.\nError is as follows: 404\n");
		SDL_Quit();
		exit(404);
	}
	
	//Load file contents and length
	std::string contents;
	GLint length;

	std::stringstream sstr;
	sstr << file.rdbuf();
	contents = sstr.str();
	length = contents.size();

	file.close();
	
	//Compile shader
	const char* data = contents.c_str();
	glShaderSource(id, 1, &(data), &length);

	glCompileShader(id);
	//Handle errors
	GLint isCompiled = 0;
	glGetShaderiv(id, GL_COMPILE_STATUS, &isCompiled);
	if(isCompiled == GL_FALSE){
		GLint errorlen = 0;
		glGetShaderiv(id, GL_INFO_LOG_LENGTH, &errorlen);

		std::vector<GLchar> errorLog(errorlen);
		glGetShaderInfoLog(id, errorlen, &errorlen, &errorLog[0]);

		//TODO: Add logger message with [ERROR] tag
		printf("Failed to compile shader.\nError is as follows:\n%s\n", (char*)(&errorLog[0]));
		
		glDeleteShader(id);

		SDL_Quit();
		exit(5);
	}

	glAttachShader(m_program, id);

	return std::make_pair(id, type);
}

}
