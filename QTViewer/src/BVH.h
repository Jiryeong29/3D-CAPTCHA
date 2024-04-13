#pragma once
#include "pmp/SurfaceMesh.h"


class BV
{

public:
    int level;
    Eigen::Vector3d minPt, maxPt;
    std::vector<pmp::Face>faces;
    BV* left_, * right_; // 좌우 자식 BV노드 포인터
	BV(pmp::SurfaceMesh* mesh, std::vector<pmp::Face> faces, int lv);
    void SplitBV(int longAxis, pmp::SurfaceMesh* mesh, int lv); // BV좌우 자식으로 분할하는 메서드
    bool IsLeaf(); // 이 노드가 리프노드인지 확인하는 메서드
    int FindLongest();
};
class BVH
{
public:
    BV* root;
    BVH(pmp::SurfaceMesh* mesh);
};

