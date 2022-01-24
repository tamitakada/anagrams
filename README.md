# Anagrams

**Group Members:** Amy Mai, Viana Lin, Tami Takada  
**Period:** 4  
**Proposal Statement:** We will make a two player anagrams game.

## Description
One user is going to run the server and wait for the other user to join. Once the other user joins, the game will start. Given 6 random letters, the player tries to make as many word combinations as possible. Each combination has a certain number of points based on difficulty, and these points are added together at the end of the 30 second timer. Whoever gets the most points wins the game. 

## Known Issues
- The result (You win/lose/tie) is printed with extra characters for some reason
- *****`main` branch does not work - please use `working` branch*****

## Instructions
1. Run `make`
2. Run `./server`
3. The game won't start until two players join, so run `./player` in two different terminals
4. Input words that use the randomly generated letters (each letter can only be used once)
5. When the timer ends, the game will be quit. If `fgets` is still running (i.e., you still see the `Input: ` line in the player program), press the enter key and the game will be finished
6. When the game is finished, run `make clean` to delete the word history files so you can run a new game

## Technical Design:  
- Files: Checking the word list, saving high scores
  - Finding Information About Files - Use `stat` to determine the file size and use a looping algorithm to read from the word file
- Sockets: Allowing the two players to share live scores
  - Use a TCP socket to establish a connection between the two players and share scores
- Memory Allocation: Track used words
  - Use `malloc` and `calloc` with a pointer to a string to track a list of words
- Signals: Quitting the game/error handling
  - Use `kill` and `sighandler` to handle different signals
- Timer (Timer library or forking parent and child process & wait(1))
- Sound effects (SDL/SDL_mixer library)
- UI: Modifying prints to make the game look nice

## Timeline:
- [ ] Files (Viana) 1/16 
- [ ] Sockets (Tami) 1/17 
- [ ] Memory Allocation (Tami) 1/17 
- [ ] Signals (Viana) 1/19 
- [ ] Timer (Amy) 1/20 
- [ ] Sound Effects (Amy) 1/20 
- [ ] UI (Amy) 1/20 
