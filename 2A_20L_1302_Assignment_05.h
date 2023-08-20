#pragma once
#include<iostream>
#include<fstream>
using namespace std;

#ifndef Creat_Grid

/*********************************************** QUESTION : 1 **********************************************************/

// To measure the length of string
static int StrLen(char* word)
{
    int length = NULL;

    for (char* temp = word; *temp != '\0'; temp++)
        length++;

    return length;
}

// This function converts buffer to string
static char* BufferToString(char* buffer)
{
    // length of string
    int bufferLength = StrLen(buffer);

    // character array of string length
    char* str = new char[bufferLength];

    // temp for storing the character array
    char* temp = str;

    str = buffer;

    for (char* src = buffer; *src != '\0'; src++)
    {
        // copying elements of buffer to character array
        if (*src != ' ')
        {
            *temp = *src;
        }
    }

    // Putting NULL charcater at the end to avoid garabage value
    *temp = '\0';

    return str;
}

// This function will create a dynamic array according to required rows and columns
char** Required_2D(int rows, int* colArray)
{
    char** charArray = new char* [rows];

    for (int i = 0; i < rows; i++)
    {
        charArray[i] = new char[colArray[i]];
    }

    return charArray;
}

// This function will create two day array of euqal rows and euqal columms
char** Two_D_Initializer(int size)
{
    size *= size;
    char** Two_D = new char* [size];

    for (int i = 0; i < size; i++)
        Two_D[i] = new char[size];

    return Two_D;
}

// This function will display the grid
void ShowGrid(char** grid, int size)
{
    cout << "\t\t\t\t\t\t\t\tEnter file name you where you want to see your grid? ";
    char _filename[100];
    cin >> _filename;
    ofstream Output(_filename);
    for (int i = 0; i < size; i++)
    {
        char* temp = grid[i];

        for (int j = 0; j < StrLen(temp); j++)
        {
            Output << grid[i][j] << " ";
        }
        Output << endl;
    }

    cout << "\t\t\t\t\t\t\t\tYOUR GRID IS PLACED IN '" << _filename << "' SUCCESSFULLY!!\n";
}

// This function is use to calculate that how much rows exist in file
int Rows(ifstream& in)
{
    int rows = 0;

    while (!in.eof())
    {
        char buffer[100];
        in.getline(buffer, 100);
        rows++;
    }

    in.seekg(0, in.beg);

    return rows;
}

// This function will find longest word
int Maximum(char** charArray, int size)
{
    int maximum = 0;

    for (int i = 0; i < size; i++)
    {
        char* temp = charArray[i];

        int currentLength = StrLen(temp);

        if (currentLength > maximum)
        {
            maximum = currentLength;
        }
    }

    return maximum;
}

// This function will sort the array in descending order so we can put the largest word in diagonal
void Sort(char**& charArray, int size)
{
    for (int i = 0; i < size; i++)
    {
        for (int j = i + 1; j < size; j++)
        {
            char* temp = charArray[i];

            char* temp1 = charArray[j];

            int length_Temp = StrLen(temp);

            int length_Temp1 = strlen(temp1);

            if (length_Temp < length_Temp1)
            {
                swap(charArray[i], charArray[j]);
            }

        }

    }
}

// This function will be used to have check that either the particular word exist in that diagonal or no
bool Diagonal_Check(char** grid, int rows, char* array)
{
    bool k = false;

    int a = 0;

    for (int i = 0; i < rows; i++)
    {
        k = false;

        for (int j = 0; j < rows; j++)
        {
            if (i == j)
            {
                if (grid[i][j] == array[a])
                {
                    k = true;
                    a++;
                }
            }
        }
    }

    return k;
}

// This function will check that the required space is vertically  elligible for putting word or not
bool Vertical_Empty(char** grid, int length, int index, int row, char* word)
{
    bool empty = false;

    for (int i = row; i < length; i++)
    {
        empty = false;

        if (grid[i][index] == 32 || grid[i][index] == word[i])
        {
            empty = true;
        }
        else
        {
            empty = false;
            break;
        }
    }

    return empty;
}

