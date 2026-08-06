export const getStatistics = (granularity, date) =>{
    return Request.get('/api/statistics',{
        params: {granularity, date}
    }).then(res => res.data);
};