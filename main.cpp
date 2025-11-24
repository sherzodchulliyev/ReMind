#include <iostream>
#include <vector>
#include <string>
#include "functions.h"
#include <limits>
using namespace std;

int main()
{
    string userName, deckName;
    int option; // Declare a global function to enable user to select from options  

    // Declare parallel vectors for front and back sides of flashcards 
    vector<string> front; 
    vector<string> back;

    cout << "Enter your name: ";
    cin >> userName;
    cin.ignore(1000, '\n');

    cout << "Enter deck name: ";
    cin >> deckName;
    cin.ignore(1000, '\n');
    
    // Check if the inputted deckname already exists, so the data can be loaded
    string temp = deckName + "_flashcard.txt"; // temporary variable to search among existing files

    // Check if any such file exists
    if (fileExists(temp))
    {
        string choice; // Declare a local variable for the following question
        cout << "This deck already exists. Do you want to load data from " << temp << " (y --> yes / n --> change deckname)?" << endl;
        
        // In case the user enters, any other value than 'y' or 'n', output an error message and redirect them to enter the correct input 
        while (true)
        {
            getline(cin, choice);  // read the whole line

            if (choice == "y")
            {
                cout << "Loading ..." << endl;
                // Read existing files into vectors
                loadFromFile(front, back, deckName);
                break;
            }
            else if (choice == "n")
            {
                cout << "Enter a different deckname: ";
                cin >> deckName;
                cin.ignore(1000, '\n');
                break;
            }
            else
            {
                cerr << "\nERROR! Invalid input!\n"
                    << "Please input either 'y' or 'n'." << endl;
            }
        }
        
    }

    // The loop runs until user decides to exit via OPTION 4
    while(true)
    {
        displayMessage(userName);
        cin >> option; // Ask the user to select from available options

        // Catch out-of-range error and redirect the user
        if (option > 4 || option < 1)  
        {
            cin.clear();  // AI SOLUTION: clear buffer
            cin.ignore(numeric_limits<streamsize>::max(), '\n'); // // AI SOLUTION:

            cerr << "\n\nERROR OCCURRED! Invalid input!\nPlease select from options 1-4." << endl;
            continue;
        }

        // --- WRITE A SEPARATE FUNCTION FOR EACH OPTION ---

        // OPTION 1
        // Enable the user to add flashcards manually
        if (option == 1)
        {
            addFlashcards(front, back);
        }

        // OPTION 2
        // Review flashcards and get feedback
        if (option == 2)
        {
            reviewFlashcards(front, back);
        }
        
        // OPTION 3
        // Save the data into a separate [deckname]_flashcard.txt file
        if ( option == 3 )
        {
            saveToFile(front, back, deckName);
        }

        // OPTION 4
        // Exit the program and ask the user to save changes
        if ( option == 4 )
        {
            char poll;
            if (!fileExists(temp))
            {
                cout << "Do you want to save the changes (y - yes, n - no)? ";
                cin >> poll;

                // Create a separate file and save changes to [deckName]_flashcard.txt
                if ( poll == 'y' )
                {
                    saveToFile(front, back, deckName);
                    cout << "Changes saved.\n";
                }
                else if (poll == 'n')
                {
                    cout << "Changes discarded.\n";
                }
            }
            else
            {
                saveToFile(front, back, deckName);
            }
            
            cout << "Exiting ...\n";
            break;
        }        
    }
    
    return 0;
}