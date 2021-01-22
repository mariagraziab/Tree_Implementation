/**
 * @file bst.hxx
 * @author Maria Grazia Berni
 * @brief Advanced Programming Project
 * 
 * 
 *
 * 
 */

#include <iostream> 
#include <memory> 
#include <algorithm> 
#include <vector>
#include <utility>
#include "iterator.hxx"

#ifndef BST_HXX__
#define BST_HXX__

/**
 * @brief  Class that implements a simple binary heap, without auto balance 
 * @tparam K is the key value 
 * @tparam V is the value stored in the node
 * @tparam Compare is the comparing function, which has default value std::less<K>
 */
template <class K, class V, class Compare = std::less<K>>

class bst{
    private:

      /**
       * @brief Internal class to represent the nodes of the tree
       */  
      class Node; 
      /** Pointer to the rot of the tree */
      std::unique_ptr<Node> root; 
      /** Size of the tree*/
      int sz = 0;
      /**Iterator and Constant Iterator definded ad an external class */
      using Iterator = iterator<Node,typename std::pair<const K,V>>;
      using Const_Iterator = iterator<Node, const typename std::pair<const K,V> >;
      /**
       * @brief Private auxiliary function to deal with the elimination of the root 
       *        when calling the erase function
       */
      void del_root();
      /**
       * @brief Private auxiliary function to deal with the elimination of a node
       *        with two children when calling the erase function 
       * @param node the node to del 
       */

      void del_node_with_two_children(Node* node);
      /**
       * @brief Private auxiliary function do deal with the elimination of a node 
       *        with only one child when calling the erase function
       * @param node the node to del 
       */

      void del_node_with_one_child(Node* node);
      /**
       * @brief Private auxiliary function to deal eith the elimination of a node
       *        that is a leaf, when calling the erase function
       * @param node the node to del
       */

      void del_leaf(Node* node); 

      /**
       * @brief auxiliary function to balance the tree
       * @param nodes  auxiliary vector with ordered elements 
       * @param firstId initial position in the vector 
       * @param lastId last position in the vecto 
       */
      

      void balanced_tree(std::vector<std::pair<K,V>>& nodes, int firstId, int lastId);



    public:

      /**
       * @brief Constructor of the tree that doesn't set the root
       * @param c optional value of the function to compare nodes
       *          if not present the compare function will be the 
       *          default std::less<K> 
       */
      bst(Compare c = Compare{}):compare{c} {}
      /**
       * @brief Constructor of the tree that sets the root
       * @param value The value to store in the root 
       * @param c optional value of the function to compare nodes
       *          if not present the compare function will be the 
       *          default std::less<K> 
       */

      bst(std::pair<const K,V> value, Compare c = Compare{}): root{std::make_unique<Node>(value)},compare{c}
      {
        sz++;
      }
      /**
       * @brief Copy Constructor create a deep copy of the tree 
       * @param other the tree to be copied 
       * 
       */
      bst(const bst& other); //copy constructor
      /**
       * @brief Copy Assignment 
       * @param other the tree to be copied 
       * @return bst&
       */

      bst& operator=(const bst& other);
      /**
       * @brief Auxiliary recursive function to perform a deep copy in the 
       *        copy assignment 
       * @param node the node to be copied 
       */

      void copy(const std::unique_ptr<Node>& node); 
      /**
       * @brief Move Constructor 
       * @param other the tree to "move" 
       */

      bst(bst&& other) noexcept: root{std::move(other.root)}, sz{std::move(other.sz)}{other.sz = 0;}
      /**
       * @brief Move assignment 
       * @param other the tree to "move" 
       * @return bst&
       */
      bst& operator=(bst&& other);
      /**
       * @brief the function that performs the comparative operation 
       *        if not set in the construction, the default value is 
       *        std::less<K> 
       */
      Compare compare; 
      /**
       * @brief function to insert a std::pair<K,V> in the tree 
       * @param data  a reference to the data to insert 
       * @return  std::pair<Iterator, bool> , a pair containing the iterator
       *          initialized with the position of the insertion of the node 
       *          and a bool which is true if the element has been inserted,
       *          false otherwise
       */
      
      std::pair<Iterator, bool> insert(const std::pair<const K,V>& data);
       /**
       * @brief    overloaded insert to deal with r-values 
       * @param data  the data to insert 
       * @return  std::pair<Iterator, bool> , a pair containing the iterator
       *          initialized with the position of the insertion of the node 
       *          and a bool which is true if the element has been inserted,
       *          false otherwise
       */

