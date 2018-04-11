# Cthereum

Ethereum binaries implemented in C.

Code should be:

1. Fast
2. Discrete
3. Modular
4. Performant
5. Reliable

Libraries are custom-made and performant to the protocol's exact specifications. Cthereum will be compatible with the extant public Ethereum blockchains and protocols, that is, with the major clients and already formed consensus algorithms. 

Once that step is ascertained in C code, optimizations to public Ethereum should become increasingly easier to implement, while older difficulties fall away. The system should stabilize over time, becoming something like the Linux kernel: built in C, reliable, and good for dozens or hundreds  of other implementations and uses.


## C Concepts to Implement

1. Datagrams as message data.
2. Syncing with datagrams: each block sync is an atomic event equal to one datagram received from a random peer. 
3. Every 64,000 blocks is one directory, and each block is one file. All 64,000 files are statically linked by a single file in the same directory. The directory above that contains a file which links each set of 64,000 to the next.
4. Receiving peers send data back for verification from the originating peer as a datagram.
5. If the originating peer receives the same data that it first sent, it sends the next valid block as a datagram. 
6. This process of send, receive, send back, send next continues on. 
7. Assuming an upload rate of ~5.6 mbps, a receiving peer could sync the full chain at a speed of 14 blocks per second with as little as 5 - 7 peers, assuming a 33% loss rate, that would still be 9+ blocks per second. 
8. Disk I/O would be minimal, and devp2p could continue to be used for syncing the most recent 100 or so blocks.

---

1. Another method would be to have a webserver that updates every epoch.
