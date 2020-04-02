#include <stdio.h>

int controlla_riga(int sud[9][9], int r, int num)
{
   int valido  = 1;
   int c = 0;
   while (c < 9 && valido) {
      if (sud[r][c] == num)
         valido = 0;
      c++;
   }
   return valido;
}

int controlla_colonna(int sud[9][9], int c, int num)
{
   int valido = 1;
   int r = 0;
   while (r < 9 && valido) {
      if (sud[r][c] == num)
         valido = 0;
      r++;
   }
   return valido;
}

int controlla_quadrato(int sud[9][9], int r, int c, int num)
{
   int valido = 1;
   int i , j;
   int startRiga;
   int startColonna;
   startRiga = (r/3) * 3;
   startColonna = (c/3) * 3;
   i = startRiga + 3;
   j = startColonna + 3;


   while (startRiga < i && valido) {
      startColonna = (c/3) * 3;
      while (startColonna < j && valido) {
         if (sud[startRiga][startColonna] == num)
            valido = 0;
      startColonna++;
      }
      startRiga++;
   }
   return valido;
}

int isValid(int sud[9][9], int r, int c, int num)
{
   int valido;
   valido = controlla_riga(sud, r, num) && controlla_colonna(sud, c, num) && controlla_quadrato(sud, r, c, num);
   return valido;
}
int solve(int sud[9][9], int r, int c)
{
   if (r==8 && c==8) {
       if (sud[r][c] != 0)
           return 1;
       else {
           int i = 1;
           int trovato = 0;
           while (i<10 && !trovato) {
               if (isValid(sud, r, c, i)) {
                   sud[r][c] = i;
                   trovato = 1;
               }
               i++;       
            }
            return trovato;
        }
    }else {
        if (sud[r][c] != 0) {
            if (c<8)
                return solve(sud, r, c+1);
            else 
                return solve(sud, r+1, 0);
        }else {
            int i = 1;
            int trovato = 0;
            while (i<10 && !trovato) {
                if (isValid(sud, r, c, i)) {
                    sud[r][c] = i;
                    if (c<8)
                        trovato = solve(sud, r, c+1);
                    else 
                        trovato = solve(sud, r+1, 0);   
                    
                    if (!trovato)
                        sud[r][c] = 0;
                }
                i++;
            }
            return trovato;
        }        
    }
}



int main()
{
    int i, j;


  int puzzle[9][9]={{0, 0, 5, 3, 0, 0, 0, 0, 0},
                    {8, 0, 0, 0, 0, 0, 0, 2, 0},
                    {0, 7, 0, 0, 1, 0, 5, 0, 0},
                    {4, 0, 0, 0, 0, 5, 3, 0, 0},
                    {0, 1, 0, 0, 7, 0, 0, 0, 6},
                    {0, 0, 3, 2, 0, 0, 0, 8, 0},
                    {0, 6, 0, 5, 0, 0, 0, 0, 9},
                    {0, 0, 4, 0, 0, 0, 0, 3, 0},
                    {0, 0, 0, 0, 0, 9, 7, 0, 0}};

    if(solve(puzzle, 0, 0))
    {
        printf("\n+-----+-----+-----+\n");
        for(i=1; i<10; ++i)
        {
            for(j=1; j<10; ++j) printf("|%d", puzzle[i-1][j-1]);
            printf("|\n");
            if (i%3 == 0) printf("+-----+-----+-----+\n");
        }
    }
    else printf("\n\nNO SOLUTION\n\n");

    return 0;
}
