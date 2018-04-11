<html>
<head>
<TITLE> Sockets Tutorial</TITLE>
</head>
<body BGCOLOR="#ffffff">
<h2>Sockets Tutorial</h2>

This is a simple tutorial on using sockets for interprocess
communication.  

<h3>The client server model</h3>
<h2> by Robert Ingalls </h2>
Most interprocess communication uses the <em>client server 
model</em>.  These terms refer to the two processes which
will be communicating with each other.  One of the
two processes, the <em>client</em>, connects to the other process, the 
<em>server</em>,
typically to make a request for information.  A good analogy is
a person who makes a phone call to another person.
<p>
Notice that the client needs to know of the existence of and
the address of the server, but the server does not need to
know the address of (or even the existence of) the client prior
to the connection being established.  Notice also that once
a connection is established, both sides can send and receive
information.
<p>
The system calls for establishing a connection are somewhat
different for the client and the server, but both involve
the basic construct of a <em>socket</em>.  A socket is one end of
an interprocess communication channel.  The two processes
each establish their own socket.
<p>
The steps involved in establishing a socket on the <em>client</em>
side are as follows:
<ol>
<li> Create a socket with the <code>socket()</code> system call
<li> Connect the socket to the address of the server using the
<code>connect()</code> system call
<li> Send and receive data.  There are a number of ways to do this,
but the simplest is to use the <code>read()</code> and <code>write() 
</code> system calls.  
</ol>

The steps involved in establishing a socket on the
<em>server</em> side are as follows:

<ol>
<li>Create a socket with the <code>socket()</code> system call
<li>Bind the socket to an address using the <code>bind()</code> system call.  
For a server socket on the Internet, an address consists of a 
port number on the host machine.
<li>Listen for connections with the <code>listen()</code> system call
<li>Accept a connection with the <code>accept()</code> system call.
This call typically blocks until a client connects with the server.  
<li>Send and receive data 
</ol>

<h3>Socket Types</h3>

When a socket is created, the program has to specify the <em>
address domain</em> and the <em> socket type</em>.  Two processes
can communicate with each other only if their sockets are of the same
type and in the same domain.

There are two widely used address domains, the <em>unix domain</em>, in which
two processes which share a common file system communicate, and the
<em>Internet domain</em>, in which two processes running on any two hosts on
the Internet communicate.  Each of these has its own address format.  
<p>
The address of a socket in
the Unix domain is a character string which is basically an entry in
the file system.  
<p>
The address of a socket in the Internet domain
consists of the Internet address of the host machine (every computer
on the Internet has a unique 32 bit address, often referred to as its
IP address).  In addition, each socket needs a port number on that
host.  Port numbers are 16 bit unsigned integers.  The lower numbers
are reserved in Unix for standard services.  For example, the
port number for the FTP server is 21.  It is important that standard
services be at the same port on all computers so that clients will
know their addresses.  However, port numbers above 2000 are
generally available.
<p>
There are two widely used socket types, <em>stream sockets</em>, and
<em>datagram sockets</em>.  Stream sockets treat communications as a
continuous stream of characters, while datagram sockets have to read
entire messages at once.  Each uses its own communciations protocol.
Stream sockets use TCP (Transmission Control Protocol), which is a
reliable, stream oriented protocol, and datagram sockets use UDP (Unix
Datagram Protocol), which is unreliable and message oriented.
<p>
The examples in this tutorial will use sockets in the Internet domain
using the TCP protocol.

<h3> Sample code</h3>

C code for a very simple client and server are provided for you.
These communicate using stream sockets in the Internet domain.  The
code is described in detail below.  However, before you read the
descriptions and look at the code, you should compile and run the two
programs to see what they do.
<p>
<a href="server.c"><img src="redball.gif"> Click here for
the server program </a>
<p>
<a href="client.c"><img src="redball.gif"> Click here for
the client program </a>
<p>
Download these into files called <code>server.c</code> and <code>
client.c</code> and compile them separately into two
executables called <code>server</code> and <code>client</code>.
They require special compiling flags as stated in their respective
progarms.
<p>
Ideally, you should run the client and the server on separate hosts on
the Internet. Start the server first.  Suppose the server is running
on a machine called <code>cheerios</code>.  When you run the server,
you need to pass the port number in as an argument.  You can choose
any number between 2000 and 65535.  If this port is already in use on
that machine, the server will tell you this and exit.  If this
happens, just choose another port and try again. If the port is
available, the server will block until it receives a connection
from the client.  Don't be alarmed if the server doesn't do anything;
it's not supposed to do anything until a connection is made.
Here is a typical command line:
<pre>
server 51717
</pre>
<p>
To run the client you need to pass in two arguments, the name of the
host on which the server is running and the port number on which the
server is listening for connections.  
Here is the command line to connect to the server described above:
<pre>
client cheerios 51717
</pre>
The client will prompt you
to enter a message.  If everything works correctly, the server will
display your message on stdout, send an acknowledgement message to
the client and terminate.  The client will print the acknowledgement
message from the server and then terminate.
<p>
You can simulate this on a single machine by running the server in one
window and the client in another.  In this case, you can use the keyword
<code>localhost</code> as the first argument to the client.

