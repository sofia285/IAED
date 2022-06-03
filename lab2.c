#include <stdio.h>

int main()
{
/* Exercicio 1 */

/*     int n1,n2,n3;
    printf("Introduza tres valores inteiros:\n");
    scanf("%d %d %d", &n1, &n2, &n3);
    if (n1 > n2 && n1 > n3)  {
        printf("O maior numero eh: %d\n", n1);
    }
    
    if (n2 > n1 && n2 > n3)  {
        printf("O maior numero eh: %d\n", n2);
    }
    if (n3 > n2 && n3 > n1)  {
        printf("O maior numero eh: %d\n", n3);
    }


return 0; */

/* Exercicio 2 */
/*    int n,m;
    printf("Introduza dois numeros:\n");
    scanf("%d %d",&n,&m);
    if (n > m) {
        printf("%d\n%d\n",m,n);
        
    }
    else {
        printf("%d\n%d\n",n,m);
    }
return 0; */

/* Exercicio 3 */
/*   int n,m;
    printf("Introduza dois numeros:\n");
    scanf("%d %d",&n,&m);
    if (m%n == 0 ) {
        printf("yes\n");
    }
    else{
        printf("no\n");
    }
return 0; */

/* Exercicio 4 */

/*    int a, b, c, min, med, max;
    printf("Introduza 3 numeros:\n");
    scanf("%d\n%d\n%d",&a,&b,&c);
    if (a > b && a > c) {
        max = a;
        if (b > c) {
            med = b;
            min = c;
        }
        else {
            med = c;
            min = b;
        }  
    }
    if (b > a && b > c) {
        max = b;
        if (a > c) {
            med = a;
            min = c;
        }
        else {
            med = c;
            min = a;
        }
    }
    if (c > b && c > a) {
        max = c;
        if (b > a) {
            med = b;
            min = a;
        }
        else {
            med = a;
            min = b;
        }
    }
    printf("%d\t%d\t%d\n",min,med,max);
return 0; */

/* Exercicio 5 */
/*    int n,aux;

    printf("Introduza um numero:\n");
    scanf("%d",&n);
    aux = 1;
    while (aux <= n) {
        printf("%d\n",aux);
        aux = aux + 1;
    }
return 0; */

/* Exercicio 6 */
/*    float n,max,min,N;
    int aux,count;
    printf("Quantos numeros quer introduzir?:\n");
    scanf("%f",&n);
    printf("Introduza o 1º numero:\n");
    scanf("%f",&min);
    max = min;
    aux = 1;
    count = 2;
    while (aux < n) {
        printf("Intruduza o %dº numero:\n",count);
        scanf("%f",&N);
        count ++;
        if (N > max) {
            max = N;
        }

        if (N < min) {
            min = N;
        }
        aux = aux + 1;
    }
    printf("min: %.1f, max: %.1f\n", min, max);
return 0; */

/* Exercicio 7 */

/*    int N, aux,count;
    count = 0;
    aux = 1;
    printf("Introduza um numero:\n");
    scanf("%d",&N);
    while (aux <= N) {
        if (N % aux == 0) {
            count = count + 1;
            aux = aux + 1;
        }
        else {
            aux = aux + 1;
        }
    }
    printf("%d\n",count);
    return 0; */

/* Exercicio 8 */

/*    float media, soma, num;
    int aux, N, count;
    aux = 1;
    soma = 0;
    count = 0;
    printf("Quantos numeros quer introduzir?:\n");
    scanf("%d",&N);
    while (aux <= N) {
        count ++;
        printf("Introduza o %dº numero:\n",count);
        scanf("%f",&num);
        soma = soma + num;
        aux ++;

    }
    media = soma / count;
    printf("%.2f\n",media);
return 0; */

/* Exercicio 9 */
/*    int N,sec,min,hora;
    printf("Introduza um numero:\n");
    scanf("%d",&N);
    hora = N / 3600; 
    min = (N - (hora * 3600))/60;
    sec = (N - (hora * 3600) - (min * 60));
    printf("%.2d:%.2d:%.2d\n",hora,min,sec);
return 0; */

/* Exercicio 10 */
/*   int N, aux, count, soma;
    count = 0;
    soma = 0;
    printf("Introduza um numero:\n");
    scanf("%d",&N);
    while (N > 0) {
        aux = N % 10;
        count ++;
        soma = soma + aux;
        N = N / 10;
    }
    printf("%d\n%d\n", count, soma);
return 0;
*/
}