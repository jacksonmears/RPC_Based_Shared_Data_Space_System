#include "../include/broker.hpp"
#include "../include/retriever.hpp"


int main(int argc, char* argv[])
{
    if (argc != 3)
    {
        std::cerr << "Usage: ./publisher hostname topic \n";
        return 1;
    }

    char*   hostname    = argv[1];
    char*   topic       = argv[2];

    CLIENT* client = clnt_create(hostname, BROKER_PROG, BROKER_VERS, "tcp");

    if (client == nullptr)
    {
        clnt_pcreateerror(hostname);
        return 1;
    }

    RETRIEVER_ARGS args;

    args.topic = topic;

    RETRIEVE_RESULT* result = retrieve_1(args, client);

    if (result == nullptr)
    {
        clnt_perror(client, "RPC call failed");
        clnt_destroy(client);
        return 1;
    }

    std::cout << "From " << topic << " retrieved: ";
    for (size_t i = 0; i < result->values.values_len; i++)
    {
        std::cout << result->values.values_val[i] << " ";
    }

    std::cout << "\n";

    clnt_destroy(client);

    return 0;
}

