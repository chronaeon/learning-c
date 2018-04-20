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


---

## Problems with Ethereum

There are a variety of oversights  and problems that create optimization issues for Ethereum. Most of these can be recognized and solutions proposed by taking a long look  at the history of software development and seeing where Ethereum falls short.

Problems:

1. Big-Endian instead of Little-Endian
2. Stack-Based instead of Memory Registry
	1. Operations can be processed and output from people's computers, that's the "work" and consensus is formed by mean average on operational results. The closer to the mean results are, the more rewards someone gets.
3. Proof-of-work loosely connected to transactions instead of tightly coupled
4. Single currency with legacy incentive system instead of a trilinear currency with one recursive and one proactive incentive per coin, that is with three total coins. Reward is generic and based on accuracy of end computation, and speed of computations, and number of computations performed. Reward can be no higher than one standard deviation above the mean, regardless of speed (this keeps people with extremely fast connections from taking all of the computation.)
5. Blocks and smart contracts are not properly incentivized. Transactions come with bounties, and the chain curators own the bounties when they include transactions in blocks. Nothing needs to be mined. Transactions are assigned to 33 nodes by a chaotic randomization function that produces chaotic behavior based on three deterministic inputs. 
6. Every peer sends one datagram per second to three other peers. Every connected peer receives three datagrams per second from other peers. Datagrams contain an integer between 1 and 1024. This means peer connections use 3kb upload bandwidth and 3kb download bandwidth per second. 
7. The first number received from a peer per cpu clock cycle is multiplied by the second number received per cpu clock cycle and divided by the third number, producing a chaotic output whose domain has a max range of 1,048,576 and a min range of .0009765. In cases where a decimal output is produced 
