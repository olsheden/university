# The task for my TCP server
Assignment:
Create a server for the automatic control of remote robots. The robots will connect to the server and it will guide them to the center of the coordinate system. For testing purposes, each robot starts at random coordinates and tries to reach the coordinate [0,0]. At the target coordinate, the robot must pick up a secret. Along the way to the target, robots may encounter obstacles that they must bypass. The server can navigate multiple robots simultaneously and implements a flawless communication protocol.

Detailed specification
Communication between the server and the robots is done using a fully textual protocol. Each command is terminated by a pair of special symbols "\a\b" (two characters '\a' and '\b'). The server must strictly adhere to the communication protocol but should account for imperfect robot firmwares (see Special Situations section).

Server messages:

Name Message Description
SERVER_CONFIRMATION <16-bit decimal number>\a\b Message with a confirmation code. It can contain a maximum of 5 digits and the terminating sequence \a\b.
SERVER_MOVE 102 MOVE\a\b Command to move forward one field
SERVER_TURN_LEFT 103 TURN LEFT\a\b Command to turn left
SERVER_TURN_RIGHT 104 TURN RIGHT\a\b Command to turn right
SERVER_PICK_UP 105 GET MESSAGE\a\b Command to pick up a message
SERVER_LOGOUT 106 LOGOUT\a\b Command to end the connection after successfully picking up the message
SERVER_KEY_REQUEST 107 KEY REQUEST\a\b Server's request for the Key ID for communication
SERVER_OK 200 OK\a\b Positive confirmation
SERVER_LOGIN_FAILED 300 LOGIN FAILED\a\b Authentication failed
SERVER_SYNTAX_ERROR 301 SYNTAX ERROR\a\b Message syntax error
SERVER_LOGIC_ERROR 302 LOGIC ERROR\a\b Message sent in the wrong situation
SERVER_KEY_OUT_OF_RANGE_ERROR 303 KEY OUT OF RANGE\a\b Key ID is out of the expected range

Client messages:

Name Message Description Maximum Length
CLIENT_USERNAME <user name>\a\b Message with the username. The name can be any sequence of characters except for the sequence \a\b and should never be identical to the content of the CLIENT_RECHARGING message. 20
CLIENT_KEY_ID <Key ID>\a\b Message containing the Key ID. It can only contain a three-digit integer. 5
CLIENT_CONFIRMATION <16-bit decimal number>\a\b Message with a confirmation code. It can contain a maximum of 5 digits and the terminating sequence \a\b. 7
CLIENT_OK OK <x> <y>\a\b Confirmation of a movement, where x and y are the robot's integer coordinates after executing the movement command. 12
CLIENT_RECHARGING RECHARGING\a\b The robot has started recharging and is no longer responding to messages. 12
CLIENT_FULL_POWER FULL POWER\a\b The robot has recharged and is ready to receive commands again. 12
CLIENT_MESSAGE <text>\a\b Text of the picked-up secret message. It can contain any characters except for the terminating sequence \a\b and should never be identical to the content of the CLIENT_RECHARGING message. 100

Time constants:

Name Value [s] Description
TIMEOUT 1 Server and client expect a response from the other party within this interval.
TIMEOUT_RECHARGING 5 Time interval within which the robot must complete recharging.

Authentication
Both the server and the client know five pairs of authentication keys (they are not public and private keys):

Key ID	Server Key	Client Key
0	    23019	      32037
1	    32037	      29295
2	    18789	      13603
3	    16443	      29533
4	    18189	      21952
Each robot starts communication by sending its username (message CLIENT_USERNAME). The username can be any sequence of 18 characters that does not contain the sequence "\a\b". In the next step, the server prompts the client to send the Key ID (message SERVER_KEY_REQUEST), which is the identifier of the key pair that the robot wants to use for authentication. The client responds with the message CLIENT_KEY_ID, in which it sends the Key ID. Then the server knows the correct key pair, so it can calculate the "hash" code from the username using the following formula:

Username: Mnau!

ASCII representation: 77 110 97 117 33

Resulting hash: ((77 + 110 + 97 + 117 + 33) * 1000) % 65536 = 40784
The resulting hash is a 16-bit decimal number. The server then adds the server key to the hash, so if the capacity of 16 bits is exceeded, the value simply overflows (here's an example for Key ID 0):

(40784 + 23019) % 65536 = 63803
The resulting server confirmation code is sent as text to the client in the message SERVER_CONFIRM. The client calculates the hash back from the received code and compares it with the expected hash that it calculated from the username itself. If they match, the client creates the client confirmation code. The calculation of the client confirmation code is similar to the server's, but the client key is used (here's an example for Key ID 0):

