////////////////////////////////////////////////////////////////////////////////
//
//  File           : BlackJack.c
//  Description    : Black Jack Game
//
//   Author        : Saad Iqbal
//

// Include Files
#include <stdio.h>
#include <time.h>
#include <stdlib.h>
#include <conio.h>


// Defines
#define NUM_CARDS 52
#define MAX_CARDS 11
#define SPADE   "\xE2\x99\xA0"
#define CLUB    "\xE2\x99\xA3"
#define HEART   "\xE2\x99\xA5"
#define DIAMOND "\xE2\x99\xA6"

// Functions

////////////////////////////////////////////////////////////////////////////////
//
// Function     : print_card
// Description  : print the card from the integer value
//
// Inputs       : card - the card to print
// Outputs      : 0 always

int print_card( int card ) {

    // CODE HERE
    char card_faces[] = "234567891JQKA";
    char *card_suits[] = { SPADE, CLUB, HEART, DIAMOND };
    int suit = card / 13, cardty = card % 13;
    if ( cardty == 8 ) {
        printf( "10%s ", card_suits[suit] );
    } else {
        printf( "%c%s ", card_faces[cardty], card_suits[suit] );
    }

    // Return zero
    return( 0 );
}

////////////////////////////////////////////////////////////////////////////////
//
// Function     : print_cards
// Description  : print a number of cards (no more than 13 on one line)
//
// Inputs       : cards - the array of cards to print
//                num_cards - the number of cards to print
// Outputs      : 0 always

int print_cards( int cards[], int num_cards) {
    for(int i=0; i < num_cards; i++ ){
        if(i%13 == 0 ){
            printf("%c",'\n');
        }
        print_card(cards[i]);
    }
}

void swap(int *xp, int *yp) 
{ 
    int temp = *xp; 
    *xp = *yp; 
    *yp = temp; 
} 

////////////////////////////////////////////////////////////////////////////////
//
// Function     : shuffle_cards
// Description  : print a number of cards (no more than 13 on one line)
//
// Inputs       : cards - the array of cards to print
//                num_cards - the number of cards to print
// Outputs      : 0 always

int shuffle_cards(int cards[], int num_cards ) {
    srand(time(NULL)) ;
  
    for (int i = num_cards - 1; i > 0; i--)  
    {  
        int j = rand() % (i + 1);  
        swap(&cards[i], &cards[j]);
    }

}

////////////////////////////////////////////////////////////////////////////////
//
// Function     : getFaceValue
// Description  : Return the face value of the given card
//
// Inputs       : card number from deck
//                
// Outputs      : Face value and for Ace it returns 0 to access 1 or 11 later in our handvalue function

int getFaceValue(int card){

    while(card > 13){
        card = card % 13;
    }
    if(card == 0){
        return 2;
    }
    if(card == 1){
        return 3;
    }
    if(card == 2){
        return 4;
    }
    if(card == 3){
        return 5;
    }
    if(card == 4){
        return 6;
    }
    if(card == 5){
        return 7;
    }
    if(card == 6){
        return 8;
    }
    if(card == 7){
        return 9;
    }
    if(card == 8){
        return 10;
    }
    if(card == 9){
        return 10;
    }
    if(card == 10){
        return 10;
    }
    if(card == 11){
        return 10;
    }
    if(card == 12){
        return 0;
    }

}

////////////////////////////////////////////////////////////////////////////////
//
// Function     : hand_value
// Description  : return the value of the hand
//
// Inputs       : cards - the array of cards in the hand
//                num_cards - the number of cards in the hand
// Outputs      : 0 always

int hand_value( int cards[], int num_cards ) {
    int input = 0;
    int sum = 0;
    for(int i=0; i<num_cards; i++){
        sum += getFaceValue(cards[i]);
        if(getFaceValue(cards[i]) == 0){
            input = rand() % 1;
            if(input == 0){
                sum += 11;
            }else
            {
                sum += 1;
            }
        }
    }
    return sum;
}
////////////////////////////////////////////////////////////////////////////////
//
// Function     : sort_cards
// Description  : sort a collection of cards
//
// Inputs       : hand - the cards to sort
//                num_cards - the number of cards in the hand
// Outputs      : 0 always

int sort_cards( int hand[], int num_cards ) {
   int i, j; 
   for (i = 0; i < num_cards-1; i++)       
       // Last i elements are already in place    
       for (j = 0; j < num_cards-i-1; j++)  
           if (hand[j] > hand[j+1]) 
              swap(&hand[j], &hand[j+1]); 

    for (i = 0; i < num_cards-1; i++)       
       // Last i elements are already in place    
       for (j = 0; j < num_cards-i-1; j++)  
           if (hand[j]%13 > hand[j+1]%13) 
              swap(&hand[j], &hand[j+1]); 

    return 0;
}

////////////////////////////////////////////////////////////////////////////////
//
// Function     : dealer_play
// Description  : dealer decision to hit or stand (hit on anything less 
//                than 17)
//
// Inputs       : hand - cards dealer has
//                num_cards - the number of cards in player hand
// Outputs      : 0 = stand, 1 = hit

int dealer_play( int hand[], int num_cards ) {
    if(hand_value(hand, num_cards)>= 17){
        return 0;
    }
    else{
        return 1;
    }
}

////////////////////////////////////////////////////////////////////////////////
//
// Function     : player_play
// Description  : player decision to hit or stand
//
// Inputs       : hand - cards player has
//                num_cards - the number of cards in player hand
//                dealer_card - the dealers face up card
// Outputs      : 0 = stand, 1 = hit

int player_play( int hand[], int num_cards, int dealer_card ) {

    int randomChoice = rand() % 2;

    if(randomChoice == 0){
        printf("Player stands (%d): ", hand_value(hand, num_cards));
        for(int i=0; i<num_cards; i++){
            print_card(hand[i]);
        }
        printf("\n");
        return 0;
    }

    if(randomChoice == 1){
        hand[num_cards++] = dealer_card;
        printf("Player hits (%d): ", hand_value(hand, num_cards));
        for(int i=0; i<num_cards; i++){
            print_card(hand[i]);
        }
        printf("\n");      
    }
    return 1;
}

////////////////////////////////////////////////////////////////////////////////
//
// Function     : play_hand
// Description  : play a hand of black jack
//
// Inputs       : deck - the whole deck of cards
//                num_cards - the number of cards in the deck
//                player_money - pointer to player amount of money
// Outputs      : 1 if player wins, 0 if dealer wins

int play_hand( int deck[], int num_cards, float *player_money ) {

    *(player_money) -= 5; //Bet Fee
    printf("---- New hand -----\n");
    int Track[52] = {0}; //To keep the track of already used cards 
    //Step 8(a)
    shuffle_cards(deck,num_cards);

    int playerHand[MAX_CARDS];
    int DealerHand[MAX_CARDS];
    srand(time(NULL));
    int randomCard;
    int playerCards = 1, DealerCards = 1;
    
    //Assign 2 random Cards for Player
    while(playerCards>=0){
        randomCard = rand() % 52;
        while(Track[randomCard] == 1 ){
            randomCard = rand() % 52;
        }

        Track[randomCard] = 1;
        playerHand[playerCards--] = deck[randomCard];
    }

    playerCards = 2;
    
    //Assign 2 random Cards for Dealer
    while(DealerCards>=0){
        randomCard = rand() % 52;
        while(Track[randomCard] == 1 ){
            randomCard = rand() % 52;
        }

        Track[randomCard] = 1;
        DealerHand[DealerCards--] = deck[randomCard];
    }
    DealerCards = 2;
    
    /* Print Both Hands */
    printf("Dealer Cards: ");
    print_card(playerHand[0]);
    printf("XX\n\n");


    printf("Player Cards: ");
    for(int i=0; i<playerCards; i++){
        print_card(playerHand[i]);
    }
    printf("\n");



    // printf("Player Hand Value: %d\n", hand_value(playerHand, playerCards));
    if(hand_value(playerHand, playerCards) == 21){
        *(player_money) += 7.5;
        printf("Player has Blackjack!, wins $7.50\n");
        return 1;
    }


    while(1){
            /* Pass the up Card */
        if(player_play(playerHand, playerCards, DealerHand[1]) == 1 ){
            playerHand[++playerCards] = DealerHand[1];
            DealerCards--;

            /* Now face up card was provided to the player, give another random card to dealer for his move */
            randomCard = rand() % 52;
            while(Track[randomCard] == 1 ){
                randomCard = rand() % 52;
            }
            Track[randomCard] = 1;
            DealerHand[++DealerCards] = deck[randomCard];

             // printf("Player Hand Value: %d\n", hand_value(playerHand, playerCards));
            if(hand_value(playerHand, playerCards) == 21){
                *(player_money) += 7.5;
                printf("Player Wins!\n");
                return 1;
            }
            if(hand_value(playerHand, playerCards) > 21){
                *(player_money) -= 5;
                printf("Player BUSTS ... dealer wins!\n");
                return 0;
            }
        }
        else
        {
            if(dealer_play(DealerHand, DealerCards) == 1){
                if(hand_value(DealerHand, DealerCards) == 21){
                    *(player_money) -= 5;
                    printf("Dealer wins\n");
                    return 0;              
                }
                if(hand_value(DealerHand, DealerCards) > 21){
                    *(player_money) += (5*2);
                    printf("Dealer BUSTS ... player wins!\n");
                    return 1;
                }
                else{
                    printf("Dealer stands (%d): ", hand_value(DealerHand, DealerCards));
                        for(int i=0; i<DealerCards; i++){
                        print_card(DealerHand[i]);
                    }
                    printf("\n");
                }
            }
            else
            {
                while(dealer_play(DealerHand, DealerCards) == 0){
                    randomCard = rand() % 52;
                    while(Track[randomCard] == 1 ){
                        randomCard = rand() % 52;
                    }
                    Track[randomCard] = 1;
                    DealerHand[DealerCards++] = deck[randomCard];
                    printf("Dealer hits (%d): ", hand_value(DealerHand, DealerCards));
                    for(int i=0; i<DealerCards; i++){
                        print_card(DealerHand[i]);
                    }
                    printf("\n");                
                    if(hand_value(DealerHand, DealerCards) > 21){
                        *(player_money) += (5*2);
                        printf("Dealer BUSTS ... player wins!\n");
                        return 1;
                    }

                    if(hand_value(DealerHand, DealerCards) < hand_value(playerHand, playerCards)){
                        *(player_money) += (5*2);
                        printf("player wins!\n");
                        return 1;
                    }    

                    if(hand_value(DealerHand, DealerCards) > hand_value(playerHand, playerCards)){
                        *(player_money) -= (5);
                        printf("Dealer wins!\n");
                        return 0;
                }  

                } 
            }
        }
    }
}


float max_element(float arr[], int n) 
{ 
    int i; 
     
    // Initialize maximum element 
    float max = arr[0]; 
  
    // Traverse array elements from second and 
    // compare every element with current max   
    for (i = 1; i < n; i++) 
        if (arr[i] > max) 
            max = arr[i]; 
  
    return max; 
} 
  

////////////////////////////////////////////////////////////////////////////////
//
// Function     : show_player_money_histogram
// Description  : Display a histogram of the player funds by hands
//
// Inputs       : money_rounds - the list of player money by hand number
//                last_round - the hand number where the game stopped
// Outputs      : 0 always

int show_player_money_histogram( float money_rounds[], int last_round ) {
float maxEle = max_element(money_rounds, last_round); 
  
    for (int i = maxEle; i >= 0; i--) { 
       // printf("%*d", 2);
        printf("%d", i);
        printf("%2s", " | ");
        for (int j = 0; j < last_round; j++) { 
  
            // if array of element is greater 
            // then array it print x 
            if (money_rounds[j] >= i) 
                printf(" x "); 
  
            // else print blank spaces 
            else
                printf(". "); 
        } 
        printf(" |\n");
    } 
  
    // print last line denoted by ---- 
    for (int i = 0; i < last_round + 3; i++) 
        printf("---"); 
  
    printf("\n"); 
    printf("     "); 
  
    for (int i = 0; i < last_round; i++) { 
       // printf("%*d", 2);
        printf("%1.f", money_rounds[i]);
        printf("%2s", " ");
    } 
}


////////////////////////////////////////////////////////////////////////////////
//
// Function     : main
// Description  : The main function for assignment #1
//
// Inputs       : argc - the number of command line parameters
//                argv - the parameters
// Outputs      : 0 if successful test, -1 if failure

int main( int argc, char **argv ) {

    float money[100];
    int wins = 0;
    /* Local variables */
    int asn1_deck[NUM_CARDS];  // This is the deck of cards
    float playerMoney = 100;
    /* Preamble information */
    printf( "Assignment #1\n\n" );
    srand(time(NULL)) ;

    /* Step #1 - create the deck of cards */
    for(int i=0; i < NUM_CARDS; i++){
        asn1_deck[i] = i;  
    }

    /* Step #2 - print the deck of cards */

    print_cards(asn1_deck, NUM_CARDS);
    printf("\n");
    /* Step #4 - shuffle the deck */
    shuffle_cards(asn1_deck , NUM_CARDS);
    /* Step #5 - print the shuffled deck of cards */
    print_cards(asn1_deck , NUM_CARDS);
    printf("\n");
    /* Step #6 - sort the cards */
    sort_cards(asn1_deck, NUM_CARDS);
    /* Step #7 - print the sorted deck of cards */
    print_cards(asn1_deck, NUM_CARDS);
    printf("\n");
    /* Step #9 - deal the hands */

    int hand = 1;
    while(hand <= 100 && playerMoney >= 5){
        if(play_hand(asn1_deck, NUM_CARDS, &playerMoney) ==1 ){
            wins++;
        }
        printf("After hand %d player has $%f left\n", hand, playerMoney);
        money[hand] = playerMoney;
        hand++;
    }
    
    printf("-------------\n");
    printf("Blackjack done - player won %d out of %d hands (%d).", wins, hand ,wins);
    printf("\n");
    /* Step 10 show historgram */

    show_player_money_histogram(money, hand);
    /* Exit the program successfully */
    printf( "\n\nAssignment #1\n" );


    return( 0 );
}