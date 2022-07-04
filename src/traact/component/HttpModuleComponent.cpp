/** Copyright (C) 2022  Frieder Pankratz <frieder.pankratz@gmail.com> **/

#include "HttpModuleComponent.h"

namespace traact::component {
std::string HttpModuleComponent::getModuleKey() {
    return "global_http_module";
}
Module::Ptr HttpModuleComponent::instantiateModule() {
    return std::make_shared<HttpModule>();
}
HttpModuleComponent::HttpModuleComponent(const std::string &name) : ModuleComponent(name,
                                                                                    ModuleType::GLOBAL) {}
void HttpModuleComponent::setModule(Module::Ptr module) {
    ModuleComponent::setModule(module);
    http_module_ = std::dynamic_pointer_cast<HttpModule>(module_);
}

} // traact