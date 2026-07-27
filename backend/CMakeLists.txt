cmake_minimum_required(VERSION 3.16)

project(LinLinZongZong)

set(CMAKE_CXX_STANDARD 17)

include_directories(
    include
    third_party
)


#正式后端启动
add_executable(

    linlinzongzong

    src/main.cpp

    src/config/Config.cpp

    src/database/Database.cpp

    src/model/Transaction.cpp

    src/repository/TransactionRepository.cpp

    src/service/TransactionService.cpp

    src/api/TransactionController.cpp

    src/utils/Logger.cpp
)

target_link_libraries(
    linlinzongzong

    sqlite3
)

# 测试：业务程序
add_executable(
    transaction_test

    tests/transaction_test.cpp

    src/model/Transaction.cpp

    src/database/Database.cpp

    src/repository/TransactionRepository.cpp

    src/service/TransactionService.cpp

    src/utils/Logger.cpp
)

target_link_libraries(
    transaction_test

    sqlite3
)

#测试：数据库连接、建表
add_executable(
    database_test

    tests/database_test.cpp

    src/database/Database.cpp

    src/utils/Logger.cpp
)

target_link_libraries(
    database_test

    sqlite3
)

# 测试：SQL CRUD
add_executable(
    repository_test

    tests/repository_test.cpp

    src/model/Transaction.cpp

    src/database/Database.cpp

    src/repository/TransactionRepository.cpp

    src/utils/Logger.cpp
)


target_link_libraries(
    repository_test
    sqlite3
)

# 测试：
add_executable(
    service_test

    tests/service_test.cpp

    src/model/Transaction.cpp

    src/database/Database.cpp

    src/service/TransactionService.cpp

    src/repository/TransactionRepository.cpp

    src/utils/Logger.cpp
)


target_link_libraries(
    service_test
    sqlite3
)

# 测试：api接口
add_executable(
    api_test

    tests/api_test.cpp

    src/model/Transaction.cpp
    src/database/Database.cpp
    src/repository/TransactionRepository.cpp
    src/service/TransactionService.cpp
    src/api/TransactionController.cpp
    src/utils/Logger.cpp
)


target_link_libraries(
    api_test
    sqlite3
)

# 测试：
add_executable(
    config_test

    tests/config_test.cpp

    src/config/Config.cpp
)

target_link_libraries(
    config_test
    sqlite3
)
