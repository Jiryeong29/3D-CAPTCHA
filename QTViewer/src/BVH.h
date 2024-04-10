#pragma once
#include "pmp/SurfaceMesh.h"

//class BV
//{
//public:
//    int level; // BV�� ����(BVH�������� ����)
//    Eigen::Vector3d minPt, maxPt; // �� BV�� �����ϴ� �ּ� �� �ִ� ��ǥ
//    std::vector<pmp::Face> faces;
//    std::vector<pmp::Vertex> vertices;
//    BV* left_, * right_; // �¿� �ڽ� BV��� ������
//    BV();
//	BV(pmp::SurfaceMesh mesh, std::vector<pmp::Face>faces, std::vector<pmp::Vertex>vertices, int lv); // ������
//    void SplitBV(); // BV�¿� �ڽ����� �����ϴ� �޼���
//    bool IsLeaf(); // �� ��尡 ����������� Ȯ���ϴ� �޼���
//    int FindLongest();
//};
//
//class BVH
//{
//private:
//
//public:
//    BV root;
//	BVH(pmp::SurfaceMesh mesh); // ������
//};

class BV
{
public:
    int level;
    Eigen::Vector3d minPt, maxPt;
    std::vector<pmp::Face>faces;
    std::vector<pmp::Vertex>vertices;
    BV* left_, * right_; // �¿� �ڽ� BV��� ������
    BV(pmp::SurfaceMesh mesh, int lv);
    void SplitBV(int longAxis); // BV�¿� �ڽ����� �����ϴ� �޼���
    bool IsLeaf(); // �� ��尡 ����������� Ȯ���ϴ� �޼���
    int FindLongest();
};
class BVH
{
public:
    BV* root;
    BVH(pmp::SurfaceMesh mesh);
};