<h4>Server code</h4>

The server code uses a number of ugly programming constructs, and so
we will go through it line by line.<p>
<hr>
<code>
#include &ltstdio.h&gt<p>
</code>
This header file contains declarations used in most input and
output and is typically included in all C programs.<p>
<hr>
<code>
#include &ltsys/types.h&gt<p>
</code>
This header file contains definitions of a number of data types
used in system calls.  These types are used in the next two
include files.<p>
<hr>
<code>
#include &ltsys/socket.h&gt<p>
</code>
The header file <a href="socket.h"> <code>socket.h</code> </a> includes 
a number of definitions of structures needed for sockets.
<p> 
<hr>
<code>
#include &ltnetinet/in.h&gt<p>
</code>
The header file <a href="in.h"><code>netinet/in.h</code></a> contains 
constants and structures needed for internet domain addresses.
<hr>
<pre>
void error(char *msg)
{
    perror(msg);
    exit(1);
}
</pre>
This function is called when a system call fails.
It displays a message about the error on <code>stderr</code> and
then aborts the program. 
<a href="perror.txt"><img src="redball.gif"> Click here </a> to see
the man page for <code>perror()</code> 
<hr>
<pre>
int main(int argc, char *argv[])
{
     int sockfd, newsockfd, portno, clilen, n;
</pre>
<code>sockfd</code> and <code>newsockfd</code> are file
descriptors, i.e. array subscripts into the 
<a href="fd.txt">file descriptor table </a>.  These two variables
store the values returned by the socket system call and the accept
system call.
<p>
<code>portno</code> stores the port number on which the server
accepts connections.
<p>
<code>clilen</code> stores the size of the address of the client.
This is needed for the accept system call.
<p>
<code>n</code> is the return value for the <code>read()</code>
and <code>write()</code> calls; i.e. it contains the number of
characters read or written.
<hr>
<pre>
     char buffer[256];
</pre>
The server reads characters from the socket connection into this buffer.
<hr>
<pre>
     struct sockaddr_in serv_addr, cli_addr;
</pre>
A <code>sockaddr_in</code> is a structure containing an internet
address.  This structure is defined in <code>&ltnetinet/in.h&gt</code>.
Here is the definition:
<pre>
struct sockaddr_in {
        short   sin_family;
        u_short sin_port;
        struct  in_addr sin_addr;
        char    sin_zero[8];
};
</pre>
An <code>in_addr</code> structure, defined in the same header file,
contains only one field, a unsigned long called <code>s_addr</code>.

The variable <code>serv_addr</code> will contain the address of
the server, and <code>cli_addr</code> will contain the address of
the client which connects to the server.
<hr>
<pre>
     if (argc < 2) {
         fprintf(stderr,"ERROR, no port provided\n");
         exit(1);
     }
</pre>
The user needs to pass in the port number on which the server will
accept connections as an argument.  This code displays an error
message if the user fails to do this.
<hr>
<pre>
     sockfd = socket(AF_INET, SOCK_STREAM, 0); 
     if (sockfd < 0) 
         error("ERROR opening socket");
</pre>
The <code>socket()</code> system call creates a new socket.  It takes
three arguments.  The first is the address domain of the socket.
Recall that there are two possible address domains, the unix domain
for two processes which share a common file system, and the Internet
domain for any two hosts on the Internet.  The symbol constant
<code>AF_UNIX</code> is used for the former, and <code>AF_INET</code>
for the latter (there are actually many other options which can be
used here for specialized purposes).<p>

The second argument is the type of socket.  Recall that there
are two choices here, a stream socket in which characters are read
in a continuous stream as if from a file or pipe, and a
datagram socket, in which messages are read in chunks.
The two symbolic constants are <code>SOCK_STREAM</code> and
<code>SOCK_DGRAM</code>.  

The third argument is the protocol. If this argument is zero
(and it always should be except for unusual circumstances), the
operating system will choose the most appropriate protocol.
It will choose TCP for stream sockets and UDP for datagram sockets.
<p>
The socket system call returns an entry into the file descriptor
table (i.e. a small integer).  This value is used for all subsequent
references to this socket. If the socket call fails, it returns -1.
In this case the program displays and error message and exits.  However,
this system call is unlikely to fail.  
<p>
This is a simplified description of the socket call; there are
numerous other choices for domains and types, but these are the most
common. <a href="socket.txt"> <img src="redball.gif"> Click here </a> to see the socket man page.
<hr>
<pre>
     bzero((char *) &serv_addr, sizeof(serv_addr));
</pre>
The function <code>bzero()</code> sets all values in a buffer to zero.
It takes two arguments, the first is a pointer to the buffer and the
second is the size of the buffer.  Thus, this line initializes
<code>serv_addr</code> to zeros.
<hr>
<pre>
     portno = atoi(argv[1]);
</pre>
The port number on which the server will listen for connections
is passed in as an argument, and this statement uses the <code>
atoi()</code> function to convert this from a string of digits
to an integer.
<hr>
<pre>
     serv_addr.sin_family = AF_INET;
</pre>
The variable <code>serv_addr</code> is a structure of type
<code>struct sockaddr_in</code>.  This structure has four fields.
The first field is <code>short sin_family</code>, which contains a
code for the address family.  It should always be set to the
symbolic constant <code>AF_INET</code>.
<hr>
<pre>
     serv_addr.sin_port = htons(portno);
</pre>
The second field of <code>serv_addr</code> is <code>unsigned short sin_port
</code>, which contain the port number.  However, instead of simply
copying the port number to this field, it is necessary to convert
this to <a href="byteorder.txt" >network byte order </a> using the function
<code> htons()</code> which converts a port number in host byte order
to a port number in network byte order.

<hr>
<pre>
     serv_addr.sin_addr.s_addr = INADDR_ANY;
</pre>
The third field of <code>sockaddr_in</code> is a structure of
type <code>struct in_addr</code> which contains only a single field
<code>unsigned long s_addr</code>.  This field contains the IP address
of the host.  For server code, this will always be the IP address of
the machine on which the server is running, and there is a symbolic
constant <code>INADDR_ANY</code> which gets this address.
<hr>
<pre>
     if (bind(sockfd, (struct sockaddr *) &serv_addr,
              sizeof(serv_addr)) < 0)
                  error("ERROR on binding");
</pre>
The <code>bind()</code> system call binds a socket to an
address, in this case the address of the current host and
port number on which the server will run.  It takes three
arguments, the socket file descriptor, the address to which
is bound, and the size of the address to which it is bound.
The second argument is a pointer to a structure of type
<code>sockaddr</code>, but what is passed in is a structure
of type <code>sockaddr_in</code>, and so this must be cast to
the correct type.  This can fail for a number of reasons, the
most obvious being that this socket is already in use on this
machine.  <a href="bind.txt"> <img src="redball.gif"> Click here </a> to see the man page
for <code>bind()</code>
<hr>
<pre>
     listen(sockfd,5);
</pre>
The <code>listen</code> system call allows the process to listen on
the socket for connections.  The first argument is the socket
file descriptor, and the second is the size of the backlog queue,
i.e., the number of connections that can be waiting while the process
is handling a particular connection.  This should be set to 5,
the maximum size permitted by most systems. If the first argument
is a valid socket, this call cannot fail, and so the code doesn't
check for errors. <a href="listen.txt"> <img src = "redball.gif">
Click here </a> to see the man page for listen.
<hr>
<pre>
     clilen = sizeof(cli_addr);
     newsockfd = accept(sockfd, (struct sockaddr *) &cli_addr, &clilen);
     if (newsockfd < 0) 
          error("ERROR on accept");
</pre>
The <code>accept()</code> system call causes the process to
block until a client connects to the server.  Thus, it wakes up
the process when a connection from a client has been successfully
established.  It returns a new file descriptor, and all communication
on this connection should be done using the new file descriptor.
The second argument is a reference pointer to the address of the
client on the other end of the connection, and the third argument is
the size of this structure.
<hr>
<pre>
     bzero(buffer,256);
     n = read(newsockfd,buffer,255);
     if (n < 0) error("ERROR reading from socket");
     printf("Here is the message: %s\n",buffer);
</pre>
Note that we would only get to this point after a client has
successfully connected to our server.  This code initializes the
buffer using the <code>bzero()</code> function, and then reads from
the socket.  Note that the read call uses the new file descriptor, the
one returned by <code>accept()</code>, not the original file descriptor
returned by <code>socket()</code>.  Note also that the <code>read()
</code> will block until there is something for it to read in the
socket, i.e. after the client has executed a <code>write()</code>.
It will read either the total number of characters in the socket or
255, whichever is less, and return the number of characters read.
<a href="read.txt"> <img src="redball.gif"> Click here</a> to see 
the man page for <code> read()</code>.
<hr>
<pre>
     n = write(newsockfd,"I got your message",18);
     if (n < 0) error("ERROR writing to socket");
</pre>
Once a connection has been established, both ends can both read and
write to the connection.  Naturally, everything written by the client 
will be read by the server, and everything written by the server
will be read by the client.  This code simply writes a short
message to the client.  The last argument of write is the size of the
message. <a href="write.txt"> <img src="redball.gif"> Click here </a> to see the man page
for write.
<hr>
<pre>
     return 0; 
}
</pre>
This terminates main and thus the program.  Since main was declared to
be of type int as specified by the ascii standard, many compilers 
complain if it does not return anything.

