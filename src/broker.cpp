#include "../include/broker.hpp"


int* publish_1_svc(PUBLISH_ARGS args, struct svc_req* req)
{
    int* result = (int*)malloc(sizeof(int));

    data[args.topic].push_back(args.value);

    *result = 0;

    return result;
}



RETRIEVE_RESULT* retrieve_1_svc(RETRIEVER_ARGS args, struct svc_req* req)
{
    RETRIEVE_RESULT* result = (RETRIEVE_RESULT*)malloc(sizeof(RETRIEVE_RESULT));

    auto it = data.find(args.topic);
    if (it == data.end())
    {
        result->status              = 1;
        result->values.values_len   = 0;
        result->values.values_val   = nullptr;
        return result;
    }
    result->status                  = 0;

    std::vector<int>& data_values   = it->second;

    result->values.values_len       = data_values.size();
    result->values.values_val       = (int*)malloc(data_values.size() * sizeof(int));

    for (size_t i = 0; i < data_values.size(); i++)
    {
        result->values.values_val[i] = data_values[i];
    }

    return result;
}
