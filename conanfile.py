# /usr/bin/python3
import os
from conans import ConanFile, CMake, tools


class TraactPackage(ConanFile):
    python_requires = "traact_run_env/1.0.0@traact/latest"
    python_requires_extend = "traact_run_env.TraactPackageCmake"

    name = "traact_component_http"
    description = "Simple HTTP sink(get)/source(post) components for traact using cereal"
    url = "https://github.com/traact/traact_component_http.git"
    license = "MIT"
    author = "Frieder Pankratz"

    settings = "os", "compiler", "build_type", "arch"
    compiler = "cppstd"

    exports_sources = "src/*", "CMakeLists.txt"

    def requirements(self):
        # add your dependencies
        self.traact_requires("traact_component_cereal", "latest")
        self.requires("cpp-httplib/0.10.8")