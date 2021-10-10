#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void tirar_newline(char buf[20]) {
    if(buf[strlen(buf)-1] == '\n') {
        buf[strlen(buf)-1] = 0;
    }
}

void read_string(char* buf, int tam) {
    fgets(buf, tam, stdin);
    tirar_newline(buf);
}

int validar_data(char buf[20]) {
    printf("Digite a data no formato DD/MM/YYYY\n");
    read_string(buf, 20);

    int cnt = 0;

    for(int i = 0; i < strlen(buf); i++) {
        if(buf[i] == '/') {
            cnt++;
        }
    }

    if(cnt != 2) {
        return -1;
    }

    int idx = 0, dg_cnt = 0;

    for(int i = idx; buf[i] != '/'; i++) {
        if( !(buf[i] >= '0' && buf[i] <= '9')) {
            return -1;
        }

        idx++;
        dg_cnt++;
    }

    if(dg_cnt < 1 || dg_cnt > 2) {
        return -1;
    }

    idx++;
    dg_cnt = 0;

    for(int i = idx; buf[i] != '/'; i++) {
        if( !(buf[i] >= '0' && buf[i] <= '9')) {
            return -1;
        }

        idx++;
        dg_cnt++;
    }

    if(dg_cnt < 1 || dg_cnt > 2) {
        return -1;
    }

    idx++;
    dg_cnt = 0;

    for(int i = idx; i < strlen(buf); i++) {
        if( !(buf[i] >= '0' && buf[i] <= '9')) {
            return -1;
        }

        dg_cnt++;
    }

    if(dg_cnt != 4) {
        return -1;
    }

    char* str1 = strchr(buf, '/');
    *str1 = 0;
    char* str2 = strchr(str1+1, '/');
    *str2 = 0;

    int dia = atoi(buf);

    if(dia < 1 || dia > 31) {
        return -1;
    }

    int mes = atoi(str1+1);

    if(mes < 1 || mes > 12) {
        return -1;
    }

    *str1 = '/';
    *str2 = '/';

    return 1;
}

int main() {
    char buf[20];
    if(validar_data(buf) == 1) {
        printf("%s\n", buf);
    } else {
        printf("A data nao esta num formato valido\n");
    }

    return 0;
}
