/**********************************************************************
 *  M�nsterigenk�nning readme.txt
 **********************************************************************/

/**********************************************************************
 *  Empirisk    Fyll i tabellen nedan med riktiga k�rtider i sekunder
 *  analys      n�r det k�nns vettigt att v�nta p� hela ber�kningen.
 *              Ge uppskattningar av k�rtiden i �vriga fall.
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
 -- h�rifr�n utr�knat -------------
   3200       221s           7.3s
   6400       1921s          29s
  12800       18262s         116s


/**********************************************************************
 *  Teoretisk   Ge ordo-uttryck f�r v�rstafallstiden f�r programmen som
 *  analys      en funktion av N. Ge en kort motivering.
 *
 **********************************************************************/

Brute: O(N^4) - h�gst 4 n�stlade for-loopar

Sortering: O(N^2*log(N)) - h�gst 2 n�stlade for-loopar
