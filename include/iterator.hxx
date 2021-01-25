/**
 * @file iterator.hxx
 * @author Maria Grazia Berni
 * @brief Advanced Programming Project
 *
 */



#ifndef ITERATOR_HXX__
#define ITERATOR_HXX__

/**
 * @brief Class that implement an iterator
 */


template <class Node, class KV> 
class iterator
{
    public: 
     
     using value_type = KV; 
     using pointer = value_type*; 
     using reference = value_type&; 
     using difference_type = std::ptrdiff_t; 
     using iterator_category = std::forward_iterator_tag; 

     //* node pointed */
     Node* current_node; 
     /**
      * @brief default constructor of iterator
      */
     iterator() = default; 
     /**
      * @brief explicit constructor of iterator 
      * @param node the node to poin 
      */
  
     explicit iterator(Node* node) noexcept: current_node{node}{}
     /**
      * @brief reference operator 
      * @return a reference to the data contained in current_node
      */

     reference operator*() const noexcept
     {
         return current_node->data; 
     }
     /**
      * @brief pointer operator 
      * @return a pointer to the data contained in current_node
      */

     pointer operator->() const noexcept
     {
        return &(*(*this)); 
     }

     /**
      * @brief pre-increment operator 
      * @return iterator
      */


     iterator operator++() noexcept
     {
         current_node = current_node->successor(current_node);
         return *this;
     }

     /**
      * @brief post-increment operator
      * @return iterator
      */

     iterator operator++(int) noexcept
     {
         iterator it{*this};
         ++(*this);
         return it;
     }
    /**
     * @brief friend operator to check equality between two iterators 
     * @return bool 
     */

     friend bool operator==(const iterator& a, const iterator& b) noexcept
     {
         return a.current_node == b.current_node;
     }

     /**
     * @brief friend operator to check inequality between two iterators 
     * @return bool 
     */

     friend bool operator!=(const iterator& a, const iterator& b) noexcept
     {
         return !(a==b);
     }



};






#endif 
