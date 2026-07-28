import axios from "axios";


const API =
"http://localhost:8080";


export function getTransactions()
{
    return axios.get(
        `${API}/transactions`
    )
    .then(res=>res.data);
}



export function addTransaction(data)
{

    return axios.post(
        `${API}/transactions`,
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