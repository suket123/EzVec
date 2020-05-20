# EzVec
C++ implementation of optimized std::vector which supports push_front() and pop_front(). 
Please let me know if you find any bugs or have any suggestions :)

**Purpose of building EzVec**
- C++ Standard Template Library (STL) provides great data structures, one of them being std::vector. It is the fastest general 
purpose data structure with O(1) insert at end and allows indexing ( [] )
- However, it doesn't support operations such as push_front() or pop_front()
- The following implementation of EzVec solves this problem by introducing push_front() and pop_front() with an amortized O(1) complexity
while maintaining most of the other essential capabilites of std::vector

**How it works**
- The implementation of EzVec internally uses std::vector where push_back populates entries from index 0 and push_front populates entries
 from the end of the vector. An index for each ends is used to optimally figure out the size at any point in time. Reading the 
 code will give an idea of exactly how elements are stored. However, there are a few drawbacks of using EzVec, one of them being 
 iterators cannot be used because the elements aren't stored in memory with in increasing index. The advantages and disadvantages 
 of EzVec are outlined below.

**Advantages**
- Additional member functions than std::vector
  - O(1) push_front()
  - O(1) pop_front
- O(1) push_back() and O(1) pop_back() - same as std::vector

**Disadvantages**
- Allocator Type and Initializer List not yet supported
- Iterators not allowed
  - Cannot call emplace(), begin(), end(), cbegin(), cend(), crbegin(), crend(), insert(), rbegin(), rend()
- data() not supported because elements are not stored incrementally in memory

**How to use**
- Simply add "EzVec.h" in the working directory and include the file wherever required.
