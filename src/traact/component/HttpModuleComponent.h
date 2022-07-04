/** Copyright (C) 2022  Frieder Pankratz <frieder.pankratz@gmail.com> **/

#ifndef TRAACT_COMPONENT_HTTP_SRC_TRAACT_COMPONENT_HTTPMODULECOMPONENT_H_
#define TRAACT_COMPONENT_HTTP_SRC_TRAACT_COMPONENT_HTTPMODULECOMPONENT_H_

#include "HttpModule.h"

namespace traact::component {

class HttpModuleComponent : public ModuleComponent{
 public:
    HttpModuleComponent(const std::string &name);
    virtual ~HttpModuleComponent() = default;

    std::string getModuleKey() override;
    Module::Ptr instantiateModule() override;
    virtual void setModule(Module::Ptr module) override;
 protected:
    std::shared_ptr<HttpModule> http_module_;

};

} // traact

#endif //TRAACT_COMPONENT_HTTP_SRC_TRAACT_COMPONENT_HTTPMODULECOMPONENT_H_
