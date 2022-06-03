/* Sofia Paiva 102835 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>


/* Maximo de uma string */
#define STR 65535

/* Maximo de aeroportos */
#define AERO 40

/* Aeroporto */
#define ID 4
#define PAIS 31
#define CID 51

/* Maximo de voos */
#define VOO 30000

/* Voo */
#define COD 9


/* Estrutura de um aeroporto */
typedef struct aeroporto{
    char id[ID];
    char pais[PAIS];
    char cidade[CID];
    int voo;
} Aero;

/* Estrutura de um voo */
typedef struct voo{
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
    int ocp;
} Voo;

/* Estrutura de uma data */
typedef struct data{
    int dia;
    int mes;
    int ano;
} Data;

typedef struct reserva *reserva;
typedef struct link *link;

/* Estrutura de uma reserva */
struct reserva{
    char voo_cod[COD];
    char *res_cod;
    int dia;
    int mes;
    int ano;
    int pass;
};

/* Estrutura de link */
struct link{
    reserva res;
    struct link *next;
};


/* Funcoes implementadas */
int adiciona_aeroporto(char s[STR], Aero aero[AERO], int n_aero);

void lista_aeroporto(char s[STR], Aero aero[AERO], int n_aero);

int adiciona_lista_voo(char s[STR], Voo voos[VOO], Aero aero[AERO], int n_aero,
int n_voo, Data data);

void lista_voo_partida(char s[STR], Voo voos[VOO], Aero aero[AERO], int n_voo,
int n_aero);

void lista_voo_chegada(char s[STR], Voo voos[VOO], Aero aero[AERO], Data data, int n_voo,
int n_aero);

Data avanca_data(char s[STR], Data data);

void bubble(Voo voo[VOO], int esq, int dir);

int menor(Voo voo[VOO], int n);

link adiciona_lista_reserva(char s[STR], Voo voos[VOO], int n_voo, Data data,
link head);

int elimina_voo_reserva(char s[STR], Voo voos[VOO], int n_voo, link head);

int elimina_voo(char s[STR], Voo voos[VOO],int n_voo, Data data);

link elimina_reserva(char s[STR], Voo voos[VOO], int n_voo, link head);


int main() {
    static link head = NULL;
    char c,comando;
    Aero aero[AERO] = {0};
    int  n_aero = 0, n_voo = 0, len;
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
                lista_voo_chegada(s, voos, aero, data, n_voo, n_aero);
                break;

            case 't':
                /* avanca data do sistema */
                data = avanca_data(s, data);
                break;

            case 'r':
                /* adiciona reserva ou lista reserva */
                head = adiciona_lista_reserva(s, voos, n_voo, data, head);
                break;

            case 'e':
                /* elimina voo ou reserva */
                if (elimina_voo_reserva(s, voos, n_voo, head)) {
                    len = strlen(s);
                    if (len < 10) {
                        n_voo = elimina_voo(s, voos, n_voo, data);
                    }
                    
                    head = elimina_reserva(s, voos, n_voo, head);
                }
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
    int i, j, min = 0, max = n_aero, len;
    char id[ID], pais[PAIS], cidade[CID];

    sscanf(s + 1,"%s %s %[^\n]",id, pais, cidade);

    /* Verifica se o ID do aeroporto eh valido */
    len = strlen(id);
    for (i = 0; id[i] != '\0'; i++) {
        if(id[i] < 'A' || id[i] > 'Z' || len != 3) {
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
    int countp = 0, countc = 0, len, count_al = 0, count_num = 0;
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
            if ((cod[i] > 'A' && cod[i] <'Z') || (cod[i] > 'a' && cod[i] < 'z')) {
                count_al++;
            }

            else {
                count_num++;
            }
        }

        for (i = 0; i < len; i++) {
            if (count_al < 2 || count_al > 4 || count_num < 1 || count_num > 4) {
                printf("invalid flight code\n");
            }
            if (i < count_al && (cod[i] < 'A' || cod[i] > 'Z' || cod[i] < 'a' || 
            cod[i] > 'z')) {
                printf("invalid flight code\n");
                return n_voo;
            }
            if (i == count_al && (cod[i] < 49 || cod[i] > 57)) {
                printf("invalid flight code\n");
                return n_voo;
            }
            if (i > count_al && (cod[i] < 48 || cod[i] > 57)) {
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
        if (cap < 10) {
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
void lista_voo_chegada(char s[STR], Voo voos[VOO], Aero aero[AERO], Data data, 
int n_voo, int n_aero) {
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
        if ((dia >= data.dia && mes == data.mes && ano == data.ano) || 
        (mes > data.mes && ano == data.ano) || (ano > data.ano)) {
            printf("%s %s %02d-%02d-%d %02d:%02d\n", voo_c[i].cod, voo_c[i].id_p,
            voo_c[i].dia, voo_c[i].mes, voo_c[i].ano, voo_c[i].hora, voo_c[i].min);
        }
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


/* str_menor ->
- Verifica se a nova reserva eh menor que a reserva ja colocada
- False no caso da nova reserva nao ser menor do que a la esta */
int str_menor(char *new_res, char *res) {
    int len_r = strlen(res), len_n = strlen(new_res), i, min;

    if (len_r < len_n) {
        min = len_r;
    }

    else {
        min = len_n;
    }

    for (i = 0; i < min; i++) {
        if (*(new_res + i) < *(res + i)) {
            return 1;
        }

        else if (*(new_res + i) > *(res + i)) {
            return 0;
        }
    }
    if (len_n < len_r) {
        return 1;
    }

    return 0;
}


/* comando 'r' ->
- No caso de apenas ter dois argumentos, lista as reservas associadas ao voo 
- No caso de ter mais do que dois argumentos adiciona a reserva */
link adiciona_lista_reserva(char s[STR], Voo voos[VOO], int n_voo, Data data,
link head) {
    char voo_cod[COD], *res_cod, buffer[STR];
    reserva res = (reserva) malloc(sizeof(struct reserva));
    int pass, count = 0, aux_voo = 0, dia, mes, ano, i, len = 0, aux = 0;
    link l, prev;
    link new = (link) malloc(sizeof(struct link));

    /* Verifica se lhe eh dada uma string com dois ou mais argumentos */
    for (i = 0; s[i] != '\0'; i++) {
        if (s[i] == ' ') {
            count++;
        }

        if (count == 2 && count <= 3) {
            aux++;
        }
    }

    /* No caso de ser com apenas dois argumentos */
    if (count == 2) {
        sscanf(s + 1,"%s %d-%d-%d", voo_cod, &dia, &mes, &ano);

    }

    /* No caso de ter mais do que dois argumentos */
    else if (count > 2) {
        sscanf(s + 1,"%s %d-%d-%d %s %d", voo_cod, &dia, &mes, &ano, buffer,
        &pass);
    }

    len = strlen(buffer);
    res_cod = (char*) malloc((len + 1) * sizeof(char*));
    strcpy(res_cod, buffer);

    /* Verifica se eh excedida a memoria */
    if (res_cod == NULL) {
        printf("No memory\n");
        free(res_cod);
        exit(0);
        return head;
    } 

    /* Verifica se o codigo de reserva eh valido */
    if (count > 2) {
        for (i = 0; i < len; i++) {
            if (!((res_cod[i] >= 'A' && res_cod[i] <= 'Z') ||
            (res_cod[i] >= '1' && res_cod[i] <= '9')) || len < 10) {
                printf("invalid reservation code\n");
                free(res_cod);
                return head;
            }
        }
    }

    /* Verifica se o codigo de voo existe */
    for (i = 0; i < n_voo; i++) {
        if (strcmp(voo_cod, voos[i].cod) || ((!strcmp(voo_cod, voos[i].cod) && 
        (voos[i].dia != dia || voos[i].mes != mes || voos[i].ano != ano)))) {
            aux_voo++;
        }
    }

    if (aux_voo == n_voo) {
        printf("%s: flight does not exist\n", voo_cod);
        free(res_cod);
        return head;
    }

    /* Verifica se o codigo de reserva ja existe */
    if (count > 2 && head != NULL) {
        for (l = head; l != NULL; l = l->next){
            if (!strcmp(l->res->res_cod, res_cod)) {
                printf("%s: flight reservation already used\n", res_cod);
                free(res_cod);
                return head;
            }        
        } 
    }

    /* Verifica se a reserva criada excede a capacidade do voo */ 
    if (count > 2) {
        for (i = 0; i < n_voo; i++) {
            if (!strcmp(voos[i].cod, voo_cod) && voos[i].dia == dia &&
            voos[i].mes == mes && voos[i].ano == ano) {
                if ((voos[i].ocp + pass) > voos[i].cap) {
                    printf("too many reservations\n");
                    free(res_cod);
                    return head;
                }
            }
        }
    }

    /* Verifica se a data eh valida */
    if ((ano < data.ano) || (ano == data.ano && mes < data.mes) 
    || (ano == data.ano && mes == data.mes && dia < data.dia)) {
        printf("invalid date\n");
        free(res_cod);
        return head;
    }

    /* Verifica se o numero de passageiros eh valido */
    if (count > 2 && pass <= 0) {
        printf("invalid passenger number\n");
        free(res_cod);
        return head;
    }

    /* Imprime as reservas que existem naquele dia e para o codigo de voo */
    if (count == 2) {
        for (l = head; l != NULL; l = l->next){
            if (!strcmp(l->res->voo_cod, voo_cod) && l->res->dia == dia &&
            l->res->mes == mes && l->res->ano == ano) {
                printf("%s %d\n", l->res->res_cod, l->res->pass);
            }        
        }
        free(res_cod);
        return head;
    }
 
    /* Atualiza o numero de passageiros que vao ocupar o voo */
    if (count > 2) {
        for (i = 0; i < n_voo; i++) {
            if (!strcmp(voos[i].cod, voo_cod) && voos[i].dia == dia &&
            voos[i].mes == mes && voos[i].ano == ano) {
                if (!((voos[i].ocp + pass) > voos[i].cap)){
                    voos[i].ocp += pass;
                }
            }
        }
    }

    /* Adiciona a reserva para a lista de reservas */
    res->res_cod = (char*) malloc((len + 1) * sizeof(char));

    strcpy(res->voo_cod, voo_cod);
    res->dia = dia;
    res->mes = mes;
    res->ano = ano;
    strcpy(res->res_cod, res_cod);
    res->pass = pass;

    new->res = res;
    new->next = NULL;
    if (head == NULL) {
        free(res_cod);
        return new;
    }

    /* Adiciona a reserva na posicao correta de acordo com a ordem 
    lexicografica */
    for (l = head, prev = NULL; l != NULL; prev = l, l = l->next) {
        if (str_menor(res_cod, l->res->res_cod)) {

            if (prev == NULL) {
                new->next = l;
                free(res_cod);
                return new;
            }

            else {
                prev->next = new;
                new->next = l;
                free(res_cod);
                return head;
            }
            break;
        }
    }

    prev->next = new;
    free(res_cod);

    return head;
}


/* comando 'e' ->
- No caso do codigo introduzido ser um codigo de voo, verifica se esse voo 
existe
- No caso do codigo introduzido ser um codigo de uma reserva verifica se essa
reserva existe */
int elimina_voo_reserva(char s[STR], Voo voos[VOO], int n_voo,
link head) {
    int count = 0, i, len, aux_res = 0;
    link l;
    char *cod, buffer[STR];

    sscanf(s + 1, "%s", buffer);

    len = strlen(buffer);
    cod = (char*) malloc((len + 1) * sizeof(char));
    strcpy(cod, buffer);

    /* Verifica se o codigo de reserva existe */
    if (len >= 10) {
        for (l = head; l != NULL; l = l->next){
            if (strcmp(l->res->res_cod, cod)) {
                count++;
            }
            aux_res++;  
        }
        
        if (aux_res == count) {
            free(cod);
            free(l);
            printf("not found\n");
            return 0;
        }

    }

    /* Verifica se o codigo de voo existe */
    else {
        for (i = 0; i < n_voo; i++) {
            if (strcmp(voos[i].cod, cod)) {
                count++;
            }
        }

        if (count == n_voo) {
            free(cod);
            printf("not found\n");
            return 0;
        }
    }

    return 1;
}


/* comando 'e' ->
- No caso do codigo introduzido ser um codigo de voo, todos os voos com esse
codigo sao eliminados */
int elimina_voo(char s[STR], Voo voos[VOO], int n_voo, Data data) {
    int i = 0, j, count_not_found = 0, hora, min, dia, mes, ano;
    char voo_cod[COD];

    sscanf(s + 1, "%s", voo_cod);

    /* Elimina o voo inserido se a data de chegada for inferior ah data do 
    sistema */
    while (i < n_voo) {
        if (!strcmp(voos[i].cod, voo_cod)){
            hora = voos[i].hora + voos[i].dur_h;
            min = voos[i].min + voos[i].dur_m;
            dia = voos[i].dia;
            mes = voos[i].mes;
            ano = voos[i].ano;

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

            if ((dia < data.dia && mes == data.mes && ano == data.ano) || 
            (mes < data.mes && ano == data.ano) || (ano < data.ano)) {
                for (j = i; j < n_voo; j++) {
                    voos[j] = voos[j + 1];
                }
                n_voo--;
            }
        }
        else {
            i++;
            count_not_found++;
        }
    }

    if (count_not_found == n_voo) {
        printf("not found\n");
        return n_voo;
    }

    return n_voo;
}


/* comando 'e' ->
- No caso do codigo introduzido ser um codigo de voo, elimina todas as reservas
associadas a esse voo
- No caso do codigo introduzido ser o codigo de uma reserva, elimina a reserva 
com esse codigo */
link elimina_reserva(char s[STR], Voo voos[VOO], int n_voo, link head) {
    char *cod, buffer[STR];
    int i, len;
    link l, prev;

    sscanf(s + 1, "%s", buffer);

    len = strlen(buffer);
    cod = (char*) malloc((len + 1) * sizeof(char));
    strcpy(cod, buffer);

    /* Elimina as reservas associadas ao voo ou ah reserva inserida */
    for (l = head, prev = NULL; l != NULL; prev = l, l = l->next) {
        if (!strcmp(l->res->res_cod, cod) || !strcmp(l->res->voo_cod, cod)) {
            if (len >= 10) {
                /* Atualiza o numero de passeiros no voo */
                for (i = 0; i < n_voo; i++) {
                    if (!strcmp(voos[i].cod, l->res->voo_cod)) {
                        voos[i].ocp -= l->res->pass;
                    }
                }
            }

            if (l == head) {
                head = l->next;
            }
            else {
                prev->next = l->next;
            }
            free(l->res->res_cod);
            free(l->res);
        }
    }

    free(l);
    free(cod);
    return head;
}