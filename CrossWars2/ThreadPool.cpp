#include "ThreadPool.h"

ThreadPool::ThreadPool(size_t t_num_threads)
{
	m_stop = false;
	start(t_num_threads);
}

ThreadPool::~ThreadPool()
{
	stop();
}

void ThreadPool::start(size_t t_num_threads)
{
	for(size_t i = 0; i < t_num_threads; ++i)
	{
		m_thread_pool.emplace_back([=]
		{
			for(;;)
			{
				Task task;

				{
					std::unique_lock<std::mutex> lock(m_event_mutex);

					m_event.wait(lock, [=] { return m_stop || !m_task_pool.empty(); });

					if (m_stop && m_task_pool.empty()) break;

					task = std::move(m_task_pool.front());
					m_task_pool.pop();
				}

				task();
			}
		});
	}
}

void ThreadPool::stop() noexcept
{
	{
		std::unique_lock<std::mutex> lock(m_event_mutex);
		m_stop = true;
	}

	m_event.notify_all();
}