(40784 + 32037) % 65536 = 7285
The client confirmation code is sent to the server in the message CLIENT_CONFIRMATION, which calculates the hash back from it and compares it with the original hash of the username. If both values match, the server sends the message SERVER_OK; otherwise, it responds with SERVER_LOGIN_FAILED and terminates the connection. The entire sequence is shown in the following diagram:

Client Server
CLIENT_USERNAME --->
<--- SERVER_KEY_REQUEST
CLIENT_KEY_ID --->
<--- SERVER_CONFIRMATION
CLIENT_CONFIRMATION --->
<--- SERVER_OK
or
SERVER_LOGIN_FAILED
.
.
.
The server does not know the usernames in advance. Therefore, robots can choose any username, but they must know the set of client and server keys. The key pair ensures mutual authentication and prevents the authentication process from being compromised by simple eavesdropping.

Robot Movement to the Target
The robot can only move straight (SERVER_MOVE) and is capable of turning right (SERVER_TURN_RIGHT) or left (SERVER_TURN_LEFT) on the spot. After each movement command, it sends a confirmation (CLIENT_OK), which includes the current coordinates. The server is initially unaware of the robot's position. Therefore, the server must determine the robot's position (position and direction) solely from its responses. To prevent infinite wandering of the robot, each robot has a limited number of movements (only forward movement). The number of movements should be sufficient for a reasonable robot movement towards the target. Here's an example of communication: The server first moves the robot forward twice to detect its current state and then guides it towards the target coordinate [0,0].

Client                  Server
​------------------------------------------
                  .
                  .
                  .
                <---    SERVER_MOVE
                          nebo
                        SERVER_TURN_LEFT
                          nebo
                        SERVER_TURN_RIGHT
CLIENT_OK       --->
                <---    SERVER_MOVE
                          nebo
                        SERVER_TURN_LEFT
                          nebo
                        SERVER_TURN_RIGHT
CLIENT_OK       --->
                <---    SERVER_MOVE
                          nebo
                        SERVER_TURN_LEFT
                          nebo
                        SERVER_TURN_RIGHT
                  .
                  .
                  .
Just after authentication, the robot expects at least one motion command - SERVER_MOVE, SERVER_TURN_LEFT or SERVER_TURN_RIGHT! You cannot try to pick up the secret right away. There are many obstacles along the way that robots must overcome by detouring. The following rules apply to the obstacles:

An obstacle always occupies a single coordinate.
It is guaranteed that each obstacle has all eight surrounding coordinates free (i.e., it can always be easily bypassed).
It is guaranteed that an obstacle never occupies the coordinate [0,0].
If the robot hits an obstacle more than 20 times, it will be damaged and terminate the connection.
The obstacle is detected so that the robot is instructed to move forward (SERVER_MOVE), but the coordinates are not changed (the CLIENT_OK message contains the same coordinates as in the previous step). If the move is not executed, there is no subtraction from the number of remaining robot steps.

Retrieving the secret message
After the robot reaches the target coordinate [0,0], it tries to pick up the secret message (SERVER_PICK_UP message). If the robot is asked to pick up the message and is not at the target coordinate, the robot self-destructs and communication with the server is interrupted. When the robot attempts to pick up at the target coordinate, it responds with a CLIENT_MESSAGE message. The server must respond to this message with a SERVER_LOGOUT message. (It is guaranteed that the secret message never matches the CLIENT_RECHARGING message, if this message is received by the server after the pick up request it is always a recharge.) Then both the client and the server terminate the connection. Example of message pickup communication:

Client                  Server
​------------------------------------------
                  .
                  .
                  .
                <---    SERVER_PICK_UP
CLIENT_MESSAGE  --->
                <---    SERVER_LOGOUT
Recharge
Each of the robots has a limited power source. If it starts to run out of battery, it will notify the server and then start recharging itself from the solar panel. It does not respond to any messages while it is recharging. When it finishes, it informs the server and resumes where it left off before recharging. If the robot does not finish recharging within the TIMEOUT_RECHARGING interval, the server terminates the connection.

Client                    Server
​------------------------------------------
CLIENT_USERNAME   --->
                  <---    SERVER_CONFIRMATION
CLIENT_RECHARGING --->

      ...

CLIENT_FULL_POWER --->
CLIENT_OK         --->
                  <---    SERVER_OK
                            nebo
                          SERVER_LOGIN_FAILED
                    .
                    .
                    .
Další ukázka:

Client                  Server
​------------------------------------------
                    .
                    .
                    .
                  <---    SERVER_MOVE
CLIENT_OK         --->
CLIENT_RECHARGING --->

      ...

CLIENT_FULL_POWER --->
                  <---    SERVER_MOVE
CLIENT_OK         --->
                  .
                  .
                  .
Error situations
Some robots may have corrupted firmware and so may not communicate properly. The server should detect this inappropriate behavior and react correctly.

Authentication errors
If there is a Key ID in the CLIENT_KEY_ID message that is outside the expected range (i.e., a number that is not between 0-4), the server responds with a SERVER_KEY_OUT_OF_RANGE_ERROR error message and terminates the connection. For simplicity, even negative values are considered a number. If there is no number (e.g., letters) in the CLIENT_KEY_ID message, the server responds with a SERVER_SYNTAX_ERROR error.

If there is a numeric value (even a negative number) in the CLIENT_CONFIRMATION message that does not match the expected confirmation, the server sends a SERVER_LOGIN_FAILED message and terminates the connection. If it is not a purely numeric value at all, the server sends a SERVER_SYNTAX_ERROR message and terminates the connection.

Syntax error
The server always responds to a syntax error immediately after receiving the message in which it detected the error. The server sends the SERVER_SYNTAX_ERROR message to the robot and then must terminate the connection as soon as possible. Syntactically incorrect messages:

The incoming message is longer than the number of characters defined for each message (including the \a\b terminating characters). Message lengths are defined in the client message summary table.
The incoming message does not syntactically match any of the CLIENT_USERNAME, CLIENT_KEY_ID, CLIENT_CONFIRMATION, CLIENT_OK, CLIENT_RECHARGING, and CLIENT_FULL_POWER messages.
Each incoming message is tested for its maximum size and only CLIENT_CONFIRMATION, CLIENT_OK, CLIENT_RECHARGING and CLIENT_FULL_POWER messages are tested for their content (CLIENT_USERNAME and CLIENT_MESSAGE messages can contain anything).

Logic error
A logical error occurs only during charging - when the robot sends charging info (CLIENT_RECHARGING) and then sends any message other than CLIENT_FULL_POWER or if it sends a CLIENT_FULL_POWER message without first sending CLIENT_RECHARGING. The server responds to such situations by sending a SERVER_LOGIC_ERROR message and terminating the connection immediately.

Timeout
The protocol for communicating with robots contains two types of timeout:

TIMEOUT - timeout for communication. If the robot or server does not receive any communication from its counterpart (but not necessarily the entire message) during this timeout, it considers the connection lost and terminates it immediately.
TIMEOUT_RECHARGING - timeout for recharging the robot. After the server receives the CLIENT_RECHARGING message, the robot must send the CLIENT_FULL_POWER message within this time interval at the latest. If the robot fails to do so, the server must immediately terminate the connection.
Special situations
When communicating over a more complicated network infrastructure, two situations can occur:

The message may arrive split into several segments that are read sequentially from the socket. (This occurs because of segmentation and possible delay of some segments as they travel through the network.)
Messages sent in quick succession may arrive almost simultaneously. In a single read from the socket, they may both be read at the same time. (This happens when the server does not have time to read the first message from the buffer before the second message arrives.)
Using a direct connection between the server and the robots combined with powerful hardware, these situations cannot occur naturally, so they are artificially created by the tester. In some tests, the two situations are combined.

Any properly implemented server should be able to cope with this situation. Robot firmwares take this fact into account and even like to exploit it. If there is a situation in the protocol where messages from the robot have a predefined order, they are sent in that order at the same time. This allows probes to reduce their consumption and simplifies the implementation of the protocol (from their point of view).

Server optimization
The server optimizes the protocol by not waiting for the completion of a message that is obviously bad. For example, when prompted for authentication, the robot sends only the username portion of the message. For example, the server receives 22 characters of the username, but still has not received the \a\b termination sequence. Since the maximum message length is 20 characters, it is clear that the received message cannot be valid. The server therefore responds by not waiting for the rest of the message, but sends a SERVER_SYNTAX_ERROR message and terminates the connection. In principle, it should do the same when retrieving a secret message.

For the part of the communication in which the robot navigates to the destination coordinates, it expects three possible messages: CLIENT_OK, CLIENT_RECHARGING or CLIENT_FULL_POWER. If the server reads part of an incomplete message and that part is longer than the maximum length of these messages, it sends SERVER_SYNTAX_ERROR and terminates the connection. To aid in optimization, the maximum message size is listed for each message in the table.

Example of communication
C: "Oompa Loompa\a\b"
S: "107 KEY REQUEST\a\b"
C: "0\a\b"
S: "64907\a\b"
C: "8389\a\b"
S: "200 OK\a\b"
S: "102 MOVE\a\b"
C: "OK 0 0\a\b"
S: "102 MOVE\a\b"
C: "OK -1 0\a\b"
S: "104 TURN RIGHT\a\b"
C: "OK -1 0\a\b"
S: "104 TURN RIGHT\a\b"
C: "OK -1 0\a\b"
S: "102 MOVE\a\b"
C: "OK 0 0\a\b"
S: "105 GET MESSAGE\a\b"
C: "Tajny vzkaz.\a\b"
S: "106 LOGOUT\a\b"