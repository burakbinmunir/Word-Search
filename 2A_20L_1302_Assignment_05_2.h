#pragma once
#include<iostream>
#include<fstream>
#include"2A_20L_1302_Assignment_05.h"
using namespace std;

#ifndef Word_Search


/*********************************************** QUESTION : 2 **********************************************************/

// This function will initialize the grid according to given rows and columns
char** Initializer_2D(int rows, int cols)
{
    char** charArray = new char* [rows];

    for (int i = 0; i < rows; i++)
        charArray[i] = new char[cols];

    return charArray;
}

// This function will input the grid from where the words to be searched
char** Input(int rows, int cols, char _input_fileName[100])
{
    char** charArray = Initializer_2D(rows, cols);

    ifstream input(_input_fileName);

    if (input.is_open())
    {
        for (int i = 0; i < rows; i++)
        {
            int j = 0;
            for (; j < cols; j++)
            {
                input >> charArray[i][j];
            }
        }

    }

    return charArray;
}

// This function is used to see either the grid is read correctly or not
// it will save the grid by default in "Output.txt" file
void Show(char** charArray, int rows, int cols)
{
    ofstream Output("Output.txt");
    if (Output.is_open())
    {

        for (int i = 0; i < rows; i++)
        {
            for (int j = 0; j < cols; j++)
            {
                Output << charArray[i][j] << " ";
            }
            Output << endl;
        }
    }
}

// This function will input the words to be searched and return 
// a 2D array of words to be searched
char** _Words_To_Be_Searched(istream& input, int testCases)
{
    char** words_To_Be_Searched = new char* [testCases];
    char buffer[100];
    input.ignore();
    for (int testcase = 0; testcase < testCases; testcase++)
    {
        input.getline(buffer, 100);
        char* temp = BufferToString(buffer);
        int column = StrLen(temp);
        words_To_Be_Searched[testcase] = new char[column];
    }
    input.seekg(9);
    input.ignore();

    for (int testcase = 0; testcase < testCases; testcase++)
    {
        input.getline(buffer, 100);
        char* temp = BufferToString(buffer);
        int col = StrLen(temp);
        int j;
        for (j = 0; j < col; j++)
        {
            words_To_Be_Searched[testcase][j] = temp[j];
        }
        words_To_Be_Searched[testcase][j] = '\0';

    }

    return words_To_Be_Searched;
}

// This function will find the word left to right horizontally
bool Left_To_Right_Horizontal(char** grid, char* word, int rows, int cols, ofstream& Out)
{

    if (Out.is_open())
    {
        int x1 = 0, y1 = 0;
        int x2 = 0, y2 = 0;
        bool found = false;


        for (int r = 0; r < rows; r++)
        {
            for (int c = 0; c < cols; c++)
            {

                if (grid[r][c] == word[0])
                {
                    x2 = r;
                    x1 = r;
                    y1 = c;
                    int l = c;

                    for (int h = 0; h < StrLen(word); h++)
                    {
                        found = false;
                        if (word[h] == grid[r][l])
                        {
                            found = true;
                            y2 = l;
                            l++;

                        }
                        else
                        {
                            break;
                        }
                    }
                }
                if (found == true)
                {
                    break;
                }

            }
            if (found == true)
            {
                break;
            }
        }

        if (found == true)
            Out << "{ " << x1 << " , " << y1 << " } , " << " { " << x2 << " , " << y2 << " }" << endl;

        return found;
    }


}

// This function will find the word from right to left horizonatlly
bool Right_To_Left_Horizontal(char** grid, char* word, int rows, int cols, ofstream& Out)
{
    if (Out.is_open())
    {
        int x1 = 0, x2 = 0, y1 = 0, y2 = 0;
        int check = NULL;

        for (int r = rows - 1; r > 0; r--)
        {
            for (int c = cols - 1; c > 0; c--)
            {
                check = 0;
                if (word[0] == grid[r][c])
                {
                    x1 = r;
                    x2 = r;
                    y1 = c;
                    int l = c;
                    for (int h = 0; h < StrLen(word); h++)
                    {
                        if (word[h] == grid[r][l])
                        {
                            check++;
                            l--;
                            y2 = l;
                        }
                    }
                    if (check == StrLen(word))
                    {
                        Out << "{ " << y1 << " , " << x1 << " } " << " { " << x2 << " , " << y2 << " }, " << endl;
                        return true;
                    }
                }
            }
        }
    }
}

// This function will find the word from top to bottom vertically
bool Top_To_Bottom_Vertical(char** grid, char* word, int rows, int cols, ofstream& Out)
{
    if (Out.is_open())
    {
        int x1 = 0;
        int y1 = 0;
        int x2 = 0, y2 = 0;
        int a = 0;
        int check = 0;
        bool found = false;

        for (int i = 0; i < rows; i++)
        {
            for (int j = 0; j < cols; j++)
            {
                check = 0;
                if (word[0] == grid[i][j])
                {
                    x1 = i;
                    y1 = j;
                    y2 = j;


                    int l = i;
                    for (int h = 0; l < rows && h < StrLen(word); h++)
                    {
                        if (word[h] == grid[l][j])
                        {
                            check++;
                            x2 = l;
                            l++;
                        }
                    }

                    if (check == StrLen(word))
                    {
                        Out << "{ " << x1 << " , " << y1 << " } , " << " { " << x2 << " , " << y2 << " }" << endl;
                        return true;

                    }
                }
            }
        }
    }
}

// This function will find the word from bottom to top vertically
bool Bottom_To_Top_Vertical(char** grid, char* word, int rows, int cols, ofstream& Out)
{
    if (Out.is_open())
    {
        int x1 = 0, x2 = 0, y1 = 0, y2 = 0;
        int check = NULL;

        for (int c = cols - 1; c > 0; c--)
        {
            for (int r = rows - 1; r > 0; r--)
            {
                check = 0;
                if (word[0] == grid[r][c])
                {
                    x1 = r;
                    y2 = c;
                    y1 = c;
                    int l = r;

                    for (int h = 0; h < StrLen(word); h++)
                    {
                        if (word[h] == grid[l][c])
                        {
                            x2 = l;
                            l--;
                            check++;
                        }
                    }
                    if (check == StrLen(word))
                    {
                        Out << "{ " << x1 << " , " << y1 << " } " << " { " << x2 << " , " << y2 << " }, " << endl;
                        return true;
                    }
                }
            }
        }
    }
}

// This function will find the word from top left diagonal
bool Left_Top_Diagonal(char** grid, char* word, int rows, int cols, ofstream& Out)
{
    if (Out.is_open())
    {
        int a = 0;
        int check = 0;
        int x1 = 0, y1 = 0, y2 = 0, x2 = 0;
        for (int i = 0; i < rows; i++)
        {
            for (int j = 0; j < cols; j++)
            {
                if (i == j)
                {
                    if (word[0] == grid[i][j])
                    {
                        x1 = i;
                        y1 = j;

                        for (int r = i; r < rows; r++)
                        {
                            for (int c = j; c < cols; c++)
                            {
                                if (r == c && check != StrLen(word))
                                {
                                    if (word[a] == grid[r][c])
                                    {

                                        x2 = r;
                                        y2 = c;
                                        check++;
                                        a++;
                                    }
                                }
                            }
                        }
                        if (check == StrLen(word))
                        {
                            Out << "{ " << x1 << " , " << y1 << " } " << " { " << x2 << " , " << y2 << " } " << endl;
                            return true;
                        }
                    }
                }
            }
        }
    }
}

// This function will find the word from right bottom diagonally
bool Right_Bottom_Diagonal(char** grid, char* word, int rows, int cols, ofstream& Out)
{
    if (Out.is_open())
    {
        int x1 = 0, x2 = 0, y1 = 0, y2 = 0;
        int check = 0;
        int a = 0;

        for (int r = rows - 1; r > 0; r--)
        {

            for (int c = cols - 1; c > 0; c--)
            {
                if (r == c)
                {
                    if (word[0] == grid[r][c])
                    {
                        x1 = r;
                        y1 = c;

                        for (int i = r; i > 0; i--)
                        {
                            for (int j = c; j > 0; j--)
                            {
                                if (i == j && check != StrLen(word))
                                {
                                    if (word[a] == grid[i][j])
                                    {
                                        x2 = i;
                                        y2 = j;
                                        a++;
                                        check++;
                                    }
                                }
                            }
                        }
                        if (check == StrLen(word))
                        {
                            Out << "{ " << x1 << " , " << y1 << " } " << " { " << x2 << " , " << y2 << " }, " << endl;
                            return true;
                        }

                    }
                }
            }
        }

        return false;
    }
}

// This function will find the word from top right diagonal
bool Right_Top_Diagonal(char** grid, char* word, int rows, int cols, ofstream& Out)
{
    if (Out.is_open())
    {
        int x1 = 0, x2 = 0, y1 = 0, y2 = 0;
        int check = 0;
        int a = 0;

        for (int c = cols - 1; c > 0; c--)
        {
            for (int r = 0; r < rows; r++)
            {
                if (r == c)
                {
                    if (word[0] == grid[r][c])
                    {
                        x1 = r;
                        y1 = c;

                        for (int j = c; j > 0; j--)
                        {
                            for (int i = r; i < rows; i++)
                            {
                                if (i == j && check != StrLen(word))
                                {
                                    if (word[a] == grid[i][j])
                                    {
                                        x2 = i;
                                        y2 = j;
                                        check++;
                                        a++;
                                    }
                                }

                            }
                        }
                        if (check == StrLen(word))
                        {
                            Out << "{ " << x1 << " , " << y1 << " } " << " { " << x2 << " , " << y2 << " }, " << endl;
                            return true;
                        }
                    }
                }
            }
        }
    }
}

// This function will find the word from left bottom diagonally
bool Left_Bottom_Diagonal(char** grid, char* word, int rows, int cols, ofstream& Out)
{
    if (Out.is_open())
    {
        int a = 0;
        int check = 0;
        int x1 = 0, y1 = 0, y2 = 0, x2 = 0;

        for (int r = 0; r < rows; r++)
        {
            for (int c = cols - 1; c > cols; c--)
            {
                if (r == c)
                {
                    if (word[0] == grid[r][c])
                    {
                        x1 = r;
                        y1 = c;

                        for (int i = r; i < rows; i++)
                        {
                            for (int j = c; j > cols; j--)
                            {
                                if (i == j && check != StrLen(word))
                                {
                                    if (grid[i][j] == word[a])
                                    {
                                        x2 = i;
                                        y2 = j;
                                        a++;
                                        check++;
                                        a++;
                                    }
                                }
                            }
                        }
                        if (check == StrLen(word))
                        {
                            Out << "{ " << x1 << " , " << y1 << " } " << " { " << x2 << " , " << y2 << " }, " << endl;

                            return true;
                        }
                    }
                }
            }
        }
    }
}

// This function will call different function to find the specfic word
void Find_Word(char** grid, char** wordlist, int rows, int cols, int testCases, char _Output_fileName[50])
{
    ofstream Out(_Output_fileName);
    if (Out.is_open())
    {
        for (int i = 0; i < testCases; i++)
        {
            char* word = wordlist[i];

            if (Left_To_Right_Horizontal(grid, word, rows, cols, Out) == true)
                Out << " '" << word << " '" << " Found Left To Right  Horizontally\n\n";
            else
                if (Top_To_Bottom_Vertical(grid, word, rows, cols, Out) == true)
                    Out << " '" << word << " '" << " Found Top To Bottom Vertically \n\n";
                else
                    if (Right_To_Left_Horizontal(grid, word, rows, cols, Out) == true)
                        Out << " '" << word << " '" << "Found Right To Left Horizontal\n\n";
                    else
                        if (Bottom_To_Top_Vertical(grid, word, rows, cols, Out) == true)
                            Out << " '" << word << " '" << "Found Bottom To Top Vertically\n\n";
                        else
                            if (Left_Top_Diagonal(grid, word, rows, cols, Out) == true)
                                Out << " '" << word << " '" << "Found Left Top Diagonally\n\n";
                            else
                                if (Right_Bottom_Diagonal(grid, word, rows, cols, Out) == true)
                                    Out << " '" << word << " '" << "Found Bottom Right Diagonally\n\n";
                                else
                                    if (Right_Top_Diagonal(grid, word, rows, cols, Out) == true)
                                        Out << " '" << word << " '" << "Found Top Right Diagonally\n\n";
                                    else
                                        if (Left_Bottom_Diagonal(grid, word, rows, cols, Out) == true)
                                            Out << " '" << word << " '" << " Found Left Bottom Diagnonally\n\n";
                                        else
                                            Out << " '" << word << " '" << "Not Found\n";
        }
        cout << "\t\t\t\t\t\t\t\tFound indexes have been placed in '" << _Output_fileName << "' filename\n";
    }
}

// This function will deal the whole program of word search by calling
// several functions which will further call several functions


#endif // !Word_Search
