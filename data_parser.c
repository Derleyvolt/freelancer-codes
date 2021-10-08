#include <stdio.h>
#include <string.h>

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

void obter_data_formato_1() {
    printf("Digite uma data no formato: DD/MM/YYYY\n");
    char buf[30];
    fgets(buf, 30, stdin);
    if(buf[strlen(buf)-1] == '\n') {
        buf[strlen(buf)-1] = 0;
    }

    data a = pegar_data_formato1(buf);
    printf("%d/%d/%d\n", a.dia, a.mes, a.ano);
}

void obter_data_formato_3() {
    printf("Digite uma data no formato: YYYY-MM-DD\n");
    char buf[30];
    fgets(buf, 30, stdin);
    if(buf[strlen(buf)-1] == '\n') {
        buf[strlen(buf)-1] = 0;
    }

    data a = pegar_data_formato2(buf);
    printf("%d/%d/%d\n", a.dia, a.mes, a.ano);
}

int main() {
    obter_data_formato_1();
    obter_data_formato_3();
    return 0;
}
