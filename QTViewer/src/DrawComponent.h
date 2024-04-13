#pragma once
#include "pmp/SurfaceMesh.h"
#include "BVH.h"
namespace MN
{
	class DrawComponent
	{
	public:
		pmp::SurfaceMesh mesh;
		
		//초기화와 관련된 함수는 Init접두를 붙인다.
		void Init();

		//시각화와 관련된 함수는 Draw접두를 붙인다.
		void Draw();
		void DrawAABB(Eigen::Vector3d minPt, Eigen::Vector3d maxPt);

		void DrawBezierCurve();

		void aabb();
		//변수들
		int arrowNum0 = 0;
		int arrowNum1 = 0;


		 Eigen::Vector3d minPt{ 99999,99999,99999 };
		 Eigen::Vector3d maxPt{ -99999,-99999,-99999 };
		 Eigen::Vector3d findMaxAxis{ -99999 ,-99999 ,-99999 };
		int longAxis;

	};

}