/*
File: wordle.cpp
Author: Atyub Ahmad
Date: 2/21/2022
Description: This program allows you to play the popular game "Wordle"
 */


#include <iostream>
#include <fstream>
#include <ctime>
#include <string>
#include <cstdlib>
using namespace std;

// Function prototypes
void initFile();
string chooseWord(string wordList[]);
void initGame(string chosenWord, string wordList[]);
void letterChecker(string actual, string guessArray[], int currSize);
void displayBoard(string rowArray[], string guessArray[], int currSize);
void resetGame();

// Constant variable declaration and initialization
const int WORD_NUM = 2315; // Amount of words in the text file
const int MIN_NUM = 0; // Set a minimum number to help with number randomizer equation
const int MAX_SIZE = 6; // Array size
const char BLANK_SPACE = '_'; // Symbol for space under letter that isn't part of the correct word
const char WRONG_POS = '&';// Symbol for space under letter that is part of the correct word just in the wrong position
const char RIGHT_POS = '!'; // Symbol for space under letter that is part of the correct word & in the right position

int main() {
    initFile(); // Calling the function that reads the text file and starts the game

    return 0;
}

// Pre-Condition: The right file must be available
// Post-Condition: Welcome statements are outputted and words from the file are saved to an array
void initFile(){
    // This function goes through the text file and saves all the words to an array

    string potentialWord; // Declaring a variable to store words from the file
    string wordList[WORD_NUM]; // Initializing a list to store the words from the file
    int count = 0; // Initializing a counter to help store the words from the file into the list

    ifstream wordfile ("proj1_data.txt"); // opening and reading the file

    if(wordfile.is_open()){ // If statement to check if the file is open
        cout << "Welcome to UMBC Wordle" << endl;
        cout << "Your file was imported!" << endl;

        while(wordfile >> potentialWord) { // While loop to run through all of the words
            wordList[count] = potentialWord; // Saving the words from the file into the list

            count ++; // Incrementing the counter by one so the words get stored in different slots
        }

        cout << count << " words imported." << endl;
        wordfile.close();

    }else{ // Outputting an error statement if the file couldn't be opened
        cout << "Unable to open file" << endl;
    }
    chooseWord(wordList); // Calling the function that randomly chooses the word
}

// Pre-Condition: wordList[] array must be filled with the words from the file
// Post-Condition: Random word is chosen for the user to guess
string chooseWord(string wordList[]){
    /*
     * @param string wordList[]: This is an array with all the words from the text file
     * This function randomly chooses a number from 0-2315. These numbers are all
     * 'assigned' to a word in the wordList and this chooses the random word that will be
     * guessed by the user.
     */

    srand(time(NULL)); // Randomizing based off time

    string chosenWord; // Declaring a variable to store the chosen word
    int chosenNum = 0; // Initializing a variable to store the random number generated


    chosenNum  = rand() % (WORD_NUM - MIN_NUM + 1) + MIN_NUM; // Chooses a number between 0 - 2315
    chosenWord = wordList[chosenNum]; // Setting the 'key' word for this round
    //cout << chosenWord << endl;

    initGame(chosenWord, wordList); // Calls the function that deals with playing the game

    return chosenWord; // Returning the chosen word that the user has to guess

}

// Pre-Condition: Random word must be chosen from the array filled with all the words
// Post-Condition: Outputs win/lose statement based off user's guesses and calls reset function
void initGame(string word, string wordList[]){
    /*
     * @param string word: The chosen word that the user has to guess
     * @param string wordList[]: The array that contains all the words from the text file.
     * This function starts the game and takes in the user's guesses and determines whether
     * they've won or not.
     */

    string userGuess; // Variable to store user's guess
    cout << "Ok. I am thinking of a word with five letters." << endl;
    bool playGame = true; // Setting a bool for a while loop
    int guessCounter = 0; // Variable to keep track of the user's guesses
    int currSize = 0; // Variable to help with array indexing

    // Initializing an array to store the user's guesses
    string guessArray[MAX_SIZE] = {"guess", "guess", "guess", "guess", "guess", "guess"};

    // While loop to play the game till the user wins or runs out of guesses
    while(playGame){
        // Asking the user for their guess and then taking it in
        cout << "What word would you like to guess?" << endl;
        cin >> userGuess;

        bool check = true; // Setting a bool for a while loop
        // While loop to check if the user's guess is in the array or not
        while (check) {
            // For loop to go through all the words in the array to check if the user's guess is valid
            for (int i = 0; i < WORD_NUM; i++) {
                // Checking to see if the user's guess is in the array
                if (userGuess == wordList[i]) {
                    check = false; // breaking out of the 'check' while loop
                }
            }
            // Takes in a 'replacement' user guess if the previous input was not valid
            if (check) {
                cout << "This is not a word in the file" << endl;
                cin >> userGuess;
            }
        }
        // Saving the valid user guess into an array and then incrementing the size so the next guess can be saved
        guessArray[currSize] = userGuess;
        currSize++;

        guessCounter++; // Incrementing the guess counter after the user guess was determined valid

        // Calls a function to check teh letters from teh user guess to the chosen word
        letterChecker(word, guessArray, currSize);

        // Checking if the user guess is the chosen word
        if(userGuess == word){
            // Printing win statements and number of guesses taken
            cout << "Congrats you won!" << endl << "The correct word was: " << word << endl;
            cout << "It took you " << guessCounter << "/6 guesses!" << endl;
            playGame = false; // Breaking out of the 'playGame' while loop

            // If the guess counter is at 6 and the user hasn't guessed the word the user loses
        }else if(guessCounter == 6){
            // Printing lose statement
            cout << "Uh oh! You're out of guesses!" << endl << "The correct word was: " << word << endl;
            playGame = false; // Breaking out of the 'playGame' while loop
        }

    }
    resetGame(); // Calls a function that deals with restarting the game based off user input
}

