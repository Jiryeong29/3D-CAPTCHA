#include "BVH.h"


BVH::BVH(pmp::SurfaceMesh* mesh)
{
    std::vector<pmp::Face> faces;

    for (auto f : mesh->faces())
        faces.push_back(f);

	root = new BV(mesh, faces, 0);
} 

// BV 클래스의 생성자
BV::BV(pmp::SurfaceMesh* mesh,  std::vector<pmp::Face> faces, int lv )
{
    this->faces = faces;
    minPt = { FLT_MAX, FLT_MAX , FLT_MAX }; // 최소값을 매우 큰 값으로 초기화
    maxPt = { -FLT_MAX, -FLT_MAX , -FLT_MAX }; // 최댓값을 매우 작은 값으로 초기화
    level = lv;
    left_ = nullptr; // 자식노드 초기화
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

    // 각 점을 순회하여 축 중 가장 긴 축을 계산
	int longest = FindLongest();

    // 분할하는 메서드
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
// BV좌우 자식으로 분할하는 메서드
void BV::SplitBV(int longAxis, pmp::SurfaceMesh* mesh, int lv) {

	double axisMiddleValue = (maxPt[longAxis] + minPt[longAxis]) / 2.0; //  x, y, z 축 중 길이가 가장 긴 축 중 중간 값
    std::vector<pmp::Face> rightFaces;
    std::vector<pmp::Face> leftFaces;

    // x:0,  y:1,  z:2
    // 모든 정점들을 순회해서 BV를 분할
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

// 이 노드가 리프노드인지 확인하는 메서드
bool BV::IsLeaf() {
	return left_ == nullptr && right_ == nullptr;
}