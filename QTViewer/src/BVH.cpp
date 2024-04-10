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

// BV 클래스의 생성자
BV::BV(pmp::SurfaceMesh mesh, int lv)
{
    minPt = { FLT_MAX, FLT_MAX , FLT_MAX }; // 최소값을 매우 큰 값으로 초기화
    maxPt = { -FLT_MAX, -FLT_MAX , -FLT_MAX }; // 최댓값을 매우 작은 값으로 초기화
    level = lv;
    left_ = nullptr; // 자식노드 초기화
    right_ = nullptr;

    for (auto v : mesh.vertices()) {
        auto p = mesh.position(v);
        for (int i = 0; i < 3; i++) {
            minPt[i] = std::min(minPt[i], p[i]);
            maxPt[i] = std::max(maxPt[i], p[i]);
        }
    }

    // 각 점을 순회하여 축 중 가장 긴 축을 계산
    std::cout << FindLongest();

    // 분할하는 메서드
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

// BV좌우 자식으로 분할하는 메서드
void BV::SplitBV(int longAxis) {

}
// 이 노드가 리프노드인지 확인하는 메서드
bool BV::IsLeaf() {

}
int BV::FindLongest(){

}