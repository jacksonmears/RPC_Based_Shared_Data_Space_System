CXX = g++
CC = gcc

CXXFLAGS = -I/usr/include/tirpc
CFLAGS = -I/usr/include/tirpc
LDFLAGS = -ltirpc

BIN = bin
BUILD = build
SRC = src

all: $(BIN)/broker $(BIN)/publisher $(BIN)/retriever

$(BIN) $(BUILD):
	mkdir -p $@

$(BIN)/broker: $(BIN) $(BUILD) $(SRC)/broker.cpp $(SRC)/rpc_svc.c $(SRC)/rpc_xdr.c
	$(CXX) $(CXXFLAGS) -c $(SRC)/broker.cpp -o $(BUILD)/broker.o
	$(CC) $(CFLAGS) -c $(SRC)/rpc_svc.c -o $(BUILD)/rpc_svc.o
	$(CC) $(CFLAGS) -c $(SRC)/rpc_xdr.c -o $(BUILD)/rpc_xdr.o
	$(CXX) $(BUILD)/broker.o $(BUILD)/rpc_svc.o $(BUILD)/rpc_xdr.o -o $@ $(LDFLAGS)

$(BIN)/publisher: $(BIN) $(BUILD) $(SRC)/publisher.cpp $(SRC)/arg_parser.cpp $(SRC)/rpc_clnt.c $(SRC)/rpc_xdr.c
	$(CXX) $(CXXFLAGS) -c $(SRC)/publisher.cpp -o $(BUILD)/publisher.o
	$(CXX) $(CXXFLAGS) -c $(SRC)/arg_parser.cpp -o $(BUILD)/arg_parser.o
	$(CC) $(CFLAGS) -c $(SRC)/rpc_clnt.c -o $(BUILD)/rpc_clnt.o
	$(CC) $(CFLAGS) -c $(SRC)/rpc_xdr.c -o $(BUILD)/rpc_xdr.o
	$(CXX) $(BUILD)/publisher.o $(BUILD)/arg_parser.o $(BUILD)/rpc_clnt.o $(BUILD)/rpc_xdr.o -o $@ $(LDFLAGS)

$(BIN)/retriever: $(BIN) $(BUILD) $(SRC)/retriever.cpp $(SRC)/arg_parser.cpp $(SRC)/rpc_clnt.c $(SRC)/rpc_xdr.c
	$(CXX) $(CXXFLAGS) -c $(SRC)/retriever.cpp -o $(BUILD)/retriever.o
	$(CXX) $(CXXFLAGS) -c $(SRC)/arg_parser.cpp -o $(BUILD)/arg_parser.o
	$(CC) $(CFLAGS) -c $(SRC)/rpc_clnt.c -o $(BUILD)/rpc_clnt.o
	$(CC) $(CFLAGS) -c $(SRC)/rpc_xdr.c -o $(BUILD)/rpc_xdr.o
	$(CXX) $(BUILD)/retriever.o $(BUILD)/arg_parser.o $(BUILD)/rpc_clnt.o $(BUILD)/rpc_xdr.o -o $@ $(LDFLAGS)

clean:
	rm -f $(BUILD)/*.o $(BIN)/broker $(BIN)/publisher $(BIN)/retriever
