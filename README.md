# 林林总总

个人记账系统

## Tech Stack

Backend:
- C++17
- SQLite3
- cpp-httplib
- nlohmann/json
- CMake

## Current Features

- [x] Database initialization
- [x] Transaction model
- [x] Add transaction
- [x] Query transactions
- [x] Update transaction
- [x] Delete transaction

## API

GET:
GET /transactions

POST:
POST /transactions

PUT:
PUT /transactions/{id}

DELETE:
DELETE /transactions/{id}


## Build

mkdir build
cd build

cmake ..
make

./linlinzongzong
