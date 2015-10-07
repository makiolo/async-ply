#ifndef _CIRCULAR_QUEUE_H_
#define _CIRCULAR_QUEUE_H_

#include "Mutex.h"
#include "Semaphore.h"

#define MAX_ELEMENTS 512

namespace asyncply
{

template <typename T>
class circular_queue
{
public:
	circular_queue()
		: _top_index(0)
		, _bottom_index(0)
		, _number_works(0)
		, _mutex()
	{
	}

	~circular_queue() {}

	circular_queue(const circular_queue& other) = delete;
	circular_queue& operator=(const circular_queue& other) = delete;

	void push(T* element)
	{
		mutex::scoped_lock_t lock(_mutex);

		assert(_number_works < MAX_ELEMENTS);  // "Demasiados elementos en la cola circular, aumente
											   // el valor de MAX_ELEMENTS");

		_queue[_top_index] = element;
		_top_index = (_top_index + 1) % (MAX_ELEMENTS - 1);

		++_number_works;
	}

	T* pop()
	{
		mutex::scoped_lock_t lock(_mutex);

		if (_number_works > 0)
		{
			T* element = _queue[_bottom_index];
			_bottom_index = (_bottom_index + 1) % (MAX_ELEMENTS - 1);

			--_number_works;

			assert(_number_works >= 0);  // "Number of elements can't be negative.");

			return element;
		}
		else
		{
			return NULL;
		}
	}

	inline int size() const { return _number_works; }

	mutex& get_mutex() const { return _mutex; }

private:
	T* _queue[MAX_ELEMENTS];
	int _top_index;
	int _bottom_index;
	int _number_works;
	mutable mutex _mutex;
};

}

#endif  // _CIRCULAR_QUEUE_H_
