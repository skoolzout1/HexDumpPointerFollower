# HexDumpPointerFollower
Designed for following pointers within Wii U memory dumps in Big Endian.


This is just a random program i made originally for myself, but i figured if anyone else wants it then why not..

It's main use was designed or following pointers within hex dumps.

In case you don't know, a pointer is just an address who's value is another address.

the format is given as such:

You MUST start with the dereferencing of an address.
All adresses and offsets must start with a "0x" (without quotes) before their values.
All addresses and offsets must be in Hexidecimal.

offsets of 0 must still be added in as 0x0.
a single space between every operator (+ or -) must be given.
Obviously, the amount of  [ and ] brackets, must match.

Here is an example of a 4 stage pointer for BoTW (this points to link's current weapon's durability).

[[[[0x101C1D40] + 0x2580] + 0xB24] + 0x40] + 0x980.

The program should HOPEFULLY catch any mistakes you make, but its no where near perfect.
