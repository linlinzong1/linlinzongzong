import { useEffect, useState} from "react";
import { getTransactions } from "../api/transaction";

function TransactionList()
{
    const [transactions, setTransactions] = useState([]);

    useEffect(()=>{
        getTransactions().then(
            res=>{
                setTransactions(
                    res.data
                );
            }
        ).catch(
            err=>{
                console.log(err);
            });
    },[]);
    return(
        <div>
            <h2>
                账单列表
            </h2>

            {
                transactions.map(
                    item=>(
                        <div key = {item.id}>
                            {item.note}
                            :
                            {item.amount}
                        </div>
                    )
                )
            }

        </div>
    );
}

export default TransactionList;