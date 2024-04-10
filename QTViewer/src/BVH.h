#pragma once
#include "pmp/SurfaceMesh.h"

//class BV
//{
//public:
//    int level; // BV의 레벨(BVH내에서의 깊이)
//    Eigen::Vector3d minPt, maxPt; // 이 BV를 포함하는 최소 및 최대 좌표
//    std::vector<pmp::Face> faces;
//    std::vector<pmp::Vertex> vertices;
//    BV* left_, * right_; // 좌우 자식 BV노드 포인터
//    BV();
//	BV(pmp::SurfaceMesh mesh, std::vector<pmp::Face>faces, std::vector<pmp::Vertex>vertices, int lv); // 생성자
//    void SplitBV(); // BV좌우 자식으로 분할하는 메서드
//    bool IsLeaf(); // 이 노드가 리프노드인지 확인하는 메서드
//    int FindLongest();
//};
//
//class BVH
//{
//private:
//
//public:
//    BV root;
//	BVH(pmp::SurfaceMesh mesh); // 생성자
//};

class BV
{
public:
    int level;
    Eigen::Vector3d minPt, maxPt;
    std::vector<pmp::Face>faces;
    std::vector<pmp::Vertex>vertices;
    BV* left_, * right_; // 좌우 자식 BV노드 포인터
    BV(pmp::SurfaceMesh mesh, int lv);
    void SplitBV(int longAxis); // BV좌우 자식으로 분할하는 메서드
    bool IsLeaf(); // 이 노드가 리프노드인지 확인하는 메서드
    int FindLongest();
};
class BVH
{
public:
    BV* root;
    BVH(pmp::SurfaceMesh mesh);
};

