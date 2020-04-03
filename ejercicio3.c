/*
  Implementar variables de exclusión mutua con Semáforos.
  Es decir, usar un semáforo para implementar la funcionalidad de
  un mutex.

  Funciones POSIX para Sincronización
   Estas funciones incluyen mecanismos de exclusión mutua (mutex),
   mecanismos de señalización del cumplimiento de condiciones por
   parte de variables, y mecanismos de acceso de variables que se
   modifican en forma exclusiva, pero pueden ser leidas en forma
   compartida. Las funciones para el manejo de zonas de acceso
   exclusivo tienen el prefijo pthread_mutex
   Un mutex es una variable especial que puede tener estado tomado
   (locked) o libre (unlocked). Es como una compuerta que permite el
   acceso controlado. Si un hilo tiene el mutex entonces se dice que
   es el dueño del mutex. Si ningún lilo lo tiene se dice que está
   libre (o unclucked). Cada mutex tiene una cola de hilos que están
   esperando para tomar el mutex. El uso de mutex es eficiente, pero
   debería ser usado sólo cuando su acceso es solicitado por corto
   tiempo.

*/
//Función POSIX
/*
  pthread_mutex_init
  permite dar las condiciones iniciales a un candado mutex

*/

int pthread_mutex_init(sem_t *sem) {
  return sem_init(sem,0,1);
}
/*
  pthread_mutex_lock
  Permite solicitar acceso al mutex, el hilo se bloquea hasata su
  obtención

*/
int pthread_mutex_lock(sem_t *sem) {
  return sem_wait(sem);


}
/*
  pthread_mutex_unlock
  Permute liberar un mutex.

*/
int pthread_mutex_unlock(sem_t *sem) {
  return sem_post(sem);

}