<h3> Client code </h3>

As before, we will go through the program <code>client.c</code> line 
by line.

<pre>
#include &ltstdio.h&gt
#include &ltsys/types.h&gt
#include &ltsys/socket.h&gt
#include &ltnetinet/in.h&gt
#include &ltnetdb.h&gt
</pre>
The header files are the same as for the server with one addition.
The file <code>netdb.h</code> defines the structure <code>
hostent</code>, which will be used below.
<hr>
<pre>
void error(char *msg)
{
    perror(msg);
    exit(0);
}

int main(int argc, char *argv[])
{
    int sockfd, portno, n;
    struct sockaddr_in serv_addr;
    struct hostent *server;
</pre>
The <code>error()</code> function is identical to that in the server,
as are the variables <code>sockfd, portno</code>, and <code>n</code>.
The variable <code>serv_addr</code> will contain the address of the
server to which we want to connect.  It is of type <a href="sockaddr">
<code>struct sockaddr_in</code></a>.
<p>
The variable <code>server</code> is a pointer to a structure of
type <code>hostent</code>.  This structure is defined in the header
file <code>netdb.h</code> as follows:
<pre>
struct  hostent {
        char    *h_name;        /* official name of host */
        char    **h_aliases;    /* alias list */
        int     h_addrtype;     /* host address type */
        int     h_length;       /* length of address */
        char    **h_addr_list;  /* list of addresses from name server */
#define h_addr  h_addr_list[0]  /* address, for backward compatiblity */
};
</pre>
It defines a host computer on the Internet.
The members of this structure are:
<pre>
h_name       Official name of the host.

h_aliases    A zero  terminated  array  of  alternate
             names for the host.

h_addrtype   The  type  of  address  being  returned;
             currently always AF_INET.

h_length     The length, in bytes, of the address.

h_addr_list  A pointer to a list of network addresses
             for the named host.  Host addresses are
             returned in network byte order.
</pre>
Note that <code>h_addr</code> is an alias for the first
address in the array of network addresses.
<hr>
<pre>
    char buffer[256];
    if (argc < 3) {
       fprintf(stderr,"usage %s hostname port\n", argv[0]);
       exit(0);
    }
    portno = atoi(argv[2]);
    sockfd = socket(AF_INET, SOCK_STREAM, 0);
    if (sockfd < 0) 
        error("ERROR opening socket");
</pre>
All of this code is the same as that in the server.
<hr>
<pre>
    server = gethostbyname(argv[1]);
    if (server == NULL) {
        fprintf(stderr,"ERROR, no such host\n");
        exit(0);
    }
</pre>
<code>argv[1]</code> contains the name of a host on the Internet,
e.g. <code>cheerios@cs.rpi.edu</code>.  The function:
<pre>
     struct hostent *gethostbyname(char *name)
</pre>
Takes such a name as an argument and returns a pointer to a
<code>hostent</code> containing information about that host.
The field <code>char *h_addr</code> contains the IP address.
If this structure is NULL, the system could not locate
a host with this name.
<p>
The mechanism by which this function works is complex,
often involves querying large databases all around the country.
<hr>
<pre>
    bzero((char *) &serv_addr, sizeof(serv_addr));
    serv_addr.sin_family = AF_INET;
    bcopy((char *)server->h_addr, 
         (char *)&serv_addr.sin_addr.s_addr,
         server->h_length);
    serv_addr.sin_port = htons(portno);
</pre>
This code sets the fields in <code>serv_addr</code>.  Much of
it is the same as in the server.  However, because the 
field <code>server->h_addr</code> is a character string,
we use the function:
<pre>
void bcopy(char *s1, char *s2, int length)
</pre>
</code> which copies <code>length</code> bytes from <code>s1</code> to
<code>s2</code>.
<hr>
<pre>
    if (connect(sockfd,&serv_addr,sizeof(serv_addr)) < 0) 
        error("ERROR connecting");
</pre>
The <code>connect</code> function is called by the client
to establish a connection to the server.  It takes three
arguments, the socket file descriptor, the address of the
host to which it wants to connect (including the port number), and
the size of this address.  This function returns 0 on success
and -1 if it fails. <a href="connect.txt"> <img src="redball.gif"> Click here </a> to
see the man page for connect.
<p>
Notice that the client needs to 
know the port number of the server, but it does not need to know
its own port number.  This is typically assigned by the system when
<code>connect</code> is called.
<hr>
<pre>
    printf("Please enter the message: ");
    bzero(buffer,256);
    fgets(buffer,255,stdin);
    n = write(sockfd,buffer,strlen(buffer));
    if (n < 0) 
         error("ERROR writing to socket");
    bzero(buffer,256);
    n = read(sockfd,buffer,255);
    if (n < 0) 
         error("ERROR reading from socket");
    printf("%s\n",buffer);
    return 0;
}
</pre>
The remaining code should be fairly clear.  It prompts the
user to enter a message, uses <code>fgets</code> to read the
message from stdin, writes the message to the socket, reads
the reply from the socket, and displays this reply on the screen.

