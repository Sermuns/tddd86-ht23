/**********************************************************************
 *  Mönsterigenkänning readme.txt
 **********************************************************************/

/**********************************************************************
 *  Empirisk    Fyll i tabellen nedan med riktiga körtider i sekunder
 *  analys      när det känns vettigt att vänta på hela beräkningen.
 *              Ge uppskattningar av körtiden i övriga fall.
 *
 **********************************************************************/
    
  N           brute[ms]       sortering
 ----------------------------------
    150       30ms
    200       90ms
    300       200ms
    400       522ms
    800       4s
   1600       28s
 -- härifrån uträknat -------------
   3200       221s
   6400       1921s
  12800       18262s


/**********************************************************************
 *  Teoretisk   Ge ordo-uttryck för värstafallstiden för programmen som
 *  analys      en funktion av N. Ge en kort motivering.
 *
 **********************************************************************/

Brute: O(N^4) - 4 nästlade for-loopar

Sortering:
