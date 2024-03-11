import Vector;

#include <iostream>

int main() {
    using namespace std;
    Vector<int> v1, v3;

    v1.push_back(10);
    v1.push_back(20);
    v1.push_back(30);
    v1.push_back(40);
    v1.push_back(50);

    cout << "v1 = ";
    for (auto &v : v1) {
        cout << v << " ";
    }
    cout << endl;

    v3.assign(7, 4);
    cout << "v3 = ";
    for (auto &v : v3) {
        cout << v << " ";
    }
    cout << endl;
}