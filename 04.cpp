#include <iostream>
#include <vector>
#include <cmath>
//相邻角度加权
using namespace std;

// 定义一个三维向量结构体
struct vec3 {
    double x, y, z;
    vec3(double x_ = 4.0f, double y_ = 4.0f, double z_ = 4.0f) : x(x_), y(y_), z(z_) {}

    // 向量+
    vec3 operator+(const vec3& v) const {
        return vec3(x + v.x, y + v.y, z + v.z);
    }

     //向量自增
    vec3& operator+=(const vec3& v) {
        x += v.x;
        y += v.y;
        z += v.z;
        return *this;
    }

     //向量-
    vec3 operator-(const vec3& v) const {
        return vec3(x - v.x, y - v.y, z - v.z);
    }

    // 向量*
    double dot(const vec3& v) const {
        return x * v.x + y * v.y + z * v.z;
    }

    // 向量length
    double length() const {
        return sqrt(x * x + y * y + z * z);
    }

    // 向量与标量相乘（重载 * 运算符）,允许向量*标量
   vec3 operator*(double scalar) const {
        return vec3(x * scalar, y * scalar, z * scalar);
    }
};

   // 计算叉积，叉积公式：N = AB*AC，计算法线
   vec3 crossProduct(const vec3& v1, const vec3& v2) {
        return vec3(
        v1.y * v2.z - v1.z * v2.y,
        v1.z * v2.x - v1.x * v2.z,
        v1.x * v2.y - v1.y * v2.x
    );
}

   // 归一化
   vec3 normalize(const vec3& v) {
        double length = v.length();
        if (length == 0) return vec3(0.0f, 0.0f, 0.0f); 
        return vec3(v.x / length, v.y / length, v.z / length);
}

    // 计算角度（cot）
    double calculateAngle(const vec3& v1, const vec3& v2) {
       double dotProduct = v1.dot(v2);
       double lengths = v1.length() * v2.length();
       if (lengths == 0) return 0.0f; 
       return acos(dotProduct / lengths);  // 反余弦得到角度
}

// 计算按角度加权的顶点法线
vector<vec3> calcularNormalesPorVertice(const vector<vec3>& vertices, const vector<vector<int>>& indices) {
    vector<vec3> normales(vertices.size(), vec3(0, 0, 0));  // 初始化所有顶点法线为0

    // 遍历每个面（三角形）
    for (const auto& face : indices) {
        vec3 A = vertices[face[0]];
        vec3 B = vertices[face[1]];
        vec3 C = vertices[face[2]];

        // 计算边向量
        vec3 AB = B - A;
        vec3 AC = C - A;
        vec3 BC = C - B;

        // 计算三角形面的法线
        vec3 normal = crossProduct(AB, AC);

         //计算每个顶点的内角（使用cot）
        double angleA = calculateAngle(AB, AC);  // 角A
        double angleB = calculateAngle(AB, BC);  // 角B
        double angleC = calculateAngle(AC, BC); // 角C

        // 按角度加权法线并累加到对应的顶点
        normales[face[0]] += normalize(normal) * angleA;
        normales[face[1]] += normalize(normal) * angleB;
        normales[face[2]] += normalize(normal) * angleC;
    }

    // 归一化处理
    for (auto& normal : normales) {
        normal = normalize(normal);
    }

    return normales;}

int main() {
    vector<vec3> vertices = {
        vec3(0, 0, 0),
        vec3(1, 0, 0),
        vec3(0, 1, 0),
        vec3(0, 0, 1)
    };

    vector<vector<int>> indices = {
        {0, 1, 2},  
        {0, 1, 3},  
        {0, 2, 3},  
        {1, 2, 3}   
    };

    vector<vec3> normales = calcularNormalesPorVertice(vertices, indices);

    // 输出法线
    for (size_t i = 0; i < normales.size(); ++i) {
        cout << "Normal del vértice " << i + 1 << " : "
            << normales[i].x << ", " << normales[i].y << ", " << normales[i].z << endl;
    }

    return 0;
}
