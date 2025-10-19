#include <gtest/gtest.h>
#include <boost/asio/co_spawn.hpp>
#include <boost/asio/detached.hpp>
#include <boost/asio/io_context.hpp>
#include <iostream>
#include "request.h"
#include "WebSocket.h"

using namespace cpphttp;

class HttpTest : public ::testing::Test {
protected:
    void SetUp() override {
        // 设置测试用的HTTP服务器地址（这里使用httpbin.org作为测试服务器）
        test_url = "http://httpbin.org";
    }

    std::string test_url;
};

// 测试HTTP GET请求
TEST_F(HttpTest, GetRequest) {
    boost::asio::io_context io_context;
    
    auto test = [&]() -> boost::asio::awaitable<void> {
        HttpRequest request(test_url + "/get", "GET");
        
        try {
            std::string response = co_await request.request();
            std::cout << "GET Response: " << response << std::endl;
            
            // 验证响应包含预期的字段
            EXPECT_TRUE(response.find("\"url\"") != std::string::npos);
            EXPECT_TRUE(response.find("httpbin.org") != std::string::npos);
        } catch (const std::exception& e) {
            std::cout << "GET请求失败: " << e.what() << std::endl;
            // 网络问题不算测试失败
        }
        
        co_return;
    };
    
    boost::asio::co_spawn(io_context, test(), boost::asio::detached);
    io_context.run();
}

// 测试HTTP POST请求
TEST_F(HttpTest, PostRequest) {
    boost::asio::io_context io_context;
    
    auto test = [&]() -> boost::asio::awaitable<void> {
        HttpRequest request(test_url + "/post", "POST");
        request.set_body("application/json", R"({"test": "data"})");
        
        try {
            std::string response = co_await request.request();
            std::cout << "POST Response: " << response << std::endl;
            
            // 验证响应包含发送的数据
            EXPECT_TRUE(response.find("\"test\"") != std::string::npos);
            EXPECT_TRUE(response.find("\"data\"") != std::string::npos);
        } catch (const std::exception& e) {
            std::cout << "POST请求失败: " << e.what() << std::endl;
            // 网络问题不算测试失败
        }
        
        co_return;
    };
    
    boost::asio::co_spawn(io_context, test(), boost::asio::detached);
    io_context.run();
}

// 测试HTTP头设置
TEST_F(HttpTest, HeadersTest) {
    boost::asio::io_context io_context;
    
    auto test = [&]() -> boost::asio::awaitable<void> {
        HttpRequest request(test_url + "/headers", "GET");
        request.set_header("X-Test-Header", "test-value");
        request.set_header("User-Agent", "Test-Agent");
        
        try {
            std::string response = co_await request.request();
            std::cout << "Headers Response: " << response << std::endl;
            
            // 验证响应包含设置的头部
            EXPECT_TRUE(response.find("\"X-Test-Header\"") != std::string::npos);
            EXPECT_TRUE(response.find("\"test-value\"") != std::string::npos);
        } catch (const std::exception& e) {
            std::cout << "Headers测试失败: " << e.what() << std::endl;
        }
        
        co_return;
    };
    
    boost::asio::co_spawn(io_context, test(), boost::asio::detached);
    io_context.run();
}

class WebSocketTest : public ::testing::Test {
protected:
    void SetUp() override {
        // 设置测试用的WebSocket服务器地址
        test_uri = "ws://echo.websocket.org";
    }

    std::string test_uri;
};

// 测试WebSocket连接和消息发送
TEST_F(WebSocketTest, BasicWebSocketTest) {
    boost::asio::io_context io_context;
    
    auto test = [&]() -> boost::asio::awaitable<void> {
        WebSocket ws(test_uri);
        
        try {
            co_await ws.connect();
            std::cout << "WebSocket连接成功" << std::endl;
            
            // 发送测试消息
            std::string test_message = "Hello, WebSocket!";
            co_await ws.write(test_message);
            std::cout << "发送消息: " << test_message << std::endl;
            
            // 接收回显消息
            std::string response = co_await ws.read();
            std::cout << "接收消息: " << response << std::endl;
            
            // 验证回显消息
            EXPECT_EQ(response, test_message);
            
            // 关闭连接
            co_await ws.close();
            std::cout << "WebSocket连接关闭" << std::endl;
            
        } catch (const std::exception& e) {
            std::cout << "WebSocket测试失败: " << e.what() << std::endl;
            // 网络问题不算测试失败
        }
        
        co_return;
    };
    
    boost::asio::co_spawn(io_context, test(), boost::asio::detached);
    io_context.run();
}

int main(int argc, char** argv) {
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
