
#include "stitch_options.hpp"
#include "core/lglog.hpp"

Stitch_pass_pack::Stitch_pass_pack(int argc, const char ** argv) {

  Options::setup(argc, argv);

  Options::get_desc()->add_options()
    ("osynth,o", boost::program_options::value(&osynth_lgdb)->required(), "lgdb path of the original synthesized netlist")
    ("nsynth,n", boost::program_options::value(&nsynth_lgdb)->required(), "lgdb path of the modified synthesized netlist")
    ("method,m", boost::program_options::value(&boundaries_name), "Type of live pass: LiveSynth (dac17) or Structural (LiveSynth is default)")
    ("boundaries,b", boost::program_options::value(&boundaries_name)->required(), "invariant boundaries files generated by lginvariant")
    ("diff,d", boost::program_options::value(&diff_file), "file containing different boundaries (default=diff)")
    ("help,h", "print usage message")
    ;

  boost::program_options::variables_map vm;
  boost::program_options::store(boost::program_options::command_line_parser(Options::get_cargc(), Options::get_cargv()).options(*Options::get_desc()).allow_unregistered().run(), vm);

  if(vm.count("help"))
    return;

  if(vm.count("osynth")) {
    osynth_lgdb  = vm["osynth"].as<std::string>();
  } else {
    console->error("osynth is required\n");
    exit(-1);
  }
  if(vm.count("nsynth")) {
    nsynth_lgdb  = vm["nsynth"].as<std::string>();
  } else {
    console->error("nsynth is required\n");
    exit(-1);
  }
  if(vm.count("boundaries")) {
    boundaries_name = vm["boundaries"].as<std::string>();
  } else {
    console->error("boundaries is required\n");
    exit(-1);
  }
  if(vm.count("method")) {
    if(vm["method"].as<std::string>() == "LiveSynth") {
      method = Live_method::LiveSynth;
    } else if(vm["method"].as<std::string>() == "Structural") {
      method = Live_method::Structural;
    } else {
      console->error("Invalid method option {}, options are LiveSynth and Structural\n", vm["live_method"].as<std::string>());
      exit(-1);
    }
  } else {
    method = Live_method::LiveSynth;
  }
  if(vm.count("diff")) {
    diff_file = vm["diff"].as<std::string>();
  } else {
    diff_file = "diff";
  }

  Options::setup_lock();
}
