#pragma once
#include "../define.h"
#include "../Maths/Maths.h"
#include "../Maths/Matrix.h"
#include "../Maths/Vectors.h"
namespace CoatlPhysicsEngine {
	class COATL_API Shape
	{
	protected:
		Vec3D Position;
		Quat Rotation;
	public:
		Shape(Vec3D initPos, Quat initRot);
		~Shape();
		Vec3D GetPosition();
		void SetPosition(Vec3D newPos);
		Quat GetRotation();
		void SetRotation(Quat newRot);
		virtual void DisplayInfo();
		virtual std::string GetStr();
		virtual std::vector<Vec3D> GetNormals();
		virtual std::vector<Vec3D> GetVertices();
		virtual Vec3D Support(Vec3D Dir);
		virtual Vec3D EPA_Support(Vec3D Dir);
		virtual Matrix3x3 GetMomentOfIntertia();
	};
}

