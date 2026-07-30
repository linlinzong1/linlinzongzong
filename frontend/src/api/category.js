import axios from "axios";


const request = axios.create({

    baseURL:"http://localhost:8080",

    timeout:5000

});



// 根据类型查询分类
export function getCategories(type)
{

    return request.get(
        "/categories",
        {
            params:{
                type:type
            }
        }
    )
    .then(res=>res.data);

}