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
	this->FarPlane = 250.f;
	//Init camera Position
	this->Main_Cam = std::make_shared<Camera>(glm::vec3(-1.f, 1.f, 0.f), glm::vec3(0.f, 1.f, 0.f));
	//Init Animation Manager
	this->A_Manager = std::make_shared<AnimHandler>();
	//Get screen information to use to render
	glfwGetFramebufferSize(this->MainWindow,&this->Frame_Buffer_Width, &this->Frame_Bufer_Height);
	//Create Default Framebuffer Texture 
	this->Main_Texture = std::make_shared<Frame_Buffer>("Main");
	this->Main_Texture->Init(this->Frame_Buffer_Width, this->Frame_Bufer_Height);
	//load some Textures to use
	this->All_Texture.push_back(std::make_shared<Stnd_Tex>("Images/No_Texture.png", GL_TEXTURE_2D, GL_RGBA));//Default for Static Texture when there is none added to it
	this->All_Texture.push_back(std::make_shared<Stnd_Tex>("Images/No_Texture.jpg", GL_TEXTURE_2D, GL_RGBA));//Default for Animas Texture when there is none added to it
	///Adding new Textures
	this->All_Texture.push_back(std::make_shared<Stnd_Tex>("Images/Scelidosaurus_Texture.png", GL_TEXTURE_2D, GL_RGBA));
	this->All_Texture.push_back(std::make_shared<Stnd_Tex>("Images/grassy2.png", GL_TEXTURE_2D, GL_RGBA));
	//loads defaults Shaders
	this->Main_Shader = std::make_shared<Shader>(ShaderType::STATIC, this->GLVerMajor, this->GLVerMinor,"vertex_core.glsl", "fragment_core.glsl");
	this->All_Shader.push_back(this->Main_Shader);
	this->Main_Shader = std::make_shared<Shader>(ShaderType::STATIC, this->GLVerMajor, this->GLVerMinor, "Screen_Shader_Vs.glsl", "Screen_Shader_Fs.glsl");
	//AnimationShader 
	S_P<Shader> AnimShader = std::make_shared<Shader>(ShaderType::ANIM, this->GLVerMajor, this->GLVerMinor, "BasicAnimVertex.glsl", "BasicAnimFrag.glsl");
	this->All_Shader.push_back(AnimShader);
	//--------------------------------------------------------------------------------------------------------------------------//
	//------------------------------------------Creates a mesh to load Framebuffer to-------------------------------------------//
	//--------------------------------------------------------------------------------------------------------------------------//
	S_P<Mesh> MainMesh = std::make_shared<Mesh>(std::make_unique<Quad_M>(), "MainMesh");
	S_P<Node> NewNode = std::make_shared<Node>();
	this->Main_Model = std::make_shared<Model>("Main_Model");
	NewNode->AddTextureId(0);
	NewNode->SetMeshId(0);
	NewNode->AddShaderId(0);
	this->Main_Model->AddMeshes(MainMesh);
	this->Main_Model->AddTextures(this->Main_Texture);
	this->Main_Model->AddNode(NewNode);
	this->Main_Model->SetPos(glm::vec3(0));
	this->Main_Model->AddShaders(this->Main_Shader);
	//--------------------------------------------------------------------------------------------------------------------------//
	// 	                                                                                                                        //
	//-----------------------------------------Load models to render to the Framebuffer-----------------------------------------//
	// 	                                                                                                                        //
	//--------------------------------------------------------------------------------------------------------------------------//
	
	//-load meshes to the item
    //std::unique_ptr<ASSIMPLOAD_M> rs = std::make_unique<ASSIMPLOAD_M>("Model_Running.dae");
	std::unique_ptr<ASSIMPLOAD_M> rs = std::make_unique<ASSIMPLOAD_M>("Scelidosaurus.dae");
	//std::unique_ptr<ASSIMPLOAD_M> rs = std::make_unique<ASSIMPLOAD_M>("ls.dae");
	S_P<Mesh> InitMesh = std::make_shared<Mesh>(std::make_unique<PlaneTerrain_M>(),"Terrain");
	this->All_Meshes.push_back(InitMesh);
	glm::mat4 Inv;
	Vec_UP<Primitive> rss = rs->GetModels(Inv);
	int jj = this->All_Meshes.size();
	for (auto &ii : rss)
		this->All_Meshes.push_back(std::make_shared<Mesh>(std::move(ii), "MainMesh"));
	//load data to textures
	S_P<Model> NewModel = std::make_shared<Model>("Terrain", glm::vec3(0.f));//1) Create the Model
	NewModel->AddMeshes(All_Meshes[0]);         //2) Load meshes into the Model used
	NewModel->AddTextures(this->All_Texture[3]);//3) Load Textures used
	NewModel->AddShaders(this->All_Shader[0]);  //4)Load shaders used
	NewModel->AddNode(NewNode);                 //5) Add nodes to load
	//NewModel->SetWMat(Inv);                     //6) set World Matrix
	this->All_Models.push_back(NewModel);       //7)add to render system
	//------------------------------------------------------------------------------
	//-------------------------Another Model being Rendered-------------------------
	//------------------------------------------------------------------------------
	//S_P<Model> NewModel1 = std::make_shared<Model>("Scelidosaurus", glm::vec3(0.f));//1) Make Model
	/*for (int ii = jj; ii < this->All_Meshes.size(); ii++)
			NewModel1->AddMeshes(All_Meshes[ii]);          //2) AddMeshes
		NewModel1->AddTextures(this->All_Texture[0]); //3) Add Textures - Error Texture if it fails it fails to dispay correctly
		NewModel1->AddTextures(this->All_Texture[2]); //3) Add Textures
		NewModel1->AddShaders(this->All_Shader[0]);   //4) add Shaders
		S_P<Node> NewNode1 = std::make_shared<Node>();//5)Create Nodes to Item
		NewNode1->AddTextureId(0);                    //6).a - Sets Textures used in the Node
		for (int ii = jj; ii < this->All_Meshes.size(); ii++)
			NewNode1->SetMeshId(ii - jj);             //6).b - Set Mesh Id for the Node
		//NewNode1->SetW_Mat(Inv);                    //6).c - set Rotation to upright the model
		NewNode1->AddShaderId(0);                     //6).d - sets Shader to use
		//NewNode1->AddChild(NewNode1);               //6).e - set child node, if it has any
		NewModel1->AddNode(NewNode1);                 //7) add node tree
		NewModel1->SetWMat(Inv);                      //8) set world Orientation of the Model
		this->All_Models.push_back(NewModel1);        //9) add model to render
	*/
	//-----------------------------------------------------------------------------
	//------------------------Load Animated Model to Render------------------------
	//-----------------------------------------------------------------------------
	//S_P<A_ASSIMP_LOAD> rrs = std::make_shared<A_ASSIMP_LOAD>("RT.fbx");
	//S_P<A_ASSIMP_LOAD> rrs = std::make_shared<A_ASSIMP_LOAD>("untitled.dae");	 
	//S_P<A_ASSIMP_LOAD> rrs = std::make_shared<A_ASSIMP_LOAD>("model_Running.dae");	 
	//S_P<A_ASSIMP_LOAD> rrs = std::make_shared<A_ASSIMP_LOAD>("dancing_vampire.dae");
	//S_P<A_ASSIMP_LOAD> rrs = std::make_shared<A_ASSIMP_LOAD>("Snek_Up.dae");
	//S_P<A_ASSIMP_LOAD> rrs = std::make_shared<A_ASSIMP_LOAD>("test.fbx");
	//glm::mat4 inv;
	//Vec_SH<Animation> Anims;
	//M_S_M BonesOffsets;
	//M_S_M BonesTransMats;
	//M_S_I BoneLoc;
	//Vec_UP<A_Primitive> rt = rrs->GetPrimitives(inv, BonesOffsets, BonesTransMats, BoneLoc, Anims);
	//this->A_Manager->AddAnims("Model_Running",BonesOffsets, BonesTransMats, BoneLoc, Anims);//add an animation data set into the animation handler
	//this->All_Anim_Meshes.push_back(std::make_shared<Anim_Mesh>(std::move(rt[0]), "Man_Walk"));
	//S_P<Anim_Model> AModel = std::make_shared<Anim_Model>("NewModel", glm::vec3(1.f, 0.f, 10.f));//1)Make Model
	//AModel->AddMeshes(this->All_Anim_Meshes[0]);          //2)     Add Meshes
	//AModel->AddTextures(this->All_Texture[1]);            //3)     Add Textures
	//AModel->AddShaders(this->All_Shader[1]);              //4)     add Shaders
	//AModel->SetWMat(inv);
	//S_P<Node> A_Node = std::make_shared<Node>();          //5)     Create Nodes to Item
	//A_Node->AddTextureId(0);                              //6).a - Sets Textures used in the Node
	//A_Node->SetMeshId(0);                                 //6).b - Set Mesh Id for the Node
	////A_Node->SetW_Mat(inv);                                //6).c - set Rotation to upright the model
	//A_Node->AddShaderId(0);                               //6).d - sets Shader to use
	////A_Node->AddChild(A_Node);                           //6).e - set Child node, if there is any
	////                                                    //6).f - repeat a to e if there is more nodes to do
	//AModel->AddNode(A_Node);                          //7)     Add Node Tree
	//AModel->SetAnimationData(this->A_Manager->GetAnim(0));//8)     Add Animation From the Anim Handler
	//this->All_Anim_Models.push_back(AModel);              //9)     add model to render
	//
	//Load Meshes and Models from the Model Loader
	//Determines if the file loaded is an Anim or a static model
	//
	S_P<Mdl_Ldr> ld = std::make_shared<Mdl_Ldr>();
	//std::string Filename = "SCelidosaurus.dae";
	//std::string Filename = "dancing_vampire.dae";
	//std::string Filename = "RT.fbx";
	std::string Filename = "C:\\Users\\josec\\OneDrive\\Desktop\\Game Engine  Second Version\\QuetzalGE\\Quetzal\\Quetzal\\\FileTest\\TestFile.Q_MF";
	ld->LoadFile(Filename, this->All_Texture, this->All_Shader,
		this->All_Models, this->All_Meshes,
		this->All_Anim_Models, this->All_Anim_Meshes, this->A_Manager);
	/*ld->LoadFile("velociraptor.dae", this->All_Texture, this->All_Shader,
		this->All_Models, this->All_Meshes,
		this->All_Anim_Models, this->All_Anim_Meshes, this->A_Manager);*/
}

void Render_Manager::Update(float dt)
{
	//Update Matrices
	this->UpdateMatrices();
	this->Main_Cam->Update(dt, 1);
	this->Main_Cam->UpdateMouseInput(dt, this->MainWindow);
	this->A_Manager->Update(dt);
	//updates uniforms of shaders being used
	glm::mat4 CamView = this->Main_Cam->GetViewMatrix();
	for (auto& jj : this->All_Shader)
	{
		jj->setMat4fv(CamView, "ViewMatrix");
		jj->setMat4fv(this->Projection, "ProjectionMatrix");
	}
	for (auto& ii : this->All_Anim_Models)
	{
		ii->UpdateUniforms();
	}
	for (auto& ii : this->All_Models)
	{
		ii->Update();
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