<h2> Enhancements to the server code </h2>

The sample server code above has the limitation that it only handles
one connection, and then dies.  A "real world" server should run 
indefinitely and should have the capability of handling a number of
simultaneous connections, each in its own process.  This is typically
done by forking off a new process to handle each new connection.  
<p>
The
following code has a dummy function called <code>dostuff(int sockfd)</code>.
This function will handle the connection after it has been established
and provide whatever services the client requests.  As we saw above,
once a connection is established, both ends can use <code>read</code>
and <code>write</code> to send information to the other end, and the
details of the information passed back and forth do not concern us here.
To write a "real world" server, you would make essentially no changes
to the main() function, and all of the code which provided the service would
be in <code>dostuff()</code>.
<p>
To allow the server to handle multiple simultaneous connections,
we make the following changes to the code:
<ol>
<li> Put the accept statement and the following code in an infinite loop.
<li> After a connection is established, call <code>fork()</code> to
create a new process.  
<li> The child process will close <code>sockfd</code> and call
<code>dostuff</code>, passing the new socket file descriptor
as an argument.  When the two processes have completed their
conversation, as indicated by <code>dostuff()</code> returning,
this process simply exits.
<li> The parent process closes <code>newsockfd</code>.  Because
all of this code is in an infinite loop, it will return to the
accept statement to wait for the next connection. 
</ol> 
Here is the code.
<pre>
 while (1) {
     newsockfd = accept(sockfd, 
           (struct sockaddr *) &cli_addr, &clilen);
     if (newsockfd < 0) 
         error("ERROR on accept");
     pid = fork();
     if (pid < 0)
         error("ERROR on fork");
     if (pid == 0)  {
         close(sockfd);
         dostuff(newsockfd);
         exit(0);
     }
     else close(newsockfd);
 } /* end of while */
