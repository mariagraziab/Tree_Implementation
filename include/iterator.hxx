#ifndef ITERATOR_HXX__
#define ITERATOR_HXX__




template <class Node, class KV> 
class iterator
{
    public: 
     
     using value_type = KV; 
     using pointer = value_type*; 
     using reference = value_type&; 
     using difference_type = std::ptrdiff_t; 
     using iterator_category = std::forward_iterator_tag; 

     
     Node* current_node; 

     iterator() = default; 
  
     explicit iterator(Node* node) noexcept: current_node{node}{}

     reference operator*() const noexcept
     {
         return current_node->data; 
     }

     pointer operator->() const noexcept
     {
        return &(*(*this)); 
     }

     iterator operator++() noexcept
     {
         current_node = current_node->successor(current_node);
         return *this;
     }

     iterator operator++(int) noexcept
     {
         iterator it{*this};
         ++(*this);
         return it;
     }


     friend bool operator==(const iterator& a, const iterator& b) noexcept
     {
         return a.current_node == b.current_node;
     }

     friend bool operator!=(const iterator& a, const iterator& b) noexcept
     {
         return !(a==b);
     }



};






#endif 