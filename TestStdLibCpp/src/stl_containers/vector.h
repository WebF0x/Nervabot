#ifndef _STL_VECTOR_H
#define _STL_VECTOR_H

#include "initializer_list.h"
namespace std {
    template <class T, class Allocator = allocator<T> > class vector;
 
    template <class T, class Allocator>
        bool operator==(const vector<T,Allocator>& x,const vector<T,Allocator>& y);
    template <class T, class Allocator>
        bool operator< (const vector<T,Allocator>& x,const vector<T,Allocator>& y);
    template <class T, class Allocator>
        bool operator!=(const vector<T,Allocator>& x,const vector<T,Allocator>& y);
    template <class T, class Allocator>
        bool operator> (const vector<T,Allocator>& x,const vector<T,Allocator>& y);
    template <class T, class Allocator>
        bool operator>=(const vector<T,Allocator>& x,const vector<T,Allocator>& y);
    template <class T, class Allocator>
        bool operator<=(const vector<T,Allocator>& x,const vector<T,Allocator>& y);
 
    template <class T, class Allocator>
        void swap(vector<T,Allocator>& x, vector<T,Allocator>& y);
 
    template <class Allocator> class vector<bool,Allocator>;
 
    // hash support
    template <class T> struct hash;
    template <class Allocator> struct hash<vector<bool, Allocator> >;
}

#endif /* _STL_VECTOR_H */