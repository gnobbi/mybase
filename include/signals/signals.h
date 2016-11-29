#ifndef MY_BASE_SIGNALS_SIGNALS_H 
#define MY_BASE_SIGNALS_SIGNALS_H

#include <vector>
#include <functional>


namespace mybase {

template<class R, class... Args>
struct Signal {
	std::vector<std::function<R(Args...)>> vec;
	int Subscribe(std::function<R(Args...)>(f)) {
		vec.push_back(f);
		return vec.size() - 1;
	}

	void Release(int index) {
		vec[index] = nullptr;
	}

	void Emit(Args... args) {
		for (const auto& fun : vec)
			if (fun != nullptr)
				fun(args...);
	}
};
} //mybase
#endif //MY_BASE_SIGNALS_SIGNALS_H 