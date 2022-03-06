#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct node {
    int value;
    char letter;
    char colorSymbol;
    int state;   
    struct node* next;

} Card, *CardList;

CardList create(char valueCard,char letterCard, char colorSCard) {
    
    CardList newCard = NULL;
    newCard = (CardList)malloc(sizeof(Card));

    newCard->value = valueCard;
    newCard->letter = letterCard;
    newCard->colorSymbol = colorSCard;
    newCard->state = 1;
    newCard->next = NULL;

    return newCard;
}

CardList insertDeck(CardList head, char valueCard,char letterCard, char colorSCard){

    CardList newCard = create(valueCard,letterCard, colorSCard); 

    CardList temp = head;

    while(temp->next != NULL){
        temp = temp->next;
    }

    temp->next = newCard;
}

void freeCardList(CardList list){
    
    CardList current;

    if(list == NULL)return;

    if(list->next == NULL){
        free(list);
        return;
    }

    while(list->next != NULL){
        current = list;
        list = list->next; 
        free(current); 
    }
    
    current = list;
    free(current);
}

int numberCards(CardList list){

    int counter = 0;

    while(list != NULL){
        counter++;
        list = list->next;
    }
 
    return counter;
}

int winnerAfter100(FILE* fout ,CardList packPlayerONE, CardList packPlayerTWO, int cardsPlayerONE, int cardsPlayerTWO){
    CardList headONE = packPlayerONE;
    CardList headTWO = packPlayerTWO;

    int freqArrayONE[] = {0,0,0,0,0, 0,0,0,0,0, 0,0,0,0};
    int freqArrayTWO[] = {0,0,0,0,0, 0,0,0,0,0, 0,0,0,0};

    int arrayValues[] = {0, 15, 14, 13, 12, 10, 9, 8, 7, 6, 5, 4, 3, 2};
    char arrayLetter[] = {'X','A','K','Q','J','T','9','8','7','6','5','4','3','2'};

    for(int i=1; i<cardsPlayerONE; i++){
        for(int j=0; j<=13; j++){
            if(headONE->value == arrayValues[j])freqArrayONE[j]++;
        }

        headONE = headONE->next;
    }
    for(int j=0; j<=13; j++){
        if(headONE->value == arrayValues[j])freqArrayONE[j]++;
    }
    for(int i=1; i<cardsPlayerTWO; i++){
        for(int j=0; j<=13; j++){
            if(headTWO->value == arrayValues[j])freqArrayTWO[j]++;
        }

        headTWO = headTWO->next;        
    }
    for(int j=0; j<=13; j++){
        if(headTWO->value == arrayValues[j])freqArrayTWO[j]++;
    }

    int contorShow = 0;

    for(int i = 1; i<=13;i++){
        if(freqArrayONE[i] > freqArrayTWO[i]){
            fprintf(fout,"%d %c",1, arrayLetter[i]);
            contorShow = 1;
        }
        else if(freqArrayTWO[i] > freqArrayONE[i]){
            fprintf(fout,"%d %c",2, arrayLetter[i]);
            contorShow = 1;
        }
        if(contorShow == 1)break;
    }

    freeCardList(packPlayerTWO);
    freeCardList(packPlayerONE);

}

int min(int nr1, int nr2) 
{
    return (nr1 > nr2 ) ? nr2 : nr1;
}

CardList attachWarCard(CardList newEnd, CardList tempPlayer){

    while(newEnd->next != NULL){
        newEnd = newEnd->next;
    }

    newEnd->next = tempPlayer;
    newEnd = newEnd->next;

    return newEnd;
}

CardList inversare(CardList list);

void printOut(FILE* fout, int winner, CardList PlayerOne1first, CardList PlayerTwo2first){

    fprintf(fout,"%d", winner);
    freeCardList(PlayerOne1first);
    freeCardList(PlayerTwo2first);
}

void razboi(FILE* fin, FILE* fout, CardList list){
    CardList headInitialList = list;
    CardList PlayerTwo2first, PlayerTwo2end;
    CardList PlayerOne1end, PlayerOne1first;

    PlayerTwo2first = headInitialList;
    PlayerTwo2end = headInitialList;
    PlayerOne1end = headInitialList;
    PlayerOne1first = headInitialList;

    for(int i=1; i<26; i++){
        PlayerTwo2first = PlayerTwo2first->next;
        PlayerOne1end = PlayerOne1end->next;
    }
    PlayerTwo2first = PlayerTwo2first->next;
    PlayerTwo2end = PlayerTwo2first;

    while(PlayerTwo2end->next != NULL){
        PlayerTwo2end = PlayerTwo2end->next;
    }

    PlayerOne1end->next = NULL;

    int hands = 0;
    int warning = 0;
    CardList tempPlayer1, tempPlayer2;
    tempPlayer1 = PlayerOne1first;
    tempPlayer2 = PlayerTwo2first;

    while(hands != 100){

        if(tempPlayer1->value > tempPlayer2->value){

            int cardsPlayerONE = numberCards(tempPlayer1);
            int cardsPlayerTWO = numberCards(tempPlayer2);

            if(cardsPlayerTWO == 1){
                warning = 1;
                printOut(fout, 1, PlayerOne1first, PlayerTwo2first);
                break;
            }    

            PlayerOne1first = PlayerOne1first->next;
            PlayerTwo2first = PlayerTwo2first->next;
            
            tempPlayer2->next = NULL;
            tempPlayer1->next = tempPlayer2;
            PlayerOne1end->next = tempPlayer1;
            PlayerOne1end = tempPlayer2;

            tempPlayer2 = PlayerTwo2first;
            tempPlayer1 = PlayerOne1first;
        }
        else if(tempPlayer2->value > tempPlayer1->value){

            int cardsPlayerONE = numberCards(tempPlayer1);
            int cardsPlayerTWO = numberCards(tempPlayer2);

            if(cardsPlayerONE == 1){
                warning = 1;
                printOut(fout, 2, PlayerOne1first, PlayerTwo2first);
                break;
            }    

            PlayerOne1first = PlayerOne1first->next;
            PlayerTwo2first = PlayerTwo2first->next;
            
            tempPlayer1->next = NULL;
            tempPlayer2->next = tempPlayer1;

            PlayerTwo2end->next = tempPlayer2;
            PlayerTwo2end = tempPlayer1;


            tempPlayer2 = PlayerTwo2first;
            tempPlayer1 = PlayerOne1first;
        }
        else if(tempPlayer1->value == tempPlayer2->value){

            int warCard = tempPlayer1->value;
            int cardsPlayerONE = numberCards(tempPlayer1)-1;
            int cardsPlayerTWO = numberCards(tempPlayer2)-1;

            int nr_cards_flipped;
            nr_cards_flipped = min(min(cardsPlayerONE, warCard), min(cardsPlayerTWO, warCard));

            if(nr_cards_flipped == cardsPlayerTWO){

                for(int i=1; i<=nr_cards_flipped+1; i++){
                    PlayerOne1first = PlayerOne1first->next;
                }

                CardList headToCut1, headToCut2;
                CardList endToCut1, endToCut2;
                headToCut1 = tempPlayer1->next;
                headToCut2 = tempPlayer2->next;
                endToCut1 = headToCut1;
                endToCut2 = headToCut2;

                PlayerTwo2end = tempPlayer2;

                for(int i=1; i<nr_cards_flipped; i++){
                    endToCut1 = endToCut1->next;
                    endToCut2 = endToCut2->next;
                }
                endToCut1->next = NULL;
                endToCut2->next = NULL;  

                tempPlayer1->next = NULL;
                tempPlayer2->next = NULL;

                headToCut1 =  inversare(headToCut1);
                headToCut2 =  inversare(headToCut2);

                if(headToCut2->value > headToCut1->value){
                    CardList newEnd1, newEnd2;
                    newEnd1 = headToCut1;
                    newEnd2 = headToCut2;

                    newEnd1 = attachWarCard(newEnd1, tempPlayer1);
                    tempPlayer1 = PlayerOne1first;

                    newEnd2 = attachWarCard(newEnd2, tempPlayer2);
                    PlayerTwo2first = headToCut2;
                    tempPlayer2 = PlayerTwo2first;

                    newEnd2->next = headToCut1;
                    PlayerTwo2end = newEnd1;                    
                }
                else{
                    warning = 1;
                    printOut(fout, 1, PlayerOne1first, PlayerTwo2first);
                    break;
                }

            }
            else if(nr_cards_flipped == cardsPlayerONE){

                for(int i=1; i<=nr_cards_flipped+1; i++){
                    PlayerTwo2first = PlayerTwo2first->next;
                }

                CardList headToCut1, headToCut2;
                CardList endToCut1, endToCut2;
                headToCut1 = tempPlayer1->next;
                headToCut2 = tempPlayer2->next;
                endToCut1 = headToCut1;
                endToCut2 = headToCut2;

                PlayerOne1end = tempPlayer1;

                for(int i=1; i<nr_cards_flipped; i++){
                    endToCut1 = endToCut1->next;
                    endToCut2 = endToCut2->next;
                }
                endToCut1->next = NULL;
                endToCut2->next = NULL;  

                tempPlayer1->next = NULL;
                tempPlayer2->next = NULL;

                headToCut1 =  inversare(headToCut1);
                headToCut2 =  inversare(headToCut2);

                if(headToCut2->value > headToCut1->value){
                    CardList newEnd1, newEnd2;
                    newEnd1 = headToCut1;
                    newEnd2 = headToCut2;

                    newEnd1 = attachWarCard(newEnd1, tempPlayer1);
                    PlayerOne1first = headToCut1;
                    tempPlayer1 = PlayerOne1first;

                    newEnd2 = attachWarCard(newEnd2, tempPlayer2);
                    tempPlayer2 = PlayerTwo2first;

                    newEnd1->next = headToCut2;
                    PlayerOne1end = newEnd2;
                }
                else{
                    warning = 1;
                    printOut(fout, 2, PlayerOne1first, PlayerTwo2first);
                    break;
                }
            }
            else if(nr_cards_flipped != cardsPlayerONE && nr_cards_flipped != cardsPlayerTWO){

                for(int i=1; i<=nr_cards_flipped+1; i++){
                    PlayerOne1first = PlayerOne1first->next;
                    PlayerTwo2first = PlayerTwo2first->next;
                }

                CardList headToCut1, headToCut2;
                CardList endToCut1, endToCut2;
                headToCut1 = tempPlayer1->next;
                headToCut2 = tempPlayer2->next;
                endToCut1 = headToCut1;
                endToCut2 = headToCut2;

                for(int i=1; i<nr_cards_flipped; i++){
                    endToCut1 = endToCut1->next;
                    endToCut2 = endToCut2->next;
                }
                endToCut1->next = NULL;
                endToCut2->next = NULL;   

                tempPlayer1->next = NULL;
                tempPlayer2->next = NULL;

                headToCut1 =  inversare(headToCut1);
                headToCut2 =  inversare(headToCut2);
   
                CardList newEnd1, newEnd2;
                newEnd1 = headToCut1;
                newEnd2 = headToCut2;

                newEnd1 = attachWarCard(newEnd1, tempPlayer1);
                tempPlayer1 = PlayerOne1first;

                newEnd2 = attachWarCard(newEnd2, tempPlayer2);
                tempPlayer2 = PlayerTwo2first;

                if(headToCut1->value > headToCut2->value){

                    PlayerOne1end->next = headToCut1;
                    newEnd1->next = headToCut2;
                    PlayerOne1end = newEnd2;
                }
                else if(headToCut2->value > headToCut1->value){

                    PlayerTwo2end->next = headToCut2;
                    newEnd2->next = headToCut1;
                    PlayerTwo2end = newEnd1;
                }
            }
        }

        hands++;
    }

    int cardsPlayerONE = numberCards(PlayerOne1first);
    int cardsPlayerTWO = numberCards(PlayerTwo2first);

    if(warning == 0)winnerAfter100(fout, PlayerOne1first, PlayerTwo2first, cardsPlayerONE, cardsPlayerTWO);

}

CardList inversare(CardList list){

    CardList head = list;
    CardList inversedList = NULL;

    while (head != NULL) {

        CardList next = head->next;
        head->next = inversedList;
        inversedList = head;
        head = next;
    }

    return inversedList;
}

CardList cutInHalf(CardList head){
    CardList fastPointer = head;

    while(fastPointer->next->next != NULL){

        head= head->next;
        fastPointer = fastPointer->next->next;
    }

    CardList middle = head->next;
    head->next = NULL;

    return middle;
}


CardList intercalare(CardList list){
    CardList head = list; 
    CardList first = list;

    CardList middleHead = cutInHalf(head);
    CardList middle = middleHead;

    while(middleHead != NULL){
        middleHead = middleHead->next;
        middle->next = first ->next;
        first->next = middle;
        first = first->next->next;
        middle = middleHead;
    }

    return list;
}

CardList mongean(CardList list){
    CardList head = list;
    CardList first = list;
    CardList second = list;
    CardList third = list;

    while(first->next->next != NULL){
        second = first->next;
        third = first->next->next;

        first->next = third;
        second->next = head;
        head = second;

        first = third;
    }

    first = first->next;
    third->next = NULL;
    first->next = head;
    head = first;
    list = head;

    return list;
}

CardList copyList(CardList headRef){

    if(headRef == NULL){
        return NULL;
    }
    else{
        CardList copyCard = (CardList)malloc(sizeof(Card));

        copyCard->value = headRef->value;
        copyCard->letter = headRef->letter;
        copyCard->colorSymbol = headRef->colorSymbol;
        copyCard->state = headRef->state;

        copyCard->next = copyList(headRef->next);

        return copyCard;
    }
    
}

CardList NPiles(CardList list, int numberSubpack, int subpackData[]){

    CardList copyListPack;
    CardList headRef = list;
    copyListPack = copyList(headRef);
    CardList tempCopyList = copyListPack;

    CardList startPack = list;
    CardList temp = list;
    CardList pStartArray[50];
    pStartArray[0] = startPack;

    int nrCardsSubPack = 52/numberSubpack;
    int contor = 0;

    for(int i=0; i<52; i++){

        if(contor == nrCardsSubPack){
            contor = 0;
            pStartArray[i/nrCardsSubPack] = temp;
        }

        temp = temp->next;
        contor++;
    }

    CardList auxpointer;

    for(int i=0; i<numberSubpack; i++){

        int locationSubPack;
        locationSubPack = subpackData[i]-1;
        auxpointer = pStartArray[locationSubPack];
        
        for(int j=1; j<=nrCardsSubPack; j++){

            tempCopyList->value = auxpointer->value;
            tempCopyList->letter = auxpointer->letter;
            tempCopyList->colorSymbol = auxpointer->colorSymbol;
            tempCopyList->state = auxpointer->state;

            tempCopyList = tempCopyList->next;
            auxpointer = auxpointer->next;
        }
    }
    freeCardList(list);

    return copyListPack;

}

CardList decideShuffleMethod(FILE* fin, CardList list){

    char shuffles[100];
    int numberShuffles;

    fscanf(fin, "%d" , &numberShuffles);

    for(int i=1; i<=numberShuffles; i++){
        fscanf(fin, "%s" , shuffles);

        
        if(strcmp(shuffles,"mongean") == 0){
            list = mongean(list);
            continue;
        }
        if(strcmp(shuffles,"inversare") == 0){
            list = inversare(list);
            continue;
        }
        if(strcmp(shuffles,"intercalare") == 0){
            list = intercalare(list);
            continue;
        }
        
        int subpackData[100];
        int numberSubpack;
        int auxiliar;

        fscanf(fin, "%d", &numberSubpack);
        
        for(int i=0; i<numberSubpack; i++){

            fscanf(fin, "%d", &auxiliar);
            subpackData[i] = auxiliar;
        }

        list = NPiles(list, numberSubpack, subpackData);
    }

    return list;
}

void getPackShuffledOut(FILE* fin, FILE* fout, CardList list){
    CardList shuffledPack;
    CardList head;
    
    shuffledPack = decideShuffleMethod(fin,list);
    head = shuffledPack;

    for(int i=1; i<=52; i++){

        if(i == 52){
            fprintf(fout, "%c%c", shuffledPack->letter, shuffledPack->colorSymbol);
        }
        else{
            fprintf(fout, "%c%c ", shuffledPack->letter, shuffledPack->colorSymbol);
        }

        shuffledPack = shuffledPack->next;
    }

    freeCardList(head);

}

int getTask(char task[]){

    if(strcmp(task,"amestecare") == 0)return 1;
    if(strcmp(task,"razboi") == 0)return 2;
    if(strcmp(task,"rollingstone") == 0)return 3;
    if(strcmp(task,"scarabei") == 0)return 4;
}

int main(){

    FILE *fin = fopen("in", "r");
    FILE *fout = fopen("out", "w");

    CardList list;
    char arrayLetter[13] = {'A','K','Q','J','T','9','8','7','6','5','4','3','2'};
    int arrayValues[13] = {15, 14, 13, 12, 10, 9, 8, 7, 6, 5, 4, 3, 2};
    int cardNumber = 52;

    list = create(15,'A','s');
    insertDeck(list, 15,'A','h');
    insertDeck(list, 15,'A','c');
    insertDeck(list, 15,'A','d');

    for(int i=1 ; i<13; i++){
        int contor = 1;
        while(contor <= 4){

            switch(contor){
                case 1:
                    insertDeck(list, arrayValues[i], arrayLetter[i],'s');
            
                    break;
                case 2:
                    insertDeck(list, arrayValues[i], arrayLetter[i],'h');
                 
                    break;
                case 3:
                    insertDeck(list, arrayValues[i], arrayLetter[i],'c');
              
                    break;
                case 4:
                    insertDeck(list, arrayValues[i], arrayLetter[i],'d');
                   
                    break;
                default:
                    break;
            }

            contor++;
        }
    }

    char task[20];
    fscanf(fin, "%s", task);

    int taskNumber = getTask(task);

    switch(taskNumber){
        case 1:
            getPackShuffledOut(fin,fout,list); 
            break;
        case 2:;
            CardList shuffledListGame;
            shuffledListGame = decideShuffleMethod(fin,list);
            
            razboi(fin, fout, shuffledListGame);
            break;
        default:
            break;
    }
    
    fclose(fin);
    fclose(fout);
    
    return 0;
}