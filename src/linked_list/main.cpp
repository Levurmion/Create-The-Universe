#include <iostream>
#include "./linked_list.cpp"


struct CustomStruct {
    std::string value1;
    std::string value2;

    CustomStruct(std::string value1, std::string value2): value1(value1), value2(value2) {};
    ~CustomStruct();
};


std::function<bool(CustomStruct*)> checkStructValue1(std::string value1) {
    return [&](CustomStruct* customStructB) -> bool {
        return customStructB->value1 == value1;
    };
};

int main() {
    LinkedList<int>* list = new LinkedList<int>();

    list->addItem(1);
    list->addItem(2);
    list->addItem(3);
    list->addItem(4);

    list->printList();

    list->removeItem([](int data) -> bool {
        return data == 4;
    });
    list->printList();

    list->addItem(5);
    list->addItem(5);
    list->addItem(5);

    list->printList();


    delete list;

    return 0;
}

