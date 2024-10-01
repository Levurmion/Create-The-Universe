#include <iostream>
#include <type_traits>

template <typename T>
struct ListNode {
    T data;
    ListNode<T>* next;

    ListNode(T data): data(data), next(nullptr) {};
    ListNode(T data, ListNode<T>* next): data(data), next(next) {};
    ~ListNode() {};
};


template <typename T>
class LinkedList {

    private:
        ListNode<T>* head;
        ListNode<T>* tail;

    public:
        uint length = 0;

        LinkedList() {
            head = new ListNode<T>(0);
            tail = head;
        };

        ~LinkedList() {
            ListNode<T>* currNode = head;
            while (currNode != nullptr) {
                ListNode<T>* nextNode = currNode->next;
                delete currNode;
                currNode = nextNode;
            }
        }

        void addItem(T data) {
            ListNode<T>* tailNode = tail;
            ListNode<T>* newNode = new ListNode<T>(data);
            tailNode->next = newNode;
            tail = newNode;
            length += 1;
        }

        void removeItem(const std::function<bool(T)>& predicate) {
            ListNode<T>* prevNode = head;
            ListNode<T>* currNode = head->next;
            while (currNode != nullptr) {
                if (predicate(currNode->data)) {
                    ListNode<T>* nextNode = currNode->next;
                    currNode->next = nullptr;
                    prevNode->next = nextNode;
                    if (nextNode == nullptr) {
                        tail = prevNode;
                    }
                    delete currNode;
                    length -= 1;
                    break;
                } else {
                    prevNode = currNode;
                    currNode = currNode->next;
                }
            }
        }

        /**
         * Get an item in the `LinkedList` satisfying a predicate function.
         */
        std::optional<T> getItem(const std::function<bool(T)>& predicate) {
            ListNode<T>* currNode = head->next;
            while (currNode != nullptr) {
                if (predicate(currNode->data)) {
                    return currNode->data;
                }
                currNode = currNode->next;
            }
            return std::nullopt;
        }

        /**
         * Dumps the current `LinkedList` data into a `vector`.
         */
        std::vector<T> dumpToVector() {
            std::vector<T> listVector;
            listVector.resize(length);
            ListNode<T>* currNode = head->next;
            uint idx = 0;
            while (currNode != nullptr) {
                listVector[idx] = currNode->data;
                currNode = currNode->next;
                idx += 1;
            }
            return listVector;
        }


        void printList() {
            ListNode<T>* currNode = head->next;
            std::cout << "HEAD";
            while (currNode != nullptr) {
                std::cout << "->" << currNode->data;
                currNode = currNode->next;
            }
            std::cout << "->NULL" << std::endl;
        }

};


