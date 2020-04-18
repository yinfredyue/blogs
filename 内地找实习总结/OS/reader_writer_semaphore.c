typedef struct __rwlock_t {
typedef struct __rwlock_t {
	sem_t lock;
	sem_t writelock;
	int readers;
} rwlock_t;

void rwlock_init(rwlock_t *l) {
	sem_init(&(l->lock), 1);
	sem_init(&(l->writelock), 1);
	l->readers = 0;
}

void rwlock_acquire_readlock(rwlock_t *l) {
	sem_wait(&(l->lock));
	++(l->readers);
	if (l->readers == 1) {
		sem_wait(&(l->writelock));
	}
	sem_post(&(l->lock));
}

void rwlock_release_readlock(rwlock_t *l) {
	sem_wait(&(l->lock));
	--(l->readers);
	if (l->readers == 0) {
		sem_post(&(l->writelock));
	}
	sem_post(&(l->lock));
}

void rwlock_acquire_writelock(rwlock_t *l) {
	sem_wait(&(l->writelock));
}

void rwlock_release_writelock(rwlock_t *l) {
	sem_post(&(l->writelock));
}