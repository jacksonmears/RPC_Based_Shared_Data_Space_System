# RPC-Based-Shared-Data-Space-System


creating ONC/SUN RPC interface (.x) file from root dir:
c:      rpcgen -C broker.x
c++:    rpcgen -N -C broker.x


if you recieved the error:
"fatal error: rpc/rpc.h: No such file or directory
    9 | #include <rpc/rpc.h>"

like I did, you may need to install the dev package for rpc library:
sudo apt update
sudo apt install libtirpc-dev
sudo apt install rpcbind

compilation command:
g++ -I/usr/include/tirpc src/broker.cpp rpc_svc.c rpc_xdr.c -o bin/broker -ltirpc -Wall -Wextra
