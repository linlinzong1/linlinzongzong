cmake_minimum_required(VERSION 3.16)

project(LinLinZongZong)

set(CMAKE_CXX_STANDARD 17)

include_directories(include)

add_executable(

    transaction_test

    tests/transaction_test.cpp

    src/model/Transaction.cpp

    src/database/Database.cpp

    src/repository/TransactionRepository.cpp

    src/service/TransactionService.cpp
)

target_link_libraries(transaction_test sqlite3)
