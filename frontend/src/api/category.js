
import request from "./request";




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