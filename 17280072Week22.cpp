#include "stdafx.h"
#include <stdio.h>
#include "string.h"
#include "stdarg.h"
#include "stdlib.h"
#include "time.h"

typedef enum S { CLUBS, DIAMONDS, HEARTS, SPADES } SUIT;
char suits[][10] = { "CLUBS", "DIAMONDS", "HEARTS", "SPADES" };

typedef enum F { TWO, THREE, FOUR, FIVE, SIX, SEVEN, EIGHT, NINE, TEN, JACK, QUEEN, KING, ACE } FACE;
char faces[][10] = { "TWO", "THREE", "FOUR", "FIVE", "SIX", "SEVEN", "EIGHT", "NINE", "TEN", "JACK", "QUEEN", "KING", "ACE" };

typedef struct
{
	SUIT suit;
	FACE face;
} card;

typedef struct
{
	card cards[5];
} hand;


hand dealHand(hand handsDealt[], int numHandsDealt);
char * compareCards(card yourCard, card dealersCard);
char * printCard(card aCard);
bool fourAces(hand aHand);
void main() {

	int i = 0;
	hand myHand, dealersHand;
	int seed = time(NULL);
	srand(seed);
	hand hands[2];

	myHand = dealHand(hands, 0);

	hands[0] = myHand;

	dealersHand = dealHand(hands, 1);
	
	while (i<5)
	{
		printf("card#%d: %s (you) vs. %s (dealer). Winner: %s \n", i + 1, printCard(myHand.cards[i]), printCard(dealersHand.cards[i]), compareCards(myHand.cards[i], dealersHand.cards[i]));
		i++;
	}

	while (1)
	{
		myHand = dealHand(hands, 0);


		if (fourAces(myHand)) break;
		i++;
	}

	printf("\n\n4 aces found after %d hands \n\n\n", i);
}

hand dealHand(hand x[],int y) {

	int i, j,k=0 ,flag = 0,flagPara = 0,counter=0;
	hand newHand;

	SUIT newSuit;
	FACE newFace;

	for (i = 0; i < 5; i++) {
	
		newSuit = (SUIT)(rand() % 4);
		newFace = (FACE)(rand() % 13);

		if (i == 0 && y == 0) {
			newHand.cards[i].suit = newSuit;
			newHand.cards[i].face = newFace;
		}
		else if (y == 0) {
			do {
				do {
					if (newSuit == newHand.cards[k].suit && newFace == newHand.cards[k].face) { flag = 1; newSuit = (SUIT)(rand() % 4);  newFace = (FACE)(rand() % 13); k = 0; }
					else { flag = 0;}
				} while (flag == 1);
				k++;
			} while (k < i);
			newHand.cards[i].suit = newSuit;
			newHand.cards[i].face = newFace;
		}
	else if(y!=0){
		do {
			counter = 0;
			for (int h = 0; h < i; h++) {
				do {
					if (newSuit == newHand.cards[h].suit && newFace == newHand.cards[h].face) { flag = 1; newSuit = (SUIT)(rand() % 4); counter--; newFace = (FACE)(rand() % 13);}
					else { flag = 0; counter++; }
				} while (flag == 1);

			}
			for (int l = 0; l < y; l++) {

				for (int m = 0; m < 5; m++) {
					do {
						if (newSuit == x[l].cards[m].suit && newFace == x[l].cards[m].face) { flag = 1; newSuit = (SUIT)(rand() % 4); counter++; newFace = (FACE)(rand() % 13); counter--;}
						else { flag = 0; counter++; }
					} while (flag == 1);
				}
			}
		} while (counter!=((y*5)+i));
		newHand.cards[i].suit = newSuit;
		newHand.cards[i].face = newFace;
	}
}
	return newHand;
}

char * compareCards(card yourCard, card dealersCard)
{
	char * sptr;
	sptr = (char *)malloc(10 * sizeof(char));

	if (yourCard.face > dealersCard.face) { strcpy(sptr,"YOU"); }
	else if (yourCard.face < dealersCard.face) { strcpy(sptr, "DEALER"); }
	else { strcpy(sptr, "DRAW"); }

	return sptr;
}

char * printCard(card aCard)
{
	char * sptr;
	sptr = (char *)malloc(25 * sizeof(char));
	char name[25];
	strcpy(name, suits[aCard.suit]);
	strcat(name , " of ");
	strcat(name, faces[aCard.face]);
	strcpy(sptr, name);
	return sptr;
}
bool fourAces(hand aHand) {

	int i;
	int numAces = 0;
	bool fourAces = false;

	for (i = 0; i < 5; i++) {
		if (aHand.cards[i].face == ACE)
		{
			numAces++;
		}
		else continue;
	}
	if (numAces == 4) { fourAces = true; }
	return fourAces;

}