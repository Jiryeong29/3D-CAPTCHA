#include "BVH.h"


BVH::BVH(pmp::SurfaceMesh* mesh)
{
    std::vector<pmp::Face> faces;

    for (auto f : mesh->faces())
        faces.push_back(f);

	root = new BV(mesh, faces, 0);
} 

// BV Ŭ������ ������
BV::BV(pmp::SurfaceMesh* mesh,  std::vector<pmp::Face> faces, int lv )
{
    this->faces = faces;
    minPt = { FLT_MAX, FLT_MAX , FLT_MAX }; // �ּҰ��� �ſ� ū ������ �ʱ�ȭ
    maxPt = { -FLT_MAX, -FLT_MAX , -FLT_MAX }; // �ִ��� �ſ� ���� ������ �ʱ�ȭ
    level = lv;
    left_ = nullptr; // �ڽĳ�� �ʱ�ȭ
    right_ = nullptr;

    for (auto f : this->faces) {
		for (auto v : mesh->vertices(f)) {
			auto p = mesh->position(v);
			for (int i = 0; i < 3; i++) {
				minPt[i] = std::min(minPt[i], p[i]);
				maxPt[i] = std::max(maxPt[i], p[i]);
			}
		}
    }

    // �� ���� ��ȸ�Ͽ� �� �� ���� �� ���� ���
	int longest = FindLongest();

    // �����ϴ� �޼���
    SplitBV(longest, mesh, lv);
}
int BV::FindLongest()
{
    //x:0, y:1, z:2

    Eigen::Vector3d findMaxAxis;
    int longAxis;
    double tmp = -9999;

    for (int i = 0; i < 3; i++) {
        findMaxAxis[i] = maxPt[i] - minPt[i];
        if (tmp <= findMaxAxis[i]) {
            longAxis = i;
        }
        tmp = findMaxAxis[i];
    }

    return longAxis;
}
// BV�¿� �ڽ����� �����ϴ� �޼���
void BV::SplitBV(int longAxis, pmp::SurfaceMesh* mesh, int lv) {

	double axisMiddleValue = (maxPt[longAxis] + minPt[longAxis]) / 2.0; //  x, y, z �� �� ���̰� ���� �� �� �� �߰� ��
    std::vector<pmp::Face> rightFaces;
    std::vector<pmp::Face> leftFaces;

    // x:0,  y:1,  z:2
    // ��� �������� ��ȸ�ؼ� BV�� ����
    for (int i = 0; i < faces.size(); i++) {
        int count = 0;
        for (auto v : mesh->vertices(faces[i])) {
            auto p = mesh->position(v);
            if (p[longAxis] >= axisMiddleValue) count++;
        }
        if (count>=2) {     // right
            rightFaces.push_back(faces[i]);
        }
        else {              // left
            leftFaces.push_back(faces[i]);
        }
    }
    if (!leftFaces.empty() && !rightFaces.empty()) {
        left_ = new BV(mesh, leftFaces, lv + 1);
        right_ = new BV(mesh, rightFaces, lv + 1);
    }
}

// �� ��尡 ����������� Ȯ���ϴ� �޼���
bool BV::IsLeaf() {
	return left_ == nullptr && right_ == nullptr;
}