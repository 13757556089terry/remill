/* Copyright 2015 Peter Goodman (peter@trailofbits.com), all rights reserved. */

#include <fstream>
#include <glog/logging.h>

#include "remill/CFG/CFG.h"

namespace remill {

const cfg::Module *ReadCFG(std::string cfg_file_name) {
  GOOGLE_PROTOBUF_VERIFY_VERSION;

  std::ifstream cfg(cfg_file_name);
  CHECK(cfg.good()) << "Invalid CFG file: " << cfg_file_name;

  auto cfg_pb = new cfg::Module;
  auto parsed = cfg_pb->ParseFromIstream(&cfg);
  CHECK(parsed) << "Unable to parse CFG file: " << cfg_file_name;

  return cfg_pb;
}

}  // namespace remill

#include "generated/CFG/CFG.pb.cc"
