# Anagrams

Group: Amy Mai, Viana Lin, Tami Takada  
Period 4  
Proposal Description:  
Two-player anagrams game.  
Given 6 random letters, the player tries to make as many word combinations as possible. Each combination has a certain number of points based on difficulty, and these points are added together at the end of the 30 second timer. Whoever gets the most points wins the game. 

Components:  
- 1/20 (Amy) Sound effects (SDL/SDL_mixer library)
- 1/20 (Amy) UI - Modifying prints to make the game look nice
- 1/17 (Tami) Sockets - Allowing the two players to share live scores
  - Use a TCP socket to establish a connection between the two players and share scores
- 1/17 (Tami) Memory Allocation - Track used words
  - Use `malloc` and `calloc` with a pointer to a string to track a list of words
- 1/16 (Viana) Files - Checking the word list, saving high scores
  - Finding Information About Files - Use `stat` to determine the file size and use a looping algorithm to read from the word file
- 1/19 (Viana) Signals - Quitting the game/error handling
  - Use `kill` and `sighandler` to handle different signals
