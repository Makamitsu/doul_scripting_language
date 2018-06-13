# Doul scripting language

If you are a reasonable person please do not use this crap.

Memento:
```c++
START	= 0x00, //Start of a Doul
PUSH	= 0x01, //Push the next 16bit to the stack
JMPIF	= 0x02, //Jump to the next JMPZ if top NOT 0
JMPZ	= 0x03, //Destination for the last JMPIF
COMP	= 0x10, //Compare the 2 first 16bit value on the stack and push 0x01 is same and 0x00 otherwise
NOT	= 0x11, //Change top 16bit value of the pile to 0x01 if its 0x00 and to 0x00 for all the othervalue
AND	= 0x12, //Push 0x01 if the two top values are not 0x00, push 0x00 otherwise
OR	= 0x13, //Push 0x01 if at least one of the two top values are not 0x00, push 0x00 otherwise
XOR	= 0x14, //Push 0x01 if exactly one of the two top values are not 0x00, push 0x00 otherwise
GRT	= 0x15, //Push 0x01 if the top value is stricly greater that the second one, push 0x00 otherwise
ADD	= 0x20, //Push the result of the addition of the two top values
SUB	= 0x21, //Push the result of the substraction of the two top values
MUL	= 0x22, //Push the result of the multiplication of the two top values
DIV	= 0x23, //Push the result of the division of the two top values
GLIFE	= 0x30, //Push the life of the entity where its id is the top value, push negative one
SLIFE	= 0x40, //Set the life of the entity where its id is the second top value to the first top value
GDMG	= 0x31, //Push the dmg of the entity where its id is the top value, push negative one
SDMG	= 0x42, //Set the dmg of the entity where its id is the second top value to the first top value
END	= 0x0F //End of a Doul program
```
