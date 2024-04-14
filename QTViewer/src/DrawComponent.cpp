#include "DrawComponent.h"
#include "GL/freeglut.h"
#include <iostream>
#include <sstream>
#include <fstream>
#include <vector>
#include <string>
#include <queue>
#include "BVH.h"

#include "pmp/io/read_obj.h"
#include "pmp/algorithms/Normals.h"

/* 0) pmp - obj 파일 로드하는 함수와, normal 가져오는 방법 확인r
*  1) 모델 전체를 감싸는 AABB 구성하고, 그리기(wireframe)
*  2) AABB BVH 만들기 (binary tree)
*  2-1) binary tree 구분하는 기준은, x,y,z 축 중 가장 긴 축을 기준으로 균등 이분할
*  2-2) 키보드 화살표 입력으로, bvh level (root = 0, root의 하위노드 2개가 1)에 따라 구분하여 시각화
*/

namespace MN
{
	BVH* bvh;
	void DrawComponent::Init()
	{
		pmp::read_obj(mesh, "models/kitten.obj");
		std::cout << "v " << mesh.n_vertices() << std::endl;
		std::cout << "f " << mesh.n_faces() << std::endl;

		pmp::Normals::compute_face_normals(mesh);
		pmp::Normals::compute_vertex_normals(mesh);

		std::ifstream in("kitten_tpIdx.txt");
		auto tpIdx = mesh.add_face_property<int>("f:tpIdx");
		for (auto f : mesh.faces())
			in >> tpIdx[f];

		bvh = new BVH(&mesh);
	}
	void DrawComponent::DrawBezierCurve(){}

	void DrawComponent::Draw()
	{
		glClearColor(1, 1, 1, 1);
		glEnable(GL_LIGHTING);

		auto normals = mesh.get_vertex_property<pmp::Normal>("v:normal");


		for (auto f : mesh.faces()) {
			glBegin(GL_TRIANGLES);
			for (auto v : mesh.vertices(f)) {
				glNormal3dv(normals[v].data());
				glVertex3dv(mesh.position(v).data());
			}
			glEnd();
		}

		std::queue<BV*>q;
		q.push(bvh->root);
		while (!q.empty()) {
			auto curr = q.front();
			q.pop();
			if (curr->level == arrowNum0) {
				DrawAABB(curr->minPt, curr->maxPt);
			}
			if (!curr->IsLeaf()) {
				q.push(curr->left_);
				q.push(curr->right_);
			}
		}
	}

	void DrawComponent::DrawAABB(Eigen::Vector3d minPt, Eigen::Vector3d maxPt) {

		glColor3f(0, 1, 0);
		glPointSize(20.0);
		glBegin(GL_LINE_LOOP);
		glVertex3f(minPt[0], minPt[1], minPt[2]);
		glVertex3f(maxPt[0], minPt[1], minPt[2]);
		glVertex3f(maxPt[0], minPt[1], maxPt[2]);
		glVertex3f(minPt[0], minPt[1], maxPt[2]);
		glEnd();

		glBegin(GL_LINE_LOOP);
		glVertex3f(minPt[0], maxPt[1], minPt[2]);
		glVertex3f(maxPt[0], maxPt[1], minPt[2]);
		glVertex3f(maxPt[0], maxPt[1], maxPt[2]);
		glVertex3f(minPt[0], maxPt[1], maxPt[2]);
		glEnd();
		glBegin(GL_LINES);

		glVertex3f(minPt[0], minPt[1], minPt[2]);
		glVertex3f(minPt[0], maxPt[1], minPt[2]);
		glVertex3f(maxPt[0], minPt[1], minPt[2]);
		glVertex3f(maxPt[0], maxPt[1], minPt[2]);
		glVertex3f(maxPt[0], minPt[1], maxPt[2]);
		glVertex3f(maxPt[0], maxPt[1], maxPt[2]);
		glVertex3f(minPt[0], minPt[1], maxPt[2]);
		glVertex3f(minPt[0], maxPt[1], maxPt[2]);

		glEnd();

	}
}