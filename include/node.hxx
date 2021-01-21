


#ifndef NODE_HXX__
#define NODE_HXX__


template <class K, class V, class Compare> 
class bst<K,V,Compare>::Node
{
    public: 
      
      std::pair<const K,V> data; 

      std::unique_ptr<Node> left; 

      std::unique_ptr<Node> right; 

      Node* parent; 

    //methods 
     
      Node() = default; 
      //constructor of a node without a parent 
      Node(std::pair<const K,V> value):data{value}, left{nullptr}, right{nullptr},parent{nullptr}{}
      //constructor of a node with a parent 
      Node(std::pair<const K,V> value, Node* p): data{value},left{nullptr},right{nullptr},parent{p}{}

      //recursive deep copy starting from an initializing node 
      explicit Node(const std::unique_ptr<Node>& n): data{n->data}
      {
          std::cout<<"Recursive copy constructor of node"<<std::endl; 
          if(n->left)
             left = std::make_unique<Node>(n->left); 
          
          if(n->right)
             right = std::make_unique<Node>(n->right);
      }

      Node(Node&& n): data{std::move(n.data)}, left{std::move(n.left)},right{std::move(n.right)},parent{std::move(n.parent)}{}


      Node& operator=(Node&& n) noexcept{ 
          data = std::move(n.data); 
          left = std::move(n.left); 
          right = std::move(n.right); 
          parent = std::move(n.parent); 
          return *this; 
      }


      void insert_left_child(const std::pair<const K,V>& data)
      {
          left = std::make_unique<Node>(data,this); 
      }

      void insert_right_child(const std::pair<const K,V>& data)
      {
          right = std::make_unique<Node>(data,this);
      }

      void insert_left_child(std::pair<const K,V>&& data)
      {
          left = std::make_unique<Node>(std::forward<std::pair<const K,V>>(data),this);
      }

      void insert_right_child(std::pair<const K,V>&& data)
      {
           right = std::make_unique<Node>(std::forward<std::pair<const K,V>>(data),this);
      }

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


      void del_left() noexcept
      {
          if(left)
          {
              left.reset();
          }
      }

      void del_right() noexcept
      {
          if(right)
          {
              right.reset(); 
          }
      }

      Node* contain_min(Node* node) noexcept
      {
          if(node)
          {
              while(node->left)
                 node = node->left.get();
          }

          return node;
      }


      Node* contain_max(Node* node) noexcept
      {
          if(node)
          {
              while(node->right)
                 node = node->right.get(); 
          }

          return node;
      }


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