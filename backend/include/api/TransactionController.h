#ifndef TRANSACTION_CONTROLLER_H
#define TRANSACTION_CONTROLLER_H

#include "service/TransactionService.h"

#include "httplib.h"

class TransactionController
{
public:
    TransactionController(TransactionService& service);
    void registerRoutes(httplib::Server& server);

private:
    TransactionService& service_; //引用成员变量，Controller不拥有Service，只是使用它
};

#endif // TRANSACTION_CONTROLLER_H