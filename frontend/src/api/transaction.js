import axios from "axios";


const request = axios.create({

    baseURL:"http://localhost:8080",

    timeout:5000

});


// 查询所有账单
export function getTransactions(){

    return request.get(
        "/transactions"
    )
    .then(res=>res.data);

}


// 新增账单
export function addTransaction(data){

    return request.post(
        "/transactions",
         {
            type:Number(data.type),
            amount:Number(data.amount),
            categoryId:Number(data.categoryId),
            date:data.date,
            note:data.note
        }
    )
    .then(res=>res.data);

}




// 删除账单
export function deleteTransaction(id){

    return request.delete(
        `/transactions/${id}`
    )
    .then(res=>res.data);

}


// 修改账单
export function updateTransaction(id,data){

    return request.put(
        `/transactions/${id}`,
        {
            type:Number(data.type),
            amount:Number(data.amount),
            categoryId:Number(data.categoryId),
            date:data.date,
            note:data.note
        }
    )
    .then(res=>res.data);

}