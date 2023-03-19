A list of operations and commands used - 

    -cd - changes the current directory to the one present; if not given one it simply shows the current one

    -clr - clears the screen

    -dir - lists the contents of a directory

    -environ - lists all environment settings 

    -echo - repeats what is typed after echo

    -help - display the user manual 

    -pause - stops shell until enter is pressed

    -quit - leaves the shell


    Batch mode allows to take its input from the command line from a file, only when the shell is called on with a command line argument such as - ./myshell myfile.sh


    I/O redirection is simply how the program runs and stores its input and output according to files if specified, such as -  shell vs2 vs2 < inputfile > outputfile. Here vs1 and vs2 are replaced by input and output done using internal commands such as dir, environ, echo and help
    > - if the output file is already created 
    >> - if the output file is not created already
    with the use of I/O redirection, we can allow input and output to be stored in files.

    Description of the process concept and the differences between background and foreground execution (5 marks)

    references used - 

    https://makefiletutorial.com/

    code from Ian G Graham