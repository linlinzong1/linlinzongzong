# 林林总总 软件架构设计

版本：V1.0

日期：2026-07-17


# 1. 系统概述


## 1.1 系统目标

林林总总是一款个人记账软件。

系统采用前后端分离架构：

- Flutter客户端负责用户交互
- C++后端负责业务逻辑
- SQLite负责数据存储



# 2. 整体架构


系统结构：



+----------------+

| Flutter Client |

+----------------+

    |

    | HTTP / JSON

    |

    ↓

+----------------+

| C++ Backend |

+----------------+

    |

    |

    ↓

+----------------+

| SQLite |

+----------------+



说明：


客户端：

负责：

- 页面显示
- 用户输入
- 数据展示


后端：

负责：

- 请求处理
- 业务逻辑
- 数据访问


数据库：

负责：

- 数据持久化



# 3. 后端架构设计


C++后端采用分层架构。


结构：



Backend

│

├── API Layer

│

├── Service Layer

│

├── Repository Layer

│

├── Database Layer

│

└── Model Layer




# 4. 各层职责



## 4.1 API Layer


作用：

处理HTTP请求。


负责：

- 接收请求
- 参数解析
- 返回JSON


例如：



POST /api/transactions



对应：


TransactionController




不负责：

- 数据库操作
- 业务判断



---


## 4.2 Service Layer


作用：

业务逻辑处理。


例如：


添加账单：



检查金额是否合法

↓

检查分类是否存在

↓

保存数据



对应：



TransactionService




---


## 4.3 Repository Layer


作用：

数据库访问。


负责：



INSERT

SELECT

UPDATE

DELETE



例如：



TransactionRepository



不负责：

- HTTP
- 用户界面



---


## 4.4 Database Layer


作用：

封装SQLite。


负责：

- 数据库连接
- SQL执行
- 事务管理



例如：



DatabaseManager




---


## 4.5 Model Layer


作用：

表示业务对象。


例如：


Transaction:


```cpp
class Transaction
{

int id;

int type;

double amount;

string note;

};

# 5. C++项目目录设计

后端：

backend/


├── CMakeLists.txt


├── include/


│
├── model/


│
├── database/


│
├── repository/


│
├── service/


│
├── api/


└── src/



说明：

model

数据结构。

例如：

Transaction.h
Category.h

database

数据库封装。

例如：

Database.h

Database.cpp

repository

数据操作。

例如：

TransactionRepository.cpp

service

业务逻辑。

例如：

TransactionService.cpp

api

HTTP接口。

例如：

TransactionController.cpp

# 6. 数据流

用户添加账单：


Flutter

  |

  | POST /api/transactions

  ↓


Controller

  |

  ↓


Service

  |

  ↓


Repository

  |

  ↓


SQLite


# 7. 技术选型
后端语言

C++17

构建工具

CMake

数据库

SQLite

HTTP

cpp-httplib

JSON

nlohmann/json

编译器

g++

# 8. 错误处理

统一异常处理。

流程：


Database Error

        ↓

Repository

        ↓

Service

        ↓

API Response



返回：

{
    "code":3,
    "message":"database error"
}

# 9. 日志系统

后端提供日志功能。

记录：

启动信息
HTTP请求
数据库错误
异常信息

日志文件：

logs/app.log

# 10. 后续扩展

未来支持：

用户系统

增加：

User Module

云同步

增加：

Sync Service

数据分析

增加：

Statistics Module


