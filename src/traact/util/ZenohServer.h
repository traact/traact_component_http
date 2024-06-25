/** Copyright (C) 2022  Frieder Pankratz <frieder.pankratz@gmail.com> **/

#ifndef TRAACT_ALL_ZENOHSERVER_H
#define TRAACT_ALL_ZENOHSERVER_H

#include <string>
#include <vector>
#include <map>
#include <functional>
#include "zenoh.h"

#include <traact/datatypes.h>
#include <spdlog/spdlog.h>

namespace traact::util {


void data_handler(const z_sample_t *sample, void *arg) {
  z_owned_str_t keystr = z_keyexpr_to_string(sample->keyexpr);

  printf(">> [Subscriber] Received %d ('%s': '%.*s')\n", (int)(sample->kind), z_loan(keystr),
         (int)sample->payload.len, sample->payload.start);
  z_drop(z_move(keystr));
}


class ZenohServer {
 public:
  ZenohServer();
  explicit ZenohServer(std::string config);
  explicit ZenohServer(z_owned_config_t config);
  ~ZenohServer();

  template<typename T> std::function<void(T, Timestamp)> addPublisher(const std::string& keyexpr, z_publisher_put_options_t options_put, z_publisher_options_t* options = nullptr) {

    SPDLOG_DEBUG("Declaring Publisher on '{0}'...", keyexpr);

    auto& local_pub = _pubs[keyexpr];
    if(options){
      local_pub.options = std::make_unique<z_publisher_options_t>(options);
    }

    local_pub.pub = z_declare_publisher(z_loan(_session), z_keyexpr(keyexpr.c_str()), local_pub.options.get());
    if (!z_check(local_pub.pub)) {
      throw std::invalid_argument("Unable to declare Publisher for key expression!");
    }


    return [local_pub](const T &value, Timestamp ts) -> void {
      uint8_t * buffer;
      uintptr_t length;
      z_publisher_put(z_loan(local_pub.pub), buffer, length, &local_pub.options_put);
    };
  }

  template<typename T> void addSubscriber(const std::string& keyexpr, std::function<void(T, Timestamp)> func ) {
    z_owned_closure_sample_t callback = z_closure(data_handler, func);
    SPDLOG_DEBUG("Declaring Subscriber on '{0}'...", keyexpr);

    z_owned_subscriber_t sub = z_declare_subscriber(z_loan(_session), z_keyexpr(keyexpr.c_str()), z_move(callback), NULL);
    if (!z_check(sub)) {
      throw std::invalid_argument("Unable to declare subscriber.");
    }
  }

  private:
   struct ZenohPub{
     z_owned_publisher_t pub;
     std::shared_ptr<z_publisher_options_t> options{};
     z_publisher_put_options_t options_put;

   };

  z_owned_config_t _config{z_config_default()};
  z_owned_session_t _session;

  std::map<std::string, ZenohPub> _pubs;

  void init();

};

}// namespace traact

#endif//TRAACT_ALL_ZENOHSERVER_H
