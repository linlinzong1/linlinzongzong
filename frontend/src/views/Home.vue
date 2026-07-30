
<script setup>

import {
    useRouter
} from "vue-router";

import {
    ref,
    onMounted
} from "vue";

import{
    getTransactions
} from "../api/transaction";

const router=useRouter();

const today=new Date()
.toISOString()
.substring(0, 10);

const transactions=ref([]);

async function loadTransactions(){
    transactions.value=
        await getTransactions();
}


function addExpense(){
    router.push(
        {
            path:"/record",
            query:{
                type:"expense"
            }
        }
    );
}

function addIncome()
{
    router.push(
        {
            path:"/record",
            query:{
                type:"income"
            }
        }
    );
}

onMounted(()=>{
    loadTransactions();
});


</script>





<template>


<div class="home">


<h1>
林林总总
</h1>


<h3>
{{today}}
</h3>



<div class="actions">

<button
@click="addExpense"
>

支出 +

</button>


<button
@click="addIncome"
>

收入 +

</button>





</div>



<h2>
最近记录
</h2>


<table border="1">


<tr>

<th>
日期
</th>

<th>
金额
</th>

<th>
类型
</th>

<th>
备注
</th>

</tr>



<tr
v-for="item in transactions.slice(0,5)"
:key="item.id"
>


<td>
{{item.date}}
</td>


<td>
{{item.amount}}
</td>

<td>
{{item.type===1?"支出":"收入"}}
</td>

<td>
{{item.note}}
</td>


</tr>


</table>


</div>


</template>



<style scoped>


.home{

padding:20px;

}



.actions button{

width:120px;

height:50px;

margin:20px;

font-size:18px;

}

.active{

background-color:#409eff;
color:white;

}


</style>