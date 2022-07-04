/** Copyright (C) 2022  Frieder Pankratz <frieder.pankratz@gmail.com> **/

#include <traact/vision.h>
#include <traact/cereal/CerealSpatial.h>
#include <traact/cereal/CerealVision.h>
#include "HttpModuleComponent.h"

namespace traact::component {
template<class T>
class HttpSink : public HttpModuleComponent {
 public:
    HttpSink(const std::string &name) : HttpModuleComponent(name) {}

    [[nodiscard]] static traact::pattern::Pattern::Ptr GetPattern() {
        std::string pattern_name = fmt::format("HttpSink_{0}", T::NativeTypeName);

        traact::pattern::Pattern::Ptr
            pattern =
            std::make_shared<traact::pattern::Pattern>(pattern_name, Concurrency::SERIAL, ComponentType::SYNC_SINK);

        pattern->addConsumerPort("input", T::NativeTypeName)
            .addStringParameter("host", "0.0.0.0")
            .addParameter("port", 1234, 0, 65535);

        pattern->addCoordinateSystem("A").addCoordinateSystem("B").addEdge("A", "B", "input");

        return pattern;

    }

    bool configure(const pattern::instance::PatternInstance &pattern_instance,
                   buffer::ComponentBufferConfig *data) override {

        pattern_instance.template setValueFromParameter("host", config_.host);
        pattern_instance.template setValueFromParameter("port", config_.port);
        auto value_to_string = [this]() -> std::string {
            return valueToString();
        };
        http_module_->addSink(pattern_instance.instance_id, value_to_string, config_);

        return ModuleComponent::configure(pattern_instance, data);
    }

    bool processTimePoint(buffer::ComponentBuffer &data) override {
        std::unique_lock guard(value_lock_);

        value_ = data.template getInput<T>(0);

        return true;
    }

    std::string valueToString() {
        std::unique_lock guard(value_lock_);

        if (value_.has_value()) {
            std::stringstream  string_stream;
            cereal::JSONOutputArchive archive(string_stream);
            archive(value_.value());
            return string_stream.str();
        } else {
            std::stringstream  string_stream;
            cereal::JSONOutputArchive archive(string_stream);
            archive(typename T::NativeType());
            return string_stream.str();
        }

    }

 private:
    HTTPConfig config_;
    std::optional<typename T::NativeType> value_;
    std::mutex value_lock_;

};
CREATE_SPATIAL_COMPONENTS(HttpSink)
CREATE_VISION_COMPONENTS(HttpSink)

}

BEGIN_TRAACT_PLUGIN_REGISTRATION
    REGISTER_SPATIAL_COMPONENTS(traact::component::HttpSink)
    REGISTER_VISION_COMPONENTS(traact::component::HttpSink)
END_TRAACT_PLUGIN_REGISTRATION


