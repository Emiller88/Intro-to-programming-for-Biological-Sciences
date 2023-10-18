#include <iostream>
#include <stdlib.h>
#include <time.h>

//Function Declaration
void printTitle();
void displayCard(int card);
void swapGreater(int& x, int& y);
int reddog(int bank);

using namespace std;

int main()
{
    int bank = 5000;
    char yOrN = 'y';
    srand(time(NULL));  // initialize random seed
    //Make Title
    printTitle();
    //Display starting bank value to user.
    cout << "You have $" << bank << "." << endl;
    do
    {
        //Call red dog game function
        bank = reddog(bank);
        //Show new bank to user
        cout << "You have $" << bank << "." << endl;
        //If bank is empty end game
        if (bank == 0)
        {
            cout << "Game Over";
            return 0;
        }
        //Ask user if they want to continue playing
        cout << "Play again(y/n):   ";
        cin >> yOrN;
    } while (yOrN == 'y');

    return 1;

}

void printTitle()
{
    cout << "***********************************************************" << endl
        << "* WELCOME TO REDDOG *" << endl
        << "***********************************************************" << endl;
}

//Takes value of card and displays letter/ number for it.
void displayCard(int cardVal)
{
    switch (cardVal)
    {
    case 0:
        cout << 'A';
        break;
    case 1:
        cout << '2';
        break;
    case 2:
        cout << '3';
        break;
    case 3:
        cout << '4';
        break;
    case 4:
        cout << '5';
        break;
    case 5:
        cout << '6';
        break;
    case 6:
        cout << '7';
        break;
    case 7:
        cout << '8';
        break;
    case 8:
        cout << '9';
        break;
    case 9:
        cout << "10";
        break;
    case 10:
        cout << 'J';
        break;
    case 11:
        cout << 'Q';
        break;
    case 12:
        cout << 'K';
        break;
    default:
        break;
    }

    cout << endl;
}

//Makes x the larger card to simplify comparisions
void swapGreater(int & x, int & y)
{  
    if (x < y)
    {
        int save1 = y;
        y = x;
        x = save1;
    }
}

//The Game
int reddog(int bank)
{
    int bet = 0, random, card1Val, card2Val, card3Val;
    bool betCheck = true;

    do
    {
        betCheck = true;
        cout << "Enter your bet: "; //Get user bet
        cin >> bet;

        if (bet > bank || bet <= 0) //Check for valid Bet
        {
            cout << "Invalid bet. Please reenter." << endl;
            betCheck = false;
        }
    } while (betCheck == false); //Repeat if invalid bet

    //Random Number for Card 1
    random = (rand() % 51) + 1;  //makes number in 0 to 51 range
    //Find what card it is
    card1Val = random % 13;

    //Random Number for Card 2  Repeat of 1
    random = (rand() % 51) + 1;
    //Find what card it is
    card2Val = random % 13;

    

    cout << "Card 1: ";
    displayCard(card1Val);
    cout << endl << "Card 2: ";
    displayCard(card2Val);

    swapGreater(card1Val, card2Val);

    //Push
    if (card1Val == (card2Val + 1) )
    {
        cout << "We Push." << endl;
        return bank;
    }

    //Random Number for Card 3  Repeat of 1 Just incase
    random = (rand() % 51) + 1;
    //Find what card it is
    card3Val = random % 13;

    //Same Cards
    if (card1Val == card2Val)
    {
        cout << "Spread is:  11-1" << endl << "Card 3: ";
        displayCard(card3Val);

        if (card1Val == card3Val)
        {
            cout << "You win!" <<endl;
            bank += (bet * 11);
        }
        else
        {
            cout << "We Push." << endl;
        }
    }
    //Differ by two
    else if (card1Val == (card2Val + 2))
    {
        cout << "Spread is: 5-1" << endl;

        //Offer to Double
        if( bet <= (bank / 2) )
        {
            cout << "Do you wish to double your bet?  (y/n):  ";
            char choice;
            cin >> choice;
            if (choice == 'y')
                bet *= 2;
        }
        cout << "Card 3: ";
        displayCard(card3Val);

        if (card3Val <= card1Val && card3Val >= card2Val)
        {
            cout << "You win!" << endl;
            bank += (bet * 5);
        }
        else
        {
            cout << "You lose!" << endl;
            bank -= bet;
        }

    }
    //Differ by three
    else if (card1Val == (card2Val + 3))
    {
        cout << "Spread is: 4-1" << endl;

        //Offer to Double
        if (bet <= (bank / 2))
        {
            cout << "Do you wish to double your bet?  (y/n):  ";
            char choice;
            cin >> choice;
            if (choice == 'y')
                bet *= 2;
        }
        cout << "Card 3: ";
        displayCard(card3Val);

        if (card3Val <= card1Val && card3Val >= card2Val)
        {
            cout << "You win!" << endl;
            bank += (bet * 4);
        }
        else
        {
            cout << "You lose!" << endl;
            bank -= bet;
        }
    }
    //Differ by Four
    else if (card1Val == (card2Val + 4))
    {
        cout << "Spread is: 2-1" << endl;

        //Offer to Double
        if (bet <= (bank / 2))
        {
            cout << "Do you wish to double your bet?  (y/n):  ";
            char choice;
            cin >> choice;
            if (choice == 'y')
                bet *= 2;
        }
        cout << "Card 3: ";
        displayCard(card3Val);

        if (card3Val <= card1Val && card3Val >= card2Val)
        {
            cout << "You win!" << endl;
            bank += (bet * 2);
        }
        else
        {
            cout << "You lose!" << endl;
            bank -= bet;
        }
    }
    //Otherwise
    else
    {
        cout << "Spread is: 1-1" << endl;

        //Offer to Double
        if (bet <= (bank / 2))
        {
            cout << "Do you wish to double your bet?  (y/n):  ";
            char choice;
            cin >> choice;
            if (choice == 'y')
                bet *= 2;
        }
        cout << "Card 3: ";
        displayCard(card3Val);

        if (card3Val <= card1Val && card3Val >= card2Val)
        {
            cout << "You win!" << endl;
            bank += bet;
        }
        else
        {
            cout << "You lose!" << endl;
            bank -= bet;
        }
    }
    return bank;
}
