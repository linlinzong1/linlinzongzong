<script setup>

import { ref, computed, onMounted, watch } from 'vue';
import { getStatistics } from '../api/statistics';

//默认以周为范围
const granularity = ref('week');
const baseDate = ref(new Date().toISOString().substring(0, 10)); // 今天

// 计算当前显示范围的标签
const periodLabel = computed(() => {
  const d = new Date(baseDate.value);
  const year = d.getFullYear();
  const month = d.getMonth() + 1;
  const day = d.getDate();
  if (granularity.value === 'year') {
    return `${year}年`;
  } else if (granularity.value === 'month') {
    return `${year}年${month}月`;
  } else { // week
    // 计算本周的周一日期和周日日期
    const monday = getMonday(d);
    const sunday = new Date(monday);
    sunday.setDate(sunday.getDate() + 6);
    const format = (d) => `${d.getMonth()+1}/${d.getDate()}`;
    return `${format(monday)} - ${format(sunday)}`;
  }
});

// 获取指定日期所在周周一的日期
function getMonday(date) {
  const d = new Date(date);
  const day = d.getDay();
  const diff = d.getDate() - day + (day === 0 ? -6 : 1);
  d.setDate(diff);
  return d;
}

// 切换粒度时重置基准日期（可选：保持当前日期不变）
function switchGranularity(g) {
  granularity.value = g;
  fetchStats();
}

// 上一期
function prevPeriod() {
  const d = new Date(baseDate.value);
  if (granularity.value === 'year') d.setFullYear(d.getFullYear() - 1);
  else if (granularity.value === 'month') d.setMonth(d.getMonth() - 1);
  else d.setDate(d.getDate() - 7); // 周
  baseDate.value = d.toISOString().substring(0, 10);
  fetchStats();
}

// 下一期
function nextPeriod() {
    const d = new Date(baseDate.value);

    if (granularity.value === 'year') d.setFullYear(d.getFullYear() + 1);

    else if (granularity.value === 'month') d.setMonth(d.getMonth() + 1);

    else d.setDate(d.getDate() + 7);

    const today = new Date();

    if(d > today)
    {
        return;
    }

    baseDate.value = d.toISOString().substring(0, 10);

    fetchStats();
}

const stats = ref({

    income:0,
    expense:0,
    balance:0,
    expenseCategories:[],
    incomeCategories:[]

});
const loading = ref(false);

// 计算支出分类（带百分比）
const expenseItems = computed(()=>{
    const items =
        stats.value.expenseCategories || [];

    const total =
        items.reduce(
            (sum,item)=>
                sum + item.amount,
            0
        );


    return items.map(item=>({
        categoryName:item.name,
        total:item.amount,
        percent:
            total ?
            item.amount / total * 100
            :
            0
    }));

});

// 计算收入分类（带百分比）
const incomeItems = computed(()=>{
    const items =
        stats.value.incomeCategories || [];

    const total =
        items.reduce(
            (sum,item)=>
                sum + item.amount,
            0
        );



    return items.map(item=>({
        categoryName:item.name,
        total:item.amount,
        percent:
            total ?
            item.amount / total * 100
            :
            0
    }));

});

//>按钮限制
const canNext = computed(()=>{

    const d = new Date(baseDate.value);


    if(granularity.value==="year")
    {
        d.setFullYear(
            d.getFullYear()+1
        );
    }


    if(granularity.value==="month")
    {
        d.setMonth(
            d.getMonth()+1
        );
    }


    if(granularity.value==="week")
    {
        d.setDate(
            d.getDate()+7
        );
    }


    return d <= new Date();

});

// 修改 fetchStats 加入 loading
async function fetchStats() {
    console.log(
        '🔥 fetchStats called'
    );

    loading.value=true;

    try {
        const data =
          await getStatistics(
            granularity.value,
            baseDate.value
          );

        console.log(
            "statistics:",
            data
        );


        stats.value={

            income: data.income,
            expense: data.expense,
            balance: data.balance,
            expenseCategories: data.expenseCategories || [],
            incomeCategories: data.incomeCategories || []

        };

    }
    catch(error){

        console.error(
            "加载统计失败",
            error
        );

    }
    finally{

        loading.value=false;

    }

}



// 监听粒度或基准日期变化（也可手动调用fetchStats）
watch([granularity, baseDate], fetchStats);

onMounted(fetchStats);

</script>


<template>
    <div class="statistics">
        <div class="granularity-tabs">
            <button :class="{
                active: granularity === 'week'}" 
                @click="switchGranularity('week')">
                周</button>
            <button :class="{
                active: granularity === 'month'}" 
                @click="switchGranularity('month')">
                月</button>
            <button :class="{
                active: granularity === 'year'}" 
                @click="switchGranularity('year')">
                年</button>
        </div>

        <div class="date-picker">
            <button @click="prevPeriod"><</button>
            <span>{{periodLabel}}</span>
            <button @click="nextPeriod":disabled="!canNext">></button>
        </div>

        <!-- 汇总卡片 -->
        <div class="summary" v-if="!loading">

            <div class="card income">
                总收入 ¥{{ stats.income.toFixed(2) }}
            </div>

            <div class="card expense">
                总支出 ¥{{ stats.expense.toFixed(2) }}
            </div>

            <div class="card balance">
                结余 ¥{{ stats.balance.toFixed(2) }}
            </div>

        </div>

        <!-- 支出分类 -->
        <h3>支出分类</h3>

        <div v-for="item in expenseItems" :key="item.categoryName" class="detail-item">

            <span>{{ item.categoryName }}</span>

            <span class="amount">¥{{ item.total.toFixed(2) }}</span>

            <div class="bar" :style="{ width: item.percent + '%' }"></div>

        </div>

        <h3>收入分类</h3>

        <div v-for="item in incomeItems" :key="item.categoryName" class="detail-item">

            <span>{{ item.categoryName }}</span>

            <span class="amount">¥{{ item.total.toFixed(2) }}</span>

            <div class="bar" :style="{ width: item.percent + '%' }"></div>

        </div>

        <div v-if="!loading && expenseItems.length === 0 
          && incomeItems.length === 0" class="empty">暂无数据</div>

    </div>

</template>

<style scoped>

.summary {
  display: flex;
  flex-wrap: wrap;
  gap: 12px;
  margin: 12px 0;
}
.card {
  flex: 1 1 100px;
  background: white;
  padding: 16px;
  border-radius: 12px;
  box-shadow: 0 2px 8px rgba(0,0,0,0.05);
  text-align: center;
  font-weight: bold;
}
.card.income { color: #2ecc71; }
.card.expense { color: #e74c3c; }
.card.balance { color: #3498db; }

.detail-list h3 {
  margin: 16px 0 8px;
  font-size: 16px;
  color: #666;
}
.detail-item {
  display: flex;
  align-items: center;
  background: white;
  padding: 10px 16px;
  border-radius: 8px;
  margin-bottom: 6px;
  position: relative;
  overflow: hidden;
}
.detail-item span:first-child {
  flex: 1;
  font-weight: 500;
}
.detail-item .amount {
  font-weight: bold;
  margin-left: 12px;
  z-index: 1;
}
.bar {
  position: absolute;
  left: 0;
  top: 0;
  height: 100%;
  background: rgba(52, 152, 219, 0.15);
  border-radius: 8px;
  transition: width 0.3s;
}
.loading, .empty {
  text-align: center;
  padding: 40px 0;
  color: #999;
}

</style>