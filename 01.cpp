#include <vector>
#include <iostream>
//计算顶点坐标的平均值
struct vec3 {
    double x, y, z;
    vec3(double x_ = 0.0f, double y_ = 0.0f, double z_ = 0.0f) : x(x_), y(y_), z(z_) {}
 };

vec3 calcularCentroide(const std::vector<vec3>& vertices) {
    vec3 centroide(0.0f, 0.0f, 0.0f); 
    for (const auto& vertice : vertices) {
        centroide.x += vertice.x;
        centroide.y += vertice.y;
        centroide.z += vertice.z;
    }
    centroide.x /= vertices.size();
    centroide.y /= vertices.size();
    centroide.z /= vertices.size();
    return centroide;
}

int main() {
    std::vector<vec3> vertices = {
        vec3(1.0f, 2.0f, 3.0f),
        vec3(4.0f, 5.0f, 6.0f),
        vec3(7.0f, 8.0f, 9.0f)
    };

    vec3 centroide = calcularCentroide(vertices);
    std::cout << "Centroide: (" << centroide.x << ", " << centroide.y << ", " << centroide.z << ")" << std::endl;

    return 0;
}








