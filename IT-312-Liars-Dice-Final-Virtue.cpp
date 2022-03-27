/*
Second attempt at Liar's Dice - Now with Objects™!
by Gwen Virtue
IT-312 Software Development with C++.NET
Southern New Hampshire University

The nearly ancient game of Liar's Dice recreated in C++ for your entertainment.
*/

#include <iostream>
#include <string>
#include <time.h> //Included to help seed random number generator.
#include <fstream>

using namespace std;


//A guess class that can contain the current maximum number of dice faces currently being guessed.
class Guesses
{
    private:
        int maxDiceFaces = 0;  //I faced an error where this value was not being updated. Solved that by passing class by reference instead of value.
        
    public:
        void setMaxDiceFaces(int diceNumChoice)
        {
            maxDiceFaces = diceNumChoice;
            return;
        }
    
        int getMaxDiceFaces()
        {
            return maxDiceFaces;
        }
};

//A structure to contain the guesses made by each player.
struct DiceGuess //I received an error trying to return value of array with these two variables. Solved it by implementing a structure.
{
    int diceNumChoice;
    int diceGuess;
};

//Player class to contain pertinent player information.
class Player
{
    //Three declared variables that contain the users dice, whether or not they have guessed, and a structure to contain their guesses.
    public:
        int dice[5] = {0, 0, 0, 0, 0};
        DiceGuess guess;
        bool hasGuessed = false;
    
};

void ShowWelcome()
{
    //A small amount of introduction text.
    cout << "Welcome to Liar's Dice!" << endl << endl;
    cout << "By Gwen Virtue" << endl;
    cout << "IT-312 Southern New Hampshire University" << endl << endl;
    cout << "To play this game, you must guess how many dice of a certain number are in play" << endl;
    cout << "between yourself and the other players." << endl << endl;
    cout << "For two or more players." << endl; 
};

//Roll dice for player
void PlayerInit(Player player[], int numPlayers)
{
    //Assign random number between 1 and 6 for each of the players dice.
    for (int i = 1; i <= numPlayers; i++)
    {
        player[i].dice[0] = rand() % 6 + 1; //Faced an error where these numbers never changed, solved that by implementing a time based random seed.
        player[i].dice[1] = rand() % 6 + 1;
        player[i].dice[2] = rand() % 6 + 1;
        player[i].dice[3] = rand() % 6 + 1;
        player[i].dice[4] = rand() % 6 + 1;
    }
};


//Provide functionality to allow player to guess number of dice in play.
DiceGuess MakeGuess(Guesses &guess) //Passed guess by reference to fix error of not updating variable.
{
    //Declare variables, one for how many dice, and the second for the value of the dice, and a boolean that assists with making valid guesses.
    int diceNumChoice;
    int diceChoice;
    bool validGuess = false;
    
    //Loop back to asking for a guess if the player guesses the same or less than prior guesses.
    while (validGuess == false)
    {
        cout << "The last guess included " << guess.getMaxDiceFaces() << " number of dice. You will need to guess more than that." << endl;
        cout << "How many dice are you guessing?" << endl;
        cin >> diceNumChoice;
        
        //Ensure player guessed more than prior guesses.
        if (diceNumChoice > guess.getMaxDiceFaces())
        {
            guess.setMaxDiceFaces(diceNumChoice);
            validGuess = true;
        }
        else
        {
            cout << "Your guess needs to increase the number of dice faces from the previous guesses." << endl;
        }
    }

    cout << "What number do you guess?" << endl;
    cin >> diceChoice;

    cout << "You guess " << diceNumChoice << " of " << diceChoice << " are in play." << endl;

    DiceGuess result = { diceNumChoice, diceChoice }; //Assign choices to DiceGuess structure

    //Return structure value for use of parent function.
    return result;

};

//This function is what presents the count of instances of a specific number within the dice arrays.
int DiceValue(int diceValue, int numPlayers, Player player[])
{
    int count = 0;
    
    //First for loop to iterate through all players.
    for (int i = 0; i <= numPlayers; i++)
    {
        //Second for loop to iterate through a players dice.
        for (int j = 0; j < 6; j++)
        {
            //Add one to count for each dice that has the value being checked.
            if (player[i].dice[j] == diceValue)
            {
                ++count; //I tried to implement this with the count() function from <algorithms> but it kept giving garbage value. Changed it to this 
                         //much simpler method that returns valid data.
            }
        }
        
    }
    
    //Returns one value, this function will be called six times, once for each value of a single die.
    return count;
};

