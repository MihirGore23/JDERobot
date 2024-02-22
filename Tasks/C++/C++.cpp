#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <queue>
#include <stack>
#include <algorithm>

#define ADD_TO_VECTOR(X) push_back(X)
#define MAKE_PAIR make_pair
#define COORD_PAIR pair<int,int>

using namespace std;

// Define a structure PathInfo_ to store starting coordinates and length of the path
typedef struct PathInfo_ {
  int starting_row, starting_col;
  int path_length;
} PathInfo;

// Compare function for std::sort function later used
bool comparePaths(PathInfo a, PathInfo b) { return a.path_length < b.path_length; }

// Depth First Search
void depthFirstSearch(int x, int y, vector<string> &map, vector<vector<int> > &visited, vector<string> &result, char &counter)
{
  for(int k = x - 1; k <= x + 1; k++)
  {
    for(int l = y - 1; l <= y + 1; l++)
    {
      if((k == x - 1 && l == y - 1) || (k == x - 1 && l == y + 1) || (k == x + 1 && l == y + 1) || (k == x + 1 && l == y - 1))
        continue; 

      if(k >= 0 && k < map.size() && l >= 0 && l < map[0].length() && map[k][l] == '.' && visited[k][l] == 0) 
      {
        visited[k][l] = 1;
        result[k].replace(l, 1, 1, counter);
        counter++;
        depthFirstSearch(k, l, map, visited, result, counter);
      }
    }
  }    	
}

int main()
{
  ifstream file("schema.txt");	
  string line;
  vector<string> matrix;

  while(getline(file, line))
  {
    matrix.ADD_TO_VECTOR(line);
  }

  vector<string> finalResult(matrix);
  int pathID = 1, i, j, k, l, rows = matrix.size(), cols = matrix[0].length();
  vector<PathInfo> paths;
  vector<vector<int> > visited(rows, vector<int>(cols, 0));
  // BFS, hence queue
  queue<COORD_PAIR> openQueue;  
  stack<COORD_PAIR> openStack;

  // Using Breadth First Search
  for(i = 0; i < rows ; i++)
  {
    for(j = 0 ; j < cols; j++)
    {
      if(matrix[i][j] == '#' || visited[i][j] > 0)
        continue;

      openQueue.push(MAKE_PAIR(i, j));
      int len = 0;

      while(!openQueue.empty())
      {
        COORD_PAIR top = openQueue.front();
        openQueue.pop();
        visited[top.first][top.second] = pathID;
        len++;

        for(k = top.first - 1; k <= top.first + 1; k++)
        {
          for(l = top.second - 1; l <= top.second + 1; l++)
          {
            if((k == top.first - 1 && l == top.second - 1) || (k == top.first - 1 && l == top.second + 1) || (k == top.first + 1 && l == top.second + 1) || (k == top.first + 1 && l == top.second - 1))
              continue; 

            if(k < 0 || l < 0 || k > rows - 1 || l > cols - 1)
              continue;

            if(matrix[k][l] == '#' || visited[k][l] > 0)
              continue;

            COORD_PAIR next = MAKE_PAIR(k, l);
            visited[k][l] = pathID;
            openQueue.push(next);
          }
        }
      }

      PathInfo nextPath = {i, j, len};
      paths.ADD_TO_VECTOR(nextPath);
      pathID++;
    }
  }

  sort(paths.begin(), paths.end(), comparePaths);

  // Make the visited array all zeroes again
  for(i = 0; i < rows; i++)
    for(j = 0; j < cols; j++)
      visited[i][j] = 0;

  char countChar = '0';

  // Push the starting position of the path of maximum length
  openStack.push(MAKE_PAIR(paths[paths.size() - 1].starting_row, paths[paths.size() - 1].starting_col));
  finalResult[paths[paths.size() - 1].starting_row].replace(paths[paths.size() - 1].starting_col, 1, 1, countChar);	

  // Applying depth first search to only the path with maximum length	
  depthFirstSearch(paths[paths.size() - 1].starting_row, paths[paths.size() - 1].starting_col, matrix, visited, finalResult, countChar);

  // Display Path Length
  cout << countChar << endl;

  for(i = 0; i < rows; i++)
  {
    for(j = 0; j < cols; j++)
      cout << finalResult[i][j];

    cout << endl;
  }

  return 0;
}
