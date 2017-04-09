Data Structures and Algorithms
================

A collection of C++ data structures and algorithms (lists, trees, graphs, sorting algorithms, etc.).

This collection is not intended for production use. It is mostly intended for personal learning and application of newer C++ concepts.

About
------------------

Author: `Daniel Sebastian Iliescu, http://dansil.net`  
License: `MIT License (MIT), http://opensource.org/licenses/MIT`  

Requirements
------------------

C++17 conforming compiler.

Notes and Limitations
------------------

Most of the data structures are written using pre-C++11 style. I have started refactoring them to incorporate C++11, C++14, and C++17 features.

As a result, the only data structure that I consider to be modernly re-written is the doubly_linked_list. This data structure has also been updated to support iterators and allocators. It is also the only data structure with unit tests. Refactoring for the other files is in-progress.