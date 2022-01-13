# Anagrams

Group: Amy Mai, Viana Lin, Tami Takada  
Period 4  
Proposal Description:  
Two-player anagrams game.  
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
