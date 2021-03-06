#include <cstdlib>
#include <ctime>
#include <iostream>
#include <string>
#include <iomanip>
#include "colormod.h"
using namespace std;

//player class: used to hold player name and balance
class Player {
  public:
    string name;
    float balance;
    float starting_balance;

  public:
    Player() {
      name = "";
      balance = 0;
      starting_balance = 10000;
    }
};

//method getMenu(), which displays the menu
int getMenu() {
   //red and green color modifiers
   Color::Modifier red(Color::FG_RED);
   Color::Modifier green(Color::FG_GREEN);
   //variable that represents the number chosen for the menu
   int menuChoice;
   //displays the menu
   cout << string(50, '\n');
   cout << red << "\n     Welcome to High-Low Card Wiz";
   cout << "\n\nMAIN MENU";
   cout << green << "\n1. Play Game Show Mode";
   cout << "\n2. Play The High-low 10 Board Card Challenge ONLY ";
   cout << "\n3. Play Bonus 7 Board Money Card Challenge ONLY";
   cout << "\n4. Display Game Rules";
   cout << "\n5. Exit";
   cout << red <<"\n\nPlease make a choice (1-5) ";
   cin >> menuChoice;  //gets the menuChoice
   //input validation: if menuChoice is not an integer
   if (cin.fail())
      {
        cin.clear();
        cin.ignore(100, '\n');
      }
   //input validation for menuChoice not from 1-5
   while (menuChoice != 1 && menuChoice != 2 && menuChoice != 3 && menuChoice != 4 && menuChoice != 5)
   {
      cout << "Sorry, invalid choice. Please try again.\n";
      cout << "\n\nPlease make a choice (1-5) ";
      cin >> menuChoice;  //gets the menuChoice
      //input validation: if menuChoice is not an integer
      if (cin.fail())
      {
        cin.clear();
        cin.ignore(100, '\n');
      }
   }
   //returns the menu number chosen
   return menuChoice;
}

//**Start of MAIN function**
int main() {
  //card function prototypes
  string getRank;
  int getRankNo(string);
  string getSuit;
  void getRules();
  void getCards(string [], string suit []);
  void checkForDuplicates(string [], string []);
  //game function prototypes
  int tenCardGame(string [], string []);
  int sevenCardMoneyGame(string [], string []);

  //define variables
  int menuChoice = 0;  //menu number
  bool menuFlag = false; //flag to terminate the game
  int gameValue = 0; //determines if player will continue to the second round in game show mode (0=no, 1=yes)
  string rankArray [35]; //holds the values of the card ranks
  string suitArray [35]; //holds the values of the card suits

  while(menuFlag == false) {
     //call function to load the cards into the game array
     getCards( rankArray, suitArray);

     //call function that checks for duplicate cards
     checkForDuplicates( rankArray, suitArray);

     //call function that displays the menu
     menuChoice = getMenu();

     if(menuChoice == 1)
     {
       //call function that plays 10 card game
       gameValue = tenCardGame(rankArray, suitArray);

       //call function that plays 7 card game if player wins 10 card game
       if(gameValue == 1)
       {
          //call function that plays 7 card game
          sevenCardMoneyGame(rankArray, suitArray);
       }
     }
     else if(menuChoice == 2)
     {
       //call function that plays 10 card game
       tenCardGame(rankArray, suitArray);
     }
     else if(menuChoice == 3)
     {
       //call function that plays 7 card game
       sevenCardMoneyGame(rankArray, suitArray);
     }
     else if(menuChoice == 4)
     {
       //call function that displays the rules
       getRules();
     }
     else if(menuChoice == 5){
         //exits game
         cout << "Bye, see you later.";
         menuFlag = true;
     }
  }
  return 0;
}
//**End of MAIN function**

