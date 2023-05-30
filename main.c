#include <stdio.h>
#include <stdlib.h>
#include <string.h>
typedef struct nodito{
    char legajo[6];
    char nombre[30];
    int sueldo;
    struct nodito* sigs;
}nodito;
typedef nodito* TSUBLISTA;

typedef struct nodo{
    char seccion[10];
    TSUBLISTA empleado;
    struct nodo* sig;
}nodo;
typedef nodo* TLISTA;
void cargalista(TLISTA *p1);
void alta(TLISTA *p1);
void muestralista(TLISTA p1);
int main()
{
    TLISTA lista;
    char x;
    cargalista(&lista);
    printf("A para alta o B para baja\n");scanf(" %c",&x);
    if(x=='A')
        alta(&lista);
    else
        baja(&lista);
    muestralista(lista);
    return 0;
}
void cargalista(TLISTA *p1)
{
    FILE* arch_empleados=fopen("empleados.txt","rt");
    TLISTA nuevo,act,ant=NULL;
    char seccion[10];
    *p1=NULL;
    act=*p1;
    TSUBLISTA nuevoS;
    nuevoS=(TSUBLISTA)malloc(sizeof(nodito));
    fscanf(arch_empleados,"%s %s %d",nuevoS->legajo,nuevoS->nombre,&nuevoS->sueldo);
    fscanf(arch_empleados,"%s",seccion);
    while(!feof(arch_empleados)){
        if(*p1==NULL || strcmp(seccion,(*p1)->seccion)<0){
            nuevo=(TLISTA)malloc(sizeof(nodo));
            strcpy(nuevo->seccion,seccion);
            nuevo->sig=*p1;
            *p1=nuevo;
            nuevo->empleado=nuevoS;
            nuevoS->sigs=NULL;
        }else{
            act=*p1;ant=NULL;
            while(act!=NULL && strcmp(seccion,act->seccion)>0){
                ant=act;act=act->sig;
            }
            if(act!=NULL && strcmp(seccion,act->seccion)==0){
                nuevoS->sigs=act->empleado;
                act->empleado=nuevoS;
            }else{
                nuevo=(TLISTA)malloc(sizeof(nodo));
                strcpy(nuevo->seccion,seccion);
                nuevo->empleado=nuevoS;
                ant->sig=nuevo;
                nuevo->sig=act;
            }

        }
     nuevoS=(TSUBLISTA)malloc(sizeof(nodito));
       fscanf(arch_empleados,"%s %s %d",nuevoS->legajo,nuevoS->nombre,&nuevoS->sueldo);
        fscanf(arch_empleados,"%s",seccion);

    }

}
void alta(TLISTA *p1)
{
    TLISTA act=*p1,ant=NULL,nuevo;
    TSUBLISTA nuevoS;
    char legajo[6],nombre[20],seccion[10];
    int sueldo;
    printf("ingese legajo, nombre, sueldo y seccion\n");scanf("%s %s %d %s",legajo,nombre,&sueldo,seccion);
    while(act!=NULL && strcmp(seccion,act->seccion)>0){
        ant=act; act=act->sig;
    }
    if(act!=NULL && strcmp(seccion,act->seccion)==0){
        nuevoS=(TSUBLISTA)malloc(sizeof(nodito));
        nuevoS->sigs=act->empleado;
        act->empleado=nuevoS;
    }else{
        nuevo=(TLISTA)malloc(sizeof(nodo));
        nuevoS=(TSUBLISTA)malloc(sizeof(nodito));
        strcpy(nuevoS->legajo,legajo);
        strcpy(nuevoS->nombre,nombre);
        nuevoS->sueldo=sueldo;
        strcpy(nuevo->seccion,seccion);
        nuevoS->sigs=NULL;
        nuevo->empleado=nuevoS;
        if(ant==NULL){
            nuevo->sig=*p1;
            *p1=nuevo;
        }else{
            ant->sig=nuevo;
            nuevo->sig=act;
        }
    }
    /*if(act==NULL){
        nuevo=(TLISTA)malloc(sizeof(nodo));
        nuevoS=(TSUBLISTA)malloc(sizeof(nodito));
        strcpy(nuevoS->legajo,legajo);
        strcpy(nuevoS->nombre,nombre);
        nuevoS->sueldo=sueldo;
        strcpy(nuevo->seccion,seccion);
        ant->sig=nuevo;
        nuevo->sig=NULL;
        nuevo->empleado=nuevoS;
    }else{
        nuevoS=(TSUBLISTA)malloc(sizeof(nodito));
        nuevoS->sigs=act->empleado;
        act->empleado=nuevoS;
    }*/
}
void baja(TLISTA *p1)
{
    TLISTA actL=*p1,antL=NULL;
    TSUBLISTA actS,antS=NULL,elim;
    char legajoElim[6],seccion[10];
    printf("Ingrese el la seccion y el legajo que quiere dar de baja\n");scanf("%s %s",seccion,legajoElim);
    while(actL!=NULL && strcmp(seccion,actL->seccion)>0){
        antL=actL; actL=actL->sig;
    }
    if(actL!=NULL){
        actS=actL->empleado;
        while(actS!=NULL && strcmp(legajoElim,actS->legajo)!=0){
            antS=actS; actS=actS->sigs;
        }
        if (actS!=NULL){
            if(antS==NULL){
                elim=actS;
                actL->empleado=actS->sigs;
                free(elim);
            }else{
                elim=actS;
                antS->sigs=actS->sigs;
                actS=actS->sigs;
                free(elim);
            }
        }else
            printf("no existe ese empleado\n");
    }else
        printf("no existe esa seccion\n");

}
void muestralista(TLISTA p1)
{
    TSUBLISTA aux;
    while(p1!=NULL){
        aux=p1->empleado;
        printf("%s\n",p1->seccion);
        while(aux!=NULL){
            printf("%s %s %d\n",aux->legajo,aux->nombre,aux->sueldo);
            aux=aux->sigs;
        }
        p1=p1->sig;
    }
}
