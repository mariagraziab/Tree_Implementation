


#ifndef NODE_HXX__
#define NODE_HXX__


template <class K, class V, class Compare> 
class bst<K , V, Compare>::Node
{
    public: 
      
      std::pair<const K,V> data; 

      std::unique_ptr<Node> left; 

      std::unique_ptr<Node> right; 

      Node* parent; 

};




#endif 