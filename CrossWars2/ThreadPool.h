#pragma once
#include <vector>
#include <thread>
#include <condition_variable>
#include <queue>
#include <future>

typedef std::function<void()> Task;

class ThreadPool
{
public:
	ThreadPool(size_t t_num_threads);
	~ThreadPool();
	void addTask(std::function<void()> t_task);

	template<class T>
	auto addTask(T t_task) -> std::future<decltype(t_task())>
	{
		auto wrapper = std::make_shared<std::packaged_task<decltype(t_task())()>>(std::move(t_task));

		{
			std::unique_lock<std::mutex> lock(m_event_mutex);
			m_task_pool.emplace([=]
			{
				(*wrapper)();
			});
		}

		m_event.notify_one();
		return wrapper->get_future();
	}
private:
	std::queue<Task> m_task_pool;

	std::vector<std::thread> m_thread_pool;

	std::condition_variable m_event;

	std::mutex m_event_mutex;
	bool m_stop;

	void start(size_t t_num_threads);
	void stop() noexcept;
};