// Pre-Condition: Guess must be valid to call this function
// Post-Condition: Updates the board based on the number of guesses taken and then calls display function
void letterChecker(string actual, string guessArray[], int currSize) {
    /*
     * @param string actual: The chosen word
     * @param string guessArray[]: Array with all the words the user has guessed
     * @param int currSize: The current size of the guessArray
     * This function compares the letters between the guess word and the actual word.
     * Checks to see if the letter is in the word, and if it is, is it in the right or wrong position.
     */

    // Variables that store the default board
    string codeWord0 = "_____";
    string codeWord1 = "_____";
    string codeWord2 = "_____";
    string codeWord3 = "_____";
    string codeWord4 = "_____";
    string codeWord5 = "_____";

    // For loop that goes through the first guessed word
    for (int j = 0; j < 5; j++) {
        // Checks to see if the letter is in the right position
        if (guessArray[0][j] == actual[j]) {
            codeWord0[j] = RIGHT_POS; // Saving an '!' to the necessary position

            // The rest of these 'else if' statements check to see if the letter is in the wrong position
        } else if (guessArray[0][0] == actual[j]) {
            codeWord0[0] = WRONG_POS; // Saving an '&' to the necessary position

        } else if (guessArray[0][1] == actual[j]) {
            codeWord0[1] = WRONG_POS;

        } else if (guessArray[0][2] == actual[j]) {
            codeWord0[2] = WRONG_POS;

        } else if (guessArray[0][3] == actual[j]) {
            codeWord0[3] = WRONG_POS;

        } else if (guessArray[0][4] == actual[j]) {
            codeWord0[4] = WRONG_POS;

        }
    }

    /*
        The rest of these for loops are the same as the first, but they just go through the different
        indexing in the guess array.
     */

    // Second guess
    for (int j = 0; j < 5; j++) {
        if (guessArray[1][j] == actual[j]) {
            codeWord1[j] = RIGHT_POS;

        } else if (guessArray[1][0] == actual[j]) {
            codeWord1[0] = WRONG_POS;

        } else if (guessArray[1][1] == actual[j]) {
            codeWord1[1] = WRONG_POS;

        } else if (guessArray[1][2] == actual[j]) {
            codeWord1[2] = WRONG_POS;

        } else if (guessArray[1][3] == actual[j]) {
            codeWord1[3] = WRONG_POS;

        } else if (guessArray[1][4] == actual[j]) {
            codeWord1[4] = WRONG_POS;

        }
    }

    // Third guess
    for (int j = 0; j < 5; j++) {
        if (guessArray[2][j] == actual[j]) {
            codeWord2[j] = RIGHT_POS;

        } else if (guessArray[2][0] == actual[j]) {
            codeWord2[0] = WRONG_POS;

        } else if (guessArray[2][1] == actual[j]) {
            codeWord2[1] = WRONG_POS;

        } else if (guessArray[2][2] == actual[j]) {
            codeWord2[2] = WRONG_POS;

        } else if (guessArray[2][3] == actual[j]) {
            codeWord2[3] = WRONG_POS;

        } else if (guessArray[2][4] == actual[j]) {
            codeWord2[4] = WRONG_POS;

        }
    }

    // Fourth guess
    for (int j = 0; j < 5; j++) {
        if (guessArray[3][j] == actual[j]) {
            codeWord3[j] = RIGHT_POS;

        } else if (guessArray[3][0] == actual[j]) {
            codeWord3[0] = WRONG_POS;

        } else if (guessArray[3][1] == actual[j]) {
            codeWord3[1] = WRONG_POS;

        } else if (guessArray[3][2] == actual[j]) {
            codeWord3[2] = WRONG_POS;

        } else if (guessArray[3][3] == actual[j]) {
            codeWord3[3] = WRONG_POS;

        } else if (guessArray[3][4] == actual[j]) {
            codeWord3[4] = WRONG_POS;

        }
    }

    // Fifth guess
    for (int j = 0; j < 5; j++) {
        if (guessArray[4][j] == actual[j]) {
            codeWord4[j] = RIGHT_POS;

        } else if (guessArray[4][0] == actual[j]) {
            codeWord4[0] = WRONG_POS;

        } else if (guessArray[4][1] == actual[j]) {
            codeWord4[1] = WRONG_POS;

        } else if (guessArray[4][2] == actual[j]) {
            codeWord4[2] = WRONG_POS;

        } else if (guessArray[4][3] == actual[j]) {
            codeWord4[3] = WRONG_POS;

        } else if (guessArray[4][4] == actual[j]) {
            codeWord4[4] = WRONG_POS;

        }
    }

    // Sixth guess
    for (int j = 0; j < 5; j++) {
        if (guessArray[5][j] == actual[j]) {
            codeWord5[j] = RIGHT_POS;

        } else if (guessArray[5][0] == actual[j]) {
            codeWord5[0] = WRONG_POS;

        } else if (guessArray[5][1] == actual[j]) {
            codeWord5[1] = WRONG_POS;

        } else if (guessArray[5][2] == actual[j]) {
            codeWord5[2] = WRONG_POS;

        } else if (guessArray[5][3] == actual[j]) {
            codeWord5[3] = WRONG_POS;

        } else if (guessArray[5][4] == actual[j]) {
            codeWord5[4] = WRONG_POS;

        }
    }

    // Setting an array that saves the updated board variables
    string rowArray[MAX_SIZE] = {codeWord0, codeWord1, codeWord2, codeWord3, codeWord4, codeWord5};

    // Calls a function that displays the board
    displayBoard(rowArray, guessArray, currSize);

}

// Pre-Condition: Boards must be updated and passed through to this function before getting called
// Post-Condition: Outputs the board properly based off the amount of guesses taken
void displayBoard(string rowArray[], string guessArray[], int currSize){
    /*
     * @param string rowArray[]: Array with the updated board variables
     * @param string guessArray[]: Array with teh user's guesses
     * @param int currSize: Variable that is the size of the guess array.
     * This function displays the board properly based on how many times the user has guessed.
     */

    // For loop to display the user's guess and the board correlated with that guess
    for (int i = 0; i < currSize; i++) {
        cout << guessArray[i] << endl << rowArray[i] << endl;
    }

    // These if statements determine how many blank spaces and rows to print
    // based off the current size of the guess array
    if (currSize == 1){

        for( int i = 0; i < 5; i++){
            for(int j = 0; j < 5; j++){
                cout << BLANK_SPACE;
            }
            cout << endl;
        }

    } else if (currSize == 2){

        for( int i = 0; i < 4; i++){
            for(int j = 0; j < 5; j++){
                cout << BLANK_SPACE;
            }
            cout << endl;
        }

    } else if (currSize == 3){

        for( int i = 0; i < 3; i++){
            for(int j = 0; j < 5; j++){
                cout << BLANK_SPACE;
            }
            cout << endl;
        }

    } else if (currSize == 4){

        for( int i = 0; i < 2; i++){
            for(int j = 0; j < 5; j++){
                cout << BLANK_SPACE;
            }
            cout << endl;
        }

    } else if (currSize == 5){
        cout << "_____" << endl;

    }

}

void resetGame(){
    /*
     * This function deals with resetting the game and running it again if the user wants to play again.
     */

    bool flag = true; // boolean for a do-while loop

    // Setting a do-while loop to deal with asking the user if they want to play again
    do {
        string playAgain; // Variable to store user input
        cout << "Another game? y/n " << endl; // Asking the user if they want to play again
        cin >> playAgain; // Getting their answer

        // If/Else statement to execute the necessary action based off user input
        if (playAgain == "y" or playAgain == "yes") {
            initFile(); // If user inputs 'y' or yes then call the first function to play the game again
            flag = false; // Breaking out of teh do-while loop
        } else {
            cout << "Thank you for playing!" << endl; // If user inputs anything else but 'y', outputs the bye statement
            flag = false; // Breaking out of the do-while loop

        }
    }while(flag); // runs while the flag is true
}
