<script setup>

import { ref } from "vue";

import {
    addTransaction
} from "../api/transaction";

const form = ref({
    type:1,
    amount:"",
    categoryId:1,
    date:"",
    note:""
});

//通知父组件刷新
const emit = defineEmits([
    "success"
]);

async function submit(){
    if(!form.value.amount)
    {
        alert("请输入金额");
        return;
    }

    if(Number(form.value.amount) <= 0)
    {
        alert("金额必须大于0");
        return
    }

    await addTransaction({
        type:Number(form.value.type),

        amount:Number(form.value.amount),

        categoryId:Number(form.value.categoryId),

        date:form.value.date,

        note:form.value.note
    });

    alert("添加成功");

    form.value = {
        type:1,

        amount:"",

        categoryId:1,

        date:"",

        note:""
    };

    emit("success");
}

</script>

<style scoped>

div{
    margin-bottom:10px;
}

input,
select{
    width:200px;
    height:30px;
    font-size:16px;
}

button{
    padding:5px 15px;
    margin-right:10px;
}

</style>

<template>

<div>

<h2>
添加账单
</h2>

<div>

金额：

<input
v-model = "form.amount"
/>

</div>


<div>

日期：

<input
type = "date"
v-model = "form.date"
/>

</div>

<div>

类型：

<select v-model = "form.type">

<option :value = "1">
支出
</option>

<option :value = "2">
收入
</option>

</select>

</div>


<div>

备注：

<input
v-model = "form.note"
/>

</div>

<button
@click = "submit"
>

添加

</button>



</div>

</template>