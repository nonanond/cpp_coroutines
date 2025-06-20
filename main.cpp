#include <iostream>
import Coro;

auto main (int argc, char** argv) -> int {
	std::cout << "hello world" << std::endl;
	auto test = test_coro_t {};
	test.run ();
	return 0;
}