//function that obtains a random rank and returns the string value
string getRank() {
      srand((unsigned) time(NULL));
      int rank = (rand() % 13 + 1);
      if (rank == 1) return "Ace";
      if (rank == 2) return "Two";
      if (rank == 3) return "Three";
      if (rank == 4) return "Four";
      if (rank == 5) return "Five";
      if (rank == 6) return "Six";
      if (rank == 7) return "Seven";
      if (rank == 8) return "Eight";
      if (rank == 9) return "Nine";
      if (rank == 10) return "Ten";
      if (rank == 11) return "Jack";
      if (rank == 12) return "Queen";
      if (rank == 13) return "King";
      else return "Unknown rank";
    }

//function that obtains a string rank value and returns the integer rank value
  int getRankNo(string rank) {
      if (rank == "Two") return  1;
      if (rank == "Three") return 2;
      if (rank == "Four") return 3;
      if (rank == "Five") return 4;
      if (rank == "Six") return 5;
      if (rank == "Seven") return 6;
      if (rank == "Eight") return 7;
      if (rank == "Nine") return 8;
      if (rank == "Ten") return  9;
      if (rank == "Jack") return 10;
      if (rank == "Queen") return 11;
      if (rank == "King") return 12;
      if (rank == "Ace") return 13;
      else return 0;
    }
//function that obtains a random suit and returns the string value
string getSuit() {
     srand((unsigned) time(NULL));
     int suit = (rand() % 4 + 1);
     if (suit == 1) return "Diamonds";
     if (suit == 2) return "Hearts";
     if (suit == 3) return "Spades";
     if (suit == 4) return "Clubs";
     else return "Unknown suit";
    }

//function that displays the rules on the screen
void getRules(){
   //blue color modifier
  Color::Modifier blue(Color::FG_BLUE);
  cout << string(50, '\n');
  cout << blue <<  "\nHigh-Low Wiz Game Show Mode:";
   cout << "\n*Once you win the High-low 10 Board Card Challenge,\n";
   cout << "you can then go onto the 7 board Money Card Challenge.\n";
  cout << "\nThe High-low 10 Board Card Challenge:";
  cout << "\n*You have 5 continues to finish the 10-card game board.";
  cout << "\n*You lose a continue if you have an incorrect answer.";
  cout << "\n*When you have no continues left you have to complete the game board.";
  cout << "\nwithout any incorrect guesses or the game is over.";
   cout << "\n*You have 3 chances to freeze your card after a correct";
  cout << "\nanswer, otherwise you have to go back to the beginning ";
  cout << "\nor at the last place you used a freeze";
  cout << "\n*You can also change your base card once per round.";
  cout << "\n*Remember, a tie results in a loss.\n";
  cout << "\nThe 7 board Money Card Challenge: ";
  cout << "\n*You are starting out with $10,000";
  cout << "\nYour bet must be between $1,000 and $10,000\n";
      cout << "and be multiples of $1,000.\n";
  cout << "*On the final card, you must bet at least half your balance. ";
  cout << "\n*One card may be changed before any turn in this round.";
  cout << "\n*Remember, a tie results in a loss.\n";
 
  cout << "\n\nPress ENTER to return to the main menu.";
  cin.get();
}

//function that puts the rank and suit into the game card arrays
void getCards(string rank[], string suit[]){
 for (int index = 0; index < 35; index ++)
  {
     rank [index] = getRank();
     suit [index] = getSuit();
  }
}
  //checks for duplicate cards and replaces them with another random card
void checkForDuplicates(string rank[], string suit[]){
  string test1;
  string test2;
  int repeat = 0;
  bool noRepeats = false;
  while (noRepeats == false){
    noRepeats = true;
    for (int index = 0; index <35; index ++){
      test1 = rank [index];
      test2 = suit[index];
      for (int index2 = 0; index2 <35; index2 ++){
         if(rank [index2] == test1){
            if ( suit [index2] == test2)
            {
               repeat +=1;
               if(repeat == 2){
                   rank [index] = getRank();
                   suit [index] = getSuit();
                    noRepeats = false;
                    repeat = 1;
               }
            }
         }
      }
      repeat = 0;
    }
  }
//test code.  prints answer array
  //for (int index = 0; index < 35; index ++){
     //cout << rank [index] << "  ";
    // cout << suit [index] << endl;}
}

