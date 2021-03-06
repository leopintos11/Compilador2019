#include "arbol.h"
#include <stdlib.h>
#include <stdio.h>
#include <string.h>

tipoArbol crearArbol() {
    return NULL;
}

tipoNodoArbol* crearNodo(char* valor, tipoNodoArbol* hijoIzquierdo, tipoNodoArbol* hijoDerecho) {
    tipoNodoArbol* nodo = (tipoNodoArbol*)malloc(sizeof(tipoNodoArbol));
    nodo->hijoDerecho = hijoDerecho;
    nodo->hijoIzquierdo = hijoIzquierdo;
    nodo->padre = NULL;
    nodo->valor = (char*)malloc(sizeof(char)*50);
    strcpy(nodo->valor, valor);

    if(hijoDerecho != NULL) {
        hijoDerecho->padre = nodo;
    }

    if(hijoIzquierdo != NULL) {
        hijoIzquierdo->padre = nodo;
    }

    return nodo;
}

tipoNodoArbol* crearHoja(char* valor) {
    return crearNodo(valor, NULL, NULL);
}

void setHijoDerecho(tipoArbol arbol, tipoNodoArbol* nodo) {
    arbol->hijoDerecho = nodo;
}

void setHijoIzquierdo(tipoArbol arbol, tipoNodoArbol* nodo) {
    arbol->hijoIzquierdo = nodo;
}

void setValor(tipoArbol arbol, char* valor) {
    arbol->valor = valor;
}

char* getValor(tipoArbol arbol) {
    return arbol->valor;
}

tipoNodoArbol* getHijoIzquierdo(tipoArbol arbol) {
    return arbol->hijoIzquierdo;
}

tipoNodoArbol* getHijoDerecho(tipoArbol arbol) {
    return arbol->hijoDerecho;
}

void recorrerArbolPreorder(tipoArbol arbol) {
    printf("%s\n", arbol->valor);
    if(arbol->hijoIzquierdo !=  NULL)
        recorrerArbolPreorder(arbol->hijoIzquierdo);
    if(arbol->hijoDerecho !=  NULL)
        recorrerArbolPreorder(arbol->hijoDerecho);
}

void recorrerArbolPostorder(tipoArbol arbol) {
    if(arbol->hijoIzquierdo !=  NULL)
        recorrerArbolPostorder(arbol->hijoIzquierdo);
    if(arbol->hijoDerecho !=  NULL)
        recorrerArbolPostorder(arbol->hijoDerecho);
    printf("%s\n", arbol->valor);
}

void recorrerArbolInorder(tipoArbol arbol) {
    if(arbol->hijoIzquierdo !=  NULL)
        recorrerArbolInorder(arbol->hijoIzquierdo);
    printf("%s\n", arbol->valor);
    if(arbol->hijoDerecho !=  NULL)
        recorrerArbolInorder(arbol->hijoDerecho);
}

void recorrerArbolPreorderConNivel(tipoArbol arbol, int nivel) {
    int i;
    for(i = 0; i < nivel; i++)
        printf("\t");
    if(arbol == NULL) {
        printf("NULL\n");
    }
    else {
        printf("%s\n", arbol->valor);
        //if(arbol->hijoIzquierdo !=  NULL) 
            recorrerArbolPreorderConNivel(arbol->hijoIzquierdo, nivel +1);
            
        //if(arbol->hijoDerecho !=  NULL)
            recorrerArbolPreorderConNivel(arbol->hijoDerecho, nivel +1);
    }
}

int tamanioArbol(tipoArbol arbol) {
    int tamanioDerecho = 0;
    int tamanioIzquierdo = 0;

    if(arbol->hijoDerecho == NULL && arbol->hijoIzquierdo == NULL)
        return 0;

    if(arbol->hijoDerecho != NULL) {
        tamanioDerecho = tamanioArbol(arbol->hijoDerecho);
    }
    if(arbol->hijoIzquierdo != NULL) {
        tamanioIzquierdo = tamanioArbol(arbol->hijoIzquierdo);
    }

    return  ((tamanioDerecho > tamanioIzquierdo) ? tamanioDerecho : tamanioIzquierdo) + 1;
}

void guardarArbolInorder(tipoArbol arbol, FILE *archivo) {
    if(arbol->hijoIzquierdo !=  NULL)
        guardarArbolInorder(arbol->hijoIzquierdo, archivo);
    fprintf(archivo, "%s\n", arbol->valor);
    if(arbol->hijoDerecho !=  NULL)
        guardarArbolInorder(arbol->hijoDerecho, archivo);
}

tipoArbol buscarSubarbolInicioAssembler(tipoArbol arbol) {
    tipoArbol subarbolIzquierdo = NULL;
    tipoArbol subarbolDerecho = NULL;

    if(arbol->hijoIzquierdo == NULL && arbol->hijoDerecho == NULL) {
        return NULL;
    }

    if(arbol->hijoIzquierdo != NULL) {
        subarbolIzquierdo = buscarSubarbolInicioAssembler(arbol->hijoIzquierdo);
    }
    if(arbol->hijoDerecho != NULL)
    {
        subarbolDerecho = buscarSubarbolInicioAssembler(arbol->hijoDerecho);
    }

    if(esOperadorUnario(arbol->valor) == 1) {
        return arbol;
    }

    if(esSentenciaControl(arbol->valor) == 1) {
        return arbol;
    }

    if(subarbolIzquierdo == NULL && subarbolDerecho == NULL) {
        return arbol;
    }

    if(subarbolIzquierdo != NULL) {
        return subarbolIzquierdo;
    }

    if(subarbolDerecho != NULL) {
        return subarbolDerecho;
    }

    return arbol;
}

int esOperadorUnario(char* valor) {
    if(strcmp(valor, "ENTRADA") == 0 || strcmp(valor, "SALIDA") == 0 || strcmp(valor, "NOT") == 0) {
        return 1;
    }
    return 0;
}

void podarArbol(tipoNodoArbol* arbol) {
    arbol->hijoDerecho = arbol->hijoIzquierdo = NULL;
}

int contarOperadores(tipoNodoArbol* arbol) {
   if (arbol->valor == NULL)
   {
      return 0;
   }
   
   return contarOperadores(arbol->hijoDerecho) + contarOperadores(arbol->hijoIzquierdo) + esOperadorAlgebraico(arbol->valor);
}

int esOperadorAlgebraico(char* operador) {
   return strcmp(operador, "+") == 0 || strcmp(operador, "-") == 0 || strcmp(operador, "*") == 0 || strcmp(operador, "/") == 0;
}

int esSentenciaControl(char* operador) {
    if(strcmp(operador, "IF") == 0 || strcmp(operador, "WHILE") == 0) {
        return 1;
    } else {
        return 0;
    }
}

tipoNodoArbol* obtenerSiguienteExpresionDeLista(tipoNodoArbol* arbol) {
    tipoNodoArbol* resultadoIzquierdo = NULL;
    tipoNodoArbol* resultadoDerecho = NULL;

    if(esListaExpresion(arbol->valor)) {
        if(arbol->hijoIzquierdo != NULL) {
            resultadoIzquierdo = obtenerSiguienteExpresionDeLista(arbol->hijoIzquierdo);
            if(resultadoIzquierdo != NULL) {
                return resultadoIzquierdo;
            }
        }
        if(arbol->hijoDerecho != NULL) {
            resultadoDerecho = obtenerSiguienteExpresionDeLista(arbol->hijoDerecho);
            if(resultadoDerecho != NULL) {
                return resultadoDerecho;
            }
        }
        return NULL;
    } else {
        return arbol;
    }
    

}

int esListaExpresion(char* operador) {
   return strcmp(operador, "LISTA_EXPRESION") == 0;
}