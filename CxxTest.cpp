#include <NonBlockingGame.h>
#include <iostream>
#include <time.h>
#include <vector>


//
//  The purpose of this assignment is to learn to 1. The classic game of Snake.
//  Move a "snake" (line of sprites) along a 2D grid attempting to run over a
//  randomly placed object to help it grow. 2. If it runs into itself the game is over
//  and the player has lost. 3. The object of the game is to make the snake as big as possible.
//
using namespace bridges::game;
using namespace std;

// this keeps a list of elements (squares) that represents the snake object
// linked list since it can grow as the game progresses
class Block {
  public:
    Block *next = nullptr;
    int x;
    int y;
    Block() {
      x = 0;
      y = 0;
    }
    Block(int x, int y) {
      this->x = x;
      this->y = y;
    }
};
class Queue {
private:
  Block* front= nullptr; // head 
  Block* back = nullptr; // back
  int size = 0;
public:
  bool enqueue(int x, int y); 
  bool dequeue();
  bool isEmpty();
  int getLength();
  Block peekFront();
  Block peekBack();
~Queue(){
  while(size > 0){
    dequeue();
  }
  front = nullptr;
  back = nullptr;
}
};


bool Queue::enqueue(int x, int y){
  Block* newBlock = new Block(x,y);
  //case 0: no memory
  if(!newBlock){
    return false;
  }
  //case 1: empty list
  if(front == nullptr){
    front = newBlock;
    back = newBlock;
  
  }
  else{
    back->next = newBlock;
    back = newBlock;  
  }
  size++;
  return true;
}
bool Queue::dequeue(){
  //case 0: empty list
  if(front == nullptr && size == 0){
    return false;
  }
  //case 1: one eleent
  if(front->next == nullptr && size == 1){
    delete front; 
    front = nullptr;
    back = nullptr;
    size = 0;
    return true;
  }
  //case 2 : more than one element
  else
  {
    Block* temp = front;
    front = front->next;
    delete temp;
    size--;
    return true;
  }
}
int Queue::getLength(){
  return size;
}

bool Queue::isEmpty(){
  if(front == nullptr && size == 0){
    return true;
  }
  else
  return false;
}

Block Queue::peekFront(){
  return *front; //if no pointer it would return the address
}

Block Queue::peekBack(){
  return *back;
}

  // keep an element to represent something the snake would consume to grow,
  // for instance, an apple and keep track of the snake head (both will be elements of
  // type Block

  // keep an element to represent something the snake would consume to grow,
  // for instance, an apple and keep track of the snake head (both will be elements of
  // type Block
struct Game : public NonBlockingGame { // derive class from class NonBlocking game
  
  long frameTime;
  long nextFrameTime;
  int frame = 0;

  Queue Snake;
  int rows = 30;
  int columns = 30;

  //"Up", "Down", "Right", "Left"
  string Direction;

  Block Apple;
  // create the game grid
  Game(int assignID, std::string username, std::string apikey)
    : NonBlockingGame (500, username, apikey, 30, 30) {
      //creates gameboard of 30x30 in assignment 500
  }

  virtual void initialize() override { // only runs once. basically a loading screen for a game
    srand(time(NULL));
    // create the snake of some number of elements,
    // perform all initializations, place the apple
    Snake.enqueue(rows/2, columns/2);//enqueue the snake in the center position of the board
    plantApple();
    Direction = "Stationary"; // starting direction of snake is Stationary 
    paint();
  }

void handleInput() {
    // Use the 4 arrow keys to move the snake in a particular direction
    if(keyW()){
      if (Direction != "Down")
        Direction = "Up";
    }
    if(keyA()){
      if(Direction != "Right")
        Direction = "Left";
    }
    if(keyD()){
      if(Direction != "Left")
        Direction = "Right";
    }
    if(keyS()){
      if(Direction != "Up")
        Direction = "Down";
    }
  }

//MULTIPle elements: snake touches queue 
  /* CURRENT FRAME
    original snake: (2,0), (1,0), (0,0), (0,1), (0,2)
 
     apple is at (3,0)
    direction is down. 


     **NEXT FRAME
      -apple is at (3,0)
      -newHead (3,0)
      -original snake: (2,0), (1,0), (0,0), (0,1), (0,2)

     what we want snake: (3,0), (2,0), (1,0), (0,0), (0,1), (0,2)
 
1) if newHead = apple run this
apple is at (3,0) = newHead (3,0)

2)set up a tempSnake and enqueue all original Snake elements
tempSnake: (2,0), (1,0), (0,0), (0,1), (0,2)
original snake: 

3)Enqueue the newHead(apple) as a new head for original snake
tempSnake: (2,0), (1,0), (0,0), (0,1), (0,2)
original snake: (3,0)

4)then just enqueue all the temp snake back
snake: (3,0), (2,0), (1,0), (0,0), (0,1), (0,2)

Queue TempSnake;

//step 1
if(newHead.x == Apple.x && newHead.y == Apple.y){

//step 2
  While(Snake.getLength()>0){
  TempSnake.enqueue(Snake.peekFront().x, Snake.peekFront().y);
  Snake.dequeue();
}
//step 3 enqueue the newHead(apple) into the original snake
Snake.enqueue(newHead.x, newHead.y);
//step 4 enqueue all tempSnake into original snake
while(TempSnake.getLength()> 0){
Snake.enqueue(TempSnake.peekFront().x, TempSnake.peekFront().y);
TempSnake.dequeue();
}
}


*/


/*---------------------------------------------------------------
1) we have the queue
      (2,0), (1,0), (0,0), (0,1), (0,2)

2)(Calculate the new head)we want a new head for the queue (based on the direction) so if it was going down then the new head would be the old head but 1 X further down
     new head (3,0)
  
3) Dequeue the original snake into another temp snake but leave the last element.
original snake (0,2)
temp snake = (2,0), (1,0), (0,0), (0,1)

4) then dequeue that last element completely out
original snake 
temp snake = (2,0), (1,0), (0,0), (0,1)

5) then we enqueue the new head into the new original snake 
original snake (3,0)
temp snake = (2,0), (1,0), (0,0), (0,1)

6) and then enqueue the temp snake into snake.
original snake (3,0), (2,0), (1,0), (0,0), (0,1)
*/

  // update snake position
void updatePosition() {

Block newHead(Snake.peekFront().x, Snake.peekFront().y);
      if(Direction == "Up"){
        int newX = Snake.peekFront().x -1;
        if(newX < 0){
          newX = rows-1;
        }
        newHead = Block(newX, Snake.peekFront().y);
      }

      if(Direction == "Down"){
        int newX = Snake.peekFront().x +1;
        if(newX > rows-1){
          newX = 0;
        }
        newHead = Block(newX, Snake.peekFront().y);
      }

      if(Direction == "Left"){
        int newY = Snake.peekFront().y -1;
        if(newY < 0){
          newY = columns-1;
        }
        newHead = Block(Snake.peekFront().x, newY);
      }

      if(Direction == "Right"){
        int newY = Snake.peekFront().y + 1;
        if(newY > columns -1){
           newY = 0;
         }
        newHead = Block(Snake.peekFront().x, newY);
      }
  //------------------------------------------------------------------------------------
  //MULTIPLE ELEMENT SNAKE (not touching apple, just moving around freely)
  if (!(newHead.x == Apple.x && newHead.y == Apple.y)) // if snake is not touching apple
  {
    Queue TempSnake;
    int length = Snake.getLength();
    for(int i = 0; i < length-1; i++)
    {
      TempSnake.enqueue(Snake.peekFront().x, Snake.peekFront().y);
      Snake.dequeue();
    }
    
    //step 2
    // now we have all elements except last of the original snake into the temp snake, so dequeue snake to delete last element
    Snake.dequeue();
    
    //step 3
    //add new head to the original snake
    Snake.enqueue(newHead.x, newHead.y);
    
    //step 4 add all temp snake elements
    while(TempSnake.getLength()> 0)
    {
      Snake.enqueue(TempSnake.peekFront().x, TempSnake.peekFront().y);
      TempSnake.dequeue();
    }
  }
  else if(newHead.x == Apple.x && newHead.y == Apple.y)
  {
    //-----------------------------------------------------------------------
    ///Now lets touch the apple and increasie size 
    Queue TempSnake1;

    //step 1
    //step 2
      while(Snake.getLength()>0)
      {
        TempSnake1.enqueue(Snake.peekFront().x, Snake.peekFront().y);
        Snake.dequeue();
      }
      //step 3 enqueue the newHead(apple) into the original snake
      Snake.enqueue(newHead.x, newHead.y);
      //step 4 enqueue all tempSnake into original snake
      while(TempSnake1.getLength()> 0)
      {
        Snake.enqueue(TempSnake1.peekFront().x, TempSnake1.peekFront().y);
        TempSnake1.dequeue();
      }
    plantApple();
  }
  //----------------------------
  
}

  

bool SnakeIsTouchingApple()
{
  bool result = false;
  Queue SnakeTemp; //elements of the original snake that were moved.
  Queue SnakeLeftOver; // elements of the original snake that were not moved.
  while(Snake.getLength() > 0)
  {
    SnakeTemp.enqueue(Snake.peekFront().x, Snake.peekFront().y);
    Snake.dequeue();
    if(SnakeTemp.peekBack().x == Apple.x && SnakeTemp.peekBack().y == Apple.y) 
    {
      
      result = true;
    }
  }
  while(SnakeTemp.getLength() > 0){
      Snake.enqueue(SnakeTemp.peekFront().x, SnakeTemp.peekFront().y);
      SnakeTemp.dequeue();
    }
  
  return result;
} 

  // locate apple at new position
void plantApple() {
srand(time(NULL));
  do
  {
     int i, j;
     i = rand()%rows; 
     j = rand()%columns;
     Apple = Block(i,j);
  }
  while (SnakeIsTouchingApple());
  
 //    // randomly position the apple, taking care to ensure that it doesnt
 //    // intersect with the snake position.
  }

