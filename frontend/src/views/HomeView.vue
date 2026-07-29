<script setup>

import { ref } from "vue";

import TransactionForm from "../components/TransactionForm.vue";

import TransactionList from "../components/TransactionList.vue";


const editingTransaction = ref(null);


// 接收列表传来的数据
function editTransaction(transaction)
{
    editingTransaction.value = transaction;
}


// 修改完成后清空
function finishEdit()
{
    editingTransaction.value = null;
}

</script>


<template>


<h1>
林林总总记账系统
</h1>


<TransactionForm
    :transaction="editingTransaction"
    @finished="finishEdit"
/>


<TransactionList
    @edit="editTransaction"
/>


</template>