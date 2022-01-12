# tetris

Group: Amy Mai, Viana Lin, Tami Takada  
Period 4  
Proposal Description: Tetris game  
Components:  
- (Amy) animation
  - sdl library
- (Viana) files to save scores
- (Tami) pipes for two player - we will allow two player 
Tetris games so players can send lines to each other. 
The pipe will facilitate communication between players.
- (Viana) signals - we will use signals to show that a game
has ended and to allow for scores to be saved before
ending.
- (Tami) memory allocation for tile placement - we have to
remember where tiles are placed, so we will use memory (heap memory with malloc/calloc)
