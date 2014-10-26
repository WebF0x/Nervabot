#ifndef _STL_MAP_H
#define _STL_MAP_H

#include "initializer_list.h"

namespace std {
    template <class Key, class T, class Compare = less<Key>,
              class Allocator = allocator<pair<const Key, T> > >
        class map;

    template <class Key, class T, class Compare, class Allocator>
        bool operator==(const map<Key,T,Compare,Allocator>& x,
                        const map<Key,T,Compare,Allocator>& y);
    template <class Key, class T, class Compare, class Allocator>
        bool operator< (const map<Key,T,Compare,Allocator>& x,
                        const map<Key,T,Compare,Allocator>& y);
    template <class Key, class T, class Compare, class Allocator>
        bool operator!=(const map<Key,T,Compare,Allocator>& x,
                        const map<Key,T,Compare,Allocator>& y);
    template <class Key, class T, class Compare, class Allocator>
        bool operator> (const map<Key,T,Compare,Allocator>& x,
                        const map<Key,T,Compare,Allocator>& y);
    template <class Key, class T, class Compare, class Allocator>
        bool operator>=(const map<Key,T,Compare,Allocator>& x,
                        const map<Key,T,Compare,Allocator>& y);
    template <class Key, class T, class Compare, class Allocator>
        bool operator<=(const map<Key,T,Compare,Allocator>& x,
                        const map<Key,T,Compare,Allocator>& y);

    template <class Key, class T, class Compare, class Allocator>
        void swap(map<Key,T,Compare,Allocator>& x,
                  map<Key,T,Compare,Allocator>& y);
 
 
    template <class Key, class T, class Compare = less<Key>,
              class Allocator = allocator<pair<const Key, T> > >
        class multimap;
 
    template <class Key, class T, class Compare, class Allocator>
        bool operator==(const multimap<Key,T,Compare,Allocator>& x,
                        const multimap<Key,T,Compare,Allocator>& y);
    template <class Key, class T, class Compare, class Allocator>
        bool operator< (const multimap<Key,T,Compare,Allocator>& x,
                        const multimap<Key,T,Compare,Allocator>& y);
    template <class Key, class T, class Compare, class Allocator>
        bool operator!=(const multimap<Key,T,Compare,Allocator>& x,
                        const multimap<Key,T,Compare,Allocator>& y);
    template <class Key, class T, class Compare, class Allocator>
        bool operator> (const multimap<Key,T,Compare,Allocator>& x,
                        const multimap<Key,T,Compare,Allocator>& y);
    template <class Key, class T, class Compare, class Allocator>
        bool operator>=(const multimap<Key,T,Compare,Allocator>& x,
                        const multimap<Key,T,Compare,Allocator>& y);
    template <class Key, class T, class Compare, class Allocator>
        bool operator<=(const multimap<Key,T,Compare,Allocator>& x,
                        const multimap<Key,T,Compare,Allocator>& y);
 
    template <class Key, class T, class Compare, class Allocator>
        void swap(multimap<Key,T,Compare,Allocator>& x,
                  multimap<Key,T,Compare,Allocator>& y);
}

#endif /* _STL_MAP_H */
