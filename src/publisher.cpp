#include "../include/broker.hpp"
#include "../include/publisher.hpp"


int main(int argc, char* argv[])
{
    if (argc != 4)
    {
        std::cerr << "Usage: ./publisher hostname topic value\n";
        return 1;
    }

    char*   hostname    = argv[1];
    char*   topic       = argv[2];
    int     value       = std::atoi(argv[3]);

    CLIENT* client = clnt_create(hostname, BROKER_PROG, BROKER_VERS, "tcp");

    if (client == nullptr)
    {
        clnt_pcreateerror(hostname);
        return 1;
    }

    PUBLISH_ARGS args;

    args.topic = topic;
    args.value = value;

    int* result = publish_1(args, client);

    if (result == nullptr)
    {
        clnt_perror(client, "RPC call failed");
        clnt_destroy(client);
        return 1;
    }

    std::cout << "Published " << value << " to topic " << topic << "\n";

    clnt_destroy(client);

    return 0;
}
