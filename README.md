LRU <a href="https://travis-ci.org/r-lyeh/LRU"><img src="https://api.travis-ci.org/r-lyeh/LRU.svg?branch=master" align="right" /></a>
===

- LRU is a lightweight [LRU cache structure](http://en.wikipedia.org/wiki/Least_Recently_Used#LRU) for list<T> and map<K,V> containers. Written in C++11
- LRU is stand-alone. No dependencies.
- LRU is tiny. Header only.
- LRU is cross-platform.
- LRU is zlib/libpng licensed.

### Quick tutorial
- Create a `lru::list<T>` or `lru::map<K,V>` structure as needed.
- Both structures are `ostream` friendly and match STL `std::list` members API (`cbegin`, `begin`, etc).
- Specify a cache limit by calling `.resize(N)` to desired `N` elements in runtime.
- If `N` is smaller than `.size()` values in tail will be truncated.
- `.insert(K)` or `.insert(K,V)` to insert elements into head.
- If `.size()` is bigger than `N`, tail element will be removed.
- `.erase(K)` to remove elements.
- `.find(K)` on inserted keys will promote element to head and return actual `.begin()` iterator.
- `.find(K)` on deprecated keys will return `.end()`.
- `operator[K]` on insert keys will promote element to head and return actual reference to value.
- `operator[K]` on deprecated keys will result in undefined behavior.

### Sample
```c++
#include "lru.hpp"
#include <iostream>

int main() {
    lru::map<int,char> map;
    map.resize(3);
    map[100] = 'a';  // 100:'a'
    map[ 99] = 'b';  // 99:'b' 100:'a'
    map[ 98] = 'c';  // 98:'c' 99:'b' 100:'a'
    map[ 97] = 'd';  // 97:'d' 98:'c' 99:'b' ; will also pop {100:'a'} from tail
    std::cout << map[99] << std::endl; // prints 'b' and promotes {99:'b'} to head
    std::cout << map << std::endl;     // prints 99:'b' 97:'d' 98:'c'
}
```

### Possible output
```
b
99:b 97:d 98:c
```
