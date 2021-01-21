#include "bst.hxx"
#include <vector> 
#include <algorithm> 
#include <chrono> 
#include <fstream> 
#include <math.h>
#include <cstdlib>

//in realtà anche math è gia includa in bst



//aggiungere gestione errori
int main(int arg, char* argv[])
{
    std::ofstream result; 
    std::string filename = "test/result"; 
    result.open(filename,std::ios::out|std::ios::app);

    std::ofstream ins_nb,rem_nb,f_nb,ins_bal,rem_bal,f_bal,rem_nb_gen,rem_bal_gen,bal_time; 
    ins_nb.open("result/ins_nb.txt",std::ios::out|std::ios::app); //
    rem_nb.open("result/rem_nb.txt",std::ios::out|std::ios::app); //
    f_nb.open("result/f_nb.txt",std::ios::out|std::ios::app);//
    ins_bal.open("result/ins_bal.txt",std::ios::out|std::ios::app);//
    rem_bal.open("result/rem_bal.txt",std::ios::out|std::ios::app);//
    f_bal.open("result/f_bal.txt",std::ios::out|std::ios::app);
    rem_nb_gen.open("result/rem_nb_gen.txt",std::ios::out|std::ios::app);
    rem_bal_gen.open("result/rem_bal_gen",std::ios::out|std::ios::app);
    
    
    bal_time.open("test/bal_time.txt",std::ios::out|std::ios::app);


    
    const int N = (arg<2) ? 1000 : atoi(argv[1]); 
    
    std::vector<int> elem_in;
    std::vector<int> elem_out; 
    std::vector<int> elem_tot; 
    for(int i = 0; i<N; i++)
    {
        elem_in.push_back(i); 
        elem_tot.push_back(i);

    }
       
    for(int i=N; i<2*N; i++)
    {
        elem_out.push_back(i); 
        elem_tot.push_back(i);
    }
    
    std::random_shuffle (elem_out.begin(), elem_out.end() );
    std::random_shuffle (elem_in.begin(), elem_in.end() );
    std::random_shuffle (elem_tot.begin(), elem_tot.end() );

    //measure the access time to the vector 

   auto begin = std::chrono::high_resolution_clock::now();
  
   for(int i=0; i<N; i++){ 
       
   }
      
   auto end = std::chrono::high_resolution_clock::now();
   auto total = std::chrono::duration_cast<std::chrono::microseconds>(end-begin).count();
   auto for_time = total/double(2*N); 
   //std::cout<<"access_time"<<total<<std::endl; 
   auto begin2 = std::chrono::high_resolution_clock::now();
  
   for(int i=0; i<N; i++){ 
       elem_out.at(i); 
       elem_in.at(i);
   }
      
   auto end2 = std::chrono::high_resolution_clock::now();
   auto total2 = std::chrono::duration_cast<std::chrono::microseconds>(end2-begin2).count();
   auto access_time = total2/double(4*N)+for_time; 



   
   bst<int,int> my_tree{};

   //auto t1 = std::chrono::high_resolution_clock::now();
   for(int i=0; i<N; i++)
   {
       my_tree.emplace(elem_in.at(i),1); 
   }
   //auto t2 = std::chrono::high_resolution_clock::now();
   //auto totCreation = std::chrono::duration_cast<std::chrono::microseconds>(t2-t1).count();

   auto tot1 = total; auto tot2 = total; auto tot3 = total; 
   auto tot4 = total; auto tot5 = total; auto tot6 = total; 
   auto tot7 = total; 

   //misuro i tempi di inserimento e rimozione a dimensione costante 


   int h = log2(N+1); 
   int leaf = pow(2,h-1)/8;  //numero elementi da inserire o cancellare 1/8 delle foglie che avrebbe l albero bilanciato  
   //posso considerare la dimensione circa costante perchè inserirsco 1/8 delle foglie quindi 
   //essendo l array non bilanciato ma comunque random, non andrò a creare molti livelli 

   //in questo caso inserisco valori che non sono presenti nell'array 
   //quindi il tempo sarò un estremo superiore
   //rimuovo invece elementi che sono nell'array ma comunque si trovano 
   //con molta probabilità nelle foglie, quindi mentre il tempo di ricerca sarà piu lungo 
   //quello di cancellazione vera e propria della foglia sarà breve 
   tot1 = tot2 =tot3= tot4=tot5=tot6=tot7=0; 
   int iter = 100;
   for(int i=0; i<iter; i++)
   { 

       auto a1 = std::chrono::high_resolution_clock::now();
       for(int j=0; j<leaf; j++)
       { 
           my_tree.emplace(elem_out.at(j),1); 
       }
       auto a2 = std::chrono::high_resolution_clock::now();
       auto da =std::chrono::duration_cast<std::chrono::microseconds>(a2-a1).count();
       tot1 +=da; //tempo inserimento estremo superiore 
       
       auto a3 = std::chrono::high_resolution_clock::now();
       for(int j=0; j<leaf; j++)
       { 
           my_tree.erase(elem_out.at(j)); 
       }
       auto a4 = std::chrono::high_resolution_clock::now();
       auto da2 =std::chrono::duration_cast<std::chrono::microseconds>(a4-a3).count();
       tot2 +=da2;    //tempo eliminazione

       //find nel caso si abbia il 50% possibilita sia o non sia nell'array 
       auto f1 =  std::chrono::high_resolution_clock::now();
       for(int j= 0; j<2*N; j++)
       {
           my_tree.find(elem_tot.at(i)); 
       }
       auto f2 = std::chrono::high_resolution_clock::now();
       auto df =std::chrono::duration_cast<std::chrono::microseconds>(f2-f1).count();
       tot6 += df;
       auto a5 = std::chrono::high_resolution_clock::now();
       my_tree.balance(); 
       auto a6 = std::chrono::high_resolution_clock::now();
       auto da3 =std::chrono::duration_cast<std::chrono::microseconds>(a6-a5).count();
       tot3 +=da3; 

       //stessa roba con albero bilanciato 

        auto a7 = std::chrono::high_resolution_clock::now();
       for(int j=0; j<leaf; j++)
       { 
           my_tree.emplace(elem_out.at(j),1); 
       }
       auto a8 = std::chrono::high_resolution_clock::now();
       auto da4 =std::chrono::duration_cast<std::chrono::microseconds>(a8-a7).count();
       tot4 +=da4; //tempo inserimento estremo superiore 

       auto a9 = std::chrono::high_resolution_clock::now();
       for(int j=0; j<leaf; j++)
       { 
           my_tree.erase(elem_out.at(j)); 
       }
       auto a10 = std::chrono::high_resolution_clock::now();
       auto da5 =std::chrono::duration_cast<std::chrono::microseconds>(a10-a9).count();
       tot5+=da5;    //tempo eliminazione

       auto f3 =  std::chrono::high_resolution_clock::now();
       for(int j= 0; j<2*N; j++)
       {
           my_tree.find(elem_tot.at(i)); 
       }
       auto f4 = std::chrono::high_resolution_clock::now();
       auto df2 =std::chrono::duration_cast<std::chrono::microseconds>(f4-f3).count();
       tot7 += df2;

       //ricostruisco un nuovo albero sbilanciato 

       my_tree.clear(); 
        std::random_shuffle (elem_out.begin(), elem_out.end() );
        std::random_shuffle (elem_in.begin(), elem_in.end() );
        std::random_shuffle (elem_tot.begin(), elem_tot.end() );

     for(int k=0; k<N; k++)
   {
       my_tree.emplace(elem_in.at(k),1); 
   }




   }


   auto time_emplace_nbal = tot1/double(leaf*iter) - access_time; 

   auto time_erase_nbal = tot2/double(leaf*iter) - access_time; 

   auto time_find_nbal = tot6/double(2*N*iter) - access_time; 

   auto time_balance = tot3/double(iter); 

   auto time_emplace_bal = tot4/double(leaf*iter) - access_time;

   auto time_erase_bal = tot5/double(leaf*iter) - access_time; 

   auto time_find_bal = tot7/double(2*N*iter) - access_time; 

   tot2 =tot5=0; 

   for(int i= 0; i<iter; i++)
   { 
       auto a3 = std::chrono::high_resolution_clock::now();
       for(int j=0; j<leaf; j++)
       { 
           my_tree.erase(elem_tot.at(j)); 
       }
       auto a4 = std::chrono::high_resolution_clock::now();
       auto da2 =std::chrono::duration_cast<std::chrono::microseconds>(a4-a3).count();
       tot2 +=da2;    //tempo eliminazione caso generale albero non bilanciato 

         my_tree.balance(); 

         auto a9 = std::chrono::high_resolution_clock::now();
       for(int j=0; j<leaf; j++)
       { 
           my_tree.erase(elem_tot.at(j)); 
       }
       auto a10 = std::chrono::high_resolution_clock::now();
       auto da5 =std::chrono::duration_cast<std::chrono::microseconds>(a10-a9).count();
       tot5+=da5;    //tempo eliminazione


       my_tree.clear(); 
        std::random_shuffle (elem_out.begin(), elem_out.end() );
        std::random_shuffle (elem_in.begin(), elem_in.end() );
        std::random_shuffle (elem_tot.begin(), elem_tot.end() );

     for(int k=0; k<N; k++)
   {
       my_tree.emplace(elem_in.at(k),1); 
   }


   }

    auto time_erase_nbal_general = tot2/double(leaf*iter) - access_time; 

      auto time_erase_bal_general = tot5/double(leaf*iter) - access_time; 
   std::cout<<"N :"<<N<<std::endl; 

   std::cout<<"insert not balaced: "<<time_emplace_nbal<<std::endl; 

   std::cout<<"remove not balanced: "<<time_erase_nbal<<std::endl;

   std::cout<<"find not balanced: "<<time_find_nbal<<std::endl; 

   std::cout<<"insert balanced: "<<time_emplace_bal<<std::endl; 

   std::cout<<"remove balanced: "<<time_erase_bal<<std::endl;

   std::cout<<"find balanced: "<<time_find_bal<<std::endl; 

   std::cout<<"time to balace the tree: "<<time_balance<<std::endl; 

    std::cout<<"remove not balanced general: "<<time_erase_nbal_general<<std::endl;

     std::cout<<"remove balanced general: "<<time_erase_bal_general<<std::endl;

//ins_nb,rem_nb,f_nb,ins_bal,rem_bal,f_bal,rem_nb_gen,rem_bal_gen,bal_time; 

   // std::cout<<"N :"<<N<<std::endl; 

   ins_nb<<N<<" "<<time_emplace_nbal<<std::endl; 

   rem_nb<<N<<" "<<time_erase_nbal<<std::endl;

   f_nb<<N<<" "<<time_find_nbal<<std::endl; 

   ins_bal<<N<<" "<<time_emplace_bal<<std::endl; 

   rem_bal<<N<<" "<<time_erase_bal<<std::endl;

   f_bal<<N<<" "<<time_find_bal<<std::endl; 

   bal_time<<N<<" "<<time_balance<<std::endl; 

    rem_nb_gen<<N<<" "<<time_erase_nbal_general<<std::endl;

    rem_bal_gen<<N<<" "<<time_erase_bal_general<<std::endl;





   


    result.close();
    return 0;
}