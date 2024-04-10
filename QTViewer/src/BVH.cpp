#include "BVH.h"


BVH::BVH(pmp::SurfaceMesh mesh)
{
    std::vector<pmp::Face> faces;
    std::vector<pmp::Vertex> vertices;

    for (auto f : mesh.faces())
        faces.push_back(f);


    for (auto v : mesh.vertices())
        vertices.push_back(v);

    root = &BV(mesh, 0);
}

// BV Ŭ������ ������
BV::BV(pmp::SurfaceMesh mesh, int lv)
{
    minPt = { FLT_MAX, FLT_MAX , FLT_MAX }; // �ּҰ��� �ſ� ū ������ �ʱ�ȭ
    maxPt = { -FLT_MAX, -FLT_MAX , -FLT_MAX }; // �ִ��� �ſ� ���� ������ �ʱ�ȭ
    level = lv;
    left_ = nullptr; // �ڽĳ�� �ʱ�ȭ
    right_ = nullptr;

    for (auto v : mesh.vertices()) {
        auto p = mesh.position(v);
        for (int i = 0; i < 3; i++) {
            minPt[i] = std::min(minPt[i], p[i]);
            maxPt[i] = std::max(maxPt[i], p[i]);
        }
    }

    // �� ���� ��ȸ�Ͽ� �� �� ���� �� ���� ���
    std::cout << FindLongest();

    // �����ϴ� �޼���
    SplitBV(FindLongest());
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
void BV::SplitBV(int longAxis) {

}
// �� ��尡 ����������� Ȯ���ϴ� �޼���
bool BV::IsLeaf() {

}
int BV::FindLongest(){

}