// This function will check that the required space is  horizontally elligible for putting word or not
bool Horizontal_Empty(char** grid, int length, int row, int col, char* word)
{
    int l = 0;

    bool empty = false;

    int a = 0;

    for (int c = col; c < length; c++)
    {
        empty = false;

        if (grid[row][c] == 32 || grid[row][c] == word[a])
        {
            empty = true;
            a++;
            l++;
        }
        else
        {
            a = 0;
            empty = false;
            break;
        }

        if (empty == true)
            break;
    }

    return empty;
}

// This function will check that the required space is fill by word vertically or not
bool Vertical_Check(char** grid, int rows, int column, char* word)
{
    bool found = false;

    int a = 0;

    for (int r = 0; r < rows; r++)
    {
        found = false;

        if (grid[r][column] == word[a])
        {
            a++;
            found = true;
        }
        else
            a = 0;
    }

    return found;
}

// This function will check that the required space is fill by word horizontally or not
bool Horizontal_Check(char** grid, int row, int cols, char* word)
{
    bool found = false;

    int a = 0;

    for (int c = 0; c < cols; c++)
    {
        found = false;

        if (grid[row][c] == word[a])
        {
            a++;
            found = true;
        }
        else
            a = 0;
    }

    return found;
}

// This function will put the words in right to left horizontal direction
void Right_To_Left_Horizontal(char**& grid, char** charArray, int maximum)
{
    char* temp = charArray[maximum - 2];
    int s = 0;
    for (int r = maximum + maximum; r > 0; r--)
    {
        for (int c = maximum + maximum; c > 0; c--)
        {
            if (s != StrLen(temp))
            {
                grid[r][c] = temp[s];
                s++;
            }
            else
            {
                break;
            }
        }
    }
}

// This function will put the words in bottom to top vertical direction
void Bottom_To_Top_Vertical(char**& grid, char** charArray, int maximum)
{
    char* temp = charArray[maximum];
    int  s = 0;
    for (int c = maximum + maximum + 1; c > 0; c--)
    {
        for (int r = maximum + maximum + 1; r > 0; r--)
        {
            if (s != StrLen(temp))
            {
                grid[r][c] = temp[s];
                s++;
            }
            else
            {
                break;
            }
        }
    }

}

// This function will check that the word is either present in the grid on not either horizontally vertically or diagnoally
bool Presence_Check(char** grid, int rows, int cols, char* word)
{
    bool found = false;

    int a = 0;

    for (int i = 0; i < rows; i++)
    {
        int j;

        for (j = 0; j < cols; j++)
        {
            found = false;

            if (Vertical_Check(grid, StrLen(word), j, word) == true)
            {
                found = true;
                break;
            }
            else
            {
                if (Horizontal_Check(grid, j, StrLen(word), word) == true)
                {
                    found = true;
                    break;
                }
                else
                {
                    if (Diagonal_Check(grid, StrLen(word), word) == true)
                    {
                        found = true;
                        break;
                    }
                }
            }
        }
    }

    return found;
}

// This function will fill the grid with spaces initially
void Fill_With_Spaces(char**& grid, int dimension)
{
    for (int i = 0; i < dimension; i++)
    {
        int j;

        for (j = 0; j < dimension; j++)
        {
            grid[i][j] = 32;
        }
        grid[i][j] = '\0';
    }
}

// This function will fill random words in grid
void Fill_Random_Words(char**& grid, int dimension)
{
    for (int i = 0; i < dimension; i++)
    {
        for (int j = 0; j < dimension; j++)
        {
            if (grid[i][j] == 32)
            {
                do
                    grid[i][j] = rand();
                while (!(grid[i][j] >= 97 && grid[i][j] <= 122));
            }
        }
    }
}

