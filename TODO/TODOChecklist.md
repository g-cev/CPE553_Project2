# TODO Folder
- [x] Share contact info
- [ ] Fill out group expectations .docx
- [ ] Upload the semi-deadlines somewhere on github
- [x] Figure out to pull repo onto personal computer
- [ ] Delegate tasks in task breakdown

## Task Breakdown

### Data Storage

![Class hierarchy](https://cdn.discordapp.com/attachments/185554058436804609/1175187612584132748/image.png?ex=656a51c0&is=6557dcc0&hm=992e48ae99f00e21fe45d3a2ecdf077af2abdd5821957043e4de0900c5a29cc5&)

1. FieldInhabitant.h, FieldInhabitant.cpp

2. Veggie.h, Veggie.cpp

3. Creature.h, Creature.cpp

4. Captain.h, Captain.cpp

5. Rabbit.h, Rabbit.cpp

### Game Engine

1. GameEngine.h, GameEngine.cpp

--Functions within GameEngine.cpp--
- [x] initializeGame()
    - [x] a. initVeggies()
    - [ ] b. initCaptain() - NEEDS TESTING
    - [x] c. initRabbits()
- [x] remainingVeggies()
- [ ] intro() - PARTIALLY DONE
- [ ] printField() - PARTIALLY DONE
- [x] getScore()
- [x] moveRabbits()
- [ ] moveCaptain() - NEEDS TESTING
    - [ ] a. moveCptVertical() - NEEDS TESTING
    - [ ] b. moveCptHorizontal() - NEEDS TESTING
- [x] gameOver()


### Main

1. [x] main.cpp


## Assigned Files
#### Genesis
- Data Storage: completed setting up classes 11/19, save for some notes/questions 
- Completed: initVeggies(), remainingVeggies(), main.cpp, 11/25
- Working on: printField(), potentially bonus?

#### Robert
- Completed initial work on initCaptain(). Needs Testing.
- Completed initial work on moveCaptain(). Needs Testing.
- Completed initial work on moveCptHorizontal(). Needs Testing.
- Completed initial work on moveCptVertical(). Needs Testing.

### Praveena
- Completed working on moveRabbits() in GameEngine.cpp-11/29
- Completed working on initRabbits() in GameEngine.cpp-11/29
- Made changes in printField() function on rabbits/captain-11/29
- Made changes for getScore(),gameOver() function in GameEngine.h & GameEngine.cpp-11/30
- Adding documentation tags and comments to the code.
- Debugging captain code,movesnake() in GameEngine.cpp
- Do not remove destructor if we remove we get memory leaks[FYI].
- Did changes in initsnake(),Captain.cpp(removeveggie())[FYI]

