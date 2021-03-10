# C++ Memory Management

Most people's dislike of c++ probably comes from the fact that when you write in cpp, you have to manage memory yourself. While this can be frustrating at times (hello there, `segfault` and `bad_alloc`:) it is actually immensely powerful and interesting.

So let's get right to it:)

## Memory Addresses and Hexadecimal Numbers

Computers store information in bytes which are themselves comprised of 8 bits. A bit can either be 0 or 1 which gives rise to the base 2 or binary system used a lot with computers. So far so trivial :) While this system might seem obvious in hindsight, in the beginning engineers tried to use the classic base 10, also called decimal system. However, as it turned out, representing 10 individual symbols is quite difficult in the presence of noise so John Atansasoff proposed the base 2, or binary system. This system turned out to be more robust and became the standard in the computing world (Source: [udacity/cpp-nanodegree](https://classroom.udacity.com/nanodegrees/nd213/parts/789a1625-9b09-4615-9210-ddbc12e9247b/modules/5d2b96c2-52eb-4264-b387-da31d90b1e1f/lessons/ec63b3b7-590d-43ef-9492-66f6f23d9988/concepts/e6830afc-c398-4af8-9221-f2675293f46f))

All computer information is stored in binary form. One of the earliest mappings or encoding schemes for characters is called ASCII (American Standard Code for Information Interchange). 

The ASCII table represents each charachter as an 8 bit number:
![ascii-table](ascii-table-black.png)

Thankfully, nowadays most programs work with UTF-8 encoding, which allows a much richer set of characters to be represented.

In the table you can also see a column called 'Hex'. This column contains the hexadecimal representation of a given character, i.e. wrt. base 16.

Why do we need yet another number system?

1. Better readability than binary
2. Information density (you can store any number from 0 to 255 since 16^2 = 256)
3. Since 1 byte is equal to 8 bits (2^8=256), it is natural to represent a byte with a hex number.

## Analysing Memory with a Debugger