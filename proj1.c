/* Sofia Paiva 102835 */

#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>


/* Maximo de uma string */
#define STR 200

/* Maximo de aeroportos */
#define AERO 40

/* Aeroporto */
#define ID 4
#define PAIS 31
#define CID 51

/* Maximo de voos */
#define VOO 30000

/* Voo */
#define COD 7

/* Maximo de datas */
#define DATA 1


/* Estrutura de um aeroporto */
typedef struct aeroporto {
    char id[ID];
    char pais[PAIS];
    char cidade[CID];
    int voo;
} Aero;

/* Estrutura de um voo */
typedef struct voo {
    char cod[COD];
    char id_p[ID];
    char id_c[ID];
    int dia;
    int mes;
    int ano;
    int min;
    int hora;
    int dur_m;
    int dur_h;
    int cap;
} Voo;

/* Estrutura de uma data */
typedef struct data {
    int dia;
    int mes;
    int ano;
} Data;


/* Funcoes implementadas */
int adiciona_aeroporto(char s[STR], Aero aero[AERO], int n_aero);

void lista_aeroporto(char s[STR], Aero aero[AERO], int n_aero);

int adiciona_lista_voo(char s[STR], Voo voos[VOO], Aero aero[AERO], int n_aero,
int n_voo, Data data);

void lista_voo_partida(char s[STR], Voo voos[VOO], Aero aero[AERO], int n_voo,
int n_aero);

void lista_voo_chegada(char s[STR], Voo voos[VOO], Aero aero[AERO], int n_voo,
int n_aero);

Data avanca_data(char s[STR], Data data);

void bubble(Voo voo[VOO], int esq, int dir);

int menor(Voo voo[VOO], int n);


int main() {
    char c,comando;
    Aero aero[AERO] = {0};
    int  n_aero = 0, n_voo = 0;
    Voo voos[VOO] = {0};
    Data data;
    data.dia = 1;
    data.mes = 1;
    data.ano = 2022;


    do { 
        char s[STR] = {0};
        int i = 0;

        while ((c = getchar()) != '\n') {
            s[i++] = c;
        }  
        
        sscanf(s,"%c", &comando);
    
        switch (comando) {

            case 'q':
                /* para programa */
                break;

            case 'a':
                /* adiciona aeroporto */
                n_aero = adiciona_aeroporto(s, aero, n_aero);
                break;

            case 'l':
                /* lista aeroportos */
                lista_aeroporto(s, aero, n_aero);
                break;

            case 'v':
                /* adiciona voo ou lista voos */
                n_voo = adiciona_lista_voo(s, voos, aero, n_aero, n_voo, data);
                break;

            case 'p':
                /* lista voos de partida de um aeroporto */
                lista_voo_partida(s, voos, aero, n_voo, n_aero);
                break;

            case 'c':
                /* lista voos de chegada a um aeroporto */
                lista_voo_chegada(s, voos, aero, n_voo, n_aero);
                break;

            case 't':
                /* avanca data do sistema */
                data = avanca_data(s, data);
                break;

            default:
                printf("Error: invalid comand\n");
        }
    } while (comando != 'q');
    return 0;
}


/* comando 'a' -> 
- Adiciona um aeroporto */
int adiciona_aeroporto(char s[STR], Aero aero[AERO], int n_aero) {
    int i, j, min = 0, max = n_aero;
    char id[ID], pais[PAIS], cidade[CID];

    sscanf(s + 1,"%s %s %[^\n]",id, pais, cidade);

    /* Verifica se o ID do aeroporto eh valido */
    for (i = 0; id[i] != '\0'; i++) {
        if(id[i] < 'A' || id[i] > 'Z') {
            printf("invalid airport ID\n");
            return n_aero;
        }
    }
    
    /* Verifica se se excedeu o limite de aeroportos */
    if (n_aero == AERO) {
        printf("too many airports\n");
        return n_aero;
    }

    /* Verifica se ja existe um aeroporto com o mesmo identificador */
    for (i = 0; i < n_aero; i++) {
        if (!strcmp(aero[i].id, id)) {
            printf("duplicate airport\n");
            return n_aero;
        }
    }

    /* Insere o aeroporto no sitio certo (por ordem alfabetica) */
    for (j = 0; j < 3; j++) {
        for (i = min; i < max; i++) {
            if(id[j] > aero[i].id[j]){
                min++;
            }
            if (id[j] < aero[i].id[j]) {
                max = i;
                break;
            }
        }
    }

    n_aero++;

    for (i = n_aero - 1; i >= max + 1; i--) {
        aero[i] = aero[i - 1];
    }

    /* Adiciona os elementos aos aeroportos */
    strcpy(aero[max].id, id);
    strcpy(aero[max].pais, pais);
    strcpy(aero[max].cidade, cidade);

    printf("airport %s\n", id);
    return n_aero;
}


/* comando l ->
- Sem argumentos lista os aeroportos que existem por ordem alfabetica
- Com argumentos lista os aeroportos pela ordem que foram chamados */
void lista_aeroporto(char s[STR], Aero aero[AERO], int n_aero) {
    int i, j, len, count = 0;
    char id[ID];

    /* Sem argumntos imprime por ordem alfabetica */
    if (strlen(s) == 1) {
        for (i = 0; i < n_aero; i++) {
            printf("%s %s %s %d\n", aero[i].id, aero[i].cidade, aero[i].pais,
            aero[i].voo);
        }
    }

    /* Com argumentos imprime pela ordem que foram chamados */
    len = strlen(s);

    for (i = 2; i < len; i += 4) {
        sscanf(s + i, "%s", id);
        count = 0;
        for (j = 0; j < n_aero; j++) {
            /* Se o id do aeroporto introduzido estiver em aero, ele imprime */
            if (!strcmp(aero[j].id, id)) {
                printf("%s %s %s %d\n", aero[j].id, aero[j].cidade,
                aero[j].pais, aero[j].voo);
            }
            else {
                count++;
            }
        }

        /* Verifica se o aeroporto introduzido esta em aero */
        if (count == n_aero) {
            printf("%s: no such airport ID\n", id);
        }
    }
    return;
}


/* comando v -> 
- Sem argumentos lista os voos pela ordem que foram introduzidos
- Com argumentos adiciona um voo a voos */
int adiciona_lista_voo(char s[STR], Voo voos[VOO], Aero aero[AERO], int n_aero,
int n_voo, Data data) {
    int i, dia, mes, ano, min, hora, dur_m, dur_h, cap;
    int countp = 0, countc = 0, len;
    char cod[COD], id_p[ID], id_c[ID];

    sscanf(s + 1, "%s %s %s %d-%d-%d %d:%d %d:%d %d",
    cod, id_p, id_c, &dia, &mes, &ano, &hora, &min, &dur_h, &dur_m, &cap);

    /* Sem argumentos imprime os voos pela ordem que foram introduzidos */
    if (strlen(s) == 1) {
        for (i = 0; i < n_voo; i++) {
            printf("%s %s %s %02d-%02d-%d %02d:%02d\n",
            voos[i].cod, voos[i].id_p, voos[i].id_c, voos[i].dia,
            voos[i].mes, voos[i].ano, voos[i].hora, voos[i].min);
        }
        return n_voo;
    }
    else {

        /* Verifica se o codigo contem duas maiusculas e entre um a
        quatro algarismos */
        len = strlen(cod);
        for (i = 0; i < len; i++) {
            if (i < 2 && (cod[i] < 'A' || cod[i] > 'Z')) {
                printf("invalid flight code\n");
                return n_voo;
            }
            if (i == 2 && (cod[i] < 49 || cod[i] > 57)) {
                printf("invalid flight code\n");
                return n_voo;
            }
            if (i > 2 && (cod[i] < 48 || cod[i] > 57)) {
                printf("invalid flight code\n");
                return n_voo;
            }
        }

        /* Verifica se o voo ja existe */
        for (i = 0; i < n_voo; i++) {
            if (!strcmp(voos[i].cod, cod) && (voos[i].dia == dia) &&
            (voos[i].mes == mes) && (voos[i].ano == ano)) {
                printf("flight already exists\n");
                return n_voo; 
            }
        }

        /* Verifica se o id de partida e de chegada existe */

        for (i = 0; i < n_aero; i++) {
            if (strcmp(id_p, aero[i].id)) {
                countp++;
            }
            if (strcmp(id_c, aero[i].id)) {
                countc++;
            }
        }

        if (countp == n_aero) {
            printf("%s: no such airport ID\n", id_p);
            return n_voo;
        }
        else if (countc == n_aero) {
            printf("%s: no such airport ID\n", id_c);
            return n_voo;
        }
    
        /* Verifica se eh excedido o limite de voos */
        if (n_voo == VOO) {
            printf("too many flights\n");
            return n_voo;
        }

        /* Verifica se a data eh valida */
        if (ano > 2023 || ano < data.ano || (ano == data.ano && mes < data.mes) 
        || (ano == data.ano && mes == data.mes && dia < data.dia) ||
        (ano > data.ano && mes > data.mes) || (ano > data.ano && mes == data.mes
        && dia > data.dia))  {
            printf("invalid date\n");
            return n_voo;
        }

        /* Verifica se a duracao eh valida */
        if ((dur_h > 12) || (dur_h == 12 && dur_m > 0))  {
            printf("invalid duration\n");
            return n_voo;
        }

        /* Verifica se a capacidade eh valida */
        if (cap < 10 || cap > 100) {
            printf("invalid capacity\n");
            return n_voo;
        }
    
        /* Adiciona o voo a voos */
        strcpy(voos[n_voo].cod, cod);
        strcpy(voos[n_voo].id_p, id_p);
        strcpy(voos[n_voo].id_c, id_c);
        voos[n_voo].dia = dia;
        voos[n_voo].mes = mes;
        voos[n_voo].ano = ano;
        voos[n_voo].hora = hora;
        voos[n_voo].min = min;
        voos[n_voo].dur_h = dur_h;
        voos[n_voo].dur_m = dur_m;
        voos[n_voo].cap = cap;

        /* incrementa o numero de voos do aeroporto de partida */
        for (i = 0; i < n_aero; i++) {
            if (!strcmp(aero[i].id, id_p)) {
                aero[i].voo++;
            }
        }

        n_voo++;

        return n_voo;
    }
    return n_voo;
}


/* comando 'p' ->
- Lista os voos que chegam ao aeroporto por ordem cronologica de partida 
- Caso nao haja nenhum nao imprime nada */
void lista_voo_partida(char s[STR], Voo voos[VOO], Aero aero[AERO], int n_voo,
int n_aero) {
    int i, count = 0, c = 0;
    char id[ID];
    Voo voo_p[VOO];

    sscanf(s + 1, "%s", id);

    /* Percorre aero para ver se o id existe */
    for(i = 0; i < n_aero; i++) {
        if (strcmp(aero[i].id, id)) {
            count++;
        }
    }

    /* Verifica se o aeroporto de partida existe */
    if (count == n_aero) {
        printf("%s: no such airport ID\n", id);
        return;
    }

    /* Adiciona a voo_p todos os os voos de voos com id de partida igual ao
    introduzido */
    for (i = 0; i < n_voo; i++) {
        if (!strcmp(voos[i].id_p, id)) {
            voo_p[c] = voos[i];
            c++;
        }
    }
    /* Organiza os voos de partida por ordem cronologica */
    bubble(voo_p, 0, c);

    for (i = 0; i < c; i++) {
        printf("%s %s %02d-%02d-%d %02d:%02d\n", voo_p[i].cod, voo_p[i].id_c,
        voo_p[i].dia, voo_p[i].mes, voo_p[i].ano, voo_p[i].hora, voo_p[i].min);
    }

}


/* comando 'c' -> 
- Lista os voos que chegam ao aeroporto por ordem cronologica de chegada
- Caso nao haja nenhum nao imprime nada */
void lista_voo_chegada(char s[STR], Voo voos[VOO], Aero aero[AERO], int n_voo,
int n_aero) {
    int i, count = 0, c = 0, hora, min, dia, mes, ano;
    char id[ID];
    Voo voo_c[VOO];

    sscanf(s + 1, "%s", id);

    /* Percorre aero para ver se o id existe */
    for (i = 0; i < n_aero; i++) {
        if (strcmp(aero[i].id, id)) {
            count++;
        }
    }

    /* Verifica se o aeroporto de partida existe */
    if (count == n_aero) {
        printf("%s: no such airport ID\n", id);
        return;
    }

    /* Calcula a data e hora de chegada de um voo */
    for (i = 0; i < n_voo; i++) {
        if (!strcmp(voos[i].id_c, id)) {
            voo_c[c] = voos[i]; 
            hora = voo_c[c].hora + voo_c[c].dur_h;
            min = voo_c[c].min + voo_c[c].dur_m;
            dia = voo_c[c].dia;
            mes = voo_c[c].mes;
            ano = voo_c[c].ano;

            if (min >= 60) {
                min -= 60;
                hora++;
            }

            if (hora >= 24) {
                hora -= 24;
                dia++;
            }

            if (dia > 28 && mes == 2) {
                dia = 1;
                mes++;
            }

            else if (((mes < 7 && mes % 2 == 0) || (mes > 7 && mes % 2 != 0))
            && (dia > 30)) {
                dia = 1;
                mes++;
            }
            else if ((((mes <= 7 && mes % 2 != 0) || (mes > 7 && mes % 2 == 0)))
            && (dia > 31)) {
                dia = 1;
                mes++;
            }

            if (mes > 12) {
                mes -= 12;
                ano++;
            }

            /* Coloca o voo em voo_c com a data e hora de chegada correta */
            voo_c[c].hora = hora;
            voo_c[c].min = min;
            voo_c[c].dia = dia;
            voo_c[c].mes = mes;
            voo_c[c].ano = ano;
            c++;
        }
    }

    /* Organiza os voos de chegada por ordem cronologica */
    bubble(voo_c, 0, c);

    for(i = 0; i < c; i++) {
        printf("%s %s %02d-%02d-%d %02d:%02d\n", voo_c[i].cod, voo_c[i].id_p,
        voo_c[i].dia, voo_c[i].mes, voo_c[i].ano, voo_c[i].hora, voo_c[i].min);
    }            
}


/* comando 't' -> 
- Avanca a data do sistema no caso de ser valida */
Data avanca_data(char s[STR], Data data) {
    int dia, mes, ano;

    sscanf(s + 1,"%d-%d-%d", &dia, &mes, &ano);

    /* Verifica se a data eh valida */
    if ((ano < data.ano) || (ano == data.ano && mes < data.mes) 
    || (ano == data.ano && mes == data.mes && dia < data.dia)) {
        printf("invalid date\n");
        return data;
    }

    /* Atualiza a data do sistema */
    data.dia = dia;
    data.mes = mes;
    data.ano = ano;

    printf("%02d-%02d-%d\n",dia, mes, ano);
    return data;
}


/* menor(a,b) -> 
- Verifica se 'a' menor que 'b' */
int menor(Voo voo[VOO], int n) {
    if (voo[n].ano < voo[n - 1].ano) {
        return 1;
    }
    else if (voo[n].ano == voo[n - 1].ano) {
        if (voo[n].mes < voo[n - 1].mes) {
            return 1;
        }
        else if (voo[n].mes == voo[n - 1].mes) {
            if(voo[n].dia < voo[n - 1].dia) {
                return 1;
            }
            else if (voo[n].dia == voo[n - 1].dia) {
                if (voo[n].hora < voo[n - 1].hora) {
                    return 1;
                }
                else if (voo[n].hora == voo[n - 1].hora) {
                    if (voo[n].min < voo[n - 1].min) {
                        return 1;
                    }
                    else if (voo[n].min == voo[n - 1].min) {
                        return 1;
                    }
                }
            }
        }
    }
    return 0;
}


/* Bubble sort ->
- Utiliza a funcao menor para organizar os voos dados */
void bubble(Voo voo[VOO], int esq, int dir) {
    int i, j, fim;
    Voo t;

    for (i = esq; i < dir-1; i++) {
        fim = 1;
        for (j = dir - 1; j > i; j--) {
            if (menor(voo, j)) {
                t = voo[j];
                voo[j] = voo[j - 1];
                voo[j - 1] = t;
                fim = 0;
            }
        }
        if (fim) break;
    }
}