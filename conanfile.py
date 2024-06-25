# /usr/bin/python3
import os
from conan import ConanFile
from conan.tools.build import can_run

class TraactPackage(ConanFile):
    python_requires = "traact_base/0.0.0@traact/latest"
    python_requires_extend = "traact_base.TraactPackageCmake"

    name = "traact_component_zenoh"
    version = "0.0.0"
    description = "Zenoh sub/pub components for traact"
    url = "https://github.com/traact/traact_component_zenoh.git"
    license = "MIT"
    author = "Frieder Pankratz"

    settings = "os", "compiler", "build_type", "arch"
    compiler = "cppstd"

    exports_sources = "src/*", "include/*", "CMakeLists.txt"

    def requirements(self):
        self.requires("traact_spatial/0.0.0@traact/latest")
        self.requires("traact_vision/0.0.0@traact/latest")
        self.requires("traact_pcpd/0.0.0@traact/latest")
        self.requires("zenoh-c/0.10.0-rc@camposs/stable", run=True)

        self.requires("cpp-httplib/0.14.0", run=True)
        self.requires("traact_component_cereal/0.0.0@traact/latest")

    def _after_package_info(self):
        self.cpp_info.libs = ["traact_component_zenoh"]
