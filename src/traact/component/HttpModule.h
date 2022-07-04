/** Copyright (C) 2022  Frieder Pankratz <frieder.pankratz@gmail.com> **/

#ifndef TRAACT_COMPONENT_HTTP_SRC_TRAACT_COMPONENT_HTTPMODULE_H_
#define TRAACT_COMPONENT_HTTP_SRC_TRAACT_COMPONENT_HTTPMODULE_H_

#include <traact/traact.h>
#include <httplib.h>


namespace traact::component {

 struct HTTPConfig{
     std::string host;
    int port;
};

class HttpModule  : public Module{
 public:
    using SinkToString = std::function<std::string(void)>;

    virtual bool start(ComponentPtr module_component) override;
    virtual bool stop(ComponentPtr module_component) override;

    void addSink(const std::string& pattern_id, SinkToString sink_to_string, HTTPConfig config = {"0.0.0.0",1234});

 private:
    HTTPConfig config_;
    httplib::Server server_;

    std::mutex component_lock_;
    std::atomic_bool running_{false};
    std::unique_ptr<std::thread> thread_;

};

} // traact

#endif //TRAACT_COMPONENT_HTTP_SRC_TRAACT_COMPONENT_HTTPMODULE_H_
