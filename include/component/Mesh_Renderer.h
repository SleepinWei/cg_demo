#pragma once
#include<glad/glad.h>
#include<glfw/glfw3.h>
#include<memory>
#include<glm/glm.hpp>
#include"component/Component.h"
#include"system/RenderManager.h"
#include"utils/header.h"

class Material; 
class MeshFilter; 
class Texture; 
class Shader;

class MeshRenderer :public Component, public std::enable_shared_from_this<MeshRenderer>{
public:

	MeshRenderer();
	~MeshRenderer();

	void render(const std::shared_ptr<Shader>& shader); 

	//void setShader(std::shared_ptr<Shader> shader) { this->shader = shader; };
	std::shared_ptr<MeshRenderer> setShader(ShaderType type);
	std::shared_ptr<MeshRenderer> setShader(std::string type);

	std::shared_ptr<MeshRenderer> setDrawMode(GLenum drawMode_);
	std::shared_ptr<MeshRenderer> setPolyMode(GLenum polyMode_);

	virtual void loadFromJson(json& data);

public:

	GLenum drawMode;
	GLenum polyMode;

	std::shared_ptr<Shader> shader; 
};
