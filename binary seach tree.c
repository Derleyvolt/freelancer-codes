// struct referente Ã  cada caractere
typedef struct Node {
    char val;
    struct Node* esq, *dir;
} node;

// cria um no
node* criar_node(char val) {
    node* no = (node*)malloc(sizeof(struct Node));
    no->val = val;
    no->esq = NULL;
    no->dir = NULL;
}

// insere os elementos na Ã¡rvore binÃ¡ria simples
void inserir(node** no, char val) {
    if((*no) == NULL) {
        (*no) = criar_node(val);
    } else {
        if(val > (*no)->val) {
            inserir(&(*no)->dir, val);
        } else if(val < (*no)->val) {
            inserir(&(*no)->esq, val);
        } else {
            return;
        }
    }
}

// busca por um caractere especÃ­fico e retorna sua frequencia
int buscar(node* no, char val) {
    if(no == NULL)
        return -1;

    if(no->val == val)
        return 1;
    
    // o elemento estÃ¡ Ã  direita ou Ã  esquerda
    if(val > no->val)
        return buscar(no->dir, val);
    else
        return buscar(no->esq, val);
}

int main() {

  
}
