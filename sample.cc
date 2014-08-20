#include "lru.hpp"
#include <iostream>

int main() {
    lru::map<int,char> map;
    map.resize(3);
    map[100] = 'a';  // 100:'a'
    map[ 99] = 'b';  // 99:'b' 100:'a'
    map[ 98] = 'c';  // 98:'c' 99:'b' 100:'a'
    map[ 97] = 'd';  // 97:'d' 98:'c' 99:'b' ; will also pop {100:'a'} from tail
    std::cout << map[99] << std::endl; // prints 'd' and promotes {99:'b'} to head

    std::cout << map << std::endl;     // prints 99:'b' 97:'d' 98:'c'
}

