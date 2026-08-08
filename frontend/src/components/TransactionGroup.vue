//一天的记录行

<script setup>

import TransactionItem from "./TransactionItem.vue"

defineProps({group:Object});
const emit = defineEmits(['edit', 'delete']);

</script>

<template>

<div class="date-group">
    <div class="date-header">
        <span>{{group.date}}</span>
        <span>
            <span v-if="group.totalExpense">
                支出：
                {{group.totalExpense.toFixed(2)}}
            </span>
            <span v-if="group.totalIncome">
                收入：
                {{group.totalIncome.toFixed(2)}}
            </span>
        </span>
    </div>

    <TransactionItem
      v-for="item in group.items"
      :key="item.id"
      :item="item"
      @edit="(item) => { $emit('edit', item); }"
      @delete="$emit('delete', $event)"
    />

</div>

</template>
