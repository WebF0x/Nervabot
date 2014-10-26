#ifndef _STL_SET_H
#define _STL_SET_H

#include "initializer_list.h"

namespace std
{
    template <class Key, class Compare = less<Key>,
              class Allocator = allocator<Key> >
        class set;

    template <class Key, class Compare, class Allocator>
        bool operator==(const set<Key,Compare,Allocator>& x,
                        const set<Key,Compare,Allocator>& y);
    template <class Key, class Compare, class Allocator>
        bool operator< (const set<Key,Compare,Allocator>& x,
                        const set<Key,Compare,Allocator>& y);
    template <class Key, class Compare, class Allocator>
        bool operator!=(const set<Key,Compare,Allocator>& x,
                        const set<Key,Compare,Allocator>& y);
    template <class Key, class Compare, class Allocator>
        bool operator> (const set<Key,Compare,Allocator>& x,
                        const set<Key,Compare,Allocator>& y);
    template <class Key, class Compare, class Allocator>
        bool operator>=(const set<Key,Compare,Allocator>& x,
                        const set<Key,Compare,Allocator>& y);
    template <class Key, class Compare, class Allocator>
        bool operator<=(const set<Key,Compare,Allocator>& x,
                        const set<Key,Compare,Allocator>& y);
 
    template <class Key, class Compare, class Allocator>
        void swap(set<Key,Compare,Allocator>& x,
                  set<Key,Compare,Allocator>& y);
 
    template <class Key, class Compare = less<Key>,
             class Allocator = allocator<Key> >
        class multiset;
 
    template <class Key, class Compare, class Allocator>
        bool operator==(const multiset<Key,Compare,Allocator>&
                        const multiset<Key,Compare,Allocator>& y);
    template <class Key, class Compare, class Allocator>
        bool operator< (const multiset<Key,Compare,Allocator>& x,
                        const multiset<Key,Compare,Allocator>& y);
    template <class Key, class Compare, class Allocator>
        bool operator!=(const multiset<Key,Compare,Allocator>& x,
                        const multiset<Key,Compare,Allocator>& y);
    template <class Key, class Compare, class Allocator>
        bool operator> (const multiset<Key,Compare,Allocator>& x,
                        const multiset<Key,Compare,Allocator>& y);
    template <class Key, class Compare, class Allocator>
        bool operator>=(const multiset<Key,Compare,Allocator>& x,
                        const multiset<Key,Compare,Allocator>& y);
    template <class Key, class Compare, class Allocator>
        bool operator<=(const multiset<Key,Compare,Allocator>& x,
                        const multiset<Key,Compare,Allocator>& y);
 
    template <class Key, class Compare, class Allocator>
        void swap(multiset<Key,Compare,Allocator>& x,
                  multiset<Key,Compare,Allocator>& y);
}

#endif /* _STL_SET_H */
