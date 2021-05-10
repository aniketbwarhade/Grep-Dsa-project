# Grep-Linux-Command
Repository contain 'Grep Command' In Linux as mini project of dataStructure subject implement in 'C' language

grep stands for global regular expression print (globally search for a regular expression and print matching lines).
grep is a  one of the most powerful and commonly used commands in Linux.

## How to run the project :

Download this files into a particular directory.
Open the terminal and cd to directory where project files are present.
Compile whole project by using 'make' command.
Run it by typing grep filename.
Try various options .


## grep options/flag that I have Implemented :

-r : recursively  search pattern in all file present in directory. 

-o : Print only the matched parts of a matching line

-v : It prints all the lines that do not match pattern

-e exp : It specifies expression and can be used multiple times.

-f file : It takes patterns from file, one per line.

-c : It prints no. of lines that will match given pattern

-h : It displays the matched lines, but do not display filenames

-H : It displays the matched lines alongwith filenames

-n : It displays the matched lines alongwith line no.

-i : It ignores the case while matching

-l : It displays list of filenames only

-w : It matches the whole word from the file

-m : it will search for only specified numberr of matches .(stop reading files after specified matched line).

-b : it will print byte offset within input file before matched line.(number of character present before matched line).

-A : Prints searched line and n lines after the result.

-B : Prints searched line and n line before the result.

-C : Prints searched line and n lines after and before the result.
