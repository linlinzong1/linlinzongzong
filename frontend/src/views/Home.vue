
<script setup>

import { useRouter } from "vue-router";
import { ref, onMounted, computed} from "vue";
import{ getTransactions } from "../api/transaction";

const router=useRouter();
const today=new Date().toISOString().substring(0, 10);
const transactions=ref([]);

async function loadTransactions(){
    transactions.value=
        await getTransactions();
}

const groupedTransactions = computed(() => {
    const sorted = [...transactions.value].sort((a, b) =>
        b.date.localeCompare(a.date)
    );

    const top10 = sorted.slice(0, 10);

    const groups = {};
    top10.forEach(item =>{
        if(!groups[item.date]){
            groups[item.date] = [];
        }
        groups[item.date].push(item);
    });

    return Object.keys(groups)
        .sort((a, b) => b.localeCompare(a))
        .map(date => {
            const items = groups[date];
            items.sort((a, b) => b.id - a.id);
            let totalExpense = 0;
            let totalIncome = 0;
            items.forEach(item =>{
                if(item.type === 1){
                    totalExpense += item.amount;
                }else if(item.type === 2){
                    totalIncome += item.amount;
                }
            });
            return { date, items, totalExpense, totalIncome };
        });
});

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
        <h1>林林总总</h1>
        <h3>{{today}}</h3>

        <div class="actions">
            <button @click="addExpense">支出 +</button>
            <button @click="addIncome">收入 +</button>
        </div>

        <div class="recent">
            <h2>最近记录</h2>
            <div 
                v-for="group in groupedTransactions"
                :key="group.date"
                class="date-group"
            >
                <div class="date-header">
                    <span>{{group.date}}</span>
                    <span class="total">
                        <span v-if="group.totalExpense > 0" class="totalExpense">
                            支出：{{group.totalExpense.toFixed(2)}}
                        </span>
                        <span v-if="group.totalIncome > 0" class="total-income">
                            收入：{{group.totalIncome.toFixed(1)}}
                        </span>
                    </span>
                </div>

                <div
                    v-for="item in group.items"
                    :key="item.id"
                    class="record"
                >
                    <div class="record-row">
                        <span class="category-name">{{item.categoryName}}</span>
                        <div class="right-side">
                            <span :class="item.type === 1 ? 'expense' : 'income'">
                                {{item.type === 1 ? '支出' : '收入'}}
                                :{{item.amount.toFixed(2)}}
                            </span>
                            <span class="note">{{item.note}}</span>
                        </div>
                    </div>
                </div>
            </div>
        </div>
    </div>
</template>

<style scoped>

.date-header {
    display: flex;
    justify-content: space-between;
    align-items: center;
    width: 100%;
    font-weight: bold;
    font-size: 16px;
    padding: 12px 0 6px 0;
    color: #333;
    border-bottom: 2px solid #eee;
    margin-bottom: 6px;
}

.totals {
    display: flex;
    gap: 20px;
    font-weight: normal;
    font-size: 14px;
}

.total-expense {
    color: red;
}
.total-income {
    color: green;
}

.record {
    padding: 15px;
    border-bottom: 1px solid #ddd;
}

.record-row{
    display: flex;
    justify-content: space-between;
    align-items: flex-start;
}

.category-name{
    font-size: 20px;
    font-weight: bold;
    color: #333;
}

.right-side{
    display: flex;
    flex-direction: column;
    align-items: flex-end;
    gap: 4px;
}

.expense {
    color: red;
}
.income {
    color: green;
}

.note{
    color: #888;
    font-size: 14px;
}
</style>