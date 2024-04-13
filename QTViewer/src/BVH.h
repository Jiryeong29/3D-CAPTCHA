#pragma once
#include "pmp/SurfaceMesh.h"


class BV
{

public:
    int level;
    Eigen::Vector3d minPt, maxPt;
    std::vector<pmp::Face>faces;
    BV* left_, * right_; // �¿� �ڽ� BV��� ������
	BV(pmp::SurfaceMesh* mesh, std::vector<pmp::Face> faces, int lv);
    void SplitBV(int longAxis, pmp::SurfaceMesh* mesh, int lv); // BV�¿� �ڽ����� �����ϴ� �޼���
    bool IsLeaf(); // �� ��尡 ����������� Ȯ���ϴ� �޼���
    int FindLongest();
};
class BVH
{
public:
    BV* root;
    BVH(pmp::SurfaceMesh* mesh);
};

