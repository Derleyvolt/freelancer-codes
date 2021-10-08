#include <stdio.h>
#include <string.h>
#include <stdlib.h>

// as funções desse arquivo assumem que o usuário entra com todos os dados corretos..

char meses[12][30] = { "janeiro", "fevereiro", "marco", "abril", "maio", "juior", "julho", "agosto", "setembro", "outubro", "novembro",
                       "dezembro" };

typedef struct dt {
    int ano;
    int mes;
    int dia;
} data;

// retorna se a primeira data vem primeiro que a segunda data
int maior(data a, data b) {
    if(a.ano > b.ano) {
        return 1;
    } else if(a.ano < b.ano) {
        return 0;
    }

    if(a.mes > b.mes) {
        return 1;
    } else if(a.mes < b.mes) {
        return 0;
    }

    if(a.dia > b.dia) {
        return 1;
    } else if(a.dia < b.dia) {
        return 0;
    }

    return 0;
}

// retorna a diferença em dias entre duas datas
int diferenca(data a, data b) {
    if(maior(a, b) == 0) {
        data c = a;
        a = b;
        b = c;
    }

    int dias = 0;
    dias += (a.ano-b.ano)*365;
    dias -= b.mes * 31 + b.dia;
    dias += a.mes * 31 + a.dia;

    return dias;
}

// parseia a data no formato DD/MM/YYYY
data pegar_data_formato1(char buf[50]) {
    data a;
    char* first_symbol, *second_symbol;
    for(int i = 0; i < strlen(buf); i++) {
        if(buf[i] == '/') {
            buf[i] = 0;
            first_symbol = buf+i+1;
            break;
        }
    }

    for(char* i = first_symbol+1; *i != '\0'; i++) {
        if(*i == '/') {
            *i = 0;
            second_symbol = i+1;
            break;
        }
    }

    a.dia = atoi(buf);
    a.mes = atoi(first_symbol);
    a.ano = atoi(second_symbol);
    return a;
}

// parseia a data no formato YYYY-MM-DD
data pegar_data_formato2(char buf[50]) {
    data a;
    char* first_symbol, *second_symbol;
    for(int i = 0; i < strlen(buf); i++) {
        if(buf[i] == '-') {
            buf[i] = 0;
            first_symbol = buf+i+1;
            break;
        }
    }

    for(char* i = first_symbol+1; *i != '\0'; i++) {
        if(*i == '-') {
            *i = 0;
            second_symbol = i+1;
            break;
        }
    }

    a.ano = atoi(buf);
    a.mes = atoi(first_symbol);
    a.dia = atoi(second_symbol);
    return a;
}

// parseia a data no formato DD [mês-por-extenso] YYYY
data pegar_data_formato3(char buf[50]) {
    data a;
    char* first_symbol, *second_symbol;
    for(int i = 0; i < strlen(buf); i++) {
        if(buf[i] == ' ') {
            buf[i] = 0;
            first_symbol = buf+i+1;
            break;
        }
    }

    for(char* i = first_symbol; *i != '\0'; i++) {
        if(*i == ' ') {
            *i = 0;
            second_symbol = i+1;
            break;
        }
    }

    a.dia = atoi(buf);

    // transformando em lower case
    for(char* i = first_symbol; *i != '\0'; i++) {
        if(*i >= 'A' && *i <= 'Z') {
            printf("xx\n");
            *i += 32;
        }
    }

    for(int i = 0; i < 12; i++) {
        if(strcmp(meses[i], first_symbol) == 0) {
            a.mes = i+1;
            break;
        }
    }

    a.ano = atoi(second_symbol);
    return a;
}

void resolver() {
    printf("Entre com duas datas em um dos formatos: [DD/MM/YYY], [YYYY-MM-DD] ou [DD (mes por extenso) YYYY]\n");
    char str_data1[30];
    char str_data2[30];
    fgets(str_data1, 30, stdin);
    fgets(str_data2, 30, stdin);

    data a, b;

    if(str_data1[strlen(str_data1)-1] == '\n') {
        str_data1[strlen(str_data1)-1] = 0;
    }

    if(strchr(str_data1, '-') != NULL) {
        a = pegar_data_formato2(str_data1);
    } else if(strchr(str_data1, '/') != NULL) {
        a = pegar_data_formato1(str_data1);
    } else {
        a = pegar_data_formato3(str_data1);
    }

    if(str_data2[strlen(str_data2)-1] == '\n') {
        str_data2[strlen(str_data2)-1] = 0;
    }

    if(strchr(str_data2, '-') != NULL) {
        b = pegar_data_formato2(str_data2);
    } else if(strchr(str_data2, '/') != NULL) {
        b = pegar_data_formato1(str_data2);
    } else {
        b = pegar_data_formato3(str_data2);
    }


    printf("A diferenca de dias entre as datas eh: %d dias\n\n", diferenca(a, b));

    if(maior(a, b)) {
        printf("A data %d/%d/%d eh maior que a data %d/%d/%d", a.dia, a.mes, a.ano, b.dia, b.mes, b.ano);
    } else if(maior(b, a)) {
        printf("A data %d/%d/%d eh maior que a data %d/%d/%d", b.dia, b.mes, b.ano, a.dia, a.mes, a.ano);
    } else {
        printf("As datas sao iguais\n");
    }
}

int main() {
    resolver();
    return 0;
}
