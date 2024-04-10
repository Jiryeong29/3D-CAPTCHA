#include "DrawComponent.h"
#include "GL/freeglut.h"
#include <iostream>
#include <sstream>
#include <fstream>
#include <vector>
#include <string>
#include "BVH.h"

#include "pmp/io/read_obj.h"
#include "pmp/algorithms/Normals.h"

/* 0) pmp - obj ���� �ε��ϴ� �Լ���, normal �������� ��� Ȯ��r
*  1) �� ��ü�� ���δ� AABB �����ϰ�, �׸���(wireframe)
*  2) AABB BVH ����� (binary tree)
*  2-1) binary tree �����ϴ� ������, x,y,z �� �� ���� �� ���� �������� �յ� �̺���
*  2-2) Ű���� ȭ��ǥ �Է�����, bvh level (root = 0, root�� ������� 2���� 1)�� ���� �����Ͽ� �ð�ȭ
*/

namespace MN
{
	void DrawComponent::Init()
	{
		pmp::read_obj(mesh, "models/kitten.obj");
		std::cout << "v " << mesh.n_vertices() << std::endl;
		std::cout << "f " << mesh.n_faces() << std::endl;

		pmp::Normals::compute_face_normals(mesh);
		pmp::Normals::compute_vertex_normals(mesh);

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

		BVH bvh(mesh);

		DrawAABB(bvh);


		double p[2];
		p[0] = 0.0;
		p[1] = 0.0;
		glColor3f(1, 0, 0);
		glPointSize(10.0);
		glBegin(GL_POINTS);
		glVertex2f(p[0], p[1]);
		glEnd();


	}
	void DrawComponent::DrawAABB(BVH& bvh) {

		glColor3f(0, 1, 0);
		glPointSize(20.0);
		glBegin(GL_LINE_LOOP);
		glVertex3f(bvh.root->minPt[0], bvh.root->minPt[1], bvh.root->minPt[2]);
		glVertex3f(bvh.root->maxPt[0], bvh.root->minPt[1], bvh.root->minPt[2]);
		glVertex3f(bvh.root->maxPt[0], bvh.root->minPt[1], bvh.root->maxPt[2]);
		glVertex3f(bvh.root->minPt[0], bvh.root->minPt[1], bvh.root->maxPt[2]);
		glEnd();

		glBegin(GL_LINE_LOOP);
		glVertex3f(bvh.root->minPt[0], bvh.root->maxPt[1], bvh.root->minPt[2]);
		glVertex3f(bvh.root->maxPt[0], bvh.root->maxPt[1], bvh.root->minPt[2]);
		glVertex3f(bvh.root->maxPt[0], bvh.root->maxPt[1], bvh.root->maxPt[2]);
		glVertex3f(bvh.root->minPt[0], bvh.root->maxPt[1], bvh.root->maxPt[2]);
		glEnd();
		glBegin(GL_LINES);

		glVertex3f(bvh.root->minPt[0], bvh.root->minPt[1], bvh.root->minPt[2]);
		glVertex3f(bvh.root->minPt[0], bvh.root->maxPt[1], bvh.root->minPt[2]);
		glVertex3f(bvh.root->maxPt[0], bvh.root->minPt[1], bvh.root->minPt[2]);
		glVertex3f(bvh.root->maxPt[0], bvh.root->maxPt[1], bvh.root->minPt[2]);
		glVertex3f(bvh.root->maxPt[0], bvh.root->minPt[1], bvh.root->maxPt[2]);
		glVertex3f(bvh.root->maxPt[0], bvh.root->maxPt[1], bvh.root->maxPt[2]);
		glVertex3f(bvh.root->minPt[0], bvh.root->minPt[1], bvh.root->maxPt[2]);
		glVertex3f(bvh.root->minPt[0], bvh.root->maxPt[1], bvh.root->maxPt[2]);

		glEnd();

	}

}