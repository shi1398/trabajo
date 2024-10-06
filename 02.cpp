#include <iostream>
#include <vector>
#include <cmath>
//����ÿ����ķ���ֵ
using namespace std;
struct vec3 {
    double x, y, z;
    vec3(double x_ = 2.0f, double y_ = 2.0f, double z_ = 2.0f) : x(x_), y(y_), z(z_) {}

     //�������������������
    vec3 operator-(const vec3& v) const {
        return vec3(x - v.x, y - v.y, z - v.z);
    }
};
     //�������������ʽ��N = AB*AC�����㷨��
    vec3 crossProduct(const vec3& v1, const vec3& v2) {
        return vec3(
        v1.y * v2.z - v1.z * v2.y,
        v1.z * v2.x - v1.x * v2.z,
        v1.x * v2.y - v1.y * v2.x
    );
}
     // ��һ��
    vec3 normalize(const vec3& v) {
        double length = sqrt(v.x * v.x + v.y * v.y + v.z * v.z);
        if (length == 0) return vec3(0.0f, 0.0f, 0.0f);  // ����
        return vec3(v.x / length, v.y / length, v.z / length);
}
     //����ÿ����������ķ���
    vector<vec3> calcularNormalesPorFaceta(const vector<vec3>& vertices, const vector<vector<int>>& indices) {
    vector<vec3> normales;

    for (const auto& face : indices) {
        vec3 A = vertices[face[0]];
        vec3 B = vertices[face[1]];
        vec3 C = vertices[face[2]];
      
        vec3 AB = B - A;
        vec3 AC = C - A;
      
        vec3 normal = crossProduct(AB, AC);
         //�����߹�һ��
        normales.push_back(normalize(normal));
    }

    return normales;
}

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

    // ����ÿ����ķ���
    vector<vec3> normales = calcularNormalesPorFaceta(vertices, indices);

    // ���
    for (size_t i = 0; i < normales.size(); ++i) {
        cout << "�� " << i + 1 << " �ķ���: "
            << normales[i].x << ", " << normales[i].y << ", " << normales[i].z << endl;
    }

    return 0;
}