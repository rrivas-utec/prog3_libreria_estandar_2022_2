#include <iostream>
#include <vector>
#include <list>
#include <type_traits>
#include <forward_list>
#include <algorithm>
using namespace std;

typedef vector<int>::iterator iterator_t;

bool pares(int a) {
    return a % 2 == 0;
}

void ejemplo_1() {
    // Usan iteradores Random
    vector<int> v = {10, 20, 30, 40, 50};
    auto it1 = v.begin();   // Notacion punto, o funciones miembro
    cout << *(it1 + 1) << endl;
    cout << it1[1] << endl;
    for (auto it = begin(v); it != end(v); ++it)
        cout << *it << endl;

    // Modificar
    for (auto& item: v)
        item += 1;
    for (auto it = begin(v); it != end(v); ++it)
        *it += 1;
    // Leer datos
    for (const auto& item: v)
        cout << item;
    for (auto it = cbegin(v); it != cend(v); ++it)
        cout << *it;

//    bool x = 10;
//    if (is_same<decltype(x), int>::value)
//        cout << "Es entero";


    // Usan iteradores bidireccionales
    list<int> l = {10, 20, 30, 40, 50};
    auto it2 = begin(l);    //No funciones miembro
    cout << *it2 << endl;
    cout << *++it2 << endl;
    cout << *--it2 << endl;
    it2++;
    it2++;  // 30
    cout << "sub-indice: " << distance(begin(l), it2) << endl;
    it2++;
    cout << *it2 << endl;



    // Usan iteradores forward
    forward_list<int> f = {10, 20, 30, 40, 50};
    auto it3 = begin(f);
    cout << *it3 << endl;
    cout << *++it3 << endl;
    // cout << *--it3 << endl;

}

void ejemplo_2() {
    list<int> l = {10, 20, 30, 40, 50};
    auto it2 = begin(l);    //No funciones miembro
    cout << *it2 << endl;
    cout << *++it2 << endl;
    cout << *--it2 << endl;
    it2++;
    it2++;  // 30
    cout << "sub-indice: " << distance(begin(l), it2) << endl;
    it2++;
    cout << *it2 << endl;
//    it2 = it2 - 3;
    it2 = prev(it2, 3);
    cout << *it2 << endl;
//    it2 = it2 + 3;
//    it2 = next(it2, 3);
    advance(it2, 3);
    cout << *it2 << endl;
    cout << l.size() << endl;
    cout << size(l) << endl;
}

// Algoritmos no modificables
void ejemplo_count() {

    // Funciones sin nombres
    auto base = 3;
    auto lambda_pares = [base] (auto a) {
        return a % base == 0;
    };

    list<int> l = {1, 2, 3, 2, 5, 3, 4, 5, 6, 1, 2, 3, 4, 8};
    auto cant1 = count(begin(l), end(l), 2);
    cout << cant1 << endl;
    auto cant2 = count_if(begin(l), end(l), pares); // Utilizando funcion
    cout << cant2 << endl;
    auto cant3 = count_if(begin(l), end(l), lambda_pares); // Utilizando lambda predefinido
    cout << cant3 << endl;
    auto cant4 = count_if(begin(l), end(l), [&base](auto a){ // Utilizando un lambda en linea // Base es modificable
        base = 3;
        return a % base == 0;
    }); // Utilizando callables
    cout << cant4 << endl;
}

int main() {
//    ejemplo_2();
    ejemplo_count();
    return 0;
}
