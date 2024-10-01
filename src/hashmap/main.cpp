#include <iostream>
#include "./hashmap.cpp"

int main () {

    HashMap<int>* pMap = new HashMap<int>();
    auto map = *pMap;
    map["key"] = 3;
    map["key2"] = 5;
    map["key4"] = 9;
    map["key"] = 44;

    map.rehash(100);
    map.rehash(1050);

    std::cout << map["key"];
    std::cout << map["key2"];
    std::cout << map["key4"];

    delete pMap;

    return 0;
}
