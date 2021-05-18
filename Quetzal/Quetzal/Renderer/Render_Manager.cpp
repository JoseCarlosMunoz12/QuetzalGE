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

Render_Manager::Render_Manager(GLFWwindow* window, const int GlVerMajorInit, const int GlVerMinorInit, bool Win_Start)
	:R_Window(Win_Start),MainWindow(window),GLVerMajor(GlVerMajorInit), GLVerMinor(GlVerMinorInit)
{
	this->Fov = 90.f;
	this->NearPlane = 0.1f;
	this->FarPlane = 100.f;
	//Init camera Position
	this->Main_Cam = M_SP<Camera>(glm::vec3(-1.f, 1.f, 0.f), glm::vec3(0.f, 1.f, 0.f));
	//Get screen information to use to render
	glfwGetFramebufferSize(this->MainWindow,&this->Frame_Buffer_Width, &this->Frame_Bufer_Height);
	//Create Default Framebuffer Texture 
	this->Main_Texture = M_SP<Frame_Buffer>("Main");
	this->Main_Texture->Init(this->Frame_Buffer_Width, this->Frame_Bufer_Height);
	//load some Textures to use
	this->All_Texture.push_back(M_SP<Stnd_Tex>("Images/pusheen.png", GL_TEXTURE_2D, GL_RGBA));
	this->All_Texture.push_back(M_SP<Stnd_Tex>("Images/diffuse.png", GL_TEXTURE_2D, GL_RGBA));
	//loads defaults Shaders
	this->Main_Shader = M_SP<Shader>(ShaderType::STATIC, this->GLVerMajor, this->GLVerMinor,"vertex_core.glsl", "fragment_core.glsl");
	this->All_Shader.push_back(this->Main_Shader);
	this->Main_Shader = M_SP<Shader>(ShaderType::STATIC, this->GLVerMajor, this->GLVerMinor, "Screen_Shader_Vs.glsl", "Screen_Shader_Fs.glsl");
	//------------------------------------------Creates a mesh to load Framebuffer to-------------------------------------------//
	S_P<Mesh> MainMesh = M_SP<Mesh>(M_UP<Quad_M>(), "MainMesh");
	S_P<Node> NewNode = M_SP<Node>();
	this->Main_Model = M_SP<Model>("Main_Model");
	NewNode->AddTextureId(0);
	NewNode->SetMeshId(0);
	NewNode->AddShaderId(0);
	this->Main_Model->AddMeshes(MainMesh);
	this->Main_Model->AddTextures(this->Main_Texture);
	this->Main_Model->AddBaseNode(NewNode);
	this->Main_Model->SetPos(glm::vec3(0));
	this->Main_Model->AddShaders(this->Main_Shader);
	//--------------------------------------------------------------------------------------------------------------------------//
	// 	                                                                                                                        //
	//-----------------------------------------Load models to render to the Framebuffer-----------------------------------------//
	// 	                                                                                                                        //
	//--------------------------------------------------------------------------------------------------------------------------//
	
	//-load meshes to the item
	std::unique_ptr<ASSIMPLOAD_M> rs = M_UP<ASSIMPLOAD_M>("model_Running.dae");
	S_P<Mesh> InitMesh = M_SP<Mesh>(M_UP<PlaneTerrain_M>(),"Terrain");
	this->All_Meshes.push_back(InitMesh);
	glm::mat4 Inv;
	std::vector<std::unique_ptr<Primitive>> rss = rs->GetModels(Inv);
	for (auto &ii : rss)
	{
		this->All_Meshes.push_back(M_SP<Mesh>(std::move(ii), "MainMesh"));
		int cur_size = this->All_Meshes.size() - 1;
		this->All_Meshes[cur_size]->SetInv(Inv);
	}
	//load data to textures
	S_P<Model> NewModel = M_SP<Model>("RES", glm::vec3(0.f));//1) Create the Model
	NewModel->AddMeshes(All_Meshes[0]);//2) Load meshes into the Model used
	NewModel->AddTextures(this->All_Texture[0]);//3) Load Textures used
	NewModel->AddShaders(this->All_Shader[0]);//4)Load shaders used
	NewModel->AddBaseNode(NewNode);//5) Add nodes to load
	this->All_Models.push_back(NewModel);//6)add to render system
	//------------------------Another Model being Rendered------------------------
	S_P<Model> NewModel1 = M_SP<Model>("REsS", glm::vec3(0.f));//1) Make Model
	NewModel1->AddMeshes(All_Meshes[1]);//2) AddMeshes
	NewModel1->AddTextures(this->All_Texture[1]);//3) Add Textures
	NewModel1->AddShaders(this->All_Shader[0]);//4) add Shaders
	S_P<Node> NewNode1 = M_SP<Node>();//5)Create Nodes to Item
	NewNode1->AddTextureId(0);//6).a - Sets Textures used in the Node
	NewNode1->SetMeshId(0);//6).b - Set Mesh Id for the Node
	NewNode1->SetW_Mat(Inv);//6).c - set Rotation to upright the model
	NewNode1->AddShaderId(0);//6).d - sets Shader to use
	NewModel1->AddBaseNode(NewNode1);//7) add node tree
	this->All_Models.push_back(NewModel1);//8) add model to render
	//------------------------Load Animated Model to Render------------------------
	S_P<A_ASSIMP_LOAD> rrs = M_SP<A_ASSIMP_LOAD>("model_Running.dae");
	rrs->Test();
}

void Render_Manager::Update(float dt)
{
	//Update Matrices
	this->UpdateMatrices();
	this->Main_Cam->Update(dt, 1);
	this->Main_Cam->UpdateMouseInput(dt, this->MainWindow);
	//updates uniforms of shaders being used
	this->All_Shader[0]->setMat4fv(this->Main_Cam->GetViewMatrix(), "ViewMatrix");
	this->All_Shader[0]->setMat4fv(this->Projection, "ProjectionMatrix");
	for (auto& ii : this->All_Models)
	{
		ii->Update();
		ii->UpdateUniforms();
	}
	for (auto& ii : this->All_Anim_Models)
	{
		ii->Update(dt);
		ii->UpdateUniforms();
	}
}

void Render_Manager::Render()
{
	//All of the rendering is saved on this Frame buffer Texture
	this->Main_Texture->WriteToBuffer(this->Frame_Buffer_Width,this->Frame_Bufer_Height, this->Main_Shader,this->Main_Cam->GetViewMatrix());
	for (auto& ii : this->All_Models)
		ii->Render();
	for (auto& ii : this->All_Anim_Models)
		ii->Render();
}

void Render_Manager::RenderToWindow()
{
	if (this->Main_Model)
		this->Main_Model->Render();
}

void Render_Manager::AddTextures(S_P<Texture> NewTexture)
{
	this->All_Texture.push_back(NewTexture);
}

void Render_Manager::AddShader(S_P<Shader> NewShader)
{
	this->All_Shader.push_back(NewShader);
}

void Render_Manager::AddMesh(S_P<Mesh> NewMesh)
{
	this->All_Meshes.push_back(NewMesh);
}

void Render_Manager::AddAnimMesh(S_P<Anim_Mesh> NewMesh)
{
	this->All_Anim_Meshes.push_back(NewMesh);
}

void Render_Manager::AddMaterials(S_P<Material> NewMaterial)
{
	this->All_Materials.push_back(NewMaterial);
}

void Render_Manager::AddModel(S_P<Model> NewModel)
{
	this->All_Models.push_back(NewModel);
}

void Render_Manager::AddAnimModel(S_P<Anim_Model> NewModel)
{
	this->All_Anim_Models.push_back(NewModel);
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

void Render_Manager::RemoveAnimMesh(int Id)
{
	this->All_Anim_Meshes.erase(this->All_Anim_Meshes.begin() + Id);
}

void Render_Manager::RemoveMaterial(int Id)
{
	this->All_Materials.erase(this->All_Materials.begin() + Id);
}

void Render_Manager::RemoveModel(int Id)
{
	this->All_Models.erase(this->All_Models.begin() + Id);
}

void Render_Manager::RemoveAnimModel(int Id)
{
	this->All_Anim_Models.erase(this->All_Anim_Models.begin() + Id);
}
