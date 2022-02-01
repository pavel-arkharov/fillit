# fillit
Project is part of 42 curriculum made during my studies in Hive Helsinki school in partnership with @kyyninen. 

Project aims at basic algorithmics. Searching for best possible solution among many options. 

### Input

Program takes a file as parameter, which contains a list of Tetriminos, or 4x4 text block-pieces consisting of four (tetro) filled-squares. 

![Screen Shot 2022-02-01 at 19 28 24](https://user-images.githubusercontent.com/7693793/152025426-c9457221-23a4-40e5-828d-82abbf72a87e.png)

Validity of input has to be checked, rules for valid tetriminos are following: 

* Input consists only of empty character '.', filled character '#' and newlines
* Tetriminos presented each on the block of 4 lines, each of which contains exactly 4 character and a newline
* There is a newline between tetriminos blocks
* Correct input consists of 1-26 tetriminos
* There are exactly four '#' in one tetrimino block
* Each '#' connected to at least one another '#' from top, down, left or right, but not diagonally



Here's some examples of non-valid input: 

![Screen Shot 2022-02-01 at 19 29 19](https://user-images.githubusercontent.com/7693793/152025392-48495296-a727-4593-8275-de9cc58011b3.png)


### Aim

Goal of the program to find the smallest possible square that will fit all the tetriminoes from the input file. In order to that we are not allowed to rotate, flip or modify the tetriminoes in any way. Resulting square has to be printed out with capital letters starting with 'A' assigned to each tetrimino. 

Example: 

![Screen Shot 2022-02-01 at 19 51 52](https://user-images.githubusercontent.com/7693793/152025342-0baa0ef8-3214-4c36-9c57-d5c9256cc8df.png)

Out of all possible solutions the program must select the one that places tetriminos to the most upper-left position. 

![Screen Shot 2022-02-01 at 19 55 57](https://user-images.githubusercontent.com/7693793/152025291-7a9716de-b811-4e4b-96a9-e3134a3e2006.png)


According to this rule, the correct answer is a). 

### Compilation 

Downlaod the repo and run the make command from the root folder. Sample input files can be found is /sample folder. 
