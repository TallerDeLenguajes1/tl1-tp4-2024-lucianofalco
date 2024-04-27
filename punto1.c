/*Desarrolle una interfaz de carga de tareas para solicitar tareas pendientes, en la cual se
solicite descripción y duración de la misma (el id debe ser generado automáticamente por
el sistema, de manera autoincremental comenzando desde el número 1000). Al cabo de
cada tarea consulte al usuario si desea ingresar una nueva tarea o finalizar la carga.
*/

/*
2) Implemente una interfaz para elegir qué tareas de la lista de pendientes deben ser
transferidas a la lista de tareas realizadas
*/

/*
4) Implemente una funcionalidad que permita consultar tareas por id o palabra clave y
mostrarlas por pantalla, indicando si corresponde a una tarea pendiente o realizada.
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

typedef struct Tarea
{
    int TareaID;       // Numérico autoincremental comenzando en 1000
    char *Descripcion; //
    int Duracion;      // entre 10 – 100
} Tarea;

typedef struct Nodo
{
    struct Tarea T;
    struct Nodo *Siguiente;
} Nodo;

typedef struct Nodo *Lista;

Lista crearListaVacia();
int generarNumeroAleatorio(int min, int max);
Tarea crearTarea();
void MostrarTarea(Tarea tarea);
Nodo *crearNodo(Tarea t);
void InsertarNodoALista(Lista *lista, Nodo *nodo);
void MostrarLista(Lista lista);
void InsertarNodoAlFinalDeLaLista(Lista *lista, Nodo *nodo);
Nodo *BuscarNodo(Lista lista, int id);
void BorrarNodo(Lista *lista, Nodo *nodo);
void moverNodo(Lista *lista1 , Lista *lista2, Tarea tarea);
void ListarTareas(Lista TP , Lista TA);


int main(int argc, char const *argv[])
{
    Lista TareaPendiente, TareaRealizada;
    Nodo *nodo1, *nodo2, *nodo3, *nodo4, *nodo5, *nodo6, *nodo7 , *nodo8;
    TareaPendiente = crearListaVacia();
    TareaRealizada = crearListaVacia();
    Tarea tarea1 = crearTarea();
    Tarea tarea2 = crearTarea();
    Tarea tarea3 = crearTarea();


    nodo1 = crearNodo(tarea1);
    nodo2 = crearNodo(tarea2);
    nodo3 = crearNodo(tarea3);

    InsertarNodoALista(&TareaPendiente , nodo1);
    InsertarNodoALista(&TareaPendiente , nodo2);
    InsertarNodoALista(&TareaPendiente , nodo3);
    printf("\nTareas Pendiente: \n\n");
    MostrarLista(TareaPendiente);

    moverNodo(&TareaPendiente , &TareaRealizada , tarea1);
    printf("\nTareas Pendientes: \n\n");
    MostrarLista(TareaPendiente);
    printf("\nTareas Finalizadas: \n\n");
    MostrarLista(TareaRealizada);
    ListarTareas(TareaPendiente , TareaRealizada);

    return 0;
}

void ListarTareas(Lista TP , Lista TA){
    printf("Tareas pendientes:\n");
    MostrarLista(TP);
    printf("\n\n");
 
    printf("Tareas Realizadas:\n");
    MostrarLista(TA);
    printf("\n\n");
}

void moverNodo(Lista *lista1 , Lista *lista2, Tarea Tarea){

    Nodo *aux = BuscarNodo(*lista1 , Tarea.TareaID);
    Nodo *nodoMover;

    if (aux == NULL)
    {
        printf("\nNo se encontro la tarea\n");
    }
    else
    {
        nodoMover  = crearNodo(aux->T);
        InsertarNodoALista(lista2 , nodoMover);
        BorrarNodo(lista1 , nodoMover);
    }   
}

void BorrarNodo(Lista *lista, Nodo *nodo)
{
    Nodo *actual = *lista;
    Nodo *anterior = NULL;

    while ((actual != NULL) && (actual->T.TareaID != nodo->T.TareaID))
    {
        anterior = actual;
        actual = actual->Siguiente;
    }

    if (actual == NULL)
    {
        if (*lista == NULL)
        {
            printf("La lista esta vacia\n");
        }
        else
            printf("\nNo se encontro el elemento en la lista\n");
    }
    else
    {
        if (*lista == actual)
        {
            *lista = actual->Siguiente;
        }
        else
        {
            anterior->Siguiente = actual->Siguiente;
            free(actual);
        }
    }
}

Nodo *BuscarNodo(Lista lista, int id)
{
    Nodo *aux = lista;
    while (aux != NULL && aux->T.TareaID != id)
    {
        aux = aux->Siguiente;
    }
    return aux;
}
void InsertarNodoAlFinalDeLaLista(Lista *lista, Nodo *nodo)
{
    Nodo *aux = *lista;

    if (*lista == NULL)
    {
        *lista = nodo;
    }
    else
    {
        while (aux->Siguiente != NULL)
        {
            aux = aux->Siguiente;
        }
        aux->Siguiente = nodo;
    }

}

void MostrarLista(Lista lista)
{
    Nodo *auxiliar = lista;
    while (auxiliar != NULL)
    {
        MostrarTarea(auxiliar->T);
        auxiliar = auxiliar->Siguiente;
    }
}

void InsertarNodoALista(Lista *lista, Nodo *nodo)
{
    nodo->Siguiente = *lista;
    *lista = nodo;
}

Nodo *crearNodo(Tarea t)
{
    Nodo *nuevoNodo = (Nodo *)malloc(sizeof(Nodo));
    nuevoNodo->T.TareaID = t.TareaID;
    nuevoNodo->T.Duracion = t.Duracion;
    nuevoNodo->T.Descripcion = t.Descripcion;
    nuevoNodo->Siguiente = NULL;
    return nuevoNodo;
}

Tarea crearTarea()
{
    Tarea tarea;
    char buff[100];
    printf("Ingresar Tarea\n");
    fflush(stdin);
    gets(buff);
    tarea.Descripcion = (char *)malloc((strlen(buff) + 1) * sizeof(char));
    strcpy(tarea.Descripcion, buff);
    tarea.Duracion = generarNumeroAleatorio(10, 100);
    static int tareaID = 1000;
    tarea.TareaID = tareaID++;
    return tarea;
}
void MostrarTarea(Tarea tarea)
{
    printf("ID: %d \n", tarea.TareaID);
    printf("Duracion: %d \n", tarea.Duracion);
    printf("descripcion: %s\n ", tarea.Descripcion);
}

Lista crearListaVacia()
{
    return NULL;
}

int generarNumeroAleatorio(int min, int max)
{
    return (rand() % (max - min + 1) + min);
}
