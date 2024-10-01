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

inline uint bounded_hash_64 (const string& data, const uint& bucketSize) {
    uint hash = static_cast<uint>(fnv1a_hash_64(data));
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
        uint load = 0;
        uint bucketSize = 1024;
        vector<TypedLinkedList*> hashBucket;

        /**
         * Callback to find item with `key` in `LinkedList`.
         */
        function<bool(TypedHashItem*)> checkKey(string key) {
            return [&](TypedHashItem* item) -> bool {
                return key == item->key;
            };
        };

        /**
         * Get a mutable reference to the `HashItem` at a specific `idx`.
         */
        T& getHashItemReferenceAtIdx(uint idx, string key) {
            TypedLinkedList*& linkedList = hashBucket[idx];

            // no collision
            if (linkedList == nullptr) {
                linkedList = new TypedLinkedList();
                load += 1;
            }

            auto existingItem = linkedList->getItem(checkKey(key));
            if (existingItem == nullopt) {
                TypedHashItem* newItem = new TypedHashItem(key);    
                linkedList->addItem(newItem);
                return newItem->item;
            }

            // optional<T> is a pointer to T, so need to dereference the pointer before accessing a member
            return (*existingItem)->item;
        }

        float getLoadFactor() {
            float loadFactor = static_cast<float>(load)/bucketSize;
            return loadFactor;
        }

    public:
        HashMap(): bucketSize(1024) {
            hashBucket.resize(bucketSize, nullptr);
        };
        HashMap(uint bucketSize): bucketSize(bucketSize) {
            hashBucket.resize(bucketSize, nullptr);
        };
        HashMap(const HashMap<T>& other) {
            load = other.load;
            bucketSize = other.bucketSize;
            hashBucket.resize(bucketSize, nullptr);
            for (uint i = 0; i < bucketSize; i++) {
                if (other.hashBucket[i] != nullptr) {
                    hashBucket[i] = new TypedLinkedList(*other.hashBucket[i]);
                }
            }
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
            uint idx = bounded_hash_64(key, bucketSize);
            T& hashItemReference = getHashItemReferenceAtIdx(idx, key);

            // rehash at powers of 2 if exceeds load factor threshold
            if (getLoadFactor() > 0.75) {
                rehash(bucketSize * 2);
            }

            return hashItemReference;
        };

        /**
         * `operator[]` overload returning an immutable reference to the item being accessed.
         */
        const optional<T&> operator[](string key) const {
            uint idx = bounded_hash_64(key, bucketSize);
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

        /**
         * Rehash existing entries to fit a new `hashBucket` size.
         */
        void rehash(uint size) {
            vector<TypedLinkedList*> oldHashBucket = hashBucket;
            vector<TypedLinkedList*> newHashBucket;
            newHashBucket.resize(size, nullptr);

            // update instance attributes
            hashBucket = newHashBucket;
            bucketSize = size;
            load = 0;

            for (TypedLinkedList*& list : oldHashBucket) {
                if (list != nullptr) {
                    vector<TypedHashItem*> listItems = list->dumpToVector();
                    for (TypedHashItem* hashItem : listItems) {
                        string key = hashItem->key;
                        T item = hashItem->item;
                        uint idx = bounded_hash_64(key, bucketSize);
                        getHashItemReferenceAtIdx(idx, key) = item;
                    }
                }
            }
        }

};