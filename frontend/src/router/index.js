import {
    createRouter,
    createWebHistory
} from "vue-router";


import Home from "../views/Home.vue";
import Record from "../views/Record.vue";
import Statistics from "../views/Statistics.vue";


const routes=[


{
    path:"/",
    component:Home
},


{
    path:"/record",
    component:Record
},

{
    path:"/statistics",
    component:Statistics
}



];


const router=createRouter({

    history:createWebHistory(),

    routes

});


export default router;