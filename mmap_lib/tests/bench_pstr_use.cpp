#include "fmt/format.h"
#include "iassert.hpp"
#include <vector>
#include "lrand.hpp"
#include "lbench.hpp"
#include "flat_hash_map.hpp"
#include <type_traits>
#include "mmap_str.hpp"
#include "mmap_map.hpp"

#if 0
//implicitly changes ts to string_view
void test_sview(const char * ts) {
  std::cout << "> Test Case: str(\"" << ts << "\")" << std::endl;
  mmap_lib::str test11(ts);
  std::cout << "  "; test11.print_PoS(); 
  std::cout << "  "; test11.print_e();
  std::cout << "  "; test11.print_StrMap();
  std::cout << "  "; test11.print_StrVec();
  std::cout << std::endl;
}
#endif

void test_ctor(mmap_lib::str ts, const char* rs) {
  std::cout << "> Test Case: str(\"" << rs << "\")" << std::endl;
  std::cout << "  "; ts.print_PoS(); 
  std::cout << "  "; ts.print_e();
  std::cout << "  "; ts.print_StrMap();
  std::cout << "  "; ts.print_StrVec();
  std::cout << std::endl;
}

void mmap_pstr_ctor_tests() { 
  std::cout << "================================ " << std::endl;
  std::cout << "Constructor 1 (size < 14) Tests: " << std::endl;
  std::cout << "================================ " << std::endl;
  
  test_ctor(mmap_lib::str("hello"),         "hello"); 
  test_ctor(mmap_lib::str("cat"),           "cat");
  test_ctor(mmap_lib::str("four"),          "four");
  test_ctor(mmap_lib::str("feedback"),      "feedback"); 
  test_ctor(mmap_lib::str("natural_fries"), "natural_fries");
  
  std::cout << "================================ " << std::endl;
  std::cout << "Constructor 2 (size >=14) Tests: " << std::endl;
  std::cout << "================================ " << std::endl;

  test_ctor(mmap_lib::str("0_words_1234567"), "0_words_1234567");
  test_ctor(mmap_lib::str("7_words_6543210"), "7_words_6543210");
  test_ctor(mmap_lib::str("0_sloan_1234567"), "0_sloan_1234567");
  test_ctor(mmap_lib::str("0_tang_1234567"),  "0_tang_1234567");
  test_ctor(mmap_lib::str("hisloanbuzzball"), "hisloanbuzzball");
  test_ctor(mmap_lib::str("--this_var_will_bee_very_longbuzzball")
                         , "--this_var_will_bee_very_longbuzzball");
  test_ctor(mmap_lib::str("hidifferentbuzzball"), "hidifferentbuzzball");

  std::cout << "================================ " << std::endl;
  std::cout << "Constructor 3 (string_view) Tests: " << std::endl;
  std::cout << "================================ " << std::endl;

  test_ctor(mmap_lib::str(std::string_view("hello")),          "hello"); 
  test_ctor(mmap_lib::str(std::string_view("cat")),            "cat"); 
  test_ctor(mmap_lib::str(std::string_view("abcd")),           "abcd"); 
  test_ctor(mmap_lib::str(std::string_view("feedback")),       "feedback"); 
  test_ctor(mmap_lib::str(std::string_view("neutralizatio")),  "neutralizatio"); 
  test_ctor(mmap_lib::str(std::string_view("neutralization")), "neutralization"); 
  test_ctor(mmap_lib::str(std::string_view("01andy23456789")), "01andy23456789"); 
  test_ctor(mmap_lib::str(std::string_view("--this_var_will_bee_very_longbuzzball"))
                         , "--this_var_will_bee_very_longbuzzball");

  std::cout << "================================== " << std::endl;
  std::cout << "Constructor 3 (const char *) Tests: " << std::endl;
  std::cout << "================================== " << std::endl;
  
  const char *hello = "hello";
  const char *cat = "cat";
  const char *abcd = "abcd";
  const char *feedback = "feedback";
  const char *n13 = "neutralizatio";
  const char *n14 = "neutralization";
  const char *andy = "01andy23456789";
  const char *lvar = "--this_var_will_bee_very_longbuzzball";

  test_ctor(mmap_lib::str(hello),          "hello"); 
  test_ctor(mmap_lib::str(cat),            "cat"); 
  test_ctor(mmap_lib::str(abcd),           "abcd"); 
  test_ctor(mmap_lib::str(feedback),       "feedback"); 
  test_ctor(mmap_lib::str(n13),  "neutralizatio"); 
  test_ctor(mmap_lib::str(n14), "neutralization"); 
  test_ctor(mmap_lib::str(andy), "01andy23456789"); 
  test_ctor(mmap_lib::str(lvar) , "--this_var_will_bee_very_longbuzzball");
  /*
  std::cout << "> Test 17: str(\"lonng_andalsjdfkajsdkfljkalsjdfkljaskldjfklajdkslfjalsdjfllaskdfjklajskdlfjklasjdfljasdklfjklasjdflasjdflkajsdflkjakljdfkljaldjfkjakldsjfjaklsjdfjklajsdfjaklsfasjdklfjklajskdljfkljlaksjdklfjlkajsdklfjkla01words23456789\") " << std::endl;
  mmap_lib::str test17("lonng_andalsjdfkajsdkfljkalsjdfkljaskldjfklajdkslfjalsdjfllaskdfjklajskdlfjklasjdfljasdklfjklasjdflasjdflkajsdflkjakljdfkljaldjfkjakldsjfjaklsjdfjklajsdfjaklsfasjdklfjklajskdljfkljlaksjdklfjlkajsdklfjkla01words23456789");
  */
}

template<std::size_t N>
bool test_eq(mmap_lib::str ts, const char (&rs)[N], bool ans) {
  return (ts == rs) == ans;
}

template<std::size_t N>
bool test_neq(mmap_lib::str ts, const char (&rs)[N], bool ans) {
  return (ts != rs) == ans;
}

bool test_eq(mmap_lib::str ls, mmap_lib::str rs, bool ans) {
  return (ls == rs) == ans;
}

bool test_neq(mmap_lib::str ls, mmap_lib::str rs, bool ans) {
  return (ls != rs) == ans;
}

/*
bool test_eq(mmap_lib::str ls, const char* rs, bool ans) {
  return (ls == rs) == ans;
}

bool test_neq(mmap_lib::str ls, const char* rs, bool ans) {
  return (ls != rs) == ans;
}
*/

bool test_eq(mmap_lib::str ls, std::string_view rs, bool ans) {
  return (ls == rs) == ans;
}

bool test_neq(mmap_lib::str ls, std::string_view rs, bool ans) {
  return (ls != rs) == ans;
}

void pstrVchar_eqeq_tests() {
  std::cout << "pstr vs. char Operator == Tests: ";
  mmap_lib::str hello("hello");
  mmap_lib::str hi("hi");
  mmap_lib::str hello_world("hello_!_world");
  mmap_lib::str micro("micro-architecture");
  mmap_lib::str foo("--foo1234567890!!!");
  
  uint8_t r = 0u, t = 0u;
  r += test_eq(hello,       "hello",              true); ++t;
  r += test_eq(hello,       "hi",                 false); ++t;
  r += test_eq(hi,          "hi",                 true); ++t;
  r += test_eq(hi,          "hello",              false); ++t;
  r += test_eq(hello_world, "hello_!_world",      true); ++t;
  r += test_eq(hello_world, "hi",                 false); ++t;
  r += test_eq(hello,       "hello_!_word",       false); ++t;
  r += test_eq(micro,       "micro-architecture", true); ++t;
  r += test_eq(foo,         "micro-architecture", false); ++t;
  r += test_eq(foo,         "--foo1234567890!!!", true); ++t;
  r += test_eq(micro,       "micro-architecture", true); ++t;
  r += test_eq(micro,       "hi",                 false); ++t;
  r += test_eq(hi,          "micro-architecture", false); ++t;
  printf("passed(%02d/%02d), failed(%02d/%02d)\n", r, t, t-r, t);
}

void pstrVchar_noeq_tests() {
  std::cout << "pstr vs. char Operator != Tests: ";
  mmap_lib::str hello("hello");
  mmap_lib::str hi("hi");
  mmap_lib::str hello_world("hello_!_world");
  mmap_lib::str amethysts("amethysts_emeralds");
  mmap_lib::str balloon("_balloon_223344!!!");
  
  uint8_t r = 0u, t = 0u;
  r += test_neq(hello,       "hi",                 true); ++t;
  r += test_neq(hello,       "hello",              false); ++t;
  r += test_neq(hello_world, "hi",                 true); ++t;
  r += test_neq(hello_world, "hello_!_world",      false); ++t;
  r += test_neq(amethysts,   "_balloon_223344!!!", true); ++t;
  r += test_neq(balloon,     "_balloon_223344!!!", false); ++t;
  r += test_neq(hello,       "amethysts_emeralds", true); ++t;
  r += test_neq(amethysts,   "hi",                 true); ++t;
  printf("passed(%02d/%02d), failed(%02d/%02d)\n", r, t, t-r, t);
}


void pstrVpstr_eqeq_tests() {
  std::cout << "pstr vs. pstr Operator == Tests: ";
  mmap_lib::str hello("hello");
  mmap_lib::str hi("hi");
  mmap_lib::str hello_world("hello_!_world");
  mmap_lib::str micro("micro-architecture");
  mmap_lib::str foo("--foo1234567890!!!");

  uint8_t r = 0u, t = 0u;
  r += test_eq(hello,       hello,       true); ++t;
  r += test_eq(hello,       hi,          false); ++t;
  r += test_eq(hi,          hi,          true); ++t;
  r += test_eq(hi,          hello,       false); ++t;
  r += test_eq(hello_world, hello_world, true); ++t;
  r += test_eq(hello_world, hi,          false); ++t;
  r += test_eq(hello,       hello_world, false); ++t;
  r += test_eq(micro,       micro,       true); ++t;
  r += test_eq(foo,         micro,       false); ++t;
  r += test_eq(foo,         foo,         true); ++t;
  r += test_eq(micro,       micro,       true); ++t;
  r += test_eq(micro,       hi,          false); ++t;
  r += test_eq(hi,          micro,       false); ++t;
  printf("passed(%02d/%02d), failed(%02d/%02d)\n", r, t, t-r, t);
}

void pstrVpstr_noeq_tests() {
  std::cout << "pstr vs. pstr Operator != Tests: ";
  mmap_lib::str hello("hello");
  mmap_lib::str hi("hi");
  mmap_lib::str hello_world("hello_!_world");
  mmap_lib::str amethysts("amethysts_emeralds");
  mmap_lib::str balloon("_balloon_223344!!!");
  
  uint8_t r = 0u, t = 0u;
  r += test_neq(hello,       hi,          true); ++t;
  r += test_neq(hello,       hello,       false); ++t;
  r += test_neq(hello_world, hi,          true); ++t;
  r += test_neq(hello_world, hello_world, false); ++t;
  r += test_neq(amethysts,   balloon,     true); ++t;
  r += test_neq(balloon,     balloon,     false); ++t;
  r += test_neq(hello,       amethysts,   true); ++t;
  r += test_neq(amethysts,   hi,          true); ++t;
  printf("passed(%02d/%02d), failed(%02d/%02d)\n", r, t, t-r, t);
}


void pstrVcstr_eqeq_tests() {
  std::cout << "pstr vs. cstr Operator == Tests: ";
  mmap_lib::str hello("hello");
  mmap_lib::str hi("hi");
  mmap_lib::str hello_world("hello_!_world");
  mmap_lib::str micro("micro-architecture");
  mmap_lib::str foo("--foo1234567890!!!");
  const char* chello = "hello";
  const char* chi = "hi";
  const char* chello_world = "hello_!_world";
  const char* cmicro = "micro-architecture";
  const char* cfoo = "--foo1234567890!!!";

  uint8_t r = 0u, t = 0u;
  r += test_eq(hello,       chello,       true); ++t;
  r += test_eq(hello,       chi,          false); ++t;
  r += test_eq(hi,          chi,          true); ++t;
  r += test_eq(hi,          chello,       false); ++t;
  r += test_eq(hello_world, chello_world, true); ++t;
  r += test_eq(hello_world, chi,          false); ++t;
  r += test_eq(hello,       chello_world, false); ++t;
  r += test_eq(micro,       cmicro,       true); ++t;
  r += test_eq(foo,         cmicro,       false); ++t;
  r += test_eq(foo,         cfoo,         true); ++t;
  r += test_eq(micro,       cmicro,       true); ++t;
  r += test_eq(micro,       chi,          false); ++t;
  r += test_eq(hi,          cmicro,       false); ++t;
  printf("passed(%02d/%02d), failed(%02d/%02d)\n", r, t, t-r, t);
}

void pstrVcstr_noeq_tests() {
  std::cout << "pstr vs. cstr Operator != Tests: ";
  mmap_lib::str hello("hello");
  mmap_lib::str hi("hi");
  mmap_lib::str hello_world("hello_!_world");
  mmap_lib::str amethysts("amethysts_emeralds");
  mmap_lib::str balloon("_balloon_223344!!!");
  const char* chello = "hello";
  const char* chi = "hi";
  const char* chello_world = "hello_!_world";
  const char* camethysts = "amethysts_emeralds";
  const char* cballoon = "_balloon_223344!!!";
  
  uint8_t r = 0u, t = 0u;
  r += test_neq(hello,       chi,          true); ++t;
  r += test_neq(hello,       chello,       false); ++t;
  r += test_neq(hello_world, chi,          true); ++t;
  r += test_neq(hello_world, chello_world, false); ++t;
  r += test_neq(amethysts,   cballoon,     true); ++t;
  r += test_neq(balloon,     cballoon,     false); ++t;
  r += test_neq(hello,       camethysts,   true); ++t;
  r += test_neq(amethysts,   chi,          true); ++t;
  printf("passed(%02d/%02d), failed(%02d/%02d)\n", r, t, t-r, t);
}

void pstr_at_operator(){
  std::cout << "pstr_at_operator Operator [] Tests: ";
  mmap_lib::str hello("hello");
  mmap_lib::str hi("hi");
  mmap_lib::str hello_world("hello_!_world");
  mmap_lib::str micro("micro-architecture");
  mmap_lib::str foo("--foo1234567890!!!");
  uint8_t p = 0u ,f = 0u;
  (hello[2] == 'l') ? p++ : f++;
  (hello[0] == 'h') ? p++ : f++;
  (hello[1] == 'e') ? p++ : f++;
  (hi[0] == 'h') ? p++ : f++;
  (hi[1] == 'i') ? p++ : f++;
  (micro[1] == 'i') ? p++ : f++;
  (micro[5] == '-') ? p++ : f++;
  (micro[10] == 'i') ? p++ : f++;
  (micro[9] == 'h') ? p++ : f++;
  (micro[17] == 'e') ? p++ : f++;
  (micro[3] == 'r') ? p++ : f++;
  (micro[2] == 'c') ? p++ : f++;
  (foo[0] == '-') ? p++ : f++;
  (foo[1] == '-') ? p++ : f++;
  printf("passed(%02d/%02d), failed(%02d/%02d)\n", p, p+f, f, p+f);
}


void pstr_isI(){
  std::cout << "pstr_isI Tests: ";
  mmap_lib::str hello("hello");
  mmap_lib::str eight("888888");
  mmap_lib::str neg_one("-111111");
  mmap_lib::str not_i("123g5");
  mmap_lib::str not_int("-1234f");
  mmap_lib::str zero("-1234f");
  mmap_lib::str num_float("12.34");
  uint8_t p = 0u ,f = 0u;
  (hello.is_i() == false) ? p++ : f++;
  (eight.is_i() == true) ? p++ : f++;
  (neg_one.is_i() == true) ? p++ : f++;
  (not_i.is_i() == false) ? p++ : f++;
  (not_int.is_i() == false) ? p++ : f++;
  (zero.is_i() == false) ? p++ : f++;
  (num_float.is_i() == false) ? p++ : f++;
  printf("passed(%02d/%02d), failed(%02d/%02d)\n", p, p+f, f, p+f);
}
void Pstr_toI(){
  std::cout << "Pstr_toI Tests: " << std::endl;
  std::cout << "you still did not test non int strings" << std::endl;
  mmap_lib::str one("1234");
  mmap_lib::str two("8828282882828282882828288282828");
  mmap_lib::str three("-2345");
  mmap_lib::str four("-987");
  mmap_lib::str five("109000002");
  mmap_lib::str six("-4332");
  mmap_lib::str seven("8");
  mmap_lib::str eight("-1");
  mmap_lib::str nine("0");
  uint8_t p = 0u ,f = 0u;
  (one.to_i() == 1234) ? p++ : f++;
  std::cout << "one is " << one.to_i() << std::endl;

  //(two.to_i() == 8) ? p++ : f++;
  (three.to_i() == -2345) ? p++ : f++;
  (four.to_i() == -987) ? p++ : f++;
  (five.to_i() == 109000002) ? p++ : f++;
  (six.to_i() == -4332) ? p++ : f++;
  //(seven.to_i() == 8) ? p++ : f++;
  ////(eight.to_i() == -1) ? p++ : f++;
  //(nine.to_i() == 8) ? p++ : f++;
  printf("passed(%02d/%02d), failed(%02d/%02d)\n", p, p+f, f, p+f);
}
void pstr_tos(){
  std::cout << "Pstr_to string Tests: ";
  mmap_lib::str hello("hello");
  std::string  hello1 = "hello";
  mmap_lib::str hi("hi");
  std::string hi1 = "hi";
  mmap_lib::str hello_world("hello_!_world");
  std::string hello_world1 = "hello_!_world";
  mmap_lib::str micro("micro-architecture");
  std::string micro1 = "micro-architecture";
  mmap_lib::str foo("--foo1234567890!!!");
  std::string foo1 = "--foo1234567890!!!";
  uint8_t p = 0u ,f = 0u;
  (hello.to_s() == hello1) ? p++ : f++;
  (hi.to_s() == hi1) ? p++ : f++;
  (hello_world.to_s() == hello_world1) ? p++ : f++;
  (micro.to_s() == micro1) ? p++ : f++;
  (foo.to_s() == foo1) ? p++ : f++;
  (foo.to_s() != hello1) ? p++ : f++;
  (hello_world.to_s() != hi1) ? p++ : f++;
  (hello.to_s() != foo1) ? p++ : f++;
  (hi.to_s() != micro1) ? p++ : f++;
  (hello.to_s() != micro1) ? p++ : f++;
  printf("passed(%02d/%02d), failed(%02d/%02d)\n", p, p+f, f, p+f);
  
}
//////////////////////////////////////////////////////rfind/////////////////////////////
void pstr_rfind_char(){
  std::cout << "pstr_rfind_char Tests: ";
  mmap_lib::str hello("hello");
  mmap_lib::str hi("hi");
  mmap_lib::str hello_world("hello_!_world");
  mmap_lib::str micro("micro-architecture");
  uint8_t p = 0u ,f = 0u;
  (hello.rfind('o', 3)  == -1) ? p++ : f++;
  (hello.rfind('o', 5)  == 4) ? p++ : f++;
  (hi.rfind('i', 2)  == 1) ? p++ : f++;// need to implement size < 4
  (hello_world.rfind('_', 11)  == 7) ? p++ : f++;
  std::cout << (hello_world.rfind('_',11));
  (hello_world.rfind('_', 6)  == 5) ? p++ : f++;
  (hello_world.rfind('_', 4)  == -1) ? p++ : f++;
  (micro.rfind('i', 1)  == 1) ? p++ : f++;
  (micro.rfind('i', 18)  == 10) ? p++ : f++;
  (micro.rfind('e', 18)  == 17) ? p++ : f++;
  (micro.rfind('e', 17)  == 17) ? p++ : f++;
  printf("passed(%02d/%02d), failed(%02d/%02d)\n", p, p+f, f, p+f);
}


int main(int argc, char **argv) {
  //mmap_pstr_ctor_tests();
  
  std::cout << "==========================" << std::endl;
 
  //pstr_at_operator();
  //pstr_isI();
  //Pstr_toI();
  //pstr_tos();

  pstr_rfind_char();
  std::cout << "==========================" << std::endl;
  
 /* 
  mmap_lib::str ts("hello");
  const char *t2 = "hello";
  const char (&t3)[6] = "hello";
  std::string t5 = "hello"; 
  std::string_view t4("hello");

  if (test_eq(ts, t5.c_str(), true)) { printf("match\n"); }
  else { printf("miss\n"); } 
  */
  return 0;
}
