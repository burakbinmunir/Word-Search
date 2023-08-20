#include"2A_20L_1302_Assignment_05.h"
#include"2A_20L_1302_Assignment_05_2.h"

void Create_Grid()
{
    cout << "\t\t\t\t\t\t\t\tEnter file's name to grabe words for creating grid: ";
    char _fileName[100];
    cin >> _fileName;
    cout << endl << endl;
    ifstream input(_fileName);

    if (input.is_open())
    {
        cout << endl << endl;
        cout << "\t\t\t\t\t\t\t\tHow many words are in the file? ";
        int rows = Rows(input);// it will count words by itself

        int rows_in_file = NULL;
        cin >> rows_in_file;
        cout << endl << endl;
        // if the words will be less than the entered number then grid will not formed 
        // or grid will be formed of only those words which are present in word

        if (rows < rows_in_file)
        {
            int choice;
            cout << "\t\t\t\t\t\t\t\tThere are less than " << rows_in_file << " words in file\n\n";
            cout << "\t\t\t\t\t\t\t\tWhat you want to do now?\n";
            cout << "\t\t\t\t\t\t\t\t1.Create Grid of available words\n";
            cout << "\t\t\t\t\t\t\t\t2.Exit the Program\n";
            cout << "\t\t\t\t\t\t\t\t";
            cin >> choice;

            if (choice == 1)
            {
                rows_in_file = rows;
            }
            if (choice == 2)
            {
                return;
            }
        }

        // Taking Words from file

        // to store the length of every word that would be the length of column
        int* colArray = new int[rows_in_file];


        for (int index = NULL; index < rows_in_file; index++)
        {
            char* temp;
            char buffer[100];
            input.getline(buffer, 100);
            temp = BufferToString(buffer);
            colArray[index] = StrLen(temp);
        }

        // it will create the 2D array of words list
        char** words = Required_2D(rows_in_file, colArray);

        input.seekg(0);//moving cursor to top of file

        // inputing words from file
        for (int _rows = NULL; _rows < rows_in_file; _rows++)
        {
            int _cols;
            for (_cols = NULL; _cols < colArray[_rows]; _cols++)
            {
                input >> words[_rows][_cols];
            }
            words[_rows][_cols] = '\0';
        }

        // Information of Grid
        cout << endl << endl;
        cout << "\t\t\t\t\t\t\t\tWhat should be the dimensions of grid?\n\n";
        cout << "\t\t\t\t\t\t\t\tRows: ";
        int rows_of_grid = NULL;
        cin >> rows_of_grid;

        cout << endl << endl;
        cout << "\t\t\t\t\t\t\t\tCols: ";
        int cols_of_grid = NULL;
        cin >> cols_of_grid;

        int maximum = Maximum(words, rows);

        if (maximum < rows_of_grid && maximum < cols_of_grid)
        {
            char** grid = Grid(words, rows_of_grid, rows_in_file);
            ShowGrid(grid, rows_of_grid);
        }
        else
        {
            cout << "\t\t\t\t\t\t\t\tSORRY GRID CANNOT BE FORMED\n";
            return;
        }
    }
    else
    {
        cout << "\t\t\t\t\t\t\t\tOOPS!! FILE NOT FOUND\n";
        return;
    }
}

void Word_Search()
{
    cout << "\t\t\t\t\t\t\t\tEnter the File Name where the grid is placed: ";
    char _grid_Filename[100];
    cin >> _grid_Filename;

    ifstream in(_grid_Filename);

    if (in.is_open())
    {
        char _input_Filename[100];
        cout << "\t\t\t\t\t\t\t\tEnter the File Name where the input if placed: ";
        cin >> _input_Filename;

        cout << endl << endl;
        ifstream input(_input_Filename);
        if (input.is_open())
        {
            int rows = NULL;
            int cols = NULL;

            input >> rows;
            input >> cols;

            char** grid = Input(rows, cols, _grid_Filename);

            Show(grid, rows, cols);// for the sake of confirmation that grid is being read

            int testCases;
            input >> testCases;

            char** words_To_Be_Searched = _Words_To_Be_Searched(input, testCases);

            char _output_Filename[50];
            cout << "\t\t\t\t\t\t\t\tEnter Output Filename: ";
            cin >> _output_Filename;

            Find_Word(grid, words_To_Be_Searched, rows, cols, testCases, _output_Filename);
        }
        else
        {
            cout << "\t\t\t\t\t\t\t\tOPPS!! INPUT FILE NOT FOUND\n";
            return;
        }
    }
    else
    {
        cout << "\t\t\t\t\t\t\t\tOOPS!! GRID FILE NOT FOUND\n";
        return;
    }
}

//Driver Program
void main()
{
    cout << "\t\t\t\t\t\t\t\tWELCOME TO WORDSEARCH\n";
    cout << endl << endl;

    char choice = NULL;
    cout << "\t\t\t\t\t\t\t\tPress I to Initialize\n";
    cin >> choice;

    while (choice == 'I' || choice == 'C' || choice == 'S' || choice == 'Q')
    {
        cout << "\t\t\t\t\t\t\t\tPress C to Create Grid\n";
        cout << "\t\t\t\t\t\t\t\tPress S to Search Words from Grid\n";
        cout << "\t\t\t\t\t\t\t\tPress Q to Quite Program\n\n";
        cout << "\t\t\t\t\t\t\t\t";
        cin >> choice;
        if (choice == 'C')
        {
            Create_Grid();
            cout << "\t\t\t\t\t\t\t\t";
            system("pause");
            for (int i = 0; i < 25; i++)
                cout << endl;
        }

        if (choice == 'S')
        {
            Word_Search();
            system("pause");
            for (int i = 0; i < 25; i++)
                cout << endl;
        }

        if (choice == 'Q')
        {
            cout << "\t\t\t\t\t\t\t\t\tBYE BYE\n";
            return;
        }
    }
}


