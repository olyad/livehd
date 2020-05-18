#include "livesim_types.hpp"

#include "sample_stage.hpp"

Sample_stage::Sample_stage(uint64_t _hidx)
  : hidx(_hidx)
  , s1(33)
  , s2(2123)
  , s3(122) {
  // FIXME: populate random reset (random per variable)
}

void Sample_stage::reset_cycle() {

  s1.reset_cycle();
  s2.reset_cycle();
  s3.reset_cycle();
}

#ifdef SIMLIB_VCD
  void Sample_stage::initialize_vcd_writer(){
    vcd::TimeStamp t=0;// = clock();
   // vcd::VCDWriter vcd_writer;
    const char *var = getenv("SIMLIB_DUMPDIR");
    if (var) {
       std::string dump_directory{var};
       std::string dump_directory_ = dump_directory + "/" + "SIMLIB_VCD.vcd";
       vcd::VCDWriter vcd_writer{dump_directory_, vcd::makeVCDHeader(vcd::TimeScale::ONE, vcd::TimeScaleUnit::ns, vcd::utils::now(), "This is the VCD file", "generated by SimLibVCD") };
  //for S3
       vcd::VarPtr vcd_to1_b = vcd_writer.register_var("sample.s3", "to1_b[31:0]", vcd::VariableType::wire, 32);
       vcd::VarPtr vcd_to3_d = vcd_writer.register_var("sample.s3", "to3_d[31:0]", vcd::VariableType::wire, 32);
       vcd::VarPtr vcd_to3_c = vcd_writer.register_var("sample.s3", "to3_c[31:0]", vcd::VariableType::wire, 32);
       vcd::VarPtr vcd_to3_cValid = vcd_writer.register_var("sample.s3", "to3_cValid", vcd::VariableType::wire, 1);
       vcd::VarPtr vcd_to3_dValid = vcd_writer.register_var("sample.s3", "to3_dValid", vcd::VariableType::wire, 1);
       vcd::VarPtr vcd_reset_iterator = vcd_writer.register_var("sample.s3", "reset_iterator[7:0]", vcd::VariableType::reg, 8);
       vcd::VarPtr vcd_clk = vcd_writer.register_var("sample.s3", "clk", vcd::VariableType::wire, 1);
       vcd::VarPtr vcd_reset = vcd_writer.register_var("sample.s3", "reset", vcd::VariableType::wire, 1);
 //for S2

//for S1
    } else {
       vcd::VCDWriter vcd_writer{"SIMLIB_VCD.vcd", vcd::makeVCDHeader(vcd::TimeScale::ONE, vcd::TimeScaleUnit::ns, vcd::utils::now(), "This is the VCD file", "generated by SimLibVCD") };
   //for S3
       vcd::VarPtr vcd_to1_b = vcd_writer.register_var("sample.s3", "to1_b[31:0]", vcd::VariableType::wire, 32);
       vcd::VarPtr vcd_to3_d = vcd_writer.register_var("sample.s3", "to3_d[31:0]", vcd::VariableType::wire, 32);
       vcd::VarPtr vcd_to3_c = vcd_writer.register_var("sample.s3", "to3_c[31:0]", vcd::VariableType::wire, 32);
       vcd::VarPtr vcd_to3_cValid = vcd_writer.register_var("sample.s3", "to3_cValid", vcd::VariableType::wire, 1);
       vcd::VarPtr vcd_to3_dValid = vcd_writer.register_var("sample.s3", "to3_dValid", vcd::VariableType::wire, 1);
       vcd::VarPtr vcd_reset_iterator = vcd_writer.register_var("sample.s3", "reset_iterator[7:0]", vcd::VariableType::reg, 8);
       vcd::VarPtr vcd_clk = vcd_writer.register_var("sample.s3", "clk", vcd::VariableType::wire, 1);
       vcd::VarPtr vcd_reset = vcd_writer.register_var("sample.s3", "reset", vcd::VariableType::wire, 1);
 //for S2

//for S1
    }
 }

  void Sample_stage::vcd_cycle() {

    auto s1_to2_aValid = s1.to2_aValid;
    auto s1_to2_a      = s1.to2_a;
    auto s1_to2_b      = s1.to2_b;
    auto s1_to3_cValid = s1.to3_cValid;
    auto s1_to3_c      = s1.to3_c;
    s1.vcd_cycle(s3.to1_b, s2.to1_aValid, s2.to1_a);

    auto s2_to3_dValid = s2.to3_dValid;
    auto s2_to3_d      = s2.to3_d;
    s2.vcd_cycle(s1_to2_aValid, s1_to2_a, s1_to2_b);

    s3.vcd_cycle(s1_to3_cValid, s1_to3_c, s2_to3_dValid, s2_to3_d);

  }
#else
  void Sample_stage::cycle() {

    auto s1_to2_aValid = s1.to2_aValid;
    auto s1_to2_a      = s1.to2_a;
    auto s1_to2_b      = s1.to2_b;
    auto s1_to3_cValid = s1.to3_cValid;
    auto s1_to3_c      = s1.to3_c;
    s1.cycle(s3.to1_b, s2.to1_aValid, s2.to1_a);

    auto s2_to3_dValid = s2.to3_dValid;
    auto s2_to3_d      = s2.to3_d;
    s2.cycle(s1_to2_aValid, s1_to2_a, s1_to2_b);

    s3.cycle(s1_to3_cValid, s1_to3_c, s2_to3_dValid, s2_to3_d);

  }
#endif
#ifdef SIMLIB_TRACE
  void Sample_stage::add_signature(Simlib_signature &s) {
    s1.add_signature(s);
    s2.add_signature(s);
    s3.add_signature(s);
  }
#endif
