# 林林总总 API接口设计

版本：V1.0

日期：2026-07-17


# 1. API概述


## 1.1 目的

定义手机客户端与C++后端服务器之间的数据通信方式。


## 1.2 通信方式


协议：

HTTP


数据格式：

JSON


字符编码：

UTF-8


## 1.3 基础地址


开发环境：


http://localhost:8080



生产环境：


http://server-address



# 2. 接口规范


请求格式：


METHOD /api/resource



响应格式：

JSON


成功：

```json
{
    "code":0,
    "message":"success",
    "data":{}
}

失败：

{
    "code":1,
    "message":"error"
}
# 3. 账单接口
## 3.1 获取账单列表
请求

GET

/api/transactions
参数

无

返回

示例：

{
    "code":0,
    "data":[
        {
            "id":1,
            "type":2,
            "amount":35,
            "category":"餐饮",
            "date":"2026-07-17",
            "note":"午饭"
        }
    ]
}
## 3.2 添加账单
请求

POST

/api/transactions
请求数据
{
    "type":2,
    "amount":35,
    "category_id":3,
    "date":"2026-07-17",
    "note":"午饭"
}
参数说明
字段	说明
type	1收入 2支出
amount	金额
category_id	分类ID
date	日期
note	备注
返回
{
    "code":0,
    "message":"created",
    "id":1
}
## 3.3 删除账单
请求

DELETE

/api/transactions/{id}

例如：

DELETE /api/transactions/1

返回：

{
    "code":0,
    "message":"deleted"
}
## 3.4 修改账单
请求

PUT

/api/transactions/{id}

数据：

{
    "amount":50,
    "note":"修改后的备注"
}
# 4. 分类接口
## 4.1 获取分类列表

GET

/api/categories

返回：

{
    "code":0,
    "data":[
        {
            "id":1,
            "name":"工资",
            "type":1
        },
        {
            "id":3,
            "name":"餐饮",
            "type":2
        }
    ]
}
# 5. 统计接口
## 5.1 获取每日统计

GET

/api/statistics/day

返回：

{
    "income":5000,
    "expense":35
}
## 5.2 获取月份统计

GET

/api/statistics/month

参数：

year=2026

month=7

返回：

{
    "income":8000,
    "expense":2500
}
# 6. 错误码
code	说明
0	成功
1	未知错误
2	参数错误
3	数据库错误
4	不存在的数据
# 7. V1.0暂不支持

以下接口未来增加：

用户
/api/user
云同步
/api/sync
多账本
/api/books
