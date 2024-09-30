#include <iostream>
#include "../linked_list/linked_list.cpp"

using namespace std;

inline uint64_t fnv1a_hash_64 (const string& data) {
    const uint64_t prime = 1099511628211ULL;
    uint64_t hash = 14695981039346656037ULL;

    for (unsigned char byte : data) {
        hash ^= byte;
        hash *= prime;
    }

    return hash;
}

inline unsigned int bounded_hash_64 (const string& data, const unsigned int& bucketSize) {
    unsigned int hash = static_cast<unsigned int>(fnv1a_hash_64(data));
    return hash % bucketSize;
}

template <typename T>
struct HashItem {
    string key;
    T item;

    HashItem(string key): key(key) {};
    HashItem(string key, T item): key(key), item(item) {};
    ~HashItem() {}; 
};

template <typename T>
class HashMap {

    typedef HashItem<T> TypedHashItem;
    typedef LinkedList<TypedHashItem*> TypedLinkedList;
    
    private:
        unsigned int load = 0;
        unsigned int bucketSize = 1024;
        vector<TypedLinkedList*> hashBucket;

        /**
         * Callback to find item with `key` in `LinkedList`.
         */
        function<bool(TypedHashItem*)> checkKey(string key) {
            return [&](TypedHashItem* item) -> bool {
                return key == item->key;
            };
        }

    public:
        HashMap(): bucketSize(1024) {
            hashBucket.resize(bucketSize, nullptr);
        };
        HashMap(unsigned int bucketSize): bucketSize(bucketSize) {
            hashBucket.resize(bucketSize, nullptr);
        };
        ~HashMap() {
            for (TypedLinkedList* linkedList : hashBucket) {
                delete linkedList;
            }
        }

        /**
         * `operator[]` overload returning a mutable reference to the item to be modified.
         */
        T& operator[](string key) {
            unsigned int idx = bounded_hash_64(key, bucketSize);
            TypedLinkedList*& linkedList = hashBucket[idx];

            if (linkedList == nullptr) {
                linkedList = new TypedLinkedList();
            }

            auto existingItem = linkedList->getItem(checkKey(key));
            if (existingItem == nullopt) {
                TypedHashItem* newItem = new TypedHashItem(key);    
                linkedList->addItem(newItem);
                return newItem->item;
            }

            // optional<T> is a pointer to T, so need to dereference the pointer before accessing a member
            return (*existingItem)->item;
        };

        /**
         * `operator[]` overload returning an immutable reference to the item being accessed.
         */
        const optional<T&> operator[](string key) const {
            unsigned int idx = bounded_hash_64(key, bucketSize);
            if (hashBucket[idx] == nullptr) {
                return nullopt;
            } else {
                TypedLinkedList* linkedList = hashBucket[idx];
                auto hashItem = linkedList->getItem(checkKey(key));
                if (hashItem != nullopt) {
                    return (*hashItem)->item;
                } else {
                    return nullopt;
                }
            }
        };


};