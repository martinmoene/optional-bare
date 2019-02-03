from conans import ConanFile

class OptionalBareConan(ConanFile):
    version = "1.0.0"
    name = "optional-bare"
    description = "A simple version of a C++17-like optional for default-constructible, copyable types, for C++98 and later in a single-file header-only library"
    license = "Boost Software License - Version 1.0. http://www.boost.org/LICENSE_1_0.txt"
    url = "https://github.com/martinmoene/optional-bare.git"
    exports_sources = "include/nonstd/*", "LICENSE.txt"
    build_policy = "missing"    
    author = "Martin Moene"

    def build(self):
        """Avoid warning on build step"""
        pass

    def package(self):
        """Provide pkg/include/nonstd/*.hpp"""
        self.copy("*.hpp")

    def package_info(self):
        self.info.header_only()
