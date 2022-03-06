Galie Ana Maria 312CD
Tema(1)
Fisiere incluse: joc.c , makefile

<main>

Am creat lista simplu inlantuita (pachetul de carti) folosind
structura de la incepul fisierului si functiile (create) si (insertDeck),
si switch(contor)-ul din main pentru a pune cartile ordonat in pachet.

Citim intai task-ul (amestecare, razboi, etc) si folosind getTask 
si switch(taskNumber) apelam functiile necesare pentru acesta.

<Amestecarea cartilor>

getPackShuffledOut:
Primeste functia amestecata prin decideShuffleMethod si
o afiseaza in .out subforma (letter)(color/symbol).
Dupa afisare se elibereaza functia.

decideShuffleMethod:
Citim cate amestecari trebuie sa facem.
Folosim un for loop pentru amestecari repetate.
Pentru mongean/inversare/intercalare citim doar cuvantul si 
apelam functia coresponda amestecarii de facut.

Daca nu intra in niciun if avem amestecare NPiles
Pentru NPiles mai citim numarul de subpachete si scocam ordinea lor
intr-un vector.

<Inversare>

Functia inversare();
Folosim un loop si un pointer care initial pointeaza spre NULL
dar care va ajunge sa pointeze spre capul listei inversate.
Ne folosim de pointer la lsita auxiliar (next) cu care inaintam in
lista originala.
Lista inversata inversedList se construieste de la coada la cap, head->next
adaugandu-se la inceputul ei la fiecare pas.

<N-Piles>

Functia NPiles();
Ne vom folosi in plus de functia copyList care ne va face o copie a 
listei primite pe care o vom modifica (la finalul functiei NPiles vom elibera
lista de carti originala).

Vom crea un vector de pointeri care vor pointa la inceputul fiecarul subpacheted
din pachetul original (pStartArray[]).
subpackData ne va spune la fiecare loop la ce subpacket trebuie sa ne uitam.
Vom lua pointer-ul corespondent la pozitie (numar subpachet)-1 in din vectorul de
pointeri (trebuie sa luam subpachetul 1, 1-1=pozitia 0 => pointerul pentru subpachetul 1
este la pStartArray[0])
Parcurgem subpachetele si transcriem cartile din ele in ordine in copia pachetului
in copyListPack pana nu mai avem subpachete.

<Intercalare>

Functia intercalare();
Cu cutInHalf primim pointer-ul de la mijlocul listei de carti originale,
adica inceputul la a doua jumatate, si deconentam prima jumatate de a doua.
(head->next == NULL)
Urmarind regula de amestecare:
Inseram pe rand cate un nod din a doua jumatate intre nodurile
primei liste de carti pana cand nu mai avem carti in a doua jumatate.

<Mongean>

Functia mongean();
Ne folosim de 3 pointeri care vor fi plasati (si vor ajunge la fiecare loop) 
unul dupa altul in ordinea first - second - third.
first se va duce tot timpul in spatele lui third in timp ce second
il vom muta in fata la head-ul listei de carti.
In final cand se iese din while vom muta si cartea/nodul de la final in
locul corespunzator. 

<Razboi>

Functia razboi();
Folosim 4 pointeri -principali- PlayerTwo2first,PlayerOne1first (care vor arata tot
timpul la inceputul pachetului din mana jucatorului indicat) si PlayerTwo2end,
PlayerOne1end (arata spre sfarsitul pachetelor din mana).
Taiam si separam pachetul amestescat pentru cei 2 jucatori.
Plasam cei 4 pointeri in pozitiile initiale de inceput.

Cu un loop while vom tine evidenta la cate maini de carti au fost jucate.
Daca se iese din el si nu s-a iesit din cauza unui castig datorita unui jucator care a 
luat toate cartie se intra in functia winnerAfter100.

In winnerAfter100 o sa avem 2 vectori de frecventa a aparitiei fiecari tip de carti
in mana fiecarui jucator si un vector de rank-uri.
Determinam cate carti de ce tip are fiecare jucator si dupa vedem cina are cele
mai multe carti de cel mai mare rank parcurgand simultam cei doi vectori.
Eliberam pachetele la final.

Pe parcursul jocului de vom folosi de pointeri auxiliari care arata spre pozitia curenta in 
mana jucatorului (cartea jucata in runda)(tempPlayer1 si tempPlayer2)

In cazul unei runde normale FARA razboi in functie de care carte a castigat,
mutam capetele principale ale pachetelor si atasam cartea pierzatoare la coada invingatoarei
(castigator->next = pierzator si pierzator->next = NULL).
In final atasam cele doua carti la pachetul jucatorului corespondent si remutam
sfarsitul pachetelor si pointerii spre cartea care urmeaza sa fie pusa jos.

Daca un jucator a pierdut si aceea era singura carte din pachetul sau atunci 
warning = 1 (semnal sa nu se mai faca si determinarea castigatorului cu vectorul de frecventa)
si apelam printOut ca sa faca afisarea castigatorului si sa elibereze pachetele.

In caz de RAZBOI determinam numarul minim de carti care trebuie puse jos.
Mutam capul pachetului nr_cards_flipped+1 in pachet.
In cazul unui RAZBOI normal vom avea pointer care arata spre inceputul/sfarsitul
sirului de carti care trebuie pus jos de fiecare player. Detasam listele de carti,
le inversam cu functia inversare de la task1 + atasam cartea de razboi la finalul lor cu
attachWarCard. 
In functie de cine castiga vom atasa cele doua liste de carti nou create la finalul pachetului
corespunzator si facem schimbarile de pointer End.

Daca minimul este chiar restul pachetului la un jucator si acesta pierde se va face afisarea
ca la o runda normala. Daca jucatorul mai are minim o carte in mana pe langa cele puse jos, 
head-ul pachetului va fi temporar plasat peste cartea jucata prima data si va fi plasat inapoi
la capatul pachetului de carti minime de pe masa.


