add_requires("gtest", "openssl", "glog", "cryptopp", "liburing", "fmt")
add_requires("boost[asio,beast,url,system,filesystem,thread]")
set_languages("c++23")

target("cpphttp_tests")
    set_kind("binary")
    add_includedirs("../include")
    add_files("test_main.cpp")
    add_deps("cpphttp")
    add_packages("gtest", "openssl", "glog", "cryptopp", "liburing", "boost", "fmt")
    add_defines("BOOST_ASIO_HAS_IO_URING", "BOOST_ASIO_HAS_FILE")
    set_toolset("cxx", "clang")
    set_toolset("ld", "clang++")

-- 添加测试运行规则
after_build(function (target)
    if is_mode("debug") then
        os.exec(target:targetfile())
    end
end)
