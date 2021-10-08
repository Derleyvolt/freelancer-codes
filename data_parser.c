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

// parseia a data no formato YYYY-MM-DD
data pegar_data_formato3(char buf[50]) {
    data a;
    a.ano = a.dia = a.mes = 0;
    int m = 1000;
    for(int i = 0; i < 4; i++) {
        a.ano += (buf[i]-'0')*m;
        m = m / 10;
    }

    int mes_tam = 0;

    for(int i = 5; i < 7; i++) {
        if(buf[i] != '-') {
            mes_tam++;
        }
    }

    m = mes_tam == 2 ? 10 : 1;
    for(int i = 5; i < 5+mes_tam; i++) {
        a.mes += (buf[i]-'0')*m;
        m = m / 10;
    }

    int sec_hif = 0;
    int aux = 0;
    for(int i = 0; i < strlen(buf) && aux < 2; i++) {
        if(buf[i] == '-') {
            aux++;
            if(aux == 2) {
                sec_hif = i;
            }
        }
    }

    m = strlen(buf)-sec_hif-1 == 2 ? 10 : 1;
    for(int i = sec_hif+1; i < strlen(buf); i++) {
        a.dia += (buf[i]-'0')*m;
        m = m / 10;
    }

    return a;
}

// parseia a data no formato DD/MM/YYYY
data pegar_data_formato1(char buf[50]) {
    data a;
    a.ano = a.dia = a.mes = 0;
    int dia_tam = strchr(buf, '/')-buf;
    int m = dia_tam == 2 ? 10 : 1;
    for(int i = 0; i < dia_tam; i++) {
        a.dia += (buf[i]-'0')*m;
        m = m/10;
    }

    int mes_tam = strchr(buf+dia_tam+1, '/') - (strchr(buf, '/')+1);

    m = mes_tam == 2 ? 10 : 1;
    for(int i = dia_tam+1; i < dia_tam+1+mes_tam; i++) {
        a.mes += (buf[i]-'0')*m;
        m = m/10;
    }

    int idx = strchr(buf+dia_tam+1, '/')-buf+1;

    m = 1000;
    for(int i = idx; i < strlen(buf); i++) {
        a.ano += (buf[i]-'0')*m;
        m = m/10;
    }

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

    data a = pegar_data_formato3(buf);
    printf("%d/%d/%d\n", a.dia, a.mes, a.ano);
}

int main() {
    obter_data_formato_1();
    obter_data_formato_3();
    return 0;
}
