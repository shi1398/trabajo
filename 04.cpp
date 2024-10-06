#include <iostream>
#include <vector>
#include <cmath>
//���ڽǶȼ�Ȩ
using namespace std;

// ����һ����ά�����ṹ��
struct vec3 {
    double x, y, z;
    vec3(double x_ = 4.0f, double y_ = 4.0f, double z_ = 4.0f) : x(x_), y(y_), z(z_) {}

    // ����+
    vec3 operator+(const vec3& v) const {
        return vec3(x + v.x, y + v.y, z + v.z);
    }

     //��������
    vec3& operator+=(const vec3& v) {
        x += v.x;
        y += v.y;
        z += v.z;
        return *this;
    }

     //����-
    vec3 operator-(const vec3& v) const {
        return vec3(x - v.x, y - v.y, z - v.z);
    }

    // ����*
    double dot(const vec3& v) const {
        return x * v.x + y * v.y + z * v.z;
    }

    // ����length
    double length() const {
        return sqrt(x * x + y * y + z * z);
    }

    // �����������ˣ����� * �������,��������*����
   vec3 operator*(double scalar) const {
        return vec3(x * scalar, y * scalar, z * scalar);
    }
};

   // �������������ʽ��N = AB*AC�����㷨��
   vec3 crossProduct(const vec3& v1, const vec3& v2) {
        return vec3(
        v1.y * v2.z - v1.z * v2.y,
        v1.z * v2.x - v1.x * v2.z,
        v1.x * v2.y - v1.y * v2.x
    );
}

   // ��һ��
   vec3 normalize(const vec3& v) {
        double length = v.length();
        if (length == 0) return vec3(0.0f, 0.0f, 0.0f); 
        return vec3(v.x / length, v.y / length, v.z / length);
}

    // ����Ƕȣ�cot��
    double calculateAngle(const vec3& v1, const vec3& v2) {
       double dotProduct = v1.dot(v2);
       double lengths = v1.length() * v2.length();
       if (lengths == 0) return 0.0f; 
       return acos(dotProduct / lengths);  // �����ҵõ��Ƕ�
}

// ���㰴�Ƕȼ�Ȩ�Ķ��㷨��
vector<vec3> calcularNormalesPorVertice(const vector<vec3>& vertices, const vector<vector<int>>& indices) {
    vector<vec3> normales(vertices.size(), vec3(0, 0, 0));  // ��ʼ�����ж��㷨��Ϊ0

    // ����ÿ���棨�����Σ�
    for (const auto& face : indices) {
        vec3 A = vertices[face[0]];
        vec3 B = vertices[face[1]];
        vec3 C = vertices[face[2]];

        // ���������
        vec3 AB = B - A;
        vec3 AC = C - A;
        vec3 BC = C - B;

        // ������������ķ���
        vec3 normal = crossProduct(AB, AC);

         //����ÿ��������ڽǣ�ʹ��cot��
        double angleA = calculateAngle(AB, AC);  // ��A
        double angleB = calculateAngle(AB, BC);  // ��B
        double angleC = calculateAngle(AC, BC); // ��C

        // ���Ƕȼ�Ȩ���߲��ۼӵ���Ӧ�Ķ���
        normales[face[0]] += normalize(normal) * angleA;
        normales[face[1]] += normalize(normal) * angleB;
        normales[face[2]] += normalize(normal) * angleC;
    }

    // ��һ������
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

    // �������
    for (size_t i = 0; i < normales.size(); ++i) {
        cout << "���� " << i + 1 << " �ķ���: "
            << normales[i].x << ", " << normales[i].y << ", " << normales[i].z << endl;
    }

    return 0;
}