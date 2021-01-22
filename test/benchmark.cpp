#include <chrono> 
#include <fstream> 
#include <cstdlib> 
#include <math.h>
#include "bst.hxx"

int main(int arg, char* argv[])
{

    const int N = (arg<2) ? 1000 : atoi(argv[1]); 

    std::ofstream ins_nb,rem_nb,f_nb,ins_bal,rem_bal,f_bal,bal_time; 

    ins_nb.open("result/ins_nb.txt",std::ios::out|std::ios::app); 
    rem_nb.open("result/rem_nb.txt",std::ios::out|std::ios::app); 
    f_nb.open("result/f_nb.txt",std::ios::out|std::ios::app);
    ins_bal.open("result/ins_bal.txt",std::ios::out|std::ios::app);
    rem_bal.open("result/rem_bal.txt",std::ios::out|std::ios::app);
    f_bal.open("result/f_bal.txt",std::ios::out|std::ios::app);




    std::vector<int> elem_tot; 

    for(int i =0; i<2*N; i++)
    {
        elem_tot.push_back(i); 
    }

    srand(N);
    std::random_shuffle (elem_tot.begin(), elem_tot.end() );

    auto begin = std::chrono::high_resolution_clock::now();
     for(int i=0; i<N; i++){ 
         elem_tot.at(i);
       
   }
      
   auto end = std::chrono::high_resolution_clock::now();

   auto total = std::chrono::duration_cast<std::chrono::microseconds>(end-begin).count();
   //sottostima tempo d'accesso al vector + tempo singolo ciclo for
   //sottostima poichè gli elementi vengono recuperati dalla cache
   auto access_time = total/double(N); 

   bst<int,int> tree{};

   for(int i= 0; i<N; i++)
      tree.emplace(elem_tot.at(i),1);


   total = 0;
   auto tot1 = total; auto tot2 = total; auto tot3 = total; auto tot4 = total; auto tot5 = total; 
   auto tot6 = total; auto tot7 = total; 
   
   int h = log2(N+1); 

   int leaf = pow(2,h-1)/8; 

   int iter = 100; 
   
   for(int i= 0; i<iter; i++)
   {
       auto a1 = std::chrono::high_resolution_clock::now();
       for(int j=N; j<N+leaf;j++)
       {
           tree.emplace(elem_tot.at(j),1);
       }
       auto a2 = std::chrono::high_resolution_clock::now();
       auto da =std::chrono::duration_cast<std::chrono::microseconds>(a2-a1).count();
       tot1 +=da;

       auto a3 = std::chrono::high_resolution_clock::now();
       for(int j=N; j<N+leaf;j++)
       {
           tree.erase(elem_tot.at(j));
       }
       auto a4 = std::chrono::high_resolution_clock::now();
       auto da2 =std::chrono::duration_cast<std::chrono::microseconds>(a4-a3).count();
       tot2 +=da2; 

       auto f1 =  std::chrono::high_resolution_clock::now();
       for(int j= 0; j<2*N; j++)
       {
           tree.find(elem_tot.at(j)); 
       }
       auto f2 = std::chrono::high_resolution_clock::now();
       auto df = std::chrono::duration_cast<std::chrono::microseconds>(f2-f1).count();
       tot3 +=df; 

       auto a5 = std::chrono::high_resolution_clock::now();
       tree.balance(); 
       auto a6 = std::chrono::high_resolution_clock::now();
       auto da3 =std::chrono::duration_cast<std::chrono::microseconds>(a6-a5).count();
       tot4 +=da3; 


       //same with balanced tree 

       auto a7 = std::chrono::high_resolution_clock::now();
        for(int j=N; j<N+leaf;j++)
       {
           tree.emplace(elem_tot.at(j),1);
       }
        auto a8 = std::chrono::high_resolution_clock::now();
       auto da4 =std::chrono::duration_cast<std::chrono::microseconds>(a8-a7).count();
       tot5 +=da4; 


       auto a9 = std::chrono::high_resolution_clock::now();
       
       for(int j=N; j<N+leaf;j++)
       {
           tree.erase(elem_tot.at(j));
       }
       auto a10 = std::chrono::high_resolution_clock::now();
       auto da5 =std::chrono::duration_cast<std::chrono::microseconds>(a10-a9).count();
       tot6+=da5; 

       auto f3 =  std::chrono::high_resolution_clock::now();
       for(int j= 0; j<2*N; j++)
       {
           tree.find(elem_tot.at(j)); 
       }
       auto f4 = std::chrono::high_resolution_clock::now();
       auto df2 =std::chrono::duration_cast<std::chrono::microseconds>(f4-f3).count();
       tot7 += df2;

       //rebuild a new tree not balanced 

        tree.clear(); 
        srand(iter);

        std::random_shuffle (elem_tot.begin(), elem_tot.end() );

        for(int k=0; k<N; k++)
            tree.emplace(elem_tot.at(k),1); 
   
    }
    

    auto time_emplace_nb = tot1/double(leaf*iter) -access_time; 

    auto time_erase_nb = tot2/double(leaf*iter) -access_time; 
   
    auto time_find_nb = tot3/double(2*N*iter) - access_time; 

    auto time_balance = tot4/double(iter);

    auto time_emplace_b = tot5/double(leaf*iter) - access_time;

    auto time_erase_b = tot6/double(leaf*iter) - access_time;

    auto time_find_b = tot7/double(2*N*iter) - access_time;


    std::cout<<"N :"<<N<<std::endl; 

    std::cout<<"insert not balaced: "<<time_emplace_nb<<std::endl; 

    std::cout<<"remove not balanced: "<<time_erase_nb<<std::endl;

    std::cout<<"find not balanced: "<<time_find_nb<<std::endl; 

    std::cout<<"insert balanced: "<<time_emplace_b<<std::endl; 

    std::cout<<"remove balanced: "<<time_erase_b<<std::endl;

    std::cout<<"find balanced: "<<time_find_b<<std::endl; 

    std::cout<<"time to balace the tree: "<<time_balance<<std::endl; 
 
    ins_nb<<N<<" "<<time_emplace_nb<<std::endl; 

    rem_nb<<N<<" "<<time_erase_nb<<std::endl;

    f_nb<<N<<" "<<time_find_nb<<std::endl; 

    ins_bal<<N<<" "<<time_emplace_b<<std::endl; 

    rem_bal<<N<<" "<<time_erase_b<<std::endl;

    f_bal<<N<<" "<<time_find_b<<std::endl; 

    bal_time<<N<<" "<<time_balance<<std::endl; 

    ins_nb.close(); 
    rem_nb.close(); 
    f_nb.close(); 
    ins_bal.close(); 
    rem_bal.close(); 
    f_bal.close(); 
    bal_time.close();

    
        


  



   return 0; 
}

   