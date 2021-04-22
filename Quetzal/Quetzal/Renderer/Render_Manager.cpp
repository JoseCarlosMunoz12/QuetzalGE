#include "Render_Manager.h"

void Render_Manager::UpdateMatrices()
{

	glfwGetFramebufferSize(this->MainWindow, &this->Frame_Buffer_Width, &this->Frame_Bufer_Height);
	this->Projection = glm::mat4(1.f);
	this->Projection = glm::perspective(glm::radians(this->Fov),
		static_cast<float>(this->Frame_Buffer_Width) / static_cast<float>(this->Frame_Bufer_Height),
		this->NearPlane,
		this->FarPlane);
}

Render_Manager::Render_Manager(GLFWwindow* window, const int GlVerMajorInit, const int GlVerMinornit, bool Win_Start)
	:R_Window(Win_Start),MainWindow(window),GLVerMajor(GlVerMajorInit), GLVerMinor(GlVerMinornit)
{
	//Get screen information to use to render
	glfwGetFramebufferSize(this->MainWindow,&this->Frame_Buffer_Width, &this->Frame_Bufer_Height);
	//Create Default Framebuffer Texture 
	this->Main_Texture = std::make_shared<Frame_Buffer>("Main");
	this->Main_Texture->Init(this->Frame_Buffer_Width, this->Frame_Bufer_Height);
	this->All_Texture.push_back(std::make_shared<Stnd_Tex>("Images/container.png", GL_TEXTURE_2D, GL_RGBA));
	//loads defaults Shaders
	this->Main_Shader = std::make_shared<Shader>(0,ShaderType::STATIC, this->GLVerMajor, this->GLVerMinor,"vertex_core.glsl", "fragment_core.glsl");
	//creating Default Model to render on screen
	std::shared_ptr<Mesh> InitMesh = std::make_shared<Mesh> (std::make_unique<Quad_M>(),"Terrain");
	this->All_Meshes.push_back(InitMesh);
	this->Main_Model = std::make_shared<Model>("Main_Model");
	S_P<Node> NewNode = std::make_shared<Node>();
	NewNode->AddTextureId(0);
	NewNode->SetMeshId(0);
	this->Main_Model->AddMeshes(All_Meshes[0]);
	this->Main_Model->AddTextures(All_Texture[0]);
	this->Main_Model->AddBaseNode(NewNode);
}

void Render_Manager::Update(float dt)
{
	//Update Matrices
	
	//updates uniforms of shaders being used
	this->Main_Shader->setMat4fv(glm::mat4(1.f), "ViewMatrix");
	this->Main_Shader->setVec3f(glm::vec3(1.f), "CameraPos");
	this->Main_Shader->setMat4fv(this->Projection, "ProjectionMatrix");
	for (auto& ii : this->All_Models)
	{
		ii->Update();
		ii->UpdateUniforms();
	}
}

void Render_Manager::Render()
{
	//All of the rendering is saved on this Frame buffer Texture
	this->Main_Texture->WriteToBuffer(this->Frame_Buffer_Width,this->Frame_Bufer_Height,this->Main_Shader, glm::mat4(1));
	for (auto& ii : this->All_Models)
		ii->Render(this->All_Shader[0]);
}

void Render_Manager::RenderToWindow()
{
	if (this->Main_Model)
		this->Main_Model->Render(this->Main_Shader);
}

void Render_Manager::AddTextures(std::shared_ptr<Texture> NewTexture)
{
	this->All_Texture.push_back(NewTexture);
}

void Render_Manager::AddShader(std::shared_ptr<Shader> NewShader)
{
	this->All_Shader.push_back(NewShader);
}

void Render_Manager::AddMesh(std::shared_ptr<Mesh> NewMesh)
{
	this->All_Meshes.push_back(NewMesh);
}

void Render_Manager::AddMaterials(std::shared_ptr<Material> NewMaterial)
{
	this->All_Materials.push_back(NewMaterial);
}

void Render_Manager::AddModel(std::shared_ptr<Model> NewModel)
{
	this->All_Models.push_back(NewModel);
}

void Render_Manager::ChangeRenderTarget(bool ToWindow)
{
	this->R_Window = ToWindow;
}

void Render_Manager::RemoveTexture(int Id)
{
	this->All_Texture.erase(this->All_Texture.begin() + Id);
}

void Render_Manager::RemoveShader(int Id)
{
	this->All_Shader.erase(this->All_Shader.begin() + Id);
}

void Render_Manager::RemoveMesh(int Id)
{
	this->All_Meshes.erase(this->All_Meshes.begin() + Id);
}

void Render_Manager::RemoveMaterial(int Id)
{
	this->All_Materials.erase(this->All_Materials.begin() + Id);
}

void Render_Manager::RemoveModel(int Id)
{
	this->All_Models.erase(this->All_Models.begin() + Id);
}
