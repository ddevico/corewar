# corewar

Corewar is a project for École 42, whose goal it is to create a game, played by coded champions in a virtual machine.

The project has three parts:

-Writing a parallel virtual machine where the game happens

-Writing a "champion" that plays the game against other champions

-Writing an assembler, that translates the champion to machine language


This repo is for the assembler, my part in the project.

Here are the rules (obs: constants like LABEL_CHARS, REG_NUMBER, etc, are defined in op.h):

VIII.1 Assembly language

• The assembly language is composed of one instruction per line.

• An instruction is composed of three elements: a label (optional) composed with a chain of characters amongst LABEL_CHARS followed by LABEL_CHAR; an opcode; and its parameters, separated by SEPARATOR_CHAR. A parameter can be of three di erent types:
    Registry: (r1 <–> rx with x = REG_NUMBER)
    Direct: The character DIRECT_CHAR followed by a numeric value or a label (preceded by LABEL_CHAR) which represents a direct value.
    Indirect: A value or a label (preceded by LABEL_CHAR), which represents a value located at the address of the parameter, relative to the PC of the current process.

• A label can have no instruction following it or be placed on a line before the in- struction it responds to.

• The caracter COMMENT_CHAR starts a comment.

• A champion will also have a name and a description, that should be on a line
following the markers NAME_CMD_STRING and COMMENT_CMD_STRING.

• All the addresses are related to PC and to IDX_MOD except for lld, lldi and lfork.

• The number of cycles for each instruction, their mnemonic representations, the associated amount and possible types of arguments are described in the op_tab array declared in op.c. The cycles are always consumed.

• All the other codes have no other action than to pass to the next one and lose a cycle.


 Algorithmic Project I corewar
 
• lfork: means long-fork, to be able to fork abut straw from a distance of 15 meters, exactly like with its opcode. Same as a fork without modulo in the address.

• sti: Opcode 11. Take a registry, and two indexes (potentially registries) add the two indexes, and use this result as an address where the value of the first parameter will be copied.

• fork: there is no argument’s coding byte, take an index, opcode 0x0c. Create a new process that will inherit the di erent states of its father, except its PC, which will be put at (PC + (1st parameter % IDX_MOD)).

• lld: Means long-load, so it’s opcode is obviously 13. It the same as ld, but without % IDX_MOD. Modify the carry.

• ld: Take a random argument and a registry. Load the value of the first argument in the registry. Its opcode is 10 in binary and it will change the carry.

• add: Opcode 4. Take three registries, add the first two, and place the result in the third, right before modifying the carry.

• zjmp: there’s never been, isn’t and will never be an argument’s coding byte behind this operation where the opcode is 9. It will take an index and jump to this address if the carry is 1.

• sub: Same as add, but with the opcode est 0b101, and uses a substraction.

• ldi: ldi, ldi, as per the name, does not imply to go swimming in chestnut cream, even if its code is 0x0a. Instead, it will use 2 indexes and 1 registry, adding the first two, treating that like an address, reading a value of a registry’s size and putting it on the third.

• or: This operation is an bit-to-bit OR, in the same spirit and principle of and, its opcode is obviously 7.

• st: take a registry and a registry or an indirect and store the value of the registry toward a second argument. Its opcode is 0x03. For example, st r1, 42 store the value of r1 at the address (PC + (42 % IDX_MOD))

• aff: The opcode is 10 in the hexadecimal. There is an argument’s coding byte, even if it’s a bit silly because there is only 1 argument that is a registry, which is a registry, and its content is interpreted by the character’s ASCII value to display on the standard output. The code is modulo 256.

• live: The instruction that allows a process to stay alive. It can also record that the player whose number is the argument is indeed alive. No argument’s coding byte, opcode 0x01. Oh and its only argument is on 4 bytes.

• xor: Acts like and with an exclusive OR. As you will have guessed, its opcode in octal is 10.

• lldi: Opcode 0x0e. Same as ldi, but does not apply any modulo to the addresses. It will however, modify the carry.

• and: Apply an & (bit-to-bit AND) over the first two arguments and store the result in a registry, which is the third argument. Opcode 0x06. Modifies the carry.


VIII.2 Encoding


Each instruction is encoded by:

• The instruction code (you find it in op_tab).

• The argument’s coding byte if appropriate. To be done as per the following examples:

    r2,23,%34 gives the coding byte 0b01111000, hence 0x78

    23,45,%34 gives the coding byte 0b11111000, hence 0xF8

    r1,r3,34 gives the coding byte 0b01011100, hence 0x5C


• The arguments, based on the following examples:

    r2,23,%34 gives the ACB 0x78 then 0x02 0x00 0x17 0x00 0x00 0x00 0x22

    23,45,%34 gives the ACB 0xF8 then 0x00 0x17 0x00 0x2d 0x00 0x00 0x00 0x22

Some important notes:

• The executable will always start with a header, defined in op.h by the header_t type.

• The virtual machine is BIG ENDIAN. Ask Google what it means.
