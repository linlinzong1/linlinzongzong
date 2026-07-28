import {useEffect,useState} from "react";

import {
    getTransactions,
    addTransaction
} from "./api/transaction";


function App()
{

    const [transactions,setTransactions]
        = useState([]);



    const [form,setForm]
        = useState({
            type:1,
            amount:"",
            categoryId:1,
            date:"",
            note:""
        });



    //加载数据
    async function loadTransactions()
    {
        const data =
            await getTransactions();

        setTransactions(data);
    }



    useEffect(()=>{

        loadTransactions();

    },[]);



    //提交新增
    async function handleSubmit()
    {

        await addTransaction(form);


        await loadTransactions();


        setForm({
            type:1,
            amount:"",
            categoryId:1,
            date:"",
            note:""
        });

    }



    return (

        <div>

            <h1>
                林林总总记账系统
            </h1>


            <h2>
                添加账单
            </h2>


            <input
                placeholder="金额"
                value={form.amount}
                onChange={
                    e=>setForm({
                        ...form,
                        amount:e.target.value
                    })
                }
            />


            <input
                placeholder="日期"
                value={form.date}
                onChange={
                    e=>setForm({
                        ...form,
                        date:e.target.value
                    })
                }
            />


            <input
                placeholder="备注"
                value={form.note}
                onChange={
                    e=>setForm({
                        ...form,
                        note:e.target.value
                    })
                }
            />


            <button
                onClick={handleSubmit}
            >
                添加
            </button>



            <h2>
                账单列表
            </h2>


            {

            transactions.map(t=>(

                <div key={t.id}>

                    {t.date}
                    {" | "}

                    {t.amount}
                    {" | "}

                    {t.note}

                </div>

            ))

            }


        </div>

    )

}


export default App;