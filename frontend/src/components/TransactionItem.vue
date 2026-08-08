//单条记录

<script setup>

import {ref} from "vue";
import TransactionEdit from "./TransactionEdit.vue";

const props=defineProps({

    item:Object

});


const showMenu=ref(false);

function toggleMenu(){

    showMenu.value=!showMenu.value;

}

const emit = defineEmits(['edit', 'delete']); 

function edit() {
  emit('edit', props.item); // 将当前item传给父组件
  showMenu.value = false;   // 关闭菜单
}

function remove() {
  if (confirm('确定删除该账单吗？')) {
    emit('delete', props.item.id);
  }
  showMenu.value = false;
}

</script>

<template>

    <div class="record">

        <div class="record-row">
            <span class="category-name">{{item.categoryName}}</span>
            <div class="right-side">
                <span :class="item.type === 1 ? 'expense' : 'income'">
                    {{item.type === 1 ? '支出' : '收入'}}
                    :{{item.amount.toFixed(2)}}
                </span>

                <span class="note">{{item.note}}</span>

                <button class="more" @click="toggleMenu">
                    ...
                </button>

                <div v-if="showMenu" class="menu" >

                <button @click="edit">修改</button>

                <button @click="remove">删除</button>

                </div>

            </div>

        </div>

    </div>


</template>

<style scoped>
/* 单条账单外层容器 */
.record {
  padding: 14px 16px;
  background: #fff;
  border-bottom: 1px solid #f0f0f0;
}

/* 行容器：左右两端对齐 + 垂直居中 */
.record-row {
  display: flex;
  justify-content: space-between;
  align-items: center;
  width: 100%;
}

/* 左侧分类名称 */
.category-name {
  font-size: 15px;
  color: #333;
  font-weight: 500;
}

/* 右侧内容区：横向排列金额、备注、按钮 */
.right-side {
  display: flex;
  align-items: center;
  gap: 12px;
  position: relative; /* 下拉菜单的定位父级 */
}

/* 支出金额：红色 */
.expense {
  color: #ff4d4f;
  font-size: 16px;
  font-weight: 600;
}

/* 收入金额：绿色 */
.income {
  color: #52c41a;
  font-size: 16px;
  font-weight: 600;
}

/* 备注文字：灰色小字，超长自动省略 */
.note {
  font-size: 13px;
  color: #999;
  max-width: 100px;
  overflow: hidden;
  text-overflow: ellipsis;
  white-space: nowrap;
}

/* 更多操作按钮 */
.more {
  border: none;
  background: transparent;
  font-size: 18px;
  color: #999;
  cursor: pointer;
  padding: 4px 8px;
  line-height: 1;
  border-radius: 4px;
}
.more:hover {
  background: #f5f5f5;
  color: #666;
}

/* 下拉操作菜单 */
.menu {
  position: absolute;
  right: 0;
  top: calc(100% + 4px);
  background: #fff;
  border: 1px solid #e8e8e8;
  border-radius: 6px;
  box-shadow: 0 2px 12px rgba(0, 0, 0, 0.1);
  z-index: 99;
  min-width: 80px;
  overflow: hidden;
}

/* 菜单内按钮 */
.menu button {
  display: block;
  width: 100%;
  border: none;
  background: transparent;
  padding: 8px 14px;
  font-size: 14px;
  color: #333;
  cursor: pointer;
  text-align: center;
}
.menu button:hover {
  background: #f5f5f5;
}
.menu button:first-child {
  border-bottom: 1px solid #f0f0f0;
}
</style>