      std::pair<Iterator, bool> insert(std::pair<const K,V>&& data);
      /**
       * @brief function to deal with the insertion of elements 
       *         cunstructing an std::pair in place 
       * @param args to pass the key and value of the pair to construct
       *             in place 
       * @return  std::pair<Iterator, bool> , a pair containing the iterator
       *          initialized with the position of the insertion of the node 
       *          and a bool which is true if the element has been inserted,
       *          false otherwise
       */

      template< class... Types >
      std::pair<Iterator,bool> emplace(Types&&... args)
      {
          return insert(std::pair<const K,V>{std::forward<Types>(args)...});
      }
      /**
       * @brief function to get the size of the tree
       * @retrns int 
       */

      int get_Size(){return sz;}
      /**
       * @brief Function to get the root node of the tree 
       * @return Node*
       */

      Node* get_root() const {return root.get(); }
      /**
       * @brief function that return an iterator to the first element
       * @return Iterator
       */

      Iterator begin() noexcept
      {
        return Iterator{root->contain_min(root.get())};
      }
      /**
       * @brief function that returns a constant iterator to the first element 
       * @return Const_Iterator
       */
      Const_Iterator begin() const noexcept
      {
        return Const_Iterator{root->contain_min(root.get())};
      }
      /**
       * @brief function that returns a constant iterator to the first element 
       * @return Const_Iterator
       */

      Const_Iterator cbegin() const noexcept{
          
         return Const_Iterator{root->contain_min(root.get())};
      }
       /**
       * @brief function that return an iterator to the end ot the tree
       *         so it returns nullptr
       * @return Iterator{nullptr}
       */


      Iterator end() noexcept
      {
          return Iterator{nullptr};
      }
      /**
       * @brief function that return an constant iterator to the end ot the tree
       *         so it returns nullptr
       * @return Const Iterator 
       */

      Const_Iterator end() const noexcept
      {
         
        return Const_Iterator{nullptr};
      }
      /**
       * @brief function that return an constant iterator to the end ot the tree
       *         so it returns nullptr
       * @return Const Iterator 
       */

       Const_Iterator cend() const noexcept
      {
         
         return Const_Iterator{nullptr};

      }
      /**
       * @brief function to find if a value with a certain key is stored in the tree
       * @param x the key of the node ot search 
       * @return Iterator an iterator to the node with the key x, or end() in case 
       *          the key is not sored in the tree
       */

      Iterator find(const K& x);
       /**
       * @brief function to find if a value with a certain key is stored in the tree
       * @param x the key of the node ot search 
       * @return Cont_Iterator a constant iterator to the node with the key x, or end() in case 
       *          the key is not sored in the tree
       */

      Const_Iterator find(const K& x) const;
      /**
       * @brief operator that returns the value corresponding to a key 
       * @param x the key to search 
       * @return V
       */
      
      V& operator[](const K& x);
       
      /**
       * @brief operator that returns the value corresponding to a key 
       * @param x the key to search 
       * @return V
       */
      

      V& operator[](K&& x);
      /**
       * @brief  function to delete all the nodes of the tree
       */

      void clear() noexcept {root.reset();}
      /**
       * @brief function to delete a node of the tree corresponding to a certain key
       * @param x the key of the node to delete
       */

      void erase(const K& x);
      
      /**
       * @brief function to balance the tree 
       */
      
      void balance();

      /**
       * @brief friend function to print the tree
       * @param os the output stream 
       * @param x the tree to print 
       * @return ostream 
       */

      template <class k,class v,class c> 
      friend std::ostream& operator<<(std::ostream& os, const bst<k,v,c>& x);


};

template <class k, class v, class c>
std::ostream& operator<<(std::ostream& os, const bst<k,v,c>& x)
{
   if (!(x.get_root()))
    {
        return os << "Empty"<<std::endl;  
    }
  
             for (auto& n : x)
             {
                  os << "key: "<<n.first <<" "<<"value: "<<n.second<<std::endl;
             }


             
            return os;
        }



template <class K, class V, class Compare> 
bst<K,V,Compare>::bst(const bst& other)
{
  
  sz = other.sz; 
  root = std::make_unique<Node>(other.root);
}

template <class K, class V, class Compare> 
void bst<K,V,Compare>::copy(const std::unique_ptr<Node>& node)
{
    if(node)
    {
      insert(node->data);
      copy(node->left);
      copy(node->right);
    }
}

template <class K, class V, class Compare> 
bst<K,V,Compare>& bst<K,V,Compare>::operator=(const bst& other)
{
    clear();
    copy(other.root);
    sz = other.sz; 
    return *this;
}

template <class K, class V, class Compare> 
bst<K,V,Compare>& bst<K,V,Compare>::operator=(bst&& other)
{
    sz = std::move(other.sz); 
    root = std::move(other.root); 
    other.sz = 0; 
    return *this; 
}

template <class K, class V, class Compare> 
std::pair<typename bst<K,V,Compare>::Iterator,bool> bst<K,V,Compare>::insert(const std::pair<const K,V>& data)
{
  
  Node* n = root.get(); 

  while(n)
  {
    if(compare(data.first,n->data.first))
    {
      if(!(n->left))
      {
        n->insert_left_child(data);
        n = n->left.get(); 
        sz++; 
        Iterator it{n}; 
        return std::pair<Iterator,bool>{it,true};
      }
      n = n->left.get(); 
    }
    else if(compare(n->data.first,data.first))
    {
      if(!(n->right))
      {
        n->insert_right_child(data); 
        n = n->right.get(); 
        sz++;
        Iterator it{n}; 
        return std::pair<Iterator,bool>{it,true};
      }
      n = n->right.get();
    }
    else
    {
      Iterator it{n}; 
      return std::pair<Iterator, bool>{it,false};
    }

    
    
  }
  root = std::make_unique<Node>(data); 
  sz ++; 
  Iterator it{root.get()}; 
  return std::pair<Iterator, bool>{it,true};
}

template <class K, class V, class Compare> 
std::pair<typename bst<K,V,Compare>::Iterator,bool> bst<K,V,Compare>::insert(std::pair<const K,V>&& data)
{
  

  Node* n = root.get();

  while(n)
  {
    if(compare(data.first,n->data.first))
    {
      if(!(n->left))
      {

        n->insert_left_child(std::forward<std::pair<const K,V>>(data));
        n = n->left.get();
        sz++; 
        Iterator it{n};
        return std::pair<Iterator,bool>{it,true}; 

      }
      n = n->left.get(); 
    }
    else if(compare(n->data.first,data.first))
    {
      if(!(n->right))
      { 
        n->insert_right_child(std::forward<std::pair<const K,V>>(data));
        n = n->right.get();
        sz++; 
        Iterator it{n}; 
        return std::pair<Iterator,bool>{it,true}; 
      }
      n = n->right.get();
    }
    else
    {
      Iterator it{n}; 
      return std::pair<Iterator,bool>{it,false};
    }
    
  }

  root = std::make_unique<Node>(std::forward<std::pair<const K,V>>(data)); 

  sz++; 
  Iterator it{root.get()}; 
  return std::pair<Iterator,bool>{it,true}; 

}

template <class K, class V, class Compare>
typename bst<K,V,Compare>::Iterator bst<K,V,Compare>::find(const K& x)
{
  
  Node* n = root.get(); 
  K key = n->data.first; 
  while(n && (key != x))
  {
    if(compare(x,key))
      n = n->left.get();
    else if(compare(key,x))
      n = n->right.get();
    if(n) key = n->data.first;
  }

  return Iterator{n};

}


template <class K, class V, class Compare>
typename bst<K,V,Compare>::Const_Iterator bst<K,V,Compare>::find(const K& x) const
{
    Node* n = root.get(); 
    K key = n->data.first; 
    while(n && (key!=x))
    {
      if(compare(x,key))
        n = n->left.get(); 
      else if (compare(key,x))
        n = n->right.get(); 
      if(n) key = n->data.first; 
    }

  return Const_Iterator{n};
}

template <class K, class V, class Compare> 
V& bst<K,V,Compare>::operator[](const K& x)
{
  std::pair<const K,V> temp{x,V{}}; 
  std::pair<Iterator,bool> ins{insert(temp)}; 
  Iterator it = ins.first; 
  return (*it).second;
}

template <class K, class V, class Compare> 
V& bst<K,V,Compare>::operator[](K&& x)
{
    auto temp = std::pair<const K,V>{std::forward<const K>(x),V{}};
    std::pair<Iterator,bool> ins{insert(std::forward<std::pair<const K,V>>(temp))};
    Iterator it = ins.first;
    return (*it).second;
}

template <class K, class V, class Compare> 
void bst<K, V, Compare>::del_root()
{
  Node* node = root.get(); 
  Node* succ = node->successor(node); 

  if(node->left && node->right)
  {
    Node* succ_child = succ->del_right_link(); 
    std::pair<K,V> value = succ->data; 
    Node* parent = succ->parent; 

    if(succ == parent->left.get())
      parent->set_left_link(succ_child); 
    else
      parent->set_right_link(succ_child);
    
    Node* leftChild = node->del_left_link();
    Node* rightChild = node->del_right_link(); 
    root.reset(); 
    root = std::make_unique<Node>(value); 
    root->set_left_link(leftChild); 
    root->set_right_link(rightChild); 
    return;
  } 
  else if(node->right || node->left)
  {
    if(succ)
    {
      //root has only a right subtree 
      std::pair<K,V> value = succ->data; 
      Node* succ_child = succ->del_right_link(); 
      Node* parent = succ->parent; 
      if(succ == parent->left.get())
        parent->set_left_link(succ_child);
      else
        parent->set_right_link(succ_child); 
      
      Node* root_child = node->del_right_link();
      root.reset(); 
      root = std::make_unique<Node>(value); 
      root ->set_right_link(root_child); 
      return; 
      
    }
    else
    {
      //root has only a left subtree 
      Node* root_child = node->left.get(); 
      Node* right_subtree = root_child->del_right_link(); 
      Node* left_subtree = root_child->del_left_link(); 
      std::pair<K,V> value = root_child->data; 
      root.reset(); 
      root = std::make_unique<Node>(value); 
      root->set_left_link(left_subtree); 
      root->set_right_link(right_subtree); 
      return;
    }
    
  }
  else
  {
    //root is a leaf; 
    root.reset();
  }
  
}

template <class K, class V, class Compare> 
void bst<K,V,Compare>::del_node_with_two_children(Node* node)
{  
    
    Node* succ = node->successor(node);

    Node* succ_child = succ->del_right_link(); 
    Node* parent = succ->parent; 
    if(succ == parent->left.get())
    {
      parent->del_left_link(); //otherwise it will delete the child
      parent->set_left_link(succ_child);
    }
    else
    {
      parent->del_right_link();
      parent->set_right_link(succ_child);
    }

    Node* node_left_child = node->del_left_link(); 
    Node* node_right_child = node->del_right_link(); 
    Node* parent_node = node->parent; 
    if(node == parent_node->left.get())
       parent_node->set_left_link(succ); 
    else 
       parent_node->set_right_link(succ); 

    succ->set_left_link(node_left_child); 
    succ->set_right_link(node_right_child); 

    return; 

  }

  template <class K, class V, class Compare> 
  void bst<K,V,Compare>::del_node_with_one_child(Node* node)
  {
    Node* child = nullptr; 

    if(node->right)
      child = node->del_right_link(); 
    else
      child = node->del_left_link();
    
    
    Node* parent = node->parent; 
    if(node == parent->left.get())
    {
      parent->set_left_link(child);
      return;
    }

    parent->set_right_link(child);
    return; 
    
  }


  template <class K, class V, class Compare>
  void bst<K,V,Compare>::del_leaf(Node* node)
  {
    Node* parent = node->parent; 
    if(node == parent->left.get())
    {
      parent->del_left(); 
      return;
    }
    parent->del_right(); 
    return; 
  }


  template <class K, class V, class Compare> 
  void bst<K,V,Compare>::erase(const K& x)
  {
    Iterator it{find(x)};

    Node* node = it.current_node; 
    if(!node) return; 

    if(node == root.get())
    {
      del_root();
      sz--; 
      return;
    }
    if(node->right && node->left)
    {
      del_node_with_two_children(node);
      sz--; 
      return; 
    }
    else if(node->right || node->left)
    {
      del_node_with_one_child(node);
      sz--; 
      return;
    }
    else
    {
      del_leaf(node); 
      sz--;
    }
    
  }
 template <class K, class V, class Compare>
 void bst<K,V,Compare>::balanced_tree(std::vector<std::pair<K,V>>& ord_vect, int firstID, int lastID)
 {
    if(firstID > lastID)
    {
        return;
    }
    int halfID = (firstID + lastID) / 2;
    insert(ord_vect[halfID]);
    balanced_tree(ord_vect, firstID, halfID - 1);
    balanced_tree(ord_vect, halfID + 1, lastID);

 }


template <class K, class V, class Compare>
 void bst<K,V,Compare>::balance(){
    Iterator it{this->begin()};
    Iterator end{this->end()};
    std::vector<std::pair<K,V>> ord_vect;
    if(it == end)
    {
        return;
    }
    for(; it != end; ++it)
    {
        ord_vect.push_back(*it);
    }
    clear();
    sz=0;
    balanced_tree(ord_vect, 0, ord_vect.size() - 1);
    
   
 }
  





















#include "node.hxx"
#endif 
