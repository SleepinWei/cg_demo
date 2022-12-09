#pragma once
#include<memory>

class RenderScene; 
class Shader;
class FrameBuffer;
class Texture;
class RenderBuffer;

using std::shared_ptr;

class HDRPass {
public:
	HDRPass();
	~HDRPass();

	void bindBuffer(); 
	void unbindBuffer();

	void render(); 

private:
	// generate texture of width by height (colorbuffer & render bfufer)
	void initPass(int SCR_WITH,int SCR_HEIGHT);

public:
	std::shared_ptr<Shader> hdrShader;
	bool dirty; 
	unsigned int hdrFBO; // framebuffer object
	unsigned int colorBuffer; // texture
	unsigned int rboDepth; // rendrebuffer object 
};

/// <summary>
/// base pass: renders scene objects to framebuffer in forward-rendering pipeline, 
/// this is not a base class for other render pass classes
/// this class should not have any functions to operate on framebuffers
/// </summary>
class BasePass {
public:
	BasePass() = default; 
	~BasePass() = default;

	void render(const std::shared_ptr<RenderScene>& scene,const std::shared_ptr<Shader>& shader);
public:

};

class DepthPass {
public:
	DepthPass();
	~DepthPass();

	void render(const std::shared_ptr<RenderScene>& scene);
public:
	std::shared_ptr<Shader> depthShader;
	std::shared_ptr<FrameBuffer> frameBuffer; //scene size
	std::shared_ptr<Texture> frontDepth;
	std::shared_ptr<Texture> backDepth;
	bool dirty;
private:
	std::shared_ptr<RenderBuffer> renderBuffer;
};

class ShadowPass {
public:
	ShadowPass();
	~ShadowPass();

	void render(const std::shared_ptr<RenderScene>& scene);
public:
	std::shared_ptr<Shader> shadowShader; 
	std::shared_ptr<FrameBuffer> frameBuffer; 
private:
	void pointLightShadow(const std::shared_ptr<RenderScene>& scene);
	void directionLightShadow(const std::shared_ptr<RenderScene>& scene);
};

//TODO:
class DeferredPass {
public:
	DeferredPass();
	~DeferredPass();

	void renderGbuffer(const std::shared_ptr<RenderScene>& scene);
	void render(const std::shared_ptr<RenderScene>& scene);
	void postProcess(const std::shared_ptr<RenderScene>& scene);

public:
	shared_ptr<Shader> gBufferShader;
	shared_ptr<Shader> lightingShader;
	shared_ptr<Shader> postProcessShader;
	shared_ptr<FrameBuffer> gBuffer;
	shared_ptr<FrameBuffer> postBuffer;

	shared_ptr<RenderBuffer> rbo;
	shared_ptr<RenderBuffer> postRbo;

	shared_ptr<Texture> gPosition;
	shared_ptr<Texture> gNormal;
	shared_ptr<Texture> gAlbedoSpec;
	shared_ptr<Texture> gPBR;
	shared_ptr<Texture> postTexture;
	//shared_ptr<Texture> gPBR;
private:
	void initShader();
	void initTextures();
};


class RSMPass {
public:
	RSMPass();
	~RSMPass();

	void render(const std::shared_ptr<RenderScene>& scene);
public:
	std::shared_ptr<Shader> RSMShader;
	std::shared_ptr<FrameBuffer> rsmFBO; 
	std::shared_ptr<Texture> depthMap;
	std::shared_ptr<Texture> normalMap;
	std::shared_ptr<Texture> worldPosMap;
	std::shared_ptr<Texture> fluxMap;
	//std::shared_ptr<Texture> randomMap;
	bool dirty;
private:
	const GLuint RSM_WIDTH = 1024, RSM_HEIGHT = 1024;
	const float light_near_plane = 0.5f, light_far_plane = 20.0f;
	void initShader();
	GLuint createRandomTexture(int size=64);
	void initTextures();
};