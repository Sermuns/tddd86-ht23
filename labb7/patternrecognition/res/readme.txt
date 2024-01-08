/**********************************************************************
 *  Mönsterigenkänning readme.txt
 **********************************************************************/

/**********************************************************************
 *  Empirisk    Fyll i tabellen nedan med riktiga körtider i sekunder
 *  analys      när det känns vettigt att vänta på hela beräkningen.
 *              Ge uppskattningar av körtiden i övriga fall.
 *
 **********************************************************************/
    
  N           brute[ms]      sortering
 ----------------------------------
    150       30ms           18ms
    200       90ms           34ms
    300       200ms          74ms
    400       522ms          126ms
    800       4s             500ms
   1600       28s            1.8s
 -- härifrån uträknat -------------
   3200       221s           7.3s
   6400       1921s          29s
  12800       18262s         116s


/**********************************************************************
 *  Teoretisk   Ge ordo-uttryck för värstafallstiden för programmen som
 *  analys      en funktion av N. Ge en kort motivering.
 *
 **********************************************************************/

Brute: O(N^4) - högst 4 nästlade for-loopar

Sortering: O(N^2*log(N)) - högst 2 nästlade for-loopar
