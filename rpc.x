
struct PUBLISH_ARGS 
{
    int value;

    string topic<>;
};

struct RETRIEVER_ARGS 
{
    string topic<>;
}; 

struct RETRIEVE_RESULT
{
    int status;
    int values<>;
};

program BROKER_PROG 
{
    version BROKER_VERS 
    {
        int PUBLISH(PUBLISH_ARGS) = 1; 
        RETRIEVE_RESULT RETRIEVE(RETRIEVER_ARGS) = 2; 
    } = 1; 
} = 0x20000001;

