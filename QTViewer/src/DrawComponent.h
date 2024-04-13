#pragma once
#include "pmp/SurfaceMesh.h"
#include "BVH.h"
namespace MN
{
	class DrawComponent
	{
	public:
		pmp::SurfaceMesh mesh;
		
		//�ʱ�ȭ�� ���õ� �Լ��� Init���θ� ���δ�.
		void Init();

		//�ð�ȭ�� ���õ� �Լ��� Draw���θ� ���δ�.
		void Draw();
		void DrawAABB(Eigen::Vector3d minPt, Eigen::Vector3d maxPt);

		void DrawBezierCurve();

		void aabb();
		//������
		int arrowNum0 = 0;
		int arrowNum1 = 0;


		 Eigen::Vector3d minPt{ 99999,99999,99999 };
		 Eigen::Vector3d maxPt{ -99999,-99999,-99999 };
		 Eigen::Vector3d findMaxAxis{ -99999 ,-99999 ,-99999 };
		int longAxis;

	};

}