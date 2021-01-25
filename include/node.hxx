/**
 * @file node.hxx
 * @author Maria Grazia Berni
 * @brief Advanced Programming Project
 *
 */



#ifndef NODE_HXX__
#define NODE_HXX__

/**
 * @brief class Node to represent the nodes stored in the binary tree 
 */ 
template <class K, class V, class Compare> 
class bst<K,V,Compare>::Node
{
    public: 
      //*pair with key and value stored in each node*/
      std::pair<const K,V> data; 
      //*left child*/
      std::unique_ptr<Node> left; 
      //* right child*/
      std::unique_ptr<Node> right; 
      //*parent node*/
      Node* parent; 

    
      /**
       * @brief default constructor of Node
       */
      Node() = default; 
      /**
       * @brief Constructor of a node with a value
       * @param value the std::pair to store in the node 
       */
      Node(std::pair<const K,V> value):data{value}, left{nullptr}, right{nullptr},parent{nullptr}{}
      /**
       * @brief Constructor of a node with a value and a parent 
       * @param value the std::pair to store in the node 
       * @param p the parent of the node 
       */
      Node(std::pair<const K,V> value, Node* p): data{value},left{nullptr},right{nullptr},parent{p}{}
      /**
       * @brief constructor to perform a recursive deep copy of the nodes 
       */
      explicit Node(const std::unique_ptr<Node>& n): data{n->data}
      {
          std::cout<<"Recursive copy constructor of node"<<std::endl; 
          if(n->left)
             left = std::make_unique<Node>(n->left); 
          
          if(n->right)
             right = std::make_unique<Node>(n->right);
      }
      /**
       * @brief move constructor of a node 
       */

      Node(Node&& n): data{std::move(n.data)}, left{std::move(n.left)},right{std::move(n.right)},parent{std::move(n.parent)}{}
      /**
       * @brief assignment operator of Node
       * @return Node
       */

      Node& operator=(Node&& n) noexcept{ 
          data = std::move(n.data); 
          left = std::move(n.left); 
          right = std::move(n.right); 
          parent = std::move(n.parent); 
          return *this; 
      }
      /**
       * @brief function to insert a left child starting from a value 
       * @param data the value to store in the child node 
       */

      void insert_left_child(const std::pair<const K,V>& data)
      {
          left = std::make_unique<Node>(data,this); 
      }
      /**
       * @brief function to insert a right child starting from a value 
       * @param data the value to store in the child node 
       */

      void insert_right_child(const std::pair<const K,V>& data)
      {
          right = std::make_unique<Node>(data,this);
      }
      /**
       * @brief function to insert a left child starting from a value 
       * @param data the value to store in the child node 
       */

      void insert_left_child(std::pair<const K,V>&& data)
      {
          left = std::make_unique<Node>(std::forward<std::pair<const K,V>>(data),this);
      }
      
       /**
       * @brief function to insert a right child starting from a value 
       * @param data the value to store in the child node 
       */     


      void insert_right_child(std::pair<const K,V>&& data)
      {
           right = std::make_unique<Node>(std::forward<std::pair<const K,V>>(data),this);
      }
      /**
       * @brief function to delete the left child 
       * @return Node 
       */

      Node* del_left_link()
      {
          Node* u = nullptr; 
          if(left)
          {
              left->parent = nullptr;
              u=left.release(); 
          }

          return u;
          
      }
       /**
       * @brief function to delete the right child 
       * @return Node 
       */


      Node* del_right_link()
      {
          Node* u = nullptr; 
          if(right)
          {
              right->parent = nullptr; 
              u = right.release();
          }

          return u;
      }
       /**
       * @brief function to set a left link 
       *        if the node is nullptr it only reset the pre-existing link
       
       */

      void set_left_link(Node* node) noexcept
      {
          if(node)
          {
              left.reset(node);
              left->parent = this; 
          }
          else
          {
              left.reset();
             // left = nullptr;
          }
          
      }
      /**
       * @brief function to set a right link 
       *        if the node is nullptr it only reset the pre-existing link
       
       */

      void set_right_link(Node* node) noexcept
      {
          if(node)
          {
              right.reset(node); 
              right->parent = this; 
          }
          else
          {
              right.reset();
              //right = nullptr;
          }
          
      }

     /**
      * @brief function to delete the left child
      */
      void del_left() noexcept
      {
          if(left)
          {
              left.reset();
          }
      }
      /**
       * @brief function to delete the right child 
       */

      void del_right() noexcept
      {
          if(right)
          {
              right.reset(); 
          }
      }
      /**
       * @brief function to determine the node containing the minimum key in the tree 
       * @return Node 
       */

      Node* contain_min(Node* node) noexcept
      {
          if(node)
          {
              while(node->left)
                 node = node->left.get();
          }

          return node;
      }

       /**
       * @brief function to determine the node containing the maximum key in the tree 
       * @return Node 
       */


      Node* contain_max(Node* node) noexcept
      {
          if(node)
          {
              while(node->right)
                 node = node->right.get(); 
          }

          return node;
      }
       /**
       * @brief function to determine the successor of a node in the tree
       * @return Node 
       */


      Node* successor(Node* node) noexcept
      {
          if(!node) return node; 

          if(node->right)
          {
              return node->contain_min(node->right.get());
          }

          while((node->parent) && (node == node->parent->right.get()))
             node = node->parent;

          return node->parent; 
      }

      






};




#endif 
