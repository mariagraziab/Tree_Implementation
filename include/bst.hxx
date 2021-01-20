#include <iostream> 
#include <memory> 
#include <algorithm> 


#ifndef BST_HXX__
#define BST_HXX__
template <class K, class V, class Compare = std::less<K>>

class bst{
    private:
      
      class Node; 

      std::unique_ptr<Node> root; 

    public:

      bst(Compare c = Compare{}):compare{c} {}

       




      Compare compare; 


};

#include "node.hxx"
#endif 