#include "../include/publisher.hpp"
#include "../include/arg_parser.hpp"

int main(int argc, char* argv[])
{
    if (argc != 4)
    {
        std::cerr << "Usage error: ./publisher hostname topic value\n";
        return 1;
    }

    if (number_found(argv[2]))
    {
        std::cerr << "Usage error: topic must not contain any integer values\n";
        return 1;
    }

    if (char_found(argv[3]))
    {
        std::cerr << "Usage error: value must only contain integer values\n";
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

    if (*result == 1)
    {
        std::cout << "must have integer for final argument" << "\n";
        clnt_destroy(client);
        return 1;
    }

    std::cout << "Published " << value << " to topic " << topic << "\n";

    clnt_destroy(client);

    return 0;
}
