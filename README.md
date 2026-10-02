# RPC-Based Shared Data Space System

## 1. Requirements

The project is intended to run on Linux.

The following software/packages are required:

- `g++`
- `gcc`
- `make`
- `rpcgen`
- `libtirpc`
- `libtirpc-dev`
- `rpcbind`

On Ubuntu/Debian-based systems, install the required packages with:

```bash
sudo apt update
sudo apt install build-essential make rpcbind libtirpc-dev rpcgen
```

---

## 2. Iowa State Server Requirements


From an Iowa State-connected machine:

```text
pyrite-n1.cs.iastate.edu
```

I personally had to do something like:
```bash
ssh jckmears@pyrite-n1.cs.iastate.edu
```

---

## 3. Clone and Build

Clone the repository:

```bash
git clone https://github.com/jacksonmears/RPC_Based_Shared_Data_Space_System.git
```

Enter the project:

```bash
cd RPC_Based_Shared_Data_Space_System
```

(only if local environment isn't functional, do NOT do this on iastate server) Start `rpcbind`:

```bash
sudo systemctl start rpcbind
```

Build the project from the project root:

```bash
make
```

The Makefile builds:

```text
bin/broker
bin/publisher
bin/retriever
```

To clean the build:

```bash
make clean
```

Then rebuild:

```bash
make
```

---

## 4. Running the Broker

The broker is the server that owns the shared data.

Start it with:

```bash
./bin/broker
```

The broker should remain running while publishers and retrievers use it, such that this termainl is to be kept open.

---

## 5. Running the Publisher

From another terminal, syntax:

```text
./bin/publisher <hostname> <topic> <value>
```

- The topic must not contain any numerical values. If it does, the program prints an error message and exits.
- The value must contain only numerical values. If it contains non-numerical characters, the program prints an error message and exits.

For example, using the iastate server:

```bash
./bin/publisher pyrite-n1.cs.iastate.edu test 55
```

This publishes:

```text
test -> 55
```

Run it again:

```bash
./bin/publisher pyrite-n1.cs.iastate.edu test 100
```

The broker now contains:

```text
test -> [55, 100]
```

---

## 6. Running the Retriever

Syntax:

```text
./bin/retriever <hostname> <topic>
```

The topic must not contain any numerical values. If it does, the program prints an error message and exits.

For example:

```bash
./bin/retriever pyrite-n1.cs.iastate.edu test
```

If the broker contains:

```text
test -> [55, 100, 25, 75]
```

the retriever will return those values.

---

## 7. Testing the Complete System Locally

The simplest test is to use three terminals.

### Terminal 1 — Broker

```bash
./bin/broker
```

Leave this process running.

### Terminal 2 — Publisher

Run:

```bash
./bin/publisher localhost test 55
```

Then:

```bash
./bin/publisher localhost test 100
```

Then:

```bash
./bin/publisher localhost test 25
```

### Terminal 3 — Retriever

Run:

```bash
./bin/retriever localhost test
```

The retriever should return the values associated with `test`.

### Testing Multiple Topics

```bash
./bin/publisher localhost temperature 72
./bin/publisher localhost temperature 75

./bin/publisher localhost score 100
./bin/publisher localhost score 95
```

Then:

```bash
./bin/retriever localhost temperature
```

and:

```bash
./bin/retriever localhost score
```

The topics maintain separate collections of values.

---


## 8. Implementation Assumptions

- The broker is the RPC server and maintains the shared data in memory.
- Publishers and retrievers are RPC clients and specify the broker hostname as a command-line argument.
- A topic may contain up to 32 characters and must not contain numeric characters.
- Each published value is an integer.
- A topic may have any number of published values and values are stored dynamically rather than in a fixed-size array.
- The broker must remain running while publishers and retrievers make requests.
- The system uses TCP RPC for publisher and retriever communication.
