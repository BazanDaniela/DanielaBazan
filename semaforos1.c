/*
semaphore cuenta con tres elementos:
  ** Un entero que representa el estado del semáforo,
  ** Una variable mutex(control_valor) que controla el acceso al contador. Un
mutex, control_valor es un mutex que se usa para controlar el acceso y
modificación de la variable valor.
  ** Un mutex control_procesos para bloquear y desbloquear procesos.
*/
#include <pthread.h>

struct semaphore_t {
  int valor;
  pthread_mutex_t control_valor;
  pthread_mutex_t control_procesos;
}

typedef struct semapfore_t sem_t;

/* Función de creación de Semáforo */
int sem_init(sem_t *sem, int init){
  int a;
  sem->valor = valor;
  pthread_mutex_t control;
  pthread_mutex_t procesos;
  a = pthread_mutex_init(&control, NULL);
  a += pthread_mutex_init(&procesos, NULL);
  sem->control_valor = control;
  sem->control_procesos = procesos;
  if (a = 0 )
    return 1;
  else
    return 0
}

/* Incremento del semáforo. */
int sem_incr(sem_t *sem){
  int a;
  a = pthread_mutex_lock (sem->control_valor);
  sem->valor++;
  a += pthread_mutex_unlock (sem->control_valor);
  if (sem->valor <= 0){
    a += pthread_mutex_unlock (sem->control_procesos);
  }
  if (a = 0 )
    return 1;
  else
    return 0
}

/* Decremento del semáforo. Notar que es una función que puede llegar a bloquear
   el proceso.*/
int sem_decr(sem_t *sem) {
  int a;
  a = pthread_mutex_lock (sem->control_valor)
  sem->valor -= 1;
  a += pthread_mutex_unlock (sem->control_valor)
  if (sem->valor < 0) {
    a += pthread_mutex_lock (sem->control_procesos)
  }
  if (a = 0 )
    return 1;
  else
    return 0
}

/* Destrucción de un semáforo */
int sem_destroy(sem_t* sem){
  int a;
  a = pthread_mutex_destroy(&(sem.control_valor));
  a += pthread_mutex_destroy(&(sem.control_procesos));
  free(sem)
  if (a = 0 )
    return 1;
  else
    return 0
}