// This function will creat grid
char** Grid(char** charArray, int size_of_grid, int rows_of_wordlist)
{
    // We will generate the dimension ( Rows X Columns ) on the basis of longest words

    int dimension = size_of_grid;
    int maximum = Maximum(charArray, rows_of_wordlist);

    Sort(charArray, rows_of_wordlist);
    char** grid = Two_D_Initializer(dimension);

    // Filled with spaces
    Fill_With_Spaces(grid, dimension);

    // Left Diagonal

    //rows 0f wordslist
    int original_maximum = maximum;
    int a;

    for (a = 0; a < rows_of_wordlist; a++)
    {
        char* temp = charArray[a];

        if (StrLen(temp) == maximum)
        {
            for (int i = 0; i < maximum; i++)
            {
                for (int j = 0; j < maximum; j++)
                {
                    if (i == j)
                    {
                        grid[i][j] = charArray[a][j];
                    }
                }
            }
        }

        if (Diagonal_Check(grid, dimension, temp) == true)
        {
            maximum--;
            a++;
            break;
        }
    }


    //Left Vertical

    a = 0;

    int maximumminus2 = maximum - 2;

    int maximumminus4 = maximum - 4;

    int maximumminus6 = maximum - 6;

    int oldmaximum = maximum;

    for (; a < maximum; a++)
    {
        if (a % 2 == 0)
        {
            bool vertical = false; // Check to see vertical

            char* temp = charArray[a];

            if (Presence_Check(grid, maximum, maximum, temp) == false)
            {
                if (StrLen(temp) == maximum + 1 || StrLen(temp) == maximum - 1 || StrLen(temp) == maximum || StrLen(temp) == maximumminus2 || StrLen(temp) == maximumminus4 || StrLen(temp) == maximumminus6 || StrLen(temp) == oldmaximum)
                {
                    for (int c = 0; c <= maximum; c++)
                    {
                        for (int r = 0; r <= maximum; r++)
                        {
                            if (Vertical_Empty(grid, StrLen(temp), c, r, temp) == true)
                            {
                                grid[r][c] = charArray[a][r];
                            }
                            else
                            {
                                break;
                            }
                        }

                        if (Vertical_Check(grid, StrLen(temp), c, temp) == true)
                        {
                            oldmaximum = maximum;

                            maximumminus2 = maximum - 2;

                            maximumminus4 = maximum - 4;

                            maximumminus6 = maximum - 6;

                            maximum--;

                            break;
                        }

                    }

                }

            }
        }

    }



    a = 0;

    maximum = original_maximum;

    maximumminus2 = maximum - 2;

    maximumminus4 = maximum - 4;

    maximumminus6 = maximum - 6;

    oldmaximum = maximum;
    for (; a < maximum; a++)
    {
        if (a % 2 == 1)
        {
            bool horizontal = false;

            char* temp = charArray[a];

            if (Presence_Check(grid, maximum, maximum, temp) == false)
            {
                if ((StrLen(temp) == maximum + 1 || StrLen(temp) == maximum - 1 || StrLen(temp) == maximum || StrLen(temp) == maximumminus2 || StrLen(temp) == maximumminus4 || StrLen(temp) == maximumminus6 || StrLen(temp) == oldmaximum))
                {
                    for (int r = 0; r < dimension; r++)
                    {
                        for (int c = 0; c < dimension; c++)
                        {
                            int pos = c;
                            int check = 0;

                            int w = c;

                            for (int ch = 0; ch < StrLen(temp); ch++)
                            {
                                if ((grid[r][w] == ' ') && w < dimension) {
                                    check++;
                                    w++;
                                }
                            }
                            if (check == StrLen(temp))
                            {
                                for (int z = 0; z < StrLen(temp); z++)
                                {
                                    grid[r][pos] = charArray[a][z];
                                    pos++;
                                }
                            }

                            check = 0;
                            if (check != StrLen(temp))
                            {
                                break;
                            }
                        }

                        if (Horizontal_Check(grid, r, StrLen(temp), temp) == true)
                        {
                            oldmaximum = maximum;

                            maximumminus2 = maximum - 2;

                            maximumminus4 = maximum - 4;

                            maximumminus6 = maximum - 6;

                            maximum--;

                            break;
                        }

                    }

                }

            }
            else

                maximum--;
        }
    }


    Right_To_Left_Horizontal(grid, charArray, maximum);

    Bottom_To_Top_Vertical(grid, charArray, maximum);

    Fill_Random_Words(grid, dimension);

    return grid;
}

// Function call for Creation of grid


#endif // !Creat_Grid

