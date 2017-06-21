# HexDumpPointerFollower/Checker
Designed for following pointers within Wii U memory dumps in Big Endian.

DISCUSS THE PROGRAM HERE: https://gbatemp.net/threads/hex-file-pointer-checker-and-follower.475000/

This is just a random program i made originally for myself, but i figured if anyone else wants it then why not..

It's main use was designed for following pointers within hex dumps and also checking lists of pointers against other Dumps.

In case you don't know, a pointer is just an address who's value is another address.

the format for this program, is given as follows:

This program assumes the dump file is located in the same directory as the .exe and expects the dump to be a ".bin" file.

You MUST start with the dereferencing of an address. (ie: [0xADDRESSS]  )
All adresses and offsets must start with a "0x" (without quotes) before their values.
All addresses and offsets must be in Hexidecimal.

offsets of 0 must still be added in as 0x0.
a single space between every operator (+ or -) must be given.
Obviously, the amount of  [ and ] brackets, must match.

Here is an example of a 4 stage pointer for BoTW (this points to link's current weapon's durability).

[[[[0x101C1D40] + 0x2580] + 0xB24] + 0x40] + 0x980.

Since initially making this, ive added a feature of reading an entire Text file full of pointers and checking to see if they reach a certain address or a certain Value within an address. This is great for checking if pointers work across dump files and is much much quicker than running a whole new pointer scan.

The program should HOPEFULLY catch any mistakes you make, but its not perfect.
