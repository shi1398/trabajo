#include <iostream>
#include <vector>
#include <cmath>
//利用面积加权计算顶点法线
using namespace std;
struct vec3 {
    double x, y, z;
    vec3(double x_ = 3.0f, double y_ = 3.0f, double z_ = 3.0f) : x(x_), y(y_), z(z_) {}

   // 向量+
vec3 operator+(const vec3& v) const {
    return vec3(x + v.x, y + v.y, z + v.z);
}

// 向量自增
vec3& operator+=(const vec3& v) {
    x += v.x;
    y += v.y;
    z += v.z;
    return *this;
}

// 向量-
vec3 operator-(const vec3& v) const {
    return vec3(x - v.x, y - v.y, z - v.z);
}

// 向量*
double dot(const vec3& v) const {
    return x * v.x + y * v.y + z * v.z;
}

// 向量与标量相乘（重载 * 运算符）,允许向量*标量
vec3 operator*(double scalar) const {
    return vec3(x * scalar, y * scalar, z * scalar);
}
};

 //计算叉积，叉积公式：N = AB*AC，计算法线
vec3 crossProduct(const vec3& v1, const vec3& v2) {
    return vec3(
        v1.y * v2.z - v1.z * v2.y,
        v1.z * v2.x - v1.x * v2.z,
        v1.x * v2.y - v1.y * v2.x
    );
}

 //归一化
vec3 normalize(const vec3& v) {
    double length = sqrt(v.x * v.x + v.y * v.y + v.z * v.z);
    if (length == 0) return vec3(0.0f, 0.0f, 0.0f); 
    return vec3(v.x / length, v.y / length, v.z / length);
}

// 计算法线按面面积加权
vector<vec3> calcularNormalesPorVertice(const vector<vec3>& vertices, const vector<vector<int>>& indices) {
    vector<vec3> normales(vertices.size(), vec3(0, 0, 0));  // 初始化所有顶点法线为0

     //遍历每个面
    for (const auto& face : indices) {
        vec3 A = vertices[face[0]];
        vec3 B = vertices[face[1]];
        vec3 C = vertices[face[2]];

        // 计算边向量
        vec3 AB = B - A;
        vec3 AC = C - A;

         //使用叉积计算面的法线
        vec3 faceNormal = crossProduct(AB, AC);

        normales[face[0]] += faceNormal;
        normales[face[1]] += faceNormal;
        normales[face[2]] += faceNormal;
    }

    // 归一化
    for (auto& normal : normales) {
        normal = normalize(normal);
    }

    return normales;
}

int main() {
     //顶点列表
    vector<vec3> vertices = {
        vec3(0, 0, 0),
        vec3(1, 0, 0),
        vec3(0, 1, 0),
        vec3(0, 0, 1)
    };

     //面的顶点索引列表
    vector<vector<int>> indices = {
        {0, 1, 2},  // 面1
        {0, 1, 3},  // 面2
        {0, 2, 3},  // 面3
        {1, 2, 3}   // 面4
    };

    // 计算按面积加权的顶点法线
    vector<vec3> normales = calcularNormalesPorVertice(vertices, indices);

     //输出每个顶点的法线
    for (size_t i = 0; i < normales.size(); ++i) {
        cout << "顶点 " << i + 1 << " 的法线: "
            << normales[i].x << ", " << normales[i].y << ", " << normales[i].z << endl;
    }

    return 0;
}