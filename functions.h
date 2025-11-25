#include <iostream>
#include <string>
#include <fstream>
#include <vector>
using namespace std;

void displayMessage( string name )
{
    cout << "\n========================================" << endl;
    cout <<   "        REMIND - YOUR STUDY TOOL        " << endl;
    cout <<   "========================================" << endl;
    cout << "\nWelcome, " << name << "!" << '\n';
    cout << "1. Add flashcard" << endl
        << "2. Review flashcards" << endl
        << "3. Edit/Delete flashcards" << endl
        << "4. Save to file" << endl
        << "5. Exit" << endl
        << "Select from options: ";
}

void addFlashcards(vector<string>& front, vector<string>& back)
{
    static unsigned int counter = 1;
    cin.ignore(); // It turns out to be necessary for getline to work as expected
    while (true)
    {
        string frontText, backText;
        
        // Enter text for the front side
        cout << "Enter question No. " << counter << ": ";
        getline(cin, frontText);

        // Quit if the user enters 0
        if ( frontText == "0" )
        {
            cout << "\nChanges saved!" << endl
                << "Quitting ...";
            break;
        }
        
        cout << "Enter the correct answer: ";
        getline(cin, backText);
        
        // Deal with empty flashcards
        if (frontText == "" || backText == "")
        {
            cerr << "\nEmpty input is not allowed!" << endl
                << "Please be more careful!\n" << endl;
            cout << "** Enter 0 to exit the program" << endl;
            
            continue;
        }

        cout << endl;

        front.push_back(frontText);
        back.push_back(backText);

        ++counter;

        if (counter >= 2 )
        {
            cout << "** Enter 0 to exit the program" << endl;
        } 
    }
}

void reviewFlashcards(const vector<string>& front, const vector<string>& back)
{
    char answer;
    unsigned int correct = 0, incorrect = 0;

    // Declare 2 parallel vectors to review mistakes after the first session
    vector<string> mistakeFront;
    vector<string> mistakeBack;
    
    // Display message if no flashcards are added so far
    if ( front.size() == 0 )
    {
        cout << "\n========== REVIEW FLASHCARDS ===========" << endl;
        cout << "\nYou haven't added any flashcards yet!" << endl
            << "Press ENTER to return to the main menu ... ";
        cin.ignore(1000, '\n');
        if (cin.get() == '\n');
        return;
    }

    // Iterate over each flashcard
    cout << "\n========== LET'S GET STARTED ===========" << endl;
    for (int i = 0; i < front.size(); i++)
    {
        cout << "\nCard " << i + 1 << " of " << front.size() << endl;
        cout << "Front: " << front.at(i) << "\n" << endl;
        cout << "Press ENTER to see the answer... ";
        
        cin.ignore(1000, '\n'); // GEMINI

        if (cin.get() == '\n')
        {   
            cout << "Back: " << back.at(i) << "\n" << endl;   
        }

        while (true)
        {
            cout << "Did you remember this (y/n)? ";
            cin >> answer;
            
            if ( answer == 'y')
            {
                correct++;
                break;
            }
            else if (answer == 'n')
            {
                incorrect++;
                mistakeFront.push_back(front[i]);
                mistakeBack.push_back(back[i]);
                break;
            }
            else
            {
                cerr << "\nERROR! Invalid input!" << endl
                    << "Please enter either 'y' or 'n'. Try again." << endl;
                cin.ignore(1000, '\n'); // GEMINI: Clear any potential remaining buffer data.
            }
        } 
    }

    // Display statistics 

    double accuracy = (static_cast<double>(correct) / static_cast<double>(incorrect + correct)) * 100;
    cout << "\n========== SESSION COMPLETED ===========" << endl
        << "Correct: " << correct << endl
        << "Wrong: " << incorrect << endl
        << "Accuracy: " << accuracy << "%" << endl;

    
    // Review mistakes

    if ( incorrect == 0 )
    {
        cout << "\nCongratulations! You have finished this deck for now!\n";
    }
    else 
    {
        string choice;
        cout << "\nDo you want to go through your mistakes to solidify your knowledge (y/n)? ";
        while (true)
        {
            cin >> choice;
            if (choice == "y")
                break;
            else if (choice == "n")
                break;
            else
                cout << "Invalid input! Please enter either 'y' or 'n'.\n";
        }
        
        if (choice == "y")
        {
            cout << "\n=========== REVIEW MISTAKES ============" << endl;
            correct = 0, incorrect = 0;
            for (int i = 0; i < mistakeFront.size(); i++)
            {
                cout << "\nCard " << i + 1 << " of " << mistakeFront.size() << endl;
                cout << "Front: " << mistakeFront.at(i) << "\n" << endl;
                cout << "Press ENTER to see the answer... ";
        
                cin.ignore(1000, '\n'); // GEMINI

                if (cin.get() == '\n')
                {   
                    cout << "Back: " << mistakeBack.at(i) << "\n" << endl;   
                }

                while (true)
                {
                    cout << "Did you remember this (y/n)? ";
                    cin >> answer;
            
                    if ( answer == 'y')
                    {
                        correct++;
                        break;
                    }
                    else if (answer == 'n')
                    {
                        incorrect++;
                        break;
                    }
                    else
                    {
                        cerr << "\nERROR! Invalid input!" << endl
                            << "Please enter either 'y' or 'n'. Try again." << endl;
                        cin.ignore(1000, '\n'); // GEMINI: Clear any potential remaining buffer data.
                    }
                }
            }

                // Display statistics 

            accuracy = (static_cast<double>(correct) / static_cast<double>(incorrect + correct)) * 100;
            cout << "\n========== SESSION COMPLETED ===========" << endl
                << "Correct: " << correct << endl
                << "Wrong: " << incorrect << endl
                << "Accuracy: " << accuracy << "%" << endl;
        }
        
    }

    cout << "\nPress ENTER to return to the main menu ... ";
    cin.ignore(1000, '\n');
    if (cin.get() == '\n');
}

