import axios from "axios";


const request = axios.create({

    baseURL:"http://localhost:8080",

    timeout:5000

});



export function getStatistics(granularity, date){

    return request.get(
        "/statistics",
        {
            params:{
                granularity,
                date
            }
        }
    )
    .then(res=>res.data);

}