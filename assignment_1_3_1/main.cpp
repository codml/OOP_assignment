#include <iostream>
#include <cmath>
#define PI 3.141592 // pi 값을 매크로로 지정
using namespace std;

int main()
{
    double t_matrix[3][3] = { 0, };
    double input_degree;
    double input_vector[3];
    double output_vector[3] = { 0, };

    cout << "Degrees: ";
    cin >> input_degree;
    for (int i = 0; i < 2; i++)
        t_matrix[i][i] = pow(-1, i + 1) * cos(input_degree * PI / 180);
    for (int i = 0; i < 2; i++)
        t_matrix[i][1 - i] = sin(input_degree * PI / 180);
    // T 매트릭스 생성
    cout << "Coordinate: ";
    cin >> input_vector[0] >> input_vector[1] >> input_vector[2];
    for (int i = 0; i < 3; i++)
    {
        for (int j = 0; j < 3; j++)
            output_vector[i] += t_matrix[i][j] * input_vector[j];
        // 행렬 곱 연산
    }
    for (int i = 0; i < 3; i++)
        cout << (int)output_vector[i] << " ";
    cout << endl;
}