<script setup>

import{ ref, onMounted, watch } from "vue";
import{ useRoute, useRouter } from "vue-router";
import{ addTransaction } from "../api/transaction";
import{ getCategories } from "../api/category";


const route=useRoute();
const router=useRouter();
const type=ref( route.query.type==="income" ? 2 : 1 );
const amount = ref('');
const note = ref('');
const today = new Date().toISOString().substring(0, 10);
const date = ref(today);
const categoryId = ref(null);
const categories = ref([]);

function changeType(value)
{

    type.value=value;
    router.replace({
        path:"/record",
        query:{
            type:
            value===1
            ?"expense"
            :"income"
        }
    });
}

function selectCategory(c)
{
    categoryId.value = c.id;
}

async function loadCategories()
{
    try{
        categories.value = await getCategories(type.value);

        if(categories.value.length > 0)
        {
            categoryId.value=categories.value[0].id;
        } else {
            categoryId.value = null;
        }
    } catch (error) {
        console.error('加载分类失败', error);
        categories.value = [];
        categoryId.value = null;
    } 
}

watch(type, () => {
    loadCategories();
});

onMounted(()=>{
    loadCategories();
});

async function submit(){
    if (categoryId.value === null) {
        alert('请选择分类');
        return;
    }
    if (!amount.value || Number(amount.value) <= 0) {
        alert('请输入有效金额');
        return;
    }
    await addTransaction({
        type: type.value,
        amount: Number(amount.value),
        categoryId: categoryId.value,
        date: date.value,
        note: note.value
    });
    alert('记录成功');
    router.push('/');
}
</script>


<template>
<div>

    <h1>记账</h1>

    <div>
        <button @click="changeType(1)">支出</button>
        <button @click="changeType(2)">收入</button>
    </div>

    <h3>类型</h3>


    <button 
        v-for="c in categories"
        :key="c.id"
        @click="selectCategory(c)"
        :class="{ active: categoryId === c.id}"
    >
        {{c.name}}
    </button>

    <h3>金额</h3>
    <input type="number" v-model="amount"/>

    <h3>日期</h3>
    <input type="date" v-model="date"/>

    <h3>备注</h3>
    <input v-model="note"/>

    <br>

    <button @click="submit">完成</button>

</div>
</template>

<style scoped>
.active{
    background-color: #42b983;
    color: white;
}
</style>