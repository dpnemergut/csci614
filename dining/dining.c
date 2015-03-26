#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <sys/time.h>
#include <sys/resource.h>

// Chopsticks
int locks[5] = {0};

/**
 * Routine that each thread will run in parallel.
 * Each thread will represent a philosopher dining.
 *
 * @param void* Arguments passed to the routine.
 */
void* routine(void* args) {
  int threadID = (int)args;
  int secondChopstick = (threadID + 1) % 5;
  struct timespec timeThink, timeDelay, timeEat;

  timeThink.tv_sec = 0;
  timeDelay.tv_sec = 0;
  timeEat.tv_sec = 0;

  while(1) {
    // Tweak these numbers to get different outcomes
    timeThink.tv_nsec = (rand() % 10) * 100000000L;
    timeDelay.tv_nsec = (rand() % 10) * 100000L;
    timeEat.tv_nsec = (rand() % 10) * 100000L;

    // Think
    printf("Phil %d thinking\n", threadID);
    nanosleep(&timeThink, NULL);
    // Lock chopstick 1
    if(locks[threadID] == -1) {
      printf("Phil %d picked up chopstick 1\n", threadID);
      locks[threadID] = threadID;

      // Delay
      nanosleep(&timeDelay, NULL);

      // Lock chopstick 2
      if(locks[secondChopstick] == -1) {
        printf("Phil %d picked up chopstick 2\n", threadID);
        locks[secondChopstick] = threadID;

        // Eat delay
        nanosleep(&timeEat, NULL);

        // Unlock chopstick 2
        printf("Phil %d put down chopstick 2\n", threadID);
        locks[secondChopstick] = -1;

        // Delay
        nanosleep(&timeDelay, NULL);

        // Unlock chopstick 1
        printf("Phil %d put down chopstick 1\n", threadID);
        locks[threadID] = -1;
      }
    }
  }
}

/**
 * Main function.
 * Creates the theads, runs them, and cleans up.
 *
 * @param int argc The number of arguments passed to the program.
 * @param char** argv The list of arguments passed to the program.
 *
 * @return int The exit status of the program.
 */
int main(int argc, char** argv) {
  int threadID;
  int numThreads = 5;
  struct timespec checkDelay;
  pthread_t* threads;

  checkDelay.tv_sec = 0;
  checkDelay.tv_nsec = 500000000L;

  // Allocate array of thread structs
  threads = malloc(numThreads * sizeof(pthread_t));

  // Initialize locks and threads
  for(threadID=0; threadID<numThreads; threadID++) {
    locks[threadID] = -1;
    if(pthread_create(&threads[threadID], NULL, routine, (void *)threadID) != 0) {
      fprintf(stderr, "Error creating thread\n");
      return 1;
    }
  }

  // Monitor the threads for deadlock
  while(1) {
    printf("%d, %d, %d, %d, %d\n", locks[0], locks[1], locks[2], locks[3], locks[4]);
    if((locks[0] == 0) && (locks[1] == 1) && (locks[2] == 2) && (locks[3] == 3) && (locks[4] == 4)) {
      printf("Deadlock reached!\n");
      for(threadID=0; threadID<numThreads; threadID++) {
        pthread_kill(&threads[threadID], 2);
      }
      break;
    }
    nanosleep(&checkDelay, NULL);
  }

  // Cleanup allocation
  free(threads);

  return 0;

}
