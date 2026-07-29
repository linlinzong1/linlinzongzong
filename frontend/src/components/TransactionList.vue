<script setup>

import {
    ref,
    onMounted
} from "vue";


import {
    getTransactions,
    deleteTransaction,
    updateTransaction
} from "../api/transaction";



const transactions = ref([]);

const editing = ref(null);


const editForm = ref({

    type:1,

    amount:"",

    categoryId:1,

    date:"",

    note:""

});


async function load()
{

    transactions.value =
        await getTransactions();

}



async function handleDelete(id)
{

    if(!confirm("确定删除该账单吗？"))
    {
        return;
    }


    await deleteTransaction(id);


    await load();

}

function startEdit(item)
{

    editing.value=item;


    editForm.value={

        type:item.type,

        amount:item.amount,

        categoryId:item.categoryId,

        date:item.date,

        note:item.note

    };

}



async function saveEdit()
{

    await updateTransaction(
        editing.value.id,
        editForm.value
    );


    editing.value=null;

    editForm.value={
        type:1,
        amount:"",
        categoryId:1,
        date:"",
        note:""
    };

    await load();

}





onMounted(()=>{

    load();

});


defineExpose({

    load

});


</script>



<template>


<div>


<h2>
账单列表
</h2>



<table border="1">


<tr>

<th>ID</th>

<th>日期</th>

<th>金额</th>

<th>备注</th>

<th>类型</th>

<th>操作</th>

</tr>



<tr
v-for="item in transactions"
:key="item.id"
>


<td>
{{item.id}}
</td>


<td>
{{item.date}}
</td>


<td>
{{item.amount}}
</td>


<td>
{{item.note}}
</td>


<td>

{{item.type===1?"支出":"收入"}}

</td>

<td>

<button
@click="startEdit(item)"
>
修改
</button>


<button
@click="handleDelete(item.id)"
>
删除
</button>

</td>

</tr>



</table>

<div v-if="editing">

<h3>
修改账单
</h3>


<input
v-model="editForm.amount"
placeholder="金额"
/>


<input
v-model="editForm.date"
placeholder="日期"
/>

<input
v-model="editForm.categoryId"
placeholder="分类"
/>


<input
v-model="editForm.note"
placeholder="备注"
/>



<select v-model="editForm.type">

<option :value="1">
支出
</option>

<option :value="2">
收入
</option>

</select>


<button
@click="saveEdit"
>
保存修改
</button>


</div>


</div>


</template>