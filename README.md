# RPC-Based Shared Data Space System


# 4. Requirements

The project is intended to run on Linux.

The following software/packages are required:

* `g++`
* `gcc`
* `make`
* `rpcgen`
* `libtirpc`
* `libtirpc-dev`
* `rpcbind`

On Ubuntu/Debian-based systems, install the required packages with:

```bash
sudo apt update
sudo apt install build-essential make rpcbind libtirpc-dev rpcgen
```

---

# 5. Iowa State Server Requirements

This project is intended to be used on the Iowa State CS departmental servers.

The Pyrite servers may not be accessible from an arbitrary Internet connection.

**You need to be connected to the Iowa State network, or to the appropriate Iowa State VPN, to access the departmental server environment.**

For example, from an Iowa State-connected machine, the assignment may provide a server hostname such as:

```text
pyrite01.cs.iastate.edu
```

---

# 6. Clone the Repository

Clone the repository:

```bash
git clone https://github.com/jacksonmears/RPC_Based_Shared_Data_Space_System.git
```

Then enter the project:

```bash
cd RPC_Based_Shared_Data_Space_System
```

Start `rpcbind`:

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

Clean the Build:

```bash
make clean
```

Then rebuild:

```bash
make
```

---

# 4. Running the Broker

The broker is the server that owns the shared data.

Start it with:

```bash
./bin/broker
```

The broker should remain running while publishers and retrievers use it.

The broker does not normally print a message for every successful request because the generated RPC server handles the network communication.

Keep this terminal open.

---

# 12. Running the Publisher

The publisher syntax is:

```text
./bin/publisher <hostname> <topic> <value>
```


The topic must not contain any numerical values, otherwise, an error will be thrown.
The value must not contain any nonnumerical values, otherwise, an error will be thrown.


For example, using the local machine:

```bash
./bin/publisher localhost test 55
```

This publishes:

```text
test -> 55
```

Run it again:

```bash
./bin/publisher localhost test 100
```

The broker now contains:

```text
test -> [55, 100]
```


---

# 13. Running the Retriever

The retriever syntax is:

```text
./bin/retriever <hostname> <topic>
```

The topic must not contain any numerical values, otherwise, an error will be thrown.


For example:
```bash
./bin/retriever localhost test
```

If the broker contains:

```text
test -> [55, 100, 25, 75]
```

the retriever will return those values.

---

# 14. Testing the Complete System Locally

The simplest test is to use three terminals.

## Terminal 1 — Broker

```bash
./bin/broker
```

Leave this process running.

## Terminal 2 — Publisher

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

## Terminal 3 — Retriever

Run:

```bash
./bin/retriever localhost test
```

The retriever should return the values associated with `test`.

You can also test multiple topics:

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

# 16. Running on an Iowa State Server

The same executables can be run on an Iowa State Pyrite server.

For example:

```text
pyrite01.cs.iastate.edu
```

First connect to the server:

```bash
ssh pyrite01.cs.iastate.edu
```

Once connected, clone the repository:

```bash
git clone <REPOSITORY_URL>
cd RPC_Based_Shared_Data_Space_System
```

Install the required packages if they are not already available:

```bash
sudo apt update
sudo apt install build-essential make rpcbind libtirpc-dev rpcgen
```

Build the project:

```bash
make
```

Start the broker:

```bash
./bin/broker
```

---


