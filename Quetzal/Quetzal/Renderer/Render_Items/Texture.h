#pragma once
#include <iostream>
#include <string>

#include <glew.h>
#include <glfw3.h>
#include <SOIL2.h>
class Texture
{
protected:
	GLuint ID;
	const char* Name;
	unsigned int Type;
public:
	Texture( const char* NewName,GLenum NewType)
		:Name(NewName),Type(NewType),ID(0)
	{
	}
	void Bind(const GLint texture_unit)
	{
		glActiveTexture(GL_TEXTURE0 + texture_unit);
		glBindTexture(this->Type, this->ID);
	}
	void UnBind()
	{
		glActiveTexture(0);
		glBindTexture(this->Type, 0);
	}
	const char* GiveChar()
	{
		return this->Name;
	}
	inline GLuint getID() const { return this->ID; }
};

class Stnd_Tex : public Texture
{
private:
	int width;
	int height;
	int NumOfChannels;
	unsigned char* ImageRGB;
public:
	Stnd_Tex(const char* fileName, GLenum type, GLenum ColorType)
		:Texture(fileName,type)
	{
		this->Type = type;
		this->Name = fileName;

		unsigned char* image = SOIL_load_image(fileName, &this->width, &this->height, &this->NumOfChannels, SOIL_LOAD_RGBA);
		this->ImageRGB = image;
		glGenTextures(1, &this->ID);
		glBindTexture(type, this->ID);
		glTexParameteri(type, GL_TEXTURE_WRAP_S, GL_REPEAT);
		glTexParameteri(type, GL_TEXTURE_WRAP_T, GL_REPEAT);
		glTexParameteri(type, GL_TEXTURE_MAG_FILTER, GL_LINEAR_MIPMAP_LINEAR);
		glTexParameteri(type, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
		if (image)
		{
			glTexImage2D(type, 0, GL_RGBA, this->width, this->height, 0, ColorType, GL_UNSIGNED_BYTE, image);
			glGenerateMipmap(type);
		}
		else
		{
			std::cout << "ERROR::TEXTURE::TEXTURE_LOADING_FAILED" << fileName << "\n";
		}
		glActiveTexture(0);
		glBindTexture(type, 0);

		SOIL_free_image_data(image);
	
	}
	~Stnd_Tex()
	{
		glDeleteTextures(1,&this->ID);
	}


};

class ShadowTex:public Texture
{
	GLuint FrameBuffer;
public:
	ShadowTex(const char* NewName)
		:Texture(NewName, GL_TEXTURE_2D)
	{
		this->ID = 0;
		this->FrameBuffer = 0;
	}
	~ShadowTex()
	{
		if (this->FrameBuffer != 0)
		{
			glDeleteFramebuffers(1, &this->FrameBuffer);
		}
		if (this->ID!= 0)
		{
			glDeleteFramebuffers(1, &this->ID);
		}
	}
	void Init(unsigned int WindowWidth, unsigned int WindowHeight)
	{
		//Create the Frame Buffer
		glGenFramebuffers(1, &this->FrameBuffer);
		//Create The Depth Buffer
		glGenTextures(1, &this->ID);
		glBindTexture(GL_TEXTURE_2D, this->ID);
		glTexImage2D(GL_TEXTURE_2D, 0, GL_DEPTH_COMPONENT, WindowWidth, WindowHeight, 0, GL_DEPTH_COMPONENT, GL_FLOAT, NULL);
		glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
		glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
		glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_BORDER);
		glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_BORDER);
		float BorderColor[] = { 1.f,1.f,1.f,1.f };
		glBindFramebuffer(GL_FRAMEBUFFER, this->FrameBuffer);
		glTexParameterfv(GL_TEXTURE_2D, GL_TEXTURE_BORDER_COLOR, BorderColor);
		glFramebufferTexture2D(GL_FRAMEBUFFER, GL_DEPTH_ATTACHMENT, GL_TEXTURE_2D, this->ID, 0);

		//Disable Writes to the color buffer
		glDrawBuffer(GL_NONE);
		glReadBuffer(GL_NONE);
		glBindFramebuffer(GL_FRAMEBUFFER, 0);
	}
	void WriteToBuffer(unsigned int WindowWidth, unsigned int WindowHeight,
		std::shared_ptr<Shader> DepthShader,glm::mat4 LightSpaceMatrix)
	{
		DepthShader->use();
		DepthShader->setMat4fv(LightSpaceMatrix, "LightSpaceMatrix");
		glViewport(0, 0, WindowWidth, WindowHeight);
		glBindFramebuffer(GL_FRAMEBUFFER, this->FrameBuffer);
		glClear(GL_DEPTH_BUFFER_BIT);
	}
};

class Frame_Buffer : public Texture
{
private:
	GLuint FrameBuffer;
	GLuint rbo;
public:
	Frame_Buffer(const char* name)
		:Texture(name,GL_TEXTURE_2D)
	{
		this->ID = 0;
		this->FrameBuffer = 0;
		this->rbo = 0;
	}
	void Init(unsigned int WindowWidth, unsigned int WindowHeight)
	{

		// -------------------------
		glGenFramebuffers(1, &this->FrameBuffer);
		glBindFramebuffer(GL_FRAMEBUFFER, this->FrameBuffer);
		// create a color attachment texture
		glGenTextures(1, &this->ID);
		glBindTexture(GL_TEXTURE_2D, this->ID);
		glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, WindowWidth, WindowHeight, 0, GL_RGB, GL_UNSIGNED_BYTE, NULL);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
		glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, GL_TEXTURE_2D, this->ID, 0);
		// create a renderbuffer object for depth and stencil attachment (we won't be sampling these)
		glGenRenderbuffers(1, &this->rbo);
		glBindRenderbuffer(GL_RENDERBUFFER, this->rbo);
		glRenderbufferStorage(GL_RENDERBUFFER, GL_DEPTH24_STENCIL8, WindowWidth, WindowHeight); // use a single renderbuffer object for both a depth AND stencil buffer.
		glFramebufferRenderbuffer(GL_FRAMEBUFFER, GL_DEPTH_STENCIL_ATTACHMENT, GL_RENDERBUFFER, this->rbo); // now actually attach it
		// now that we actually created the framebuffer and added all attachments we want to check if it is actually complete now
		if (glCheckFramebufferStatus(GL_FRAMEBUFFER) != GL_FRAMEBUFFER_COMPLETE)
			std::cout << "ERROR::FRAMEBUFFER:: Framebuffer is not complete!\n";
		glBindFramebuffer(GL_FRAMEBUFFER, 0);
	}
	void WriteToBuffer(unsigned int WindowWidth, unsigned int WindowHeight,
		std::shared_ptr<Shader> DepthShader, glm::mat4 CamMatrix)
	{
		DepthShader->use();
		DepthShader->setMat4fv(CamMatrix, "CamMatrix");
		glViewport(0, 0, WindowWidth, WindowHeight);
		glBindFramebuffer(GL_FRAMEBUFFER, this->FrameBuffer);
		glClearColor(0.1f, 0.1f, 0.1f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
		glClear(GL_DEPTH_BUFFER_BIT);
	}
};
