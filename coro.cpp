module;
#include <iostream>
#include <coroutine>
export module Coro;

using std::cout, std::endl;

struct suspend_always_t {
	auto await_ready () noexcept {
		// cout << __PRETTY_FUNCTION__ << endl;
		return false;
	}
	auto await_suspend (auto awaiting_coroutine) noexcept {
		// cout << __PRETTY_FUNCTION__ << endl;
	}
	auto await_resume () noexcept {
		// cout << __PRETTY_FUNCTION__ << endl;
	}
};

struct coro_t {
	struct promise_type {
		auto get_return_object () noexcept {
			return coro_t{std::coroutine_handle<promise_type>::from_promise(*this)};
		}
		auto initial_suspend () noexcept {
			return suspend_always_t {};
		}
		auto final_suspend () noexcept {
			return suspend_always_t {};
		}
		auto unhandled_exception () {
			std::terminate ();
		}
	};

	explicit coro_t(std::coroutine_handle<promise_type> h) : handle(h) {}
    
    ~coro_t() { 
        if (handle) handle.destroy(); 
    }
    
    // Resume the coroutine
    void resume() {
        if (handle && !handle.done()) {
            handle.resume();
        }
    }
    
    // Check if coroutine is done
    bool done() const {
        return handle.done();
    }

	std::coroutine_handle <promise_type> handle;
};


struct some_work {
	int i = 0;
	auto await_ready () noexcept {
		cout << __PRETTY_FUNCTION__ << endl;
		return false;
		return i < 10;
	}
	auto await_suspend (auto awaiting_coroutine) noexcept {
		cout << __PRETTY_FUNCTION__ << endl;
	}
	auto await_resume () noexcept {
		cout << __PRETTY_FUNCTION__ << endl;
	}
};



auto coro () -> coro_t {
	for (auto i = 0;; ++i) {
		cout << i << endl;
		co_await some_work ();
		cout << i << endl;
	}
}

export struct test_coro_t {
	auto run () {
		auto c = coro ();
		cout << "resuming" << endl;
		c.resume ();
		c.resume ();
	}
};