</pre>

<a href="server2.c"><img src="redball.gif"> Click here </a> for
a complete server program which includes this change.  This
will run with the program client.c.  

<h3> Alternative types of sockets </h3>

This example showed a stream socket in the Internet domain.  This is the
most common type of connection.  A second type of connection is a 
datagram socket.  You might want to use a datagram socket in cases
where there is only one message being sent from the client to the
server, and only one message being sent back.  
There are several differences between a datagram socket and
a stream socket.
<ol>
<li> Datagrams are unreliable,
which means that if a packet of information gets lost somewhere in the
Internet, the sender is not told (and of course the receiver does not
know about the existence of the message).  In contrast, with a stream socket, 
the underlying TCP protocol will detect that a message was lost because
it was not acknowledged, and it will be retransmitted without 
the process at either end knowing about this.
<li> Message boundaries are preserved in datagram sockets. 
If the sender sends a datagram of 100
bytes, the receiver must read all 100 bytes at once.  This can be
contrasted with a stream socket, where if the sender wrote a 100
byte message, the receiver could read it in two chunks of 50 bytes
or 100 chunks of one byte.  
<li> The communication is done using special system calls <code>
sendto()</code> and <code>receivefrom()</code> rather than the more
generic <code>read()</code> and <code>write()</code>.
<li> There is a lot less overhead associated with a datagram socket
because connections do not need to be established and broken down,
and packets do not need to be acknowledged.  This is why datagram
sockets are often used when the service to be provided is short,
such as a time-of-day service.
</ol>

<h3> Server code with a datagram socket </h4>

<img src="at_work.gif">


</body>





