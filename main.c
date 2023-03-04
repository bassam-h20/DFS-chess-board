// I confirm that this assignment is my own work - P311414

/*
The program that was requested is based on a chessboard with 8 X 8 dimensions, in which a “knight” should start from the top right of the chessboard and land on each square only once. As mentioned, the movements of the knight should be similar of the knights L-shape movements in real-life chess. The program is meant to be developed using the depth-first search algorithm. The module tutor provided a code template for the coursework, which was a maze, however it was modified. The code had to be altered to fit the requirements of the knight’s movements and allow it to move freely as the template provided was a maze with walls in between squares. To begin with, the program allows the user to freely adjust the dimensions of the chessboard, and a variable is created to initialize the count of the steps taken by the knight. Many functions were created for the purpose of this program. Starting with a function initializing the chessboard, the next function focused on implementing the depth-first search algorithm by declaring the directions the knight could navigate in. The function includes a shuffle function embedded to randomize steps to be taken. Another function helps in instruction the knight to move in the correct steps in how it navigates inside the chessboard using rows and columns, moreover, it increments the step counter variable to be taken by the knight. The next function assists in making sure knight’s movements are inside the chessboard dimensions and not out of bounds, and check whether the square that is yet to be moved to has been visited or not. Another function was designed to print the results of the steps taken in the chessboard so the user can observe the route taken by the knight.
*/
  
#include <stdio.h>
#include <time.h>
#include <stdlib.h>

// delcaring size of chessboard 
#define SIZE 8

#define SROW 0
#define SCOL 0


int stepCount = 1; 

void generalInits(int* arr, int row, int col, int val);

void printMaze(int visited[SIZE][SIZE], int flag);

int checkOptions(int row, int col, int maze[SIZE][SIZE], int options[8]);

void shuffle(int arr[], int arr2[], int n);

int allVisited(int visited[SIZE][SIZE]);

void DFS(int visited[SIZE][SIZE], int row, int col);

void movementSolver(int opt, int visited[SIZE][SIZE], int *srow, int *scol);



int main(void) 
{
  srand(time(NULL));
  
  int visitedCell[SIZE][SIZE];
  
  generalInits(visitedCell, SIZE, SIZE, 0);

  visitedCell[SROW][SCOL] = stepCount;
  
  printMaze(visitedCell, 1);
  
  DFS(visitedCell, SROW, SCOL);
  
  printMaze(visitedCell, 1);

  
  return 0;
}
// Chessboard initiallizer, prints chessboard in 0's
void generalInits(int* arr, int row, int col, int val)
{
  for(int i = 0; i < row; i++) 
  {
    for(int j = 0; j < col; j++)
    {
      arr[i*col+j] = val;
    }
  }
  return;
}
//Depth-first search algorithm function
void DFS(int visited[SIZE][SIZE], int row, int col)
{
  int directions[8] = {0, 1, 2, 3, 4, 5 ,6, 7}; 
  // For the 8 directions the knight can go
  int options[8] = {0, 0, 0, 0, 0, 0, 0, 0};
  int count = checkOptions(row, col, visited, options);
  int opt = -1;

  while(!allVisited(visited))
  {
    for(int i = 0; i < 8; i++)
    {
      directions[i] = i;
      options[i] = 0;  
    }
    
    count = checkOptions(row, col, visited, options);
    opt = -1;

    if(count > 1)
    {
      // shuffling two arrays randomly
      shuffle(options, directions, 8);
  
      for(int i = 0; i < 8; i++) // for every option
      {
        if(options[i])
        {
          opt = directions[i];
          movementSolver(opt, visited, &row, &col);
          
          DFS(visited, row, col);
          break; // an option was picked, move on by breaking the for loop
        }
      }
    }
    else if(count == 1)
    {
      for(int i = 0; i < 8; i++)
      {
        if(options[i])
        {
          opt = directions[i];;
          break;
        }
      }
      movementSolver(opt, visited, &row, &col);

      DFS(visited, row, col);
    }
    else
    {
      return; // returning due to not having any options
    }
  }
}

//Function for directions of movement
void movementSolver(int opt, int visited[SIZE][SIZE], int *srow, int *scol)
{
  int row = *srow;
  int col = *scol;

  
  if(opt==0)//Movement/Direction 3 
  {
    row = row + (opt - 1); //row - 1
    col = col + (opt - 2); //column -2
    stepCount++;
    visited[row][col] = stepCount;
  }

  else if(opt==1) //Movement/Direction 1
  {
    row = row + (opt - 3); //row - 2
    col = col + (opt - 2); //column - 1
    stepCount++;
    visited[row][col] = stepCount;
  }

  else if(opt==2) //Movement/Direction 5
  {
    row = row + (opt - 1); // row + 1
    col = col + (opt - 4); // column - 2
    stepCount++; 
    visited[row][col] = stepCount;
  }

  else if(opt==3) //Movement/Direction 2
  {
    row = row + (opt - 5); // row - 2
    col = col + (opt - 2);// column + 1
    stepCount++;
    visited[row][col] = stepCount;
  }

  else if(opt==4) //Movement/Direction 4
  {
    row = row + (opt - 5); // row - 1
    col = col + (opt - 2); // column +2
    stepCount++;    
    visited[row][col] = stepCount;
  }
    
  else if(opt==5) //Movement/Direction 7
  {
    row = row + (opt - 3); // row + 2
    col = col + (opt - 6); // column - 1
    stepCount++;
    visited[row][col] = stepCount;
  }

  else if(opt==6) //Movement/Direction 6
  {
    row = row + (opt - 5); // row - 1
    col = col + (opt - 4); // column + 2
    stepCount++;
    visited[row][col] = stepCount;
  }

  else if(opt==7) //Movement/Direction 8
  {
    row = row + (opt - 5); 
    col = col + (opt - 6);
    stepCount++;
    visited[row][col] = stepCount;
  }
  

  *srow = row;
  *scol = col;

  return;
}