//function that plays the 10 card game
int tenCardGame(string rankArray[], string suitArray[]){
  int dealer_rank = 0;
  int player_rank = 0;
  float bet = 0;
  char choice;
  char freezeIt;
  Player player = Player();
  int cardCount = 0;
  bool roundLoss = false;
  int freezePoint = 0;
  int turns = 5;
  int saves = 3;
  int ctr = 1;
  bool changeFlag = false;
  int changeCount = 15;
  //color modifiers
  Color::Modifier def(Color::FG_DEFAULT);
  Color::Modifier red(Color::FG_RED);
  Color::Modifier blue(Color::FG_BLUE);
  Color::Modifier green(Color::FG_GREEN);
  //get name from the player
  cout << def << "\n\nPlayer 1, what is your name? ";
  cin.ignore();
  getline(cin, player.name);
  //input validation for name not entered
  while( player.name == ""){
    cout << def << "\nPlayer 1, what is your name? ";
    cin.ignore();
    getline(cin, player.name);
  }
  cout << "Okay, " << player.name << ". Let us begin.";
  cout << "\npress any key TWICE to continue.";
  cin.ignore();
      cin.get();

  //plays game while player has not lost, card position is less than 10, and turns left are greater or equal to zero 
  while(roundLoss == false && cardCount < 9 && turns >= 0)
  {
     cout << string(50, '\n');
     cout <<green << "\n\nContinues Left: " << turns;
     cout << "\nFreezes Left: " << saves << def << "\n\n";
     if(cardCount == 0){
        cout << "Your base card is the " << red << rankArray [cardCount] << " of " << suitArray [cardCount];
     }
     else{
        cout << def << "Card # " << (cardCount+1) << " is the " << red << rankArray [cardCount] << " of " << suitArray [cardCount];
     }
     //function call that gets the current random card rank
     dealer_rank = getRankNo(rankArray [cardCount]);

     cout <<def << "\nWill Card # " << (cardCount+2) << " be higher or lower? ";
      if(changeFlag == false ){
            cout << "\nEnter \"c\" to change your base card, or \n";}

        cout << "Enter \"h\" for higher or \"l\" for lower: ";
        cin >> choice;
        //input validation
        while (choice != 'h' && choice != 'l' && choice != 'c')
            {
              cout << "Sorry, invalid choice. Please try again.\n";
              cin >> choice;
            }
        //input validation
        while (choice == 'c' && changeFlag == true)
            {
              cout << "Sorry, invalid choice. Please try again.\n";
              cin >> choice;
            }
         //changes the base card
         if(choice =='c' && changeFlag == false){
           rankArray [cardCount] = rankArray [changeCount];
           suitArray [cardCount] = suitArray [changeCount];
           dealer_rank = getRankNo(rankArray [cardCount]);
           changeCount +=1;
           changeFlag = true;
           cout << "\nYour base card is now the " << red <<  rankArray [cardCount] << " of " << suitArray [cardCount] << endl;
           cout <<def << "\nWill Card # " << (cardCount+2) << " be higher or lower? ";
            cout << "Enter \"h\" for higher or \"l\" for lower: ";
            cin >> choice;
            //input validation
            while (choice != 'h' && choice != 'l')
            {
              cout << "Sorry, invalid choice. Please try again.\n";
              cout << "Enter \"h\" for higher or \"l\" for lower: ";
              cin >> choice;
            }
         }
     //function call that gets the next random card rank
     player_rank = getRankNo(rankArray [cardCount+1]);

     cout << "\nCard # " << (cardCount+2) << " is the " << blue << rankArray [cardCount+1] << " of " << suitArray [cardCount+1];

    //if the player makes a wrong guess
    if ((choice == 'h' && dealer_rank > player_rank) ||
        (choice == 'l' && dealer_rank < player_rank) ||
        (choice == 'h' && dealer_rank == player_rank) ||
        (choice == 'l' && dealer_rank == player_rank))
        {

      cout << def << "\n\nNo, Incorrect guess, " <<  player.name;
      if (turns > 0)
      {
         cout << "\nYou have to go back to card # " << freezePoint+1 <<"\n";
         cout << "\n\nPress ENTER to continue.";
         cin.ignore();
         cin.get();
      }
           cardCount = freezePoint;
           rankArray [cardCount+1] = rankArray [ctr+ 9];
           suitArray [cardCount+1] = suitArray [ctr +9];
           ctr +=1;
           turns -=1;
           changeFlag = false;
    }
    else
    {
      //if the player makes a correct guess
      cout << def << "\nYES, correct guess, " << player.name;

      if(cardCount < 8)
      {
        //ask if the player wants to freeze their card or continue
        if (saves >0){
         cout << "\n\nDo you want to freeze your card (f) or continue (c). ";
         cin >> freezeIt;
         //if the player wants to freeze their card
         if (freezeIt == 'f')
         {
           freezePoint = (cardCount+1);
           cardCount +=1;
           saves -=1;
           changeFlag = false;
           cout << "\nYou have frozen your position on the board. ";
           cout << "\nLet's go to the next card. ";
           cout << "\n\nPress ENTER to continue.";
           cin.ignore();
           cin.get();
         }
         else{
         //goes to the next card without freezing  
         cout << "\nLet's go to the next card. ";
         cout << "\n\nPress ENTER to continue.";
         cin.ignore();
         cin.get();
         cardCount +=1;
         }
        }
        else{
          //last turn sudden death message
           cout << "\nLast Round. The next wrong answer results in  ";
           cout << "\na game over. ";
            cout << "\n\nPress ENTER to continue.";
           cin.ignore();
           cin.get();
           cardCount +=1;
        }
      }
    }
  }
  //if the player is out of turns
  if(turns < 0)
  {
    cout << "\n\nSorry, you lose.  GAME OVER.";
    return 2;
    cout << "\n\nPress ENTER to continue.";
    cin.ignore();
    cin.get();
  }
  //if the player completes the board
  else{
  cout << "\n\nCongratulations, You Win the Challenge!!!";
  return 1;
   cout << "\n\nPress ENTER to continue.";
         cin.ignore();
         cin.get();
  }

}

