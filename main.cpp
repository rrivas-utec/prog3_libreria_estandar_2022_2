#include <iostream>
#include <vector>
#include <list>
#include <type_traits>
#include <forward_list>
#include <algorithm>
#include <functional>
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

template <typename Iterator>
auto obtener_valor_cambiado(Iterator it, typename Iterator::value_type value) {
//    // Definir una variable
//    int x = 0;
    // Definir una variable del tipo que almacena un iterador
//    typename Iterator::value_type y = value;
    auto y = value * 2;
    return y;
}

void ejemplo_3() {
    vector<int> vec = {};
    auto it = begin(vec);
    vector<int>::iterator it2 = begin(vec);
    auto val = obtener_valor_cambiado(it, 20.0);
    cout << val << endl;
}

//template <typename Iterator, typename Callable, typename Type = typename Iterator::value_type>
//Type copiar_si(Iterator start, Iterator stop, Callable func) {
//
//}

template <typename Iterator, typename Callable>
auto contar_si(Iterator start, Iterator stop, Callable func) {
    int total = 0;
    while (start != stop) {
        if (func(*start) == true)
            total++;
        start++;
    }
    return total;
}

void ejemplo_4() {
    list<int> l = {1, 2, 3, 2, 5, 3, 4, 5, 6, 1, 2, 3, 4, 8};
    int base = 2;
    auto total = contar_si(begin(l), end(l), [base](int a){
        auto result = (a % base == 0);
        return result;
    });
    cout << base << endl;
    cout << total << endl;
}

void ejemplo_5() {
    int x = 10;
    auto lambda = [x](int y) mutable {
        x *= 10;
        return x + y;
    };
    cout << x << endl;
    cout << lambda(2) << endl;
}

void ejemplo_6() {
    int x = 10;
    int y = 20;
    int z = 30;
    int w = 40;
    auto lambda = [=](){
        return x + y  + z + w;
    };

    auto duplicar = [&](){
        x *= 2;
        y *= 2;
        z *= 2;
        w *= 2;
    };
    cout << lambda() << endl;
    duplicar();
    cout << x << y << z << w << endl;
}

int sumar(int a, int b) {
    return a + b;
}

int restar(int a, int b) {
    return a - b;
}

// Punteros a funciones
void ejemplo_7() {
    int x = 0, y = 0;
    cin >> x >> y;

    // puntero a funciones del tipo: int(int, int)
    int (*operation)(int, int) = nullptr;
    if (x > y)
        operation = restar;
    else
        operation = sumar;

    cout << operation(x, y);

}

void ejemplo_8() {
    // Vector almacena una coleccion de punteros del tipo int(*)(int, int)
    vector<int(*)(int, int)> vec;
    vec.push_back(restar);
    vec.push_back(sumar);
    int x = 0, y = 0;
    cin >> x >> y;
    for (auto& op: vec)
        cout << op(x, y) << endl;
}

void ejemplo_9() {
    list<function<int(int, int)>> lst;
    lst.emplace_back(restar);
    lst.emplace_back(sumar);
    int x = 0, y = 0;
    cin >> x >> y;
    for (auto& op: lst)
        cout << op(x, y) << endl;
}

int main() {
//    ejemplo_2();
//    ejemplo_count();
//    ejemplo_3();
//    ejemplo_4();
//    ejemplo_5();
//    ejemplo_6();
//    ejemplo_8();
    ejemplo_9();
    return 0;
}
