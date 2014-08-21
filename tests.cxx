#include <iostream>
#include <cassert>
#include "lru.hpp"

int main()
{
    /* test list case #1 */
    {
        lru::list<int> lruCache({1,2,3,4,5,6,7,8,9,10,11,12});
        std::cout << lruCache << std::endl;
    }

    /* test list case #2 */
    {
        lru::list<int> lruCache; //({1,2,3,4,5,6,7,8,9,10,11,12});

        lruCache.resize(10);

        lruCache.insert(5);  std::cout << lruCache << std::endl;
        lruCache.insert(7);  std::cout << lruCache << std::endl;
        lruCache.insert(15); std::cout << lruCache << std::endl;
        lruCache.insert(34); std::cout << lruCache << std::endl;
        lruCache.insert(23); std::cout << lruCache << std::endl;
        lruCache.insert(21); std::cout << lruCache << std::endl;
        lruCache.insert(7);  std::cout << lruCache << std::endl;
        lruCache.insert(32); std::cout << lruCache << std::endl;
        lruCache.insert(34); std::cout << lruCache << std::endl;
        lruCache.insert(35); std::cout << lruCache << std::endl;
        lruCache.insert(15); std::cout << lruCache << std::endl;
        lruCache.insert(37); std::cout << lruCache << std::endl;
        lruCache.insert(17); std::cout << lruCache << std::endl;
        lruCache.insert(28); std::cout << lruCache << std::endl;
        lruCache.insert(16); std::cout << lruCache << std::endl;

        /*
            5
            7 5
            15 7 5
            34 15 7 5
            23 34 15 7 5
            21 23 34 15 7 5
            7 21 23 34 15 5
            32 7 21 23 34 15 5
            34 32 7 21 23 15 5
            35 34 32 7 21 23 15 5
            15 35 34 32 7 21 23 5
            37 15 35 34 32 7 21 23 5
            17 37 15 35 34 32 7 21 23 5
            28 17 37 15 35 34 32 7 21 23
            16 28 17 37 15 35 34 32 7 21
        */

        lruCache.insert(28); std::cout << lruCache << std::endl;

        assert( lruCache.find(7) != lruCache.end() );
        lruCache.erase(7);   std::cout << lruCache << std::endl;
        assert( lruCache.find(7) == lruCache.end() );

        assert( lruCache.find(16) != lruCache.end() );
        lruCache.erase(16);  std::cout << lruCache << std::endl;
        assert( lruCache.find(16) == lruCache.end() );
    }

    /* test map #1 */
    {
        lru::map<char,int> lruCache;

        lruCache.resize(4);

        lruCache.insert( 'a', 1 );
        lruCache.insert( 'b', 2 );
        lruCache.insert( 'c', 3 );
        lruCache.insert( 'd', 4 );

        std::cout << lruCache << std::endl;
        assert( lruCache.begin()->first == 'd' );

        std::cout << lruCache << std::endl;
        lruCache['a'];

        std::cout << lruCache << std::endl;
        assert( lruCache.begin()->first == 'a' );

        std::cout << lruCache << std::endl;
        std::cout << lruCache['d'] << std::endl;
        assert( lruCache['d'] == 4 );

        std::cout << lruCache << std::endl;
        assert( lruCache['c'] == 3 );

        std::cout << lruCache << std::endl;
    }

    /* test map #2 */
    {
        lru::map<char,int> lruCache( {{'a',1}, {'b', 2}, {'c', 3}, {'d', 4}} );

        std::cout << lruCache << std::endl;
        std::cout << lruCache['a'] << std::endl;
        std::cout << lruCache['b'] << std::endl;
        std::cout << lruCache['c'] << std::endl;
        std::cout << lruCache['d'] << std::endl;
        assert(lruCache['d'] == 4);
    }

    std::cout << "All ok." << std::endl;
}
