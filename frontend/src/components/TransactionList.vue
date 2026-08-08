//最近记录

<script setup>
import {computed, ref, onMounted} from "vue";
import { getTransactions, deleteTransaction, updateTransaction } from "../api/transaction";
import TransactionGroup from "./TransactionGroup.vue";
import TransactionEdit from './TransactionEdit.vue';

const transactions = ref([]);
const editingItem = ref(null);

async function loadTransactions() {
  transactions.value = await getTransactions();
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

// 处理编辑请求
function handleEdit(item) {
    console.log('📝 TransactionList.handleEdit 收到', item);
  editingItem.value = item; // 将记录存入编辑状态
}

// 保存编辑
async function handleSave(updatedData) {
  await updateTransaction(editingItem.value.id, updatedData);
  editingItem.value = null; // 关闭编辑
  await loadTransactions(); // 刷新列表
}

// 取消编辑
function handleCancel() {
  editingItem.value = null;
}

// 删除
async function handleDelete(id) {
  if (confirm('确定删除该账单吗？')) {
    await deleteTransaction(id);
    await loadTransactions();
  }
}


defineExpose({
  refresh: loadTransactions
});

onMounted(() => {
  loadTransactions();
});

</script>


<template>

<div class="recent">
    <h2>最近记录</h2>

    <!-- 遍历分组，并将事件继续向下传递 -->
    <TransactionGroup
      v-for="group in groupedTransactions"
      :key="group.date"
      :group="group"
      @edit="handleEdit"
      @delete="handleDelete"
    />

    <!-- 编辑弹窗/内联区域 -->
    <TransactionEdit
      v-if="editingItem"
      :item="editingItem"
      @save="handleSave"
      @cancel="handleCancel"
    />

</div>


</template>