void editDeleteFlashcards(vector<string>& front, vector<string>& back)
{
    if (front.size() == 0)
    {
        cout << "\nNo flashcards to edit or delete!" << endl;
        return;
    }

    cout << "\n========== EDIT/DELETE FLASHCARDS ==========" << endl;
    for (int i = 0; i < front.size(); i++)
    {
        cout << i + 1 << ". " << front[i] << " | " << back[i] << endl;
    }

    int choice;
    cout << "\nEnter the number of the flashcard you want to edit/delete: ";
    cin >> choice;

    if (choice < 1 || choice > front.size())
    {
        cout << "Invalid choice!" << endl;
        return;
    }

    char action;
    cout << "Enter 'e' to edit or 'd' to delete: ";
    cin >> action;

    if (action == 'e')
    {
        string newFront, newBack;
        cin.ignore(); 

        cout << "Current Front: " << front[choice - 1] << endl;
        cout << "Enter new Front: ";
        getline(cin, newFront);

        cout << "Current Back: " << back[choice - 1] << endl;
        cout << "Enter new Back: ";
        getline(cin, newBack);

        front[choice - 1] = newFront;
        back[choice - 1] = newBack;
        cout << "Flashcard updated successfully!" << endl;
    }
    else if (action == 'd')
    {
        char confirm;
        cout << "Are you sure you want to delete this flashcard? (y/n): ";
        cin >> confirm;

        if (confirm == 'y')
        {
            front.erase(front.begin() + (choice - 1));
            back.erase(back.begin() + (choice - 1));
            cout << "Flashcard deleted successfully!" << endl;
        }
        else
        {
            cout << "Deletion cancelled." << endl;
        }
    }
    else
    {
        cout << "Invalid action!" << endl;
    }
}

void saveToFile(const vector<string>& front, const vector<string>& back, const string& deckName)
{
    if (front.size() == 0)
    {
        cout << "\nThere is nothing to save. You haven't added any flashcards yet!" << endl
            << "Press ENTER to return to the main menu ... ";
        cin.ignore(1000, '\n');
        if (cin.get() == '\n');
        return;
    }

    string filename = deckName + "_flashcard.txt"; 

    ofstream outputFile(filename);

    if (!outputFile) {
        cout << "Error: Could not open file for writing.\n";
        return;
    }

    for (int i = 0; i < front.size(); i++) 
    {
        outputFile << front[i] << "|" << back[i] << "\n";
    }

    cout << "\nFlashcards saved to " << filename << endl;

    outputFile.close();

}

void loadFromFile( vector<string>& front, vector<string>& back, const string& deckName )
{
    string filename = deckName + "_flashcard.txt";

    ifstream in(filename);
    if (!in) {
        cout << "No existing flashcard file found.\n";
        return;
    }

    front.clear();
    back.clear();

    string line;
    while (getline(in, line)) {
        int pos = line.find("|");
        if (pos != string::npos) {
            string f = line.substr(0, pos);
            string b = line.substr(pos + 1);
            front.push_back(f);
            back.push_back(b);
        }
    }

    in.close();
    cout << "\nLoaded flashcards from " << filename << endl;
}

bool fileExists(const string& temp)
{
    ifstream file(temp);
    return file.good();
}