# Kaun-Banega-Crorepati-KBC-game
A command line interface game based on the popular TV show Kaun Banega Crorepati (KBC) written entirely in C



Description of how to run the code and observe the output (using a linux terminal) :
The file titled kbcgame can be run simply by the command in quotes "./kbcgame", however if "permission denied" is prompted on doing the above, The user shall simply run the command "chmod +x kbcgame" to grant permission to run the file, where the inverted commas enclose the command to be executed.

On running, the file will lead to the intro page of a KBC game showing key information about the game followed by prompting the user to press enter/return to continue. Once pressed, the gameplay instructions will be prompted, explaining the fairly simple command line UI, in which all the user has to do to answer is input the option index and press enter, where the lifelines are themselves given as two extra options, which can only be used once. following these gameplay instructions, the user is again prompted to press enter/return to continue, following which the game starts, with self explanatory prompts for any kind of input the user may enter, even a string or nothing but pressing enter.

The game ends when you answer a question wrong or get all correct, upon which a congratulatory message shall be received. Note that the developer is not liable to pay any money promised in the game, the game is just a work of fiction.

To compile and run the code, simply execute the command "gcc kbcgame.c -o outputfilename" followed by "./outputfilename" where outputfilename is any name the user compilig the code wishes to give to the executable file upon successful compilation. Since the code only uses standard libraries, doing the above shall suffice.

However note that, the code takes input from two files, "ques.txt" and "ques5050.txt", and hence, to ensure that the code compiles and runs alongside the executable, have all these files, the .c, the .exe and these two .txts from the shared zip folder in the same directory.


