# 林林总总 数据库设计

版本：V1.0

日期：2026-07-17


# 1. 数据库概述


## 1.1 数据库类型

V1.0 使用 SQLite 作为数据库。


原因：

- 轻量
- 不需要独立服务器
- 适合个人记账软件
- 支持 Linux 环境


数据库文件：

llzz.db

## 1.2 数据设计目标

保存用户的：

- 收入记录
- 支出记录
- 分类信息

支持：

- 新增记录
- 查询记录
- 删除记录
- 修改记录
- 统计分析



# 2. 数据库结构


V1.0 包含三个数据表：



transaction
category
setting



关系：


category

1
|
|
N

transaction




# 3. transaction 表


## 3.1 功能

保存每一笔收入或支出记录。


## 3.2 表结构


| 字段 | 类型 | 说明 |
|-|-|-|
| id | INTEGER | 主键 |
| type | INTEGER | 类型 |
| amount | REAL | 金额 |
| category_id | INTEGER | 分类ID |
| date | TEXT | 日期 |
| note | TEXT | 备注 |
| created_at | TEXT | 创建时间 |



## 3.3 字段说明


### id

唯一编号。

例如：


1
2
3



### type

记录类型：


1 = 收入

2 = 支出



例如：

工资：


type = 1


午餐：


type = 2



### amount


金额。

例如：


35.50



### category_id

对应分类表。


例如：


餐饮

category_id = 3



### date

发生日期。


格式：


YYYY-MM-DD



例如：


2026-07-17



### note

备注。


例如：


朋友聚餐




# 4. category 表


## 4.1 功能

保存账单分类。


## 4.2 表结构


|字段|类型|说明|
|-|-|-|
|id|INTEGER|主键|
|name|TEXT|分类名称|
|type|INTEGER|分类类型|



## 4.3 示例数据


|id|name|type|
|-|-|-|
|1|工资|1|
|2|奖金|1|
|3|餐饮|2|
|4|交通|2|
|5|购物|2|



# 5. setting 表


## 5.1 功能

保存软件配置。


## 5.2 表结构


|字段|类型|说明|
|-|-|-|
|key|TEXT|配置名称|
|value|TEXT|配置内容|



示例：


|key|value|
|-|-|
|currency|CNY|
|theme|dark|



# 6. SQL 创建语句


## transaction


```sql
CREATE TABLE transaction
(
    id INTEGER PRIMARY KEY AUTOINCREMENT,

    type INTEGER NOT NULL,

    amount REAL NOT NULL,

    category_id INTEGER,

    date TEXT NOT NULL,

    note TEXT,

    created_at TEXT
);
category
CREATE TABLE category
(
    id INTEGER PRIMARY KEY AUTOINCREMENT,

    name TEXT NOT NULL,

    type INTEGER NOT NULL
);
setting
CREATE TABLE setting
(
    key TEXT PRIMARY KEY,

    value TEXT
);
# 7. 数据操作需求
添加账单

输入：

类型
金额
分类
日期
备注

生成：

transaction记录

查询账单

支持：

查询全部
按日期查询
按类型查询
按分类查询
删除账单

根据：

id

删除。

# 8. 后续扩展

未来版本可能增加：

用户表
user

支持：

登录
多用户
账本表
book

支持：

家庭账本
工作账本
标签表
tag

支持：

自定义标签

V1.0暂不实现。

