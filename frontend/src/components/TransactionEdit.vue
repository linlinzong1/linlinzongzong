//修改单条记录


<script setup>

import { ref, watch } from 'vue';

const props = defineProps({
  item: Object
});


const emit=defineEmits([
    "save",
    "cancel"
]);

// 复制一份数据，避免直接修改原对象
const form = ref({
  type: 1,
  amount: '',
  categoryId: 1,
  date: '',
  note: ''
});

// 当 item 变化时，填充表单
watch(() => props.item, (newVal) => {
  if (newVal) {
    form.value = {
      type: newVal.type,
      amount: newVal.amount,
      categoryId: newVal.categoryId,
      date: newVal.date,
      note: newVal.note || ''
    };
  }
}, { immediate: true });

function save() {
  emit('save', form.value);
}

function cancel() {
  emit('cancel');
}

</script>



<template>

<div class="edit-modal" v-if="item">
    <div class="edit-content">
      <h3>修改账单</h3>
      <input v-model="form.amount" placeholder="金额" type="number" />
      <input v-model="form.date" placeholder="日期" type="date" />
      <input v-model="form.categoryId" placeholder="分类ID" />
      <input v-model="form.note" placeholder="备注" />
      <select v-model="form.type">
        <option :value="1">支出</option>
        <option :value="2">收入</option>
      </select>
      <div class="actions">
        <button @click="save">保存</button>
        <button @click="cancel">取消</button>
      </div>
    </div>
  </div>


</template>
<style scope>
.edit-modal {
  position: fixed;
  top: 0;
  left: 0;
  width: 100%;
  height: 100%;
  background: rgba(0,0,0,0.5);
  display: flex;
  justify-content: center;
  align-items: center;
  z-index: 9999;
}
.edit-content {
  background: white;
  padding: 20px;
  border-radius: 8px;
  min-width: 300px;
}
</style>