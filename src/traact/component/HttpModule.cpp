/** Copyright (C) 2022  Frieder Pankratz <frieder.pankratz@gmail.com> **/

#include "HttpModule.h"

namespace traact::component {
bool HttpModule::start(Module::ComponentPtr module_component) {
    std::unique_lock guard(component_lock_);

    if(!running_){
        running_ = true;
        thread_ = std::make_unique<std::thread>([this]() {
            server_.listen(config_.host.c_str(), config_.port);
        });
    }
    return true;
}
bool HttpModule::stop(Module::ComponentPtr module_component) {
    std::unique_lock guard(component_lock_);

    if(running_){
        server_.stop();
        thread_->join();
        thread_.reset();
        running_ = false;
    }

    return true;
}
void HttpModule::addSink(const std::string &pattern_id,
                         HttpModule::SinkToString sink_to_string,
                         HTTPConfig config) {

    std::unique_lock guard(component_lock_);
    config_ = config;

    server_.Get(fmt::format("/{0}", pattern_id), [sink_to_string](const httplib::Request& req, httplib::Response& res){
        res.set_content(sink_to_string(), "text/plain");
    });
}
} // traact