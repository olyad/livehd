<<<<<<< HEAD
#include "fmt/format.h"
#include "iassert.hpp"
#include <vector>
#include "lrand.hpp"
#include "lbench.hpp"
#include "flat_hash_map.hpp"
#include <type_traits>
#include "mmap_str.hpp"
#include "mmap_map.hpp"


void mmap_pstr(std::string_view name) {
  mmap_lib::str foo("23");
  foo.print_size(); // expect 8
  foo.print_e(); // 2345678
  //foo.print_PoS(); 
  std::cout << foo.is_i() << std::endl; 
}


int main(int argc, char **argv) {

  mmap_pstr("bench_map_use_mmap.data");

}
=======

//  This file is distributed under the BSD 3-Clause License. See LICENSE for details.

#include "fmt/format.h"
#include "iassert.hpp"
#include <vector>
#include "lrand.hpp"
#include "lbench.hpp"
#include "flat_hash_map.hpp"
#include <type_traits>
#include "mmap_pstr.hpp"
#include "mmap_map.hpp"




/*
 * Creates a vset from mmap_lib namespace
 * And tests it a little
 */
void mmap_pstr( std::string_view name) {
  /*
  Lrand<int> rng;

  std::string type_test("mmap_vset ");
	if (name.empty()) { type_test += "(effemeral)"; }
	else { type_test += "(persistent)"; }

	Lbench b(type_test);
	mmap_lib::vset<uint32_t, uint32_t> set("lgdb_bench", name);
	//mmap_lib::map<uint32_t, uint64_t> map("lgdb_bench", name);
	*/
	mmap_lib::pstr<uint32_t, uint32_t> set("lgdb_bench", name);
}

int main(int argc, char **argv) {

  bool run_mmap_pstr = false;

	if (argc>1) {
    if (strcasecmp(argv[1],"pstr") == 0) {
      run_mmap_pstr= true;
		}
  } else {
    run_mmap_pstr = true;
  }

  
  if (run_mmap_pstr) {
      mmap_pstr( "bench_map_use_mmap.data");
		}
  

  return 0;
}

>>>>>>> 11afae2d20857b98e5aa08ec125651938742ccfb
