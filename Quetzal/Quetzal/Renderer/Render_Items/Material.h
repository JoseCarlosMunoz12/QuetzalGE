#pragma once

#include <glew.h>
#include <glfw3.h>
#include <glm.hpp>
#include <vector>

#include <vec2.hpp>
#include <vec3.hpp>
#include <vec4.hpp>
#include <mat4x4.hpp>
#include <gtc\type_ptr.hpp>

#include "Shader.h"
class Material
{
private:
	std::string MatName;
	int MatId;
protected:
	std::vector<GLint> TexIndex;
	std::vector<GLint> ShadowTex;
	//All Shadow Textures
	std::vector<GLint> ptrShadow;
	std::vector<GLint> CnShadow;
	std::vector<GLint> ArShadow;
	glm::vec3 SkyClr;
public:
	Material(std::string Name,int SetId)
	{
		this->MatName = Name;
		this->MatId = SetId;
	}
	~Material()
	{
	}
	virtual void SendToShader(std::shared_ptr<Shader> program)
	{
	}
	virtual void SendToShader(std::shared_ptr<Shader> program,std::vector<glm::mat4> LightMatrix)
	{
	}
	const char* GetName()
	{
		return this->MatName.c_str();
	}
	int GetMatId()
	{
		return this->MatId;
	}

};

class SingleTextMat : public Material
{
public:
	SingleTextMat(std::string name, int SetId, glm::vec3 Skycolor, GLint TexId)
		:Material(name, SetId)
	{
		this->SkyClr = Skycolor;
		this->TexIndex.push_back(TexId);
	}
	void SendToShader(std::shared_ptr<Shader> program)  override
	{
		program->setVec3f(this->SkyClr, "SkyColor");
		program->set1i(this->TexIndex[0], "Texture0");
	}
	void SendToShader(std::shared_ptr<Shader> program,std::vector<glm::mat4> LightMatix) override
	{
		this->SendToShader(program);
		int Value = 0;
		for (auto& ii : LightMatix)
		{
			std::string LightPos = "AllDirInfo[" + std::to_string(Value) + "].LightMatrix";
			program->setMat4fv(ii, LightPos.c_str());
			Value++;
		}
	}
};

class Standardmat : public Material
{
public:
	Standardmat(std::string Name, int SetId, int ShaderId, glm::vec3 SkyColor)
		:Material(Name,SetId)
	{
		this->SkyClr = SkyColor;
	}
	void SendToShader(std::shared_ptr<Shader> program) override
	{
		program->setVec3f(this->SkyClr, "SkyColor");
	}
	void SendToShader(std::shared_ptr<Shader> program,std::vector<glm::mat4> LightMatix) override
	{
		this->SendToShader(program);
		int Value = 0;
		for (auto& ii : LightMatix)
		{
			std::string LightPos = "AllDirInfo[" + std::to_string(Value) + "].LightMatrix";
			program->setMat4fv(ii, LightPos.c_str());
			Value++;
		}

		for (int ii = 0; ii < this->CnShadow.size(); ii++)
		{
			std::string LghtMatrix = "AllCnInfo[" + std::to_string(ii) + "].LightMatrix";
			program->setMat4fv(LightMatix[Value], LghtMatrix.c_str());
			Value++;
		}
		for (int ii = 0; ii < this->ArShadow.size(); ii++)
		{
			std::string LighMatrix = "AllArInfo[" + std::to_string(ii) + "].LightMatrix";
			program->setMat4fv(LightMatix[Value], LighMatrix.c_str());
			Value++;
		}
	}
};

class TxtMat : public Material
{
	glm::vec3 Ambient;
	glm::vec3 Diffuse;
	glm::vec3 Specular;
public:
	TxtMat(std::string Name, int SetId,
			glm::vec3 SkyColor, glm::vec3 ambient,
			glm::vec3 diffuse, glm::vec3 specular,
			GLint diffuseTex, GLint specularTex,
			std::vector<GLint> InitShadowTx = { 2 },
			std::vector<GLint> InitCnShadow = {},
			std::vector<GLint> InitptrShadow = {},
			std::vector<GLint> InitArShadow = {})
			:Material(Name, SetId)
	{
		this->ShadowTex = InitShadowTx;
		this->CnShadow = InitCnShadow;
		this->ptrShadow = InitptrShadow;
		this->ArShadow = InitArShadow;
		this->SkyClr = SkyColor;
		this->Ambient = ambient;
		this->Diffuse = diffuse;
		this->Specular = specular;
		this->TexIndex.push_back(diffuseTex);
		this->TexIndex.push_back(specularTex);
	}
	void SendToShader(std::shared_ptr<Shader> program) override
	{
		program->setVec3f(this->Ambient, "material.ambient");
		program->setVec3f(this->Diffuse, "material.diffuse");
		program->setVec3f(this->Specular, "material.specular");
		program->set1i(this->TexIndex[0], "material.diffuseTex");
		program->set1i(this->TexIndex[1], "material.speculartex");
		int Value = 0;
		for (auto& ii : this->ShadowTex)
		{

			std::string lShadow = "AllDirInfo[" + std::to_string(Value) + "].LightShadow";
			program->set1i(ii,lShadow.c_str());
			Value++;
		}
		Value = 0;
		for (auto& ii : this->CnShadow)
		{
			std::string CShadow = "AllCnInfo[" + std::to_string(Value) + "].LightShadow";
			program->set1i(ii,CShadow.c_str());
			Value++;
		}
		Value = 0;
		for (auto& ii : this->ArShadow)
		{
			std::string AShadow = "AllArInfo[" + std::to_string(Value) + "].LightShadow";
			program->set1i(ii, AShadow.c_str());
			Value++;
		}
		program->setVec3f(this->SkyClr, "SkyColor");
	}
	void SendToShader(std::shared_ptr<Shader> program, std::vector<glm::mat4> LightMatix) override
	{
		this->SendToShader(program);
		int Value = 0;
		for (int ii = 0; ii < this->ShadowTex.size();ii++)
		{
			std::string LIghtMatrix = "AllDirInfo[" + std::to_string(Value) + "].LightMatrix";
			program->setMat4fv(LightMatix[Value], LIghtMatrix.c_str());
			Value++;
		}
		for (int ii = 0; ii < this->CnShadow.size(); ii++)
		{
			std::string LghtMatrix = "AllCnInfo[" + std::to_string(ii) + "].LightMatrix";
			program->setMat4fv(LightMatix[Value], LghtMatrix.c_str());
			Value++;
		}
		for (int ii = 0; ii < this->ArShadow.size(); ii++)
		{
			std::string LighMatrix = "AllArInfo[" + std::to_string(ii) + "].LightMatrix";
			program->setMat4fv(LightMatix[Value], LighMatrix.c_str());
			Value++;
		}
	}
	~TxtMat()
	{
	}
};

class MipMapMat : public Material
{
	glm::vec3 Ambient;
	glm::vec3 Diffuse;
	glm::vec3 Specular;
public:
	MipMapMat(std::string Name, int SetId,
		glm::vec3 SkyColor,	std::vector<GLint> TexIndex,
		std::vector<GLint> InitShadowTex,
		std::vector<GLint> InitCnShadow = {},
		std::vector<GLint> InitptrShadow = {},
		std::vector<GLint> InitArShadow = {},
		glm::vec3 ambient = glm::vec3(0.1f),
		glm::vec3 diffuse = glm::vec3(1.0f),
		glm::vec3 specular = glm::vec3(1.0f))
		:Material(Name, SetId)
	{
		this->ShadowTex = InitShadowTex;
		this->CnShadow = InitCnShadow;
		this->ptrShadow = InitptrShadow;
		this->ArShadow = InitArShadow;
		this->SkyClr = SkyColor;
		this->TexIndex = TexIndex;
		this->Ambient = ambient;
		this->Diffuse = diffuse;
		this->Specular = specular;
	}
	void SendToShader(std::shared_ptr<Shader> program) override
	{
		program->setVec3f(this->Ambient, "material.ambient");
		program->setVec3f(this->Diffuse, "material.diffuse");
		program->setVec3f(this->Specular, "material.specular");
		program->set1i(this->TexIndex[0], "Texture0");
		program->set1i(this->TexIndex[1], "Texture1");
		program->set1i(this->TexIndex[2], "Texture2");
		program->set1i(this->TexIndex[3], "Texture3");
		program->set1i(this->TexIndex[4], "Texture4");
		int Value = 0;
		for (auto& ii : this->ShadowTex)
		{
			std::string lShadow = "AllDirInfo[" + std::to_string(Value) + "].LightShadow";
			program->set1i(ii, lShadow.c_str());
			Value++;
		}
		Value = 0;
		for (auto& ii : this->CnShadow)
		{
			std::string CShadow = "AllCnInfo[" + std::to_string(Value) + "].LightShadow";
			program->set1i(ii, CShadow.c_str());
			Value++;
		}
		Value = 0;
		for (auto& ii : this->ArShadow)
		{
			std::string AShadow = "AllArInfo[" + std::to_string(Value) + "].LightShadow";
			program->set1i(ii, AShadow.c_str());
			Value++;
		}
		program->setVec3f(this->SkyClr, "SkyColor");
	}
	void SendToShader(std::shared_ptr<Shader> program, std::vector<glm::mat4> LightMatix) override
	{
		this->SendToShader(program);
		int Value = 0;
		for (int ii = 0; ii < this->ShadowTex.size(); ii++)
		{
			std::string LghtMatrix = "AllDirInfo[" + std::to_string(Value) + "].LightMatrix";
			program->setMat4fv(LightMatix[ii], LghtMatrix.c_str());
			Value++;
		}
		for (int ii = 0; ii < this->CnShadow.size(); ii++)
		{
			std::string LghtMatrix = "AllCnInfo[" + std::to_string(ii) + "].LightMatrix";
			program->setMat4fv(LightMatix[Value], LghtMatrix.c_str());
			Value++;
		}
		for (int ii = 0; ii < this->ArShadow.size(); ii++)
		{
			std::string LighMatrix = "AllArInfo[" + std::to_string(ii) + "].LightMatrix";
			program->setMat4fv(LightMatix[Value],LighMatrix.c_str());
			Value++;
		}
	}
};