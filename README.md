# nonimatulaelcebe

One Friday afternoon, while daydreaming at my desk and wikijumping I somehow landed on a page about esolangs and read about brainfuck,  a programming language that uses only 8 commands. For God knows what reason my mind pointed me to the fact that the longest possible (maybe it's not, but it's used as a joke) sentence using only 2 letter words in a transylvanian dialect is "No ni ma tu la el ce be!" which translates to "Now look at him what he's drinking!".
The weekend project was settled.

As you can see from the code at this point, it's nothing more than a functional mess of duct-tape. But it works! At least, I tested it with one "Hello-world" style program and a simple loop. Haven't tested it with nested loops yet.

The correspondence of words to the brainfuck language is listed below:

Brainfuck | Equivalent C | nonimatulaelcebe
------------ | ------------- | -------------
'>' | ++ptr; | ma
'<' | --ptr; | la
'+' | ++*ptr; | tu
'-' | --*ptr; | ni
'.' | putchar(*ptr); | be
',' | *ptr=getchar(); | ce
'[' | while(*ptr){ | no
']' | } | el


**To use it** you must specify the name of the *.no* file as the first argument. Place the *.no* file in the same folder with the compiled interpreter (I used Visual Studioa Community 2017). The 2nd argument is optional and it specifies the DEBUG level (a number from 1 to 3), this was more a feature I implemented to help me understand where the program crapped on me.
- Debug Level 1: Print each line of code and the final assembled code array
- Debug Level 2: Level 1 + Print each pointer operation and its current value
- Debug Level 3: Level 1 + Memory dump of first 10 program memory cells(hardcoded for now) and a pause after each command.

# Syntax
Words **MUST** be separated by one space character. A maximum of 300 characters are allowed per line(hardcoded). All lines(including the last one) **MUST** be terminated in the '\n' new line character. If using Notepad++ you can switch on viewing of the symbols.
If not using valid command the interpreter will indicate the line of error.

# Examples

**Hello World** - This prints *No bine*, the hello world of Ardeal language
*see **test.no** file

**Loop test** - This increments the 2nd memory cell by 10 and then increments 5 times the first cell for 10 iterations. It then prints the first cell which is now is at value 50 - which is "2" in ASCII.
*see **loopTest.no** file

# Your code is a mess
I welcome any comments to improve what I've done. This is just a fun little project of mine. I learned for example the importance of the null-terminating character '\0' when using the family of *str* methods in C. I also lost 2 days without progress because I didn't realize that *strncpy()* does not add a null-terminating character :\.