void CallOut(Player player[], int numPlayers)
{
    //This function processes the total dice in play, counts the specific instances of dice values and displays them. 
    //It is a little bit clunky, and I intend to revise it a bit.
    int callOutPlayer;
    int realValue;
    int ones, twos, threes, fours, fives, sixes;

    cout << "Which player would you like to call out?" << endl;
    cin >> callOutPlayer;
    
    //Check player object to ensure that they have made a guess to be called out.
    if (player[callOutPlayer].hasGuessed == true)
    {
        
        //Display the guess that the target player had previously made.
        cout << "Player " << callOutPlayer << " guessed the following: " << endl;
        cout << player[callOutPlayer].guess.diceNumChoice << " of " << player[callOutPlayer].guess.diceGuess << endl;
    
        //Possibly not needed. I would prefer these to be inline with the cout statements, however I made this bundle 
        //for debugging purposes and I am reluctant to change it lest I break something again. The error I was receiving was that each
        //value was only displaying itself, so it read "1 1s, 2 2s, etc." I solved this by implementing nested for loops to iterate a count and
        //calling that function six times, rather than the count() function I tried previously.
        ones = DiceValue(1, numPlayers, player);
        twos = DiceValue(2, numPlayers, player);
        threes = DiceValue(3, numPlayers, player);
        fours = DiceValue(4, numPlayers, player);
        fives = DiceValue(5, numPlayers, player);
        sixes = DiceValue(6, numPlayers, player);
        
        //Display the total number of each dice in play amongst all players.
        cout << "In actuality, there were the following dice in play: " << endl;
        cout << "1s: " << ones << endl;
        cout << "2s: " << twos << endl;
        cout << "3s: " << threes << endl;
        cout << "4s: " << fours << endl;
        cout << "5s: " << fives << endl;
        cout << "6s: " << sixes << endl << endl;

        //Exit gracefully.
        cout << "Thank you for playing!" << endl;
    
        exit(0);
    }
    else
    {
        //Display error message and return to menu.
        cout << "This player has not made a guess and cannot be called out." << endl;
    }


};


//Main menu and primary game loop.
void ShowMenu(Player player[], int currentPlayer, int numPlayers, Guesses guess)
{
    int menuChoice = 0;
    
    
    
    //Using a while loop to redisplay the menu as needed. Whenever the menuChoice value is returned back to 0
    //The full menu is displayed to the user once again.
    while (menuChoice == 0)
    {
        //Display main menu
        cout << "Player " << currentPlayer << endl << endl;
        cout << "Please choose an option" << endl << endl;
        cout << "1: Display rules." << endl;
        cout << "2: Display my dice." << endl;
        cout << "3: Make a guess and move onto next player." << endl;
        cout << "4: Call out a player and end game." << endl;
        cout << "5: Quit" << endl;

        //Player input
        cin >> menuChoice;
        
        //Check to see if players choice is in range of menu options, display error if not, and return to menu.
        if ((menuChoice < 1) && (menuChoice > 5))
        {
            cout << "Invalid choice, please try again." << endl;
            
            menuChoice = 0;
        }
        if (menuChoice == 1)
        {
            string line;
            ifstream myfile;
    
            //Open previously created text file
            myfile.open ("liarsdicerules.txt");
    
            //Ensure that the file opened correctly.
            if (myfile.is_open())
            {
                //Read each line of text file and display to screen.
                while (getline (myfile, line))
                {
                    cout << line << endl;
                }
        
                //Close out file to prevent errors and memory leaks.
                myfile.close();
            }
            //Display error message if file can't be opened or found.
            else
            {
                cout << "Unable to open file.";
            }
            
            //Return to main menu
            menuChoice == 0;
            
        }
        
        
        if (menuChoice == 2)
        {
            //Iterate through current player's dice and display.
            for (int i = 0; i < 5; i++)
            {
                cout << player[currentPlayer].dice[i];
            }
            cout << endl;
            
            //Return to main menu
            menuChoice = 0;
        }
        else if (menuChoice == 3)
        {
            //Call MakeGuess function and mark the player as having made a guess.
            player[currentPlayer].guess = MakeGuess(guess);
            
            player[currentPlayer].hasGuessed = true;
            
            //Iterate to the next player, or back to the first player if last player is making the guess.
            if (currentPlayer < numPlayers)
            {
                currentPlayer++;
            }
            else
            {
                currentPlayer = 1;
            }
            
            //Return to main menu.
            menuChoice = 0;
            
        }
        else if (menuChoice == 4)
        {
            //Call out a player's guess, display how accurate they are, and end the game.
            CallOut(player, numPlayers);
            
            menuChoice = 0;
        }
        else if (menuChoice == 5)
        {
            //Display confirmation to user that the game is over.
            cout << "Thank you for playing!" << endl;
            
            exit( 0 );
        }
        else 
        {
            //A secondary check for erroneous selection, that may be redundant.
            cout << "Sorry, that is not a valid selection. Please try again!" << endl;
            menuChoice = 0;
        }
    }
};

int main()
{
    
    srand(time(NULL)); //Reseed random number generator based on current time.
    
    int numPlayers = 0;
    int currentPlayer = 1;
    
    Guesses guess; //Create guess object from Guesses class.

    ShowWelcome(); //Display introduction to users.
    
    while (numPlayers < 2)
    {
        cout << "Please enter the number of players (2 or more): " << endl;
        cin >> numPlayers;
        cout << endl;
    }
    
    Player player[numPlayers]; //Create array of Player objects based on number of players.
    
    PlayerInit(player, numPlayers); //Roll dice and assign them to players.
    
    ShowMenu(player, currentPlayer, numPlayers, guess); //Initiate main gameplay loop.
    
    return 0; //Exit gracefully.
}