  // check if snake has found the apple
void detectApple() 
{
    // if apple is found, snake consumes it and update the board and plant
    // a new apple on the board.
  //enqueue the Snake with an extra block, with x and y depending on the direction snake is moving
  cout << "hi " << endl;
   if(SnakeIsTouchingApple())
   {
     plantApple();
     if(Direction == "Up")
     {
       Snake.enqueue(Snake.peekFront().x+1, Snake.peekFront().y); //x added by 1 because it is added below the snake head which is going up
     }
     if(Direction == "Down"){
       Snake.enqueue(Snake.peekFront().x - 1, Snake.peekFront().y);
     }
     if(Direction == "Left"){
       Snake.enqueue(Snake.peekFront().x, Snake.peekFront().y +1);
     }
     if(Direction == "Right"){
       Snake.enqueue(Snake.peekFront().x, Snake.peekFront().y-1);
     }
   }
  }


  // check if snake ate itself! Yuk!

  //1 get the snake head. dequeue and store it in a temp variable
 //Loop through the snake by dequeuing everything to a temp snake
 //Check if the x and y of each element is equal to the x and y of snake head
 //if they're equal, result = true;
 //after looping, store everything back into the snake
//return result
  bool detectDeath() {
     bool result = false;
    Queue SnakeHead; //For the Snake Head
    Queue TempSnake; //For the Snake body. Compare Snake's body with Snake Head to detect death
    Queue TempSnake2; //If Snake's body doesnt equal head, store those elements into this temp queue so it doesnt get lost forever when we dequeue the TempSnake. Then when we rebuild the Snake, we still have those elements saved and can enqueue it back.
    //store snake head in a queue 
    SnakeHead.enqueue(Snake.peekFront().x, Snake.peekFront().y);
    Snake.dequeue();
    //store snake body in a diff queue
    while(Snake.getLength() >0){
      TempSnake.enqueue(Snake.peekFront().x, Snake.peekFront().y);
      Snake.dequeue();
    
    }
    //compare the front of the tempSnake with SnakeHEad, if they are equal that means Snake ate itself and died
    while(TempSnake.getLength() >0){
      if((TempSnake.peekFront().x == SnakeHead.peekFront().x)&& (TempSnake.peekFront().y == SnakeHead.peekFront().y )){ // snake ate itself (snake head = body)
        result = true;
      }
      else
        TempSnake2.enqueue(TempSnake.peekFront().x, TempSnake.peekFront().y);
        TempSnake.dequeue();
      }
//now put all elements back in Snake
    //enqueue the snake head back
  Snake.enqueue(SnakeHead.peekFront().x, SnakeHead.peekFront().y);
  SnakeHead.dequeue();
//then the body
  while(TempSnake2.getLength() > 0 ){
    Snake.enqueue(TempSnake2.peekFront().x, TempSnake2.peekFront().y);
    TempSnake2.dequeue();
  }
  while(TempSnake.getLength()  > 0){
    Snake.enqueue(TempSnake.peekFront().x, TempSnake.peekFront().y);
    TempSnake.dequeue();
  }
return result;
    }

  // redraw
  void paint() { // draw the board

    // draw the board, the apple and the snake
    // make sure to choose colors so that snake and apple are clearly visible.
		for(int i = 0; i < getBoardHeight(); i++) // rows
			for (int j = 0; j < getBoardWidth(); j++){ // collumns
         if(i%2 != 0 && j%2 != 0){
           setBGColor(i, j, NamedColor::whitesmoke);
         }
         else
           setBGColor(i, j, NamedColor::ivory);
         if(i%2 == 0 && j%2 == 0){
           setBGColor(i, j, NamedColor::whitesmoke);
         }
       }

      //paint the apple
      setBGColor(Apple.x, Apple.y, NamedColor::red);
    
      //paint entire snake
      Queue SnakeTemp;
    
      


    while(Snake.getLength() > 0)
      {
        setBGColor(Snake.peekFront().x, Snake.peekFront().y, NamedColor::blue);
        SnakeTemp.enqueue(Snake.peekFront().x, Snake.peekFront().y);
        Snake.dequeue();
      }
  
      while (SnakeTemp.getLength() > 0)
      {
        Snake.enqueue(SnakeTemp.peekFront().x, SnakeTemp.peekFront().y);
        SnakeTemp.dequeue();
      }
      setBGColor(Snake.peekFront().x, Snake.peekFront().y, NamedColor::black); // snake head == black 
  }

  // handle input, check if apple was detected, update position, redraw,
  // detect if snake ate itself. To adjust speed of game and make it playable,
  // keep the frame counter
  // and perform updates every n frames or so.


  virtual void gameLoop() override {
    int score = Snake.getLength() -1;
     frame++;
    handleInput();
    updatePosition();
    paint();
     frame = 0;
    
  
  if (detectDeath()){ // game over 
  cout << "u died loser " << endl;
  cout << "Your Score: " << score << endl;
     quit();
  }
    
    }
    

};

// Initialize your game
// Call your game class with your assignment id, username, and api key
int main(int argc, char** argv) {
  Game g(500, "robertle123", "1290081228771");
  g.start();
  }



