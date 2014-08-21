// A lightweight LRU cache structure for list<T> and map<K,V> containers. Written in C++11
// - rlyeh, mit licensed.

#pragma once

#include <map>
#include <list>

// why list container? ~deque container, where only:
// erase, pop_front, pop_back, clear
// will invalidate the iterators and references to the erased elements.

// @todo:
// split cache class into lru::list and lru::map different classes eventually.

namespace lru {

    template<typename K,typename V = K>
    class cache : public std::list< std::pair<K,V> > {
        const bool equivalent = ( typeid(K).hash_code() == typeid(V).hash_code() );
        using list_t = std::list< std::pair<K,V> >;
        std::map<typename K,typename list_t::iterator> map;
        size_t limit;

    public:

        using key_type = K;
        using value_type = V;

        explicit
        cache( const std::initializer_list<K> &&list = {} ) : list_t(), limit( list.size() ) {
            std::list<K> inv( list );
            for( auto it = inv.rbegin(), end = inv.rend(); it != end; ++it ) { // @todo: std::rbegin(list) (c++14)
                insert( *it );
            }
        }

        cache( const std::initializer_list<std::pair<K,V>> &&list ) : list_t(), limit( list.size() ) {
            std::list<std::pair<K,V>> inv( list );
            for( auto it = inv.rbegin(), end = inv.rend(); it != end; ++it ) { // @todo: std::rbegin(list) (c++14)
                insert( it->first, it->second );
            }
        }

        void resize( size_t nth ) {
            list_t &list = *this;
            limit = nth;
            while( list.size() > limit ) {
                map.erase( list.back().first );
                list.pop_back();
            }
        }

        typename list_t::iterator find( const K &k ) {
            // if not found return end() list iterator
            auto found = map.find( k );
            if( found == map.end() ) {
                return this->end();
            }
            // if found reinsert (promote to top) and return it
            auto copy = found->second->second;
            insert( k, copy );
            return this->begin();
        }

        typename list_t::iterator insert( const K &k, const V &v ) {
            list_t &list = *this;

            auto found = map.find(k);
            if( found == map.end() ) {
                list.push_front({k,v});
                map.insert( {k,list.begin()} );
                found = map.find(k);
                if( list.size() > limit ) {
                    map.erase( list.back().first );
                    list.pop_back();
                }
            } else {
                list.erase(found->second);
                list.push_front({k,v});
                found->second = list.begin();
            }

            return found->second;
        }

        typename list_t::iterator insert( const V &v ) {
            return insert( K(v), v );
        }

        void erase( const K &k ) {
            list_t &list = *this;

            auto found = map.find(k);
            if( found != map.end() ) {
                list.erase(found->second);
                map.erase(found);
            }
        }

        V &operator[]( const K &k ) {
            // if found, return it (~promoted), else insert it
            auto found = find(k);
            if( found == this->end() ) {
                return insert(k)->second;
            } else {
                return found->second;
            }
        }
        const V &operator[]( const K &k ) const {
            return find(k)->second;
        }

        template<typename ostream>
        friend inline ostream &operator <<( ostream &os, const cache &self ) {
            if( self.equivalent ) {
                for( auto &in : self ) {
                    os << in.first << " ";
                }
            } else {
                for( auto &in : self ) {
                    os << in.first << ":" << in.second << " ";
                }
            }
            return os;
        }
    };

    template<typename T>
    using list = cache<T>;

    template<typename K, typename V>
    using map = cache<K, V>;
}