//function that plays the 7 card money game
int sevenCardMoneyGame(string rankArray[], string suitArray[]){
  int dealer_rank = 0;
  int player_rank = 0;
  float bet = 0;
  char choice;
  char freezeIt;
  Player player = Player();
  int cardCount = 0;
  bool roundLoss = false;
  int freezePoint = 0;
  int turns = 1;
  bool changeFlag = false;
  int changeCount = 15;
  //color modifiers
  Color::Modifier def(Color::FG_DEFAULT);
  Color::Modifier red(Color::FG_RED);
  Color::Modifier blue(Color::FG_BLUE);
  //get name from the player
  cout << def <<"\n\nPlayer 1, what is your name? ";
  cin.ignore();
  getline(cin, player.name);
  //input validation for name not entered
  while( player.name == ""){
    cout << def << "Player 1, what is your name? ";
    cin.ignore();
    getline(cin, player.name);
  }
  cout << "Okay, " << player.name << ". Let us start the 7 board Money Card Challenge.\n";
  cout << "\npress any key TWICE to continue.";
  cin.ignore();
  cin.get();
  //call class that gets the player balance
  player.balance = player.starting_balance;
  cardCount = 20; //card array positions
  changeCount = 27;  //card array positions
  turns = 0;
  changeFlag = false;

  //plays game while player balance is greater than zero or turns are less than 7
  while (player.balance > 0 && (player.balance < player.starting_balance * 5) && turns < 6 ) {
    cout << string(50, '\n');
    cout << setprecision(2) << fixed  << player.name << " you now have $" << player.balance << ". " << endl;
    cout << "\nCard # " << (cardCount-19) << " is the " << red << rankArray [cardCount] << " of " << suitArray [cardCount] << def << endl;
     //function call that gets the current random card rank
     dealer_rank = getRankNo(rankArray [cardCount]);
      //ask if player wants to change their base card if they have not already
      if(changeFlag == false ){
          cout << "\nDo you want to change your base card (y) or (n)? \n";
          cin >> choice;
          //input validation
           while (choice != 'y' && choice != 'n')
            {
              cout << "Sorry, invalid choice. Please try again.\n";
              cout << "\nDo you want to change your base card (y) or (n)? \n";
              cin >> choice;
            }
          //changes base card if answer is yes and card has not been changed
          if (choice == 'y'){
              rankArray [cardCount] = rankArray [changeCount];
              suitArray [cardCount] = suitArray [changeCount];
              dealer_rank = getRankNo(rankArray [cardCount]);
              changeCount +=1;
              changeFlag = true;
              cout << "\nYour base card is now the " << red << rankArray [cardCount] << " of " << suitArray [cardCount] << def << endl;
            }
        }
     //player must bet at least half on final card
     if(turns == 5){
        cout << "\nFinal card. \nYou must bet more than half your balance. " << endl;
        cout << player.name << ", you have $" << player.balance << ". " << endl;
        cout << "Your minimum bet is " << player.balance/2 << endl;
        cout << "How much money do you want to bet? ";
        cin >> bet;
        //input validation on bet
        while (bet < player.balance/2) {
        cout << "Sorry, you must bet more than half your balance.\n";
        cout << "Bet again.  How much money do you want to bet? ";
        cin >> bet;}
     }
     else{
    // bets are between $1000 and 10,000
     cout << "\nYour minimum bet is $1,000 " << endl;
     cout << "Your maximum bet is $10,000 " << endl;
    cout << "How much money do you want to bet? ";
    cin >> bet;
    //input validation for the bet
    while (bet != 1000 && bet != 2000 && bet != 3000 && bet != 4000 && bet != 5000 && bet != 6000
             && bet != 7000 && bet != 8000 && bet != 9000 && bet != 10000) {
      cout << "Sorry, your bet must be greater than $1,000.\n";
      cout << "and multiples of $1,000.\n";
        cout << "Bet again.  How much money do you want to bet? ";
        cin >> bet;
      }
     }
      while (bet > player.balance) {
        cout << "Sorry, you don't have enough money to make that bet.\n";
        cout << "Bet again.  How much money do you want to bet? ";
        cin >> bet;
      }

     cout << "Will Card # " << (cardCount-18) << " be higher or lower? "
         << "Enter \"h\" for higher or \"l\" for lower: ";
     cin >> choice;
    //function call that gets the next random card rank
     player_rank = getRankNo(rankArray [cardCount+1]);
     cout << "\nCard # " << (cardCount-18) << " is the " << blue << rankArray [cardCount+1] << " of " << suitArray [cardCount+1] << def << endl;
    //if player makes an incorrect guess
    if ((choice == 'h' && dealer_rank > player_rank) ||
        (choice == 'l' && dealer_rank < player_rank) ||
        (choice == 'h' && dealer_rank == player_rank) ||
        (choice == 'l' && dealer_rank == player_rank))
        {
      player.balance -= bet;  //decrease balance
      cout << setprecision(2) << fixed  <<  "\nSorry, Incorrect. Too bad " + player.name << ". You lose $" << bet << ".\n";
      cout << "\n\nPress ENTER to continue.";
           cin.ignore();
           cin.get();
           cardCount+=1;
           turns+=1;
           changeFlag = false;
    } else {
      //if player makes a correct guess
      player.balance += bet; //increment balance
       cout << setprecision(2) << fixed << "\nCORRECT!!! Congratulations " + player.name << ". You win $" << bet << "!\n";
       cout << "\n\nPress ENTER to continue.";
           cin.ignore();
           cin.get();
           cardCount +=1;
           turns +=1;
           changeFlag = false;
    }
    bet = 0;
  }
  //if player loses all their money
  if (player.balance <= 0) {
    cout << "Too bad " + player.name << ". "
         << "You are out of money!";
    cout << "\n\nSorry, you lose.  GAME OVER.";
    return 2;
  } else {
    //if player wins
    cout << "YOU WIN the game, " + player.name << "!";
    cout << setprecision(2) << fixed  << "\nYou have won $" << player.balance << "!";
    return 1;
  }
}