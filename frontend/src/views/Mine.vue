<script setup>

import UserHeader from "../components/UserHeader.vue";
import MineMenuItem from "../components/MineMenuItem.vue";

</script>


<template>

<div class="mine">

    <UserHeader
        name="林林总"
    />

    <div class="menu">

        <MineMenuItem
            title="账户安全"
            icon="🔒"
        />

        <MineMenuItem
            title="设置"
            icon="⚙"
        />

    </div>
</div>


</template>

<style scoped>

.mine{

    padding:20px;

}


.menu{

    margin-top:30px;

}


</style>