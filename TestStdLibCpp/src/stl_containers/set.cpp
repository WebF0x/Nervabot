#include "set.h"

template <class Key, class Compare = less<Key>,
class Allocator = allocator<Key> >
class set
{
public:
    // types:
    typedef Key key_type;
    typedef Key value_type;
    typedef Compare key_compare;
    typedef Compare value_compare;
    typedef Allocator allocator_type;
    typedef value_type& reference;
    typedef const value_type& const_reference;
    typedef /*implementation-defined*/ iterator;
    typedef /*implementation-defined*/ const_iterator;
    typedef /*implementation-defined*/ size_type;
    typedef /*implementation-defined*/ difference_type;
    typedef typename allocator_traits<Allocator>::pointer pointer;
    typedef typename allocator_traits<Allocator>::const_pointer const_pointer;
    typedef std::reverse_iterator<iterator> reverse_iterator;
    typedef std::reverse_iterator<const_iterator> const_reverse_iterator;
 
    // construct/copy/destroy:
    explicit set(const Compare& comp = Compare(),
                 const Allocator& = Allocator());
    template <class InputIterator>
    set(InputIterator first, InputIterator last,
        const Compare& comp = Compare(), const Allocator& = Allocator());
    set(const set<Key,Compare,Allocator>& x);
    set(set<Key,Compare,Allocator>&& x);
    explicit set(const Allocator&);
    set(const set&, const Allocator&);
    set(set&&, const Allocator&);
    set(initializer_list<value_type>,
        const Compare& = Compare(),
        const Allocator& = Allocator());
    ~set();
 
    set<Key,Compare,Allocator>& operator= (const set<Key,Compare,Allocator>& x);
    set<Key,Compare,Allocator>& operator= (set<Key,Compare,Allocator>&& x);
    set& operator=(initializer_list<value_type>);
    allocator_type get_allocator() const noexcept;
 
    // iterators:
    iterator        begin() noexcept;
    const_iterator  begin() const noexcept;
    iterator        end() noexcept;
    const_iterator  end() const noexcept;
 
    reverse_iterator        rbegin() noexcept;
    const_reverse_iterator  rbegin() const noexcept;
    reverse_iterator        rend() noexcept;
    const_reverse_iterator  rend() const noexcept;
 
    const_iterator          cbegin() const noexcept;
    const_iterator          cend() const noexcept;
    const_reverse_iterator  crbegin() const noexcept;
    const_reverse_iterator  crend() const noexcept;
 
    // capacity:
    bool        empty() const noexcept;
    size_type   size() const noexcept;
    size_type   max_size() const noexcept;
 
    // modifiers:
    template <class... Args> pair<iterator, bool> emplace(Args&&... args);
    template <class... Args>
        iterator emplace_hint(const_iterator position, Args&&... args);
 
    pair<iterator,bool> insert(const value_type& x);
    pair<iterator,bool> insert(value_type&& x);
    iterator insert(const_iterator position, const value_type& x);
    iterator insert(const_iterator position, value_type&& x);
    template <class InputIterator>
    void insert(InputIterator first, InputIterator last);
    void insert(initializer_list<value_type>);
 
    iterator erase(const_iterator position);
    size_type erase(const key_type& x);
    iterator erase(const_iterator first, const_iterator last);

    void swap(set<Key,Compare,Allocator>&);
    void clear() noexcept;

    // observers:
    key_compare   key_comp() const;
    value_compare value_comp() const;

    // set operations:
    iterator       find(const key_type& x);
    const_iterator find(const key_type& x) const;
    size_type      count(const key_type& x) const;
    iterator       lower_bound(const key_type& x);
    const_iterator lower_bound(const key_type& x) const;
    iterator       upper_bound(const key_type& x);
    const_iterator upper_bound(const key_type& x) const;
    pair<iterator,iterator> equal_range(const key_type& x);
    pair<const_iterator,const_iterator> equal_range(const key_type& x) const;
};
