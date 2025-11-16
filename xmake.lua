add_requires("openssl", "cryptopp", "liburing", "fmt")
add_requires("boost[asio,beast,url,system,filesystem,thread]")
add_rules("plugin.compile_commands.autoupdate", {outputdir = "build/"})
set_languages("c++23")

-- 在debug模式下添加gtest依赖
if is_mode("debug") then
    add_requires("gtest")
end

target("cpphttp")
    set_kind("static")
    add_includedirs("include")
    add_files("src/*.cpp")
    add_packages("openssl", "cryptopp", "liburing", "boost", "fmt")
    add_defines("BOOST_ASIO_HAS_IO_URING", "BOOST_ASIO_HAS_FILE")
    set_toolset("cxx", "clang")
    set_toolset("ld", "clang++")

-- 添加测试目标
if is_mode("debug") then
    target("cpphttp_tests")
        set_kind("binary")
        add_includedirs("include")
        add_files("tests/*.cpp")
        add_deps("cpphttp")
        add_packages("gtest", "openssl", "glog", "cryptopp", "liburing", "boost", "fmt")
        add_defines("BOOST_ASIO_HAS_IO_URING", "BOOST_ASIO_HAS_FILE")
        set_toolset("cxx", "clang")
        set_toolset("ld", "clang++")
end
