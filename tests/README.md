# HTTP客户端库测试套件

这个目录包含了cpphttp HTTP客户端库的完整测试套件。

## 测试文件说明

### test_main.cpp
- **功能**: 集成测试，测试实际的HTTP请求和WebSocket连接
- **测试内容**:
  - HTTP GET请求测试（使用httpbin.org）
  - HTTP POST请求测试
  - HTTP头部设置测试
  - WebSocket连接和消息传输测试

### test_unit.cpp
- **功能**: 单元测试，测试库的核心功能
- **测试内容**:
  - 连接类构造和基本功能
  - 无效URL处理
  - HTTP方法验证
  - 头部设置功能
  - URL设置功能
  - WebSocket URI解析

### test_mock.cpp
- **功能**: Mock测试，不依赖网络连接测试核心逻辑
- **测试内容**:
  - 请求构建逻辑
  - URL解析功能
  - 方法验证逻辑
  - 头部操作
  - 请求体设置
  - WebSocket URI解析逻辑
  - 连接类接口
  - 协程功能

## 构建和运行测试

### 前提条件
- 已安装xmake构建工具
- 已安装clang编译器（支持C++23）
- 网络连接（用于集成测试）

### 构建测试

```bash
# 进入项目根目录
cd /data/workspace/cpphttp

# 配置为debug模式（包含测试目标）
xmake config -m debug

# 构建测试程序
xmake build cpphttp_tests
```

### 运行测试

```bash
# 运行所有测试
xmake run cpphttp_tests

# 或者直接运行测试程序
./build/linux/x86_64/debug/cpphttp_tests
```

### 运行特定测试

```bash
# 运行HTTP相关测试
./build/linux/x86_64/debug/cpphttp_tests --gtest_filter="Http*"

# 运行WebSocket相关测试
./build/linux/x86_64/debug/cpphttp_tests --gtest_filter="WebSocket*"

# 运行单元测试
./build/linux/x86_64/debug/cpphttp_tests --gtest_filter="*Unit*"

# 运行Mock测试
./build/linux/x86_64/debug/cpphttp_tests --gtest_filter="*Mock*"
```

## 测试覆盖范围

### HTTP功能测试
- ✅ GET请求
- ✅ POST请求
- ✅ 头部设置
- ✅ URL解析
- ✅ 方法验证
- ✅ 请求体设置
- ✅ 错误处理

### WebSocket功能测试
- ✅ 连接建立
- ✅ 消息发送和接收
- ✅ URI解析
- ✅ 连接关闭

### 核心逻辑测试
- ✅ 连接类接口
- ✅ 协程功能
- ✅ 参数验证
- ✅ 异常处理

## 注意事项

1. **网络依赖**: 集成测试需要网络连接，测试失败可能是网络问题而非代码问题
2. **外部服务**: 测试使用httpbin.org和websocket.org作为测试服务器
3. **调试模式**: 测试只在debug模式下构建，release模式不包含测试目标
4. **测试隔离**: Mock测试不依赖网络，适合离线环境运行

## 添加新测试

要添加新的测试用例，请遵循以下模式：

```cpp
TEST(TestSuiteName, TestCaseName) {
    // 测试逻辑
    EXPECT_EQ(expected, actual);
}
```

将新测试添加到相应的测试文件中，或创建新的测试文件。

## 故障排除

如果测试失败，请检查：
- 网络连接是否正常
- 外部测试服务是否可用
- 依赖库是否正确安装
- 编译器是否支持C++23特性
