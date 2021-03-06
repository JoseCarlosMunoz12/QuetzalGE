#include "AABB_Obj.h"
using namespace CoatlPhysicsEngine;

float AABB_Obj::GetPoint(float P, float Max, float Min)
{
    if (P < Min)
        P = Min;
    if (P > Max)
        P = Max;
    return P;
}

float AABB_Obj::LocPoint(float P, float Max, float Min)
{
    if (P < Min)
        return -1;
    if (P > Max)
        return 1;
    return 0;
}

AABB_Obj::AABB_Obj(float DimXYZ)
    :ColShapes()
{
    this->XLength = DimXYZ;
    this->YLength = DimXYZ;
    this->ZLength = DimXYZ;
}

AABB_Obj::AABB_Obj(float DimX, float DimYZ)
    : ColShapes()
{
    this->XLength = DimX;
    this->YLength = DimYZ;
    this->ZLength = DimYZ;
}

AABB_Obj::AABB_Obj(float DimX, float DimY, float DimZ)
    : ColShapes()
{
    this->XLength = DimX;
    this->YLength = DimY;
    this->ZLength = DimZ;
}

AABB_Obj::~AABB_Obj()
{
}

glm::vec3 AABB_Obj::GetLengths()
{
    return glm::vec3(this->XLength,
        this->YLength,
        this->ZLength);
}

std::vector<glm::vec3> AABB_Obj::GetPoints(glm::vec3 pos, glm::quat quatAngle)
{
    glm::vec3 L = GetLengths();
    glm::vec3 Positions[] =
    {
        //Bottom Plane
        glm::vec3( L.x,-L.y,-L.z), glm::vec3( L.x, L.y,-L.z),
        glm::vec3(-L.x, L.y,-L.z), glm::vec3(-L.x,-L.y,-L.z),
        //Top Plane 
        glm::vec3( L.x,-L.y, L.z), glm::vec3(L.x, L.y, L.z),
        glm::vec3(-L.x, L.y, L.z), glm::vec3(-L.x,-L.y, L.z)
    };
    std::vector<glm::vec3> Lines(std::begin(Positions),std::end(Positions));
    for (auto& jj : Lines)
    {
        jj = jj + pos;
    }
	return Lines;
}

std::vector<glm::vec3> AABB_Obj::GetSegs(glm::vec3 pos, glm::quat quatAngle)
{
    return GetPoints(pos, quatAngle);
}

std::vector<int> AABB_Obj::GetSegmentsID()
{
    return {0,1,1,2,2,3,3,0,
        4,5,5,6,6,7,7,4,
        0,4,1,5,2,6,3,7};
}

void AABB_Obj::SetLengths(glm::vec3 NewLengths)
{
    this->XLength = NewLengths.x;
    this->YLength = NewLengths.y;
    this->ZLength = NewLengths.z;
}

glm::vec3 AABB_Obj::GetClosesPoint(glm::vec3 Point, glm::vec3 pos, glm::quat quatAngle)
{
    glm::vec3 P = Point;
    glm::vec3 L = GetLengths();
    P.x = this->GetPoint(P.x, pos.x + L.x, pos.x - L.x);
    P.y = this->GetPoint(P.y, pos.y + L.y, pos.y - L.y);
    P.z = this->GetPoint(P.z, pos.z + L.z, pos.z - L.z);
	return P;
}

bool AABB_Obj::Inside(glm::vec3 Point, glm::vec3 pos, glm::quat quatAngle)
{
     if (Point.x > pos.x + XLength/2  && Point.x < pos.x - XLength/2 )
     {
         return false;
     }
     if (Point.y > pos.y + YLength / 2 && Point.y < pos.y - YLength / 2)
     {
         return false;
     }
     if (Point.z > pos.z + ZLength / 2 && Point.z < pos.z - ZLength / 2)
     {
         return false;
     }
	return true;
}

glm::vec3 AABB_Obj::Support(glm::vec3 Dir, glm::vec3 pos, glm::quat quatAngle)
{
    std::vector<glm::vec3> Pnts = this->GetPoints(pos, quatAngle);
    float S = glm::dot(Pnts[0], Dir);
    glm::vec3 MaxPnt = Pnts[0];
    int Size = Pnts.size();
    for (int ii = 1; ii < Size; ii++)
    {
        float T = glm::dot(Pnts[ii], Dir);
        if (T > S)
        {
            S = T;
            MaxPnt = Pnts[ii];
        }
    }
    return MaxPnt;
}

glm::vec3 AABB_Obj::EPA_Support(glm::vec3 Dir, glm::vec3 pos, glm::quat quatAngle)
{
    return this->Support(Dir, pos, quatAngle);
}

std::vector<glm::vec3> AABB_Obj::GetVertices(glm::vec3 pos, glm::quat quatAngle)
{
    return this->GetSegs(pos, quatAngle);
}

std::vector<glm::vec3> AABB_Obj::GetNormals(glm::vec3 pos, glm::quat quatAngle)
{
    std::vector<glm::vec3> T = this->GetSegs(pos, quatAngle);
    std::vector<glm::vec3> AABB_N = {glm::vec3(1.f,0.f,0.f),glm::vec3(0.f,1.f,0.f),glm::vec3(0.f,0.f,1.f) };
    return AABB_N;
}

glm::mat3 AABB_Obj::GetInertia(float Mass)
{
    glm::vec3 Ex = GetLengths();
    float LH2 = (Ex.x * Ex.x + Ex.z * Ex.z) / 3.f;
    float HW2 = (Ex.y * Ex.y + Ex.z * Ex.z) / 3.f;
    float LW2 = (Ex.x * Ex.x + Ex.y * Ex.y) / 3.f;
    float LW = Ex.x * Ex.y / 4.f;
    float LH = Ex.x * Ex.z / 4.f;
    float HW = Ex.z * Ex.y / 4.f;
    glm::vec3 Col0 = glm::vec3(LH2, LW, HW);
    glm::vec3 Col1 = glm::vec3(LW, HW2, LH);
    glm::vec3 Col2 = glm::vec3(HW, LH, LW2);
    return Mass * glm::mat3(Col0, Col1, Col2);
}