//function for checking if knight movements are correct and inside dimensions
int checkOptions(int row, int col, int maze[SIZE][SIZE], int options[8])
{
  int count = 0;

  // going through every cell you can go from current position
  
  for(int i = -2; i <= 2; i++) // rows range from -2 to +2
  {
    for(int j = -2; j <= 2; j++) // columns range from -2 to +2
    {

      
      if(i%2 == 0 && i != 0) //  Direction/Movement 1 and 7
      { // movement by -2 or 2 rows and -1 column
        if(j == -1)
        { // checking if the knight's location is within bounds
          if((row + i) >= 0 && (col + j) >= 0)
          {
            if((row + i) < SIZE && (col + j) < SIZE) 
            {
             if(maze[row+i][col + j] == 0)
             {  
               count++;
               options[i + 3]++; // option (-2 or 2) to (1 or 5) 
              }
            }  
          }
        }
      }


      
        if(i%2 == 0 && i != 0) //  Direction/Movement 2 and 8
      { // movement by -2 or 2 rows and +1 column
        if(j == 1)
        { // checking if the knight's location is within bounds
          if((row + i) >= 0 && (col + j) >= 0)
          {
            if((row + i) < SIZE && (col + j) < SIZE)
            {
             if(maze[row+i][col + j] == 0)
             {  
               count++;
               options[i + 5]++; // option (-2 or 2) to (3 or 7) 
              }
            }  
          }
        }
      }


      
       if(j%2 == 0 && j != 0) // Direction/Movement 3 and 4
      { // movement by -2 or +2 columns and -1 row
        if(i == -1)
        { // checking if the knight's location is within bounds
          if((row + i) >= 0 && (col + j) >= 0)
          {
            if((row + i) < SIZE && (col + j) < SIZE)
              {
                if(maze[row+i][col + j] == 0)
               {  
                count++;
                options[j + 2]++; // option (-2 or 2) to (0 or 4) 
               }
              }  
          }
        }
      }


      
       if(j%2 == 0 && j != 0) // Direction/Movement 5 and 6
      { // movement by -2 or + 2 columns and +1 row
        if(i == 1)
        { // checking if the knight's location is within bounds
          if((row + i) >= 0 && (col + j) >= 0)
          {
            if((row + i) < SIZE && (col + j) < SIZE) 
              {
                if(maze[row+i][col + j] == 0)
               {  
                count++;
                options[j + 4]++; // option (-2 or 2) to (2 or 6) 
               }
              }  
          }
        }
      }


      
    }
  }
  return count;
}

//prints maze and step numbers
void printMaze(int visited[SIZE][SIZE], int flag)

{ 
  for(int i = 0; i < 2 * SIZE + 1; i++)
  {
    for(int j = 0;j < 2 * SIZE + 1; j++)
    {
      if(flag) //identifies whether numbers should be printed to cells
      { 
        
        if(i%2 == 1 && j%2== 1)
        {
          int value = visited[(i-1)/2][(j-1)/2];
          if(value >= 100)
          {
            printf("%d", value);
          }
          else
          {
            printf("   ");
            printf("%d", value);
          }
          if(value < 10)
          {
            printf(" ");
          }
        }
      }
      else
      {
        if(i%2 == 1 && j%2== 1)
        {
          printf("   ");
        }
      }
    
    }
    printf("\n");
  } 
  printf("\n");
    
}
    


int allVisited(int visited[SIZE][SIZE])
{
  for(int i = 0; i < SIZE; i++)
  {
    for(int j = 0; j < SIZE; j++)
    {
      if(visited[i][j] == 0) //if one cell is not visited
      {
        return 0; 
      }
    }
  }
  return 1;
}

void shuffle(int arr[], int arr2[], int n)
{
  if (n > 1) 
  {
    for (int i = 0; i < n - 1; i++) 
    {
      int j = i + rand() / (RAND_MAX / (n - i) + 1);
      int t = arr[j];
      arr[j] = arr[i];
      arr[i] = t;
      // repeating process for second array
      t = arr2[j];
      arr2[j] = arr2[i];
      arr2[i] = t;
    }
  }
  return;
}