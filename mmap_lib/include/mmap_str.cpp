#include "fmt/format.h"
#include "iassert.hpp"
#include <vector>
#include "lrand.hpp"
#include "lbench.hpp"
#include "flat_hash_map.hpp"
#include <type_traits>
#include "mmap_str.hpp"
#include "mmap_map.hpp"

//helper functions

find_small_size(const str &my, const str &v, std::size_t pos = 0){
	char first = ((v.ptr_or_start >> (8 * (v._size-1))) & 0xFF);//different ways
      size_t retval = 0;
      bool found_flag = false;
      int i,j,k;
      int e_pos_self =0;
      int e_pos_thier =0;
      for ( i =0; i <4 ; i++){
        retval = 0;
        found_flag = false;
        e_pos_self =0;
        e_pos_thier =0;
        if ((first == ((my.ptr_or_start >> (8 * (3 - i))) & 0xFF)) and  ( pos >= i)) {
          retval = i;
          found_flag = true;
          for ( j = i,  k =1; j< 4; j++,k++){
            
            if (((v.ptr_or_start >> (8 * (3 - k))) & 0xFF) != ((my.ptr_or_start >> (8 * (3 - j))) & 0xFF)){
              found_flag = false;
              break;
            }
          }
          while(k < v._size){
            if (k < 4){
              if(((v.ptr_or_start >> (8 * (3 - k))) & 0xFF)  != my.e[e_pos_self]) {

                found_flag = false;
                break;
              }
            } else {
              if (v.e[e_pos_thier ] != my.e[e_pos_self]){
                found_flag = false;
                e_pos_thier++;
                break;
              }
            }
            e_pos_self++;
            k++;
          }

        }
        if (found_flag == true) return retval;
      }
      //if you havent found the string at this point and this string is < 4 chaars then find returns -1
      //if((_size < 4 ) and (found_flag == false)) return -1;
      return -1;
}