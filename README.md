# 林林总总

个人记账系统

## Tech Stack

Backend:
- C++17
- SQLite3
- cpp-httplib
- nlohmann/json
- CMake

Frontend
- Vue3
- Vite
- Axios

## Features

Transaction Management
- Database initialization
- Transaction model
- Add transaction
- Query transactions
- Update transaction
- Delete transaction

Statistics
- Expense statistics
- Income statistics
- Category statistics
- Weekly statistics
- Monthly statistics
- Yearly statistics

Frontend
- Transaction list
- Transaction creation form
- Transaction editing
- Statistics page
- User center page

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
Backend

cd backend

mkdir build
cd build

cmake ..
make

./linlinzongzong

Backend server:
http://localhost:8080

Frontend
cd frontend

npm install

npm run dev

Frontend:
http://localhost:5173
