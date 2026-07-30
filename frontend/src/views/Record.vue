<script setup>

import{
    ref
} from "vue";

import{
    useRoute,
    useRouter
} from "vue-router";

import{
    addTransaction
} from "../api/transaction";

import{
    getCategories
} from "../api/category";

import{
    onMounted,
    watch
} from "vue";

const route=useRoute();

const router=useRouter();

const type=ref(
    route.query.type==="income"
    ?2
    :1
);


const amount=ref("");

const note=ref("");

const today =
    new Date()
    .toISOString()
    .substring(0,10);


const date=ref(today);

const categoryId=ref(null);

const selectedCategory=ref(null);

const categories=ref([]);

async function loadCategories()
{
    categories.value = 
        await getCategories(
            type.value
        );

    if(categories.value.lenth>0)
    {
        categoryId.value=
            categories.value[0].id;
        
        selectedCategory.value=
            categories.value[0].id;
    }
}

onMounted(()=>{
    loadCategories();
});


watch(
    type,
    ()=>{

        loadCategories();

    }
);

async function submit(){


await addTransaction({

type:type.value,

amount:Number(amount.value),

categoryId:categoryId.value,

date:date.value,

note:note.value

});


alert("记录成功");


router.push("/");


}


</script>



<template>


<div>


<h1>

记账

</h1>



<div>


<button
@click="type=1;
loadCategories();
"
>

支出

</button>



<button
@click="type=2;
loadCategories();
"
>

收入

</button>


</div>




<h3>

类型

</h3>


<button
v-for="c in categories"
:key="c.id"

@click="categoryId=c.id;
selectedCategory=c.id;
"
:class="
selectedCategory===c.id
?'active'
:''
"
>

{{c.name}}

</button>



<h3>

金额

</h3>


<input

type="number"

v-model="amount"

/>

<h3>
日期
</h3>

<input
type="date"
v-model="date"
/>



<h3>

备注

</h3>


<input

v-model="note"

/>



<br>


<button
@click="submit"
>

完成

</button>


</div>


</template>