# Language-Compiler
Description
Language Compiler is a simple C-based compiler for a custom Tiny Language (TL). This project includes lexical analysis, parsing, and basic symbol table management for the TL language. The compiler can process source code written in TL and performs basic checks like identifying keywords, operators, and handling symbol table entries.

Features
Lexical Analysis: Identification of keywords, operators, and tokens in TL code.
Symbol Table Management: Tracks identifiers and literals within the TL program.
Basic File Handling: Reads source code from a file and outputs the analysis results.
Error Handling: Basic error detection for invalid tokens and incomplete structures.
Prerequisites
GCC or any standard C compiler.
Standard C libraries: stdio.h, stdlib.h, string.h, ctype.h.
Installation
To install and run this project on your local machine:

Clone this repository:

bash
Copier le code
git clone https://github.com/yourusername/language-compiler.git
Navigate to the project directory:

bash
Copier le code
cd language-compiler
Compile the C code:

bash
Copier le code
gcc -o language_compiler language_compiler.c
Usage
To run the compiler, you need to pass a TL source file as input. Here's how you can use the program:

bash
./language_compiler input_file.tl
input_file.tl: This is a sample TL language source file that you want to compile.
Example
Here is an example of how to run the program with an input file:

bash
./language_compiler sample_program.tl
The program will read the input file and output the identified tokens and any errors it encounters.

Contribution
Feel free to submit issues or fork the repository and create pull requests. Contributions are welcome!

License
This project is licensed under the MIT License.
