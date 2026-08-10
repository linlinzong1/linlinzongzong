<script setup>

defineProps({
    name:{
        type:String,
        default:"用户"
    }
});

</script>


<template>


<div class="user-header">

    <div class="avatar">

        <img
        src="/avatar.png"
        alt="avatar"
        />

    </div>

    <div class="name">

        {{name}}

    </div>

</div>

</template>



<style scoped>


.user-header{

    display:flex;

    align-items:center;

    padding:20px;

    gap: 12px;

}


.avatar{

    width:70px;

    height:70px;

    border-radius:50%;

    overflow:hidden;

    margin-right:20px;

}


.avatar img{

    width:100%;

    height:100%;

    object-fit:cover;

}



.name{

    font-size:22px;

    font-weight:bold;

}


</style>