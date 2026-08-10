<script setup>

defineProps({

    title:String,

    icon:String

});


</script>



<template>


<div class="menu-item">

    <div class="left">

        <span class="icon">
        {{icon}}
        </span>

        <span>
        {{title}}
        </span>

    </div>

    <div class="arrow">
        >
    </div>

</div>

</template>



<style scoped>


.menu-item{

    height:55px;

    display:flex;

    justify-content:space-between;

    align-items:center;

    border-bottom:1px solid #eee;

    padding:0 15px;

    font-size:16px;

}


.left{

    display:flex;

    align-items:center;

}


.icon{

    margin-right:15px;

}


.arrow{

    color:#999;

}


</style>