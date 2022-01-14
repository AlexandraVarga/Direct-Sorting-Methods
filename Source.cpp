/*
	TEMA LAB 2: ALEXANDRA-IOANA VARGA, GRUPA 30223 - CTI-RO

*/
#include "Profiler.h"
#define MAX_SIZE 10000
#define STEP_SIZE 100
#define NR_TESTS 5
#define N 10000
#include <iostream>
using namespace std;

Profiler p("SORTARI");
void afisare(int* a, int n)
{
    for (int i = 0; i < n; i++)
        printf("%d ", a[i]);
    printf("\n");
}

/*
Sortarea bulelor are urmatoarele complexitati:
- pentru cazul mediu : O(n^2) comparatii si O(n^2) asignari ---> O(n^2)
- pentru cazul favorabil (cand toate elementele sunt deja sortate) : O(n) comparatii si O(1) asignari ---> O(n)
- pentru cazul defavorabil (cand toate elementele sunt deja sortate) : O(n^2) comparatii si O(n^2) asignari ---> O(n^2)
ESTE stabil
*/

void bubbleSort(int a[], int n) {
    Operation comparatii = p.createOperation("COMPARATII_BUBBLE", n);
    Operation asignari = p.createOperation("ASIGNARI_BUBBLE", n);
    
    int swapped = 0;
    do
    {
        swapped = 1;
        for (int i = 0; i < n-1; i++) {
            comparatii.count();
            if (a[i] > a[i + 1]) {
                int aux = a[i];
                a[i] = a[i + 1];
                a[i + 1] = aux;
                swapped = 0;
                asignari.count(4);
                
            }
        }
        n--;
        asignari.count();
        
    } while (!swapped);
}

/*
Sortarea prin inserare este sortarea cu preluare rapida si are urmatoarele complexitati:
- pentru cazul mediu : O(n^2) comparatii si O(n) asignari ---> O(n^2)
- pentru cazul favorabil (cand toate elementele sunt deja sortate) : O(n) comparatii si O(1) asignari ---> O(n)
- pentru cazul defavorabil (cand toate elementele sunt deja sortate) : O(n^2) comparatii si O(n^2) asignari ---> O(n^2)
ESTE STABIL
*/

void insertionSort(int a[], int n)
{
    Operation comparatii = p.createOperation("COMPARATII_INSERTION", n);
    Operation asignari = p.createOperation("ASIGNARI_INSERTION", n);
    
    for (int i = 1; i < n; i++)
    {
        int x = a[i];
        int j = i - 1;
        while (j >= 0 && a[j] > x)
        {
            comparatii.count();   
            a[j + 1] = a[j];
            j--;
            asignari.count(2);
           
        }
        if (j != i - 1)
        {
            a[j + 1] = x;
            asignari.count();
        }
        asignari.count(2);
        if (j >= 0)
        {
            comparatii.count();
        }
    }
}

/*
Sortarea prin selectie este sortarea prin depunere rapida si are urmatoarele complexitati:
- pentru cazul mediu : O(n^2) comparatii si O(n) asignari ---> O(n^2)
- pentru cazul favorabil (cand toate elementele sunt deja sortate) : O(n^2) comparatii si O(1) asignari ---> O(n^2)
- pentru cazul defavorabil (cand toate elementele sunt deja sortate) : O(n^2) comparatii si O(n) asignari ---> O(n^2)
- worst case Selection == ultimul element este minimul din tablou, iar restul elementelor sunt sortate
NU putem spune daca este stabil sau nu
*/

void selectionSort(int a[], int n)
{
    Operation comparatii = p.createOperation("COMPARATII_SELECTION", n);
    Operation asignari = p.createOperation("ASIGNARI_SELECTION", n);
    
    
    for (int i = 0; i < n-1 ; i++)
    {   
        int jmin = i;   
        for (int j = i + 1; j < n; j++)
        {
            comparatii.count();
            if (a[j] < a[jmin])
            {
                jmin = j;
            }
        }
        if (jmin != i)
        {
            int aux = a[i];
            a[i] = a[jmin];
            a[jmin] = aux;
            asignari.count(3);
            
        }
    }
}

void copyTest(int aux[], int a[], int n)
{
    for (int i = 0; i < n; i++)
    {
        aux[i] = a[i];
    }
}

void worstSelection(int a[], int n)
{
    for (int i = 0; i < n - 1; i++)
    {
        a[i] = i + 1;
    }
    a[n - 1] = 0;
}
void demo()
{
    int bubbleVect[] = { 4,3,2,1 };
    int selectionVect[]= { 4,3,2,1 };
    int insertionVect[]= { 4,3,2,1 };
    int n = sizeof(bubbleVect) / sizeof(int);

    printf("BUBBLE SORT:\n");
    bubbleSort(bubbleVect, n);
    afisare(bubbleVect, n);

    printf("INSERTION SORT:\n");
    bubbleSort(insertionVect, n);
    afisare(insertionVect, n);

    printf("SELECTION SORT:\n");
    bubbleSort(selectionVect, n);
    afisare(selectionVect, n);
    
    int a[5];
    worstSelection(a, 5);
    afisare(a, 5);
}

void perf(int order)
{
    int a[MAX_SIZE];
    int n;
    for (int n = STEP_SIZE; n <= MAX_SIZE; n += STEP_SIZE)
    {
        for (int test = 0; test < NR_TESTS; test++)
        {
            FillRandomArray(a, n, 10, 50000, false, order);//order : 0-nesortat, 1-sortat crescator, 2- sortat descrescator
            int aux[MAX_SIZE];
            copyTest(aux, a, n);
            bubbleSort(aux, n);
            copyTest(aux, a, n);
            insertionSort(aux, n);
            if (order == 2)
                worstSelection(aux, n);
            else
                copyTest(aux, a, n);
            selectionSort(aux, n);
        }

    }
    p.divideValues("COMPARATII_BUBBLE", NR_TESTS);
    p.divideValues("ASIGNARI_BUBBLE", NR_TESTS);
    p.addSeries("BUBBLE", "COMPARATII_BUBBLE", "ASIGNARI_BUBBLE");

    p.divideValues("COMPARATII_INSERTION", NR_TESTS);
    p.divideValues("ASIGNARI_INSERTION", NR_TESTS);
    p.addSeries("INSERTION", "COMPARATII_INSERTION", "ASIGNARI_INSERTION");

    p.divideValues("COMPARATII_SELECTION", NR_TESTS);
    p.divideValues("ASIGNARI_SELECTION", NR_TESTS);
    p.addSeries("SELECTION", "COMPARATII_SELECTION", "ASIGNARI_SELECTION");
    

    p.createGroup("COMPARATII", "COMPARATII_BUBBLE", "COMPARATII_INSERTION","COMPARATII_SELECTION");// atribuiri atr pe un grafic
	p.createGroup("ASIGNARI", "ASIGNARI_BUBBLE", "ASIGNARI_INSERTION","ASIGNARI_SELECTION");// comparatii pe un grafic
	p.createGroup("TOTAL", "BUBBLE", "INSERTION","SELECTION");// grafic total
	//9 grafice - best, worst, average
	//p.showReport();

}

void perf_all()
{
    p.reset("average");
    perf(0);//0-unsorted
    p.reset("best");
    perf(1);//1-ascending
    p.reset("wrost");
    perf(2);//2-descending
    p.showReport();
}
int main()
{
    //demo();
    perf_all();

    return 0;
}