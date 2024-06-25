/** Copyright (C) 2022  Frieder Pankratz <frieder.pankratz@gmail.com> **/

#include "ZenohServer.h"

namespace traact {
util::ZenohServer::ZenohServer() {
  init();
}

util::ZenohServer::ZenohServer(std::string config) {
  if (zc_config_insert_json(z_loan(_config), Z_CONFIG_CONNECT_KEY, config.c_str()) < 0) {
    throw std::invalid_argument(fmt::format("Couldn't insert value `{0}` in configuration at `{1}`. This is likely because `{2}` expects a "
                                            "JSON-serialized list of strings\n", config, Z_CONFIG_CONNECT_KEY, Z_CONFIG_CONNECT_KEY));
  }
  init();
}


util::ZenohServer::ZenohServer(z_owned_config_t config) {
  _config = config;
  init();
}

util::ZenohServer::~ZenohServer() {

  for (auto & name_pub : _pubs) {
    z_undeclare_publisher(z_move(name_pub.second.pub));
  }

  z_close(z_move(_session));
}
void util::ZenohServer::init() {
  SPDLOG_INFO("Opening zenoh session ...");
  _session = z_open(z_move(_config));
  if (!z_check(_session)) {
    throw std::invalid_argument("Unable to open zenoh session");
  }

}

}// namespace traact