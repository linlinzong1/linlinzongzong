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

    src/model/Transaction.cpp

    src/database/Database.cpp

    src/repository/TransactionRepository.cpp

    src/service/TransactionService.cpp

    src/api/TransactionController.cpp

    src/utils/Logger.cpp
)

target_link_libraries(
    linlinzongzong

    sqlite3
)

# 测试业务程序
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

#测试数据库程序
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
