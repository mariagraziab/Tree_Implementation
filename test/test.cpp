#include "bst.hxx" 

int main()
{ 
  const std::pair<int,int> a(5,5); 
  std::pair<int,int> b(6,6);
  std::pair<int,int> c(3,3); 
  std::pair<int,int> d(12,12); 
  std::pair<int,int> e(9,9); 
  std::pair<int,int> f(20,20); 
  std::pair<int,int> g(20,20); 
  std::pair<int,int> h(33,33); 
 
  // TEST ON CONSTRUCTORS
  std::cout<<"Test on constructors"<<std::endl; 
  bst<int,int> tree1{};
  std::cout<<"construct an empty tree"<<std::endl;
  std::cout<<"Size of the tree : "<<tree1.get_Size()<<std::endl; 
  std::cout<<"Construct tree2 with one element"<<std::endl;
  bst<int,int> tree2{a}; 
  std::cout<<"Size of tree2 : "<<tree2.get_Size()<<std::endl; 
  std::cout<<"Tree2 in order visit:"<<std::endl; 
  std::cout<<tree2<<std::endl; 
  std::cout<<"Construct tree3 using copy constructor initialized with tree2"<<std::endl;
  bst<int,int> tree3{tree2};
  std::cout<<"tree3 in order visit"<<std::endl; 
  std::cout<<tree3<<std::endl;

  std::cout<<"dereference operator:"<<tree3[5]<<std::endl;
  std::cout<<"Size of tree3 : ";
  std::cout<<tree3.get_Size()<<std::endl; 

  std::cout<<"Construct tree4 using move constructor initialized with tree3"<<std::endl; 
  bst<int,int> tree4{std::move(tree3)}; 
  std::cout<<"tree4 in order visit"<<std::endl; 
  std::cout<<tree4<<std::endl;
  std::cout<<"Size of tee4: ";
  std::cout<<tree4.get_Size()<<std::endl; 
  std::cout<<"tree3 in order visit "<<std::endl;
  std::cout<<tree3<<std::endl;
  std::cout<<"Size of tree3: ";
  std::cout<<tree3.get_Size()<<std::endl;
 
  //TEST ON INSERT, EMPLACE AND AGAIN COPY AND MOVE 

  std::cout<<"Test on insert, emplace and again copy and move"<<std::endl; 

  bst<int,int> tree5{}; 
  tree5.insert(a); tree5.insert(b); tree5.insert(c); tree5.insert(c); tree5.emplace(3,3);
  tree5.emplace(16,16); tree5.emplace(10,10); tree5.emplace(27,27);
  tree5.insert(std::pair<int,int>(10,10));
  std::cout<<"tree5 in order visit"<<std::endl; 
  std::cout<<tree5<<std::endl; 
  std::cout<<"tree5 size: ";
  std::cout<<tree5.get_Size()<<std::endl; 

  bst<int,int> tree6{std::move(tree5)};
  std::cout<<"tree 6 initialized with move constructor on tree5"<<std::endl;
  std::cout<<"In order visit in tree6 :"<<std::endl;
  std::cout<<tree6<<std::endl; 
  std::cout<<"Size of tree6: ";
std::cout<<tree6.get_Size()<<std::endl; 
  std::cout<<"Tree5 :"<<std::endl; 
  std::cout<<tree5<<std::endl;
  std::cout<<"Size of tree5 :"<<tree5.get_Size()<<std::endl; 
  //FIND TEST ON TREE6 
  tree6.emplace(80,80);tree6.emplace(30,30);tree6.emplace(19,19);

  if( tree6.find(123) == tree6.end())  
    std::cout<<"Key is not present in the tree"<<std::endl; 
  else
    std::cout<<"Key present in the tree"<<std::endl; 

  if( tree6.find(30) == tree6.end())  
    std::cout<<"Key is not present in the tree"<<std::endl; 
  else
    std::cout<<"Key present in the tree"<<std::endl; 

  //test copy and move assignment 

  bst<int,int> tree7; 
  tree7 = tree6; 
  std::cout<<"Tree7 with copy assignment on tree6, in order visit of tree7"<<std::endl; 
  std::cout<<tree7<<std::endl; 
  std::cout<<"In order visit of tree6: "<<std::endl; 
  std::cout<<tree6<<std::endl; 

  std::cout<<"tree8 with move assignment on tree6, in order visit of tree8"<<std::endl; 
  bst<int,int> tree8; 
  tree8 = std::move(tree6);
  std::cout<<tree8<<std::endl; 
  std::cout<<"tree7 "<<std::endl; 
  std::cout<<tree7<<std::endl; 
  
  //REMOVING KEY TEST

  tree8.erase(10);
  std::cout<<tree8<<std::endl; 
  tree8.erase(3);tree8.erase(16);tree8.erase(19);
  std::cout<<tree8<<std::endl; 
  tree8.erase(3);
  tree8.erase(27);tree8.erase(30);tree8.erase(5);
   
   std::cout<<tree8<<std::endl; 
   tree8.erase(6);
    std::cout<<tree8<<std::endl; 

std::cout<<"New Tree"<<std::endl; 

 bst<int,int> newTree; 
 newTree.emplace(2,2);
 newTree.emplace(3,3); 
 newTree.emplace(1,1);
 std::cout<<newTree<<std::endl; 
 newTree.erase(2); 
 std::cout<<newTree<<std::endl; 
 newTree.erase(1);
 std::cout<<newTree<<std::endl; 
newTree.erase(3);
 std::cout<<newTree<<std::endl; 

 bst<int,int> nt; 
 nt.emplace(4,4); nt.emplace(6,6); nt.emplace(2,2);nt.emplace(5,5);nt.emplace(7,7);
 std::cout<<nt<<std::endl; 
 nt.erase(6); 
 std::cout<<nt<<std::endl; 
 nt.erase(4);
 std::cout<<nt<<std::endl;
 nt.erase(5);
 std::cout<<nt<<std::endl;
 nt.erase(2); 
 std::cout<<nt<<std::endl;
 nt.erase(7); 
 std::cout<<nt<<std::endl;




 



   

  









  









  



    return 0;
   



  
  

    
}