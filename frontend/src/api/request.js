import axios from "axios";


const request = axios.create({

    baseURL:"http://172.20.10.6:8080",

    timeout:5000

});


export default request;