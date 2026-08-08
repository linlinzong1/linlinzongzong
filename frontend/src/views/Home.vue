
<script setup>

import { useRouter } from "vue-router";
import { ref } from "vue";
import TransactionList from "../components/TransactionList.vue";

const router=useRouter();
const today=new Date().toISOString().substring(0, 10);
const transactionListRef=ref(null);

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

</script>


<template>
    <div class="home">
        <h1>林林总总</h1>
        <h3>{{today}}</h3>

        <div class="actions">
            <button @click="addExpense">支出 +</button>
            <button @click="addIncome">收入 +</button>
        </div>

        <TransactionList ref="transactionListRef"/>
    </div>
</template>
