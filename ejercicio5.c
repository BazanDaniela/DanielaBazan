#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#define N_FILOSOFOS 5

pthread_mutex_t tenedor[N_FILOSOFOS];

/* Definición de la estructura y sinónimo de tipo.*/

struct cond_barrier {
  unsigned int NHilos;
  unsigned int count;
  pthread_mutex_t mutex;
  pthread_cond_t cond;
};

typedef struct cond_barrier barrier_t;
/****/

/****/
/* Operaciones*/

/* Creación de una barrera de condición, tomando como argumento
la cantidad de hilos que se van a esperar*/
int barrier_init(barrier_t *barr, unsigned int count) {
  barr->NHilos = count;
  barr->count = 0;
  pthread_mutex_init(&barr->mutex, NULL);
  pthread_cond_init(&barr->cond, NULL);
  return 0;
}

/* Función bloqueante para esperar a los demás hilos */
int barrier_wait(barrier_t *barr) {
  pthread_mutex_lock(&barr->mutex);

  barr->count++;


  if (barr->count == barr->NHilos)
  	pthread_cond_broadcast(&barr->cond);
  else
    pthread_cond_wait(&barr->cond, &barr->mutex);

  //pthread_cond_signal(&barr->cond);

  pthread_mutex_unlock(&barr->mutex);

  return 0;
}

/* Eliminación de la barrera */

int barrier_destroy(barrier_t *barr) {
  pthread_mutex_destroy(&barr->mutex);
  pthread_cond_destroy(&barr->cond);
  return 0;
}

barrier_t *barrera, *barrera2;

void *funcion(void *arg)
{
  int i = (int)arg;
  //for (;;)
  //{

    printf("hola, soy el proceso %d.\n",i);

    barrier_wait(barrera);


    printf("hola de nuevo, soy el proceso %d.\n" ,i);
    //barrier_wait(barrera2);
  //}
}




int main(int argc, char const *argv[])
{
  barrera = malloc(sizeof(barrier_t));

  barrier_init(barrera, N_FILOSOFOS);

  barrera2 = malloc(sizeof(barrier_t));

  barrier_init(barrera2, N_FILOSOFOS);


  int i;
  pthread_t filo[N_FILOSOFOS];

  for (i=0;i<N_FILOSOFOS;i++)
    pthread_create(&filo[i], NULL, funcion, (void *)i);
  for (int i = 0; i < N_FILOSOFOS; ++i)
    pthread_join(filo[i], NULL);

  barrier_destroy(barrera);
  barrier_destroy(barrera2);
  return 0;

}

/*
  pregunta: descomentando lo que esta en la funcion funcion(),
  se podria hacer algo para que se siga ejecutando todo en
  el mismo orden. es decir que se siga repetando la barrera,
  no solo en el princiṕio sino en en el final tambien.
  tipo
  region1
  esperen todos los hilos
  region2
  esperem todos los hilos
  y asi se siga repitiendo el bucle
*/



/*
Concurrencia - Variables Condicionales


Esta entrada es una continuación de la entrada de mutex y de
la entrada acerca de la creación de hilos. En esta entrada
hablaré acerca de las variables condicionales. Estas deben usarse
conjuntamente a los mutex. Pronto veremos de qué forma nos pueden
 ser útiles las variables condicionales.

Para comenzar con ellas veremos qué es una variable condicional:
“Son variables de sincronización asociadas a un mutex”.  Estas
variables nos ayudaran a sincronizar nuestros bloqueos entre
hilos. Por ejemplo realizamos un bloqueo pero tenemos que esperar
a que otro recurso realice una acción, con estas variables
podemos esperar esta acción. Estas variables pueden realizar
 principalmente dos acciones: wait y signal. Las operaciones
 conviene realizarlas entre lock y unlock de un mutex.
 Los métodos que podemos usar con estas variables son:

 int pthread_cond_init(pthread_cond_t*cond,
  pthread_condattr_t*attr);
    Inicializa la variable condicional.
 int pthread cond destroy(pthread_cond_t *cond);
    Destruye la variable condicional.
 int pthread_cond_wait(pthread_cond_t*cond, pthread_mutex_t*mutex);
    Mediante este método suspendemos el hilo en el que se ejecuta y liberamos el mutex. El proceso queda suspendido hasta que recibe una señal de activación. Una vez que se activa se vuelve a luchar por el control del mutex.
int pthread_cond_signal(pthread_cond_t *cond);
    Se reanuda la ejecución de uno o más hilos que estén
    esperando por la variable condicional (cond).
    En caso de no haber ningún proceso esperando no ocurre nada.
int pthread_cond_broadcast(pthread_cond_t *cond);
    Se reanudan todos los hilos que estaban suspendidos por
    la variable condicional (cond).
*/
