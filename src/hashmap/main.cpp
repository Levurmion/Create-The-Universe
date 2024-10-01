#include <iostream>
#include <string>
#include <random>
#include <algorithm>
#include "./hashmap.cpp"

std::string generateRandomString(size_t length) {
    const std::string characters = "abcdefghijklmnopqrstuvwxyz"
                                   "ABCDEFGHIJKLMNOPQRSTUVWXYZ"
                                   "0123456789";
                                   
    // Use random_device to seed the random number generator
    std::random_device rd;  
    std::mt19937 generator(rd());  // Mersenne Twister random number generator
    std::uniform_int_distribution<> distribution(0, characters.size() - 1);

    // Generate a random string
    std::string randomString;
    for (size_t i = 0; i < length; ++i) {
        randomString += characters[distribution(generator)];
    }
    return randomString;
}

int main () {

    HashMap<int> map = HashMap<int>(64);

    for (uint i = 0; i < 500000; i++) {
        map[generateRandomString(10)] = i;
    }

    return 0;
}
