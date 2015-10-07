#ifndef _POOL_THREAD_
#define _POOL_THREAD_

#include "Thread.h"

#define THREADCOUNT_MAX 16

namespace asyncply
{

class multithread_API pool_thread : public thread
{
public:
	pool_thread(uint32_t numThreads = 4);
	virtual ~pool_thread(void);

	pool_thread(const pool_thread& other) = delete;
    pool_thread& operator=(const pool_thread& other) = delete;

	void Stop();

	circular_queue<job>* get_queue() const { return _queue; }

	void submit(job* j);

	synchronizer* get_synchronizer_workers_finished() const { return _workers_finished; }

	unsigned int get_number_threads() const { return _number_threads; }

protected:
	void Start();

	virtual void execute();

protected:
	friend class worker;

	uint32_t _number_threads;
	bool _started;
	worker* _workers[THREADCOUNT_MAX];
	circular_queue<job>* _queue;
#ifdef _WIN32
	DWORD _threads_id[THREADCOUNT_MAX];
	HANDLE _threads[THREADCOUNT_MAX];
#else
	pthread_t _threads[THREADCOUNT_MAX];
#endif

	synchronizer* _any_job;
	synchronizer* _workers_finished;

public:
#ifdef _WIN32
	static DWORD HandleGlobalMyPoolThread(LPVOID parms);
#else
	static void* HandleGlobalMyPoolThread(void* parms);
#endif
};
}

#endif  // _POOL_THREAD_
