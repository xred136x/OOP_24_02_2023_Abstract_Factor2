#include<iostream>
#include<memory>
#include<string>
#include<thread>
#include<mutex>

//ÏÎÒÎÊÈ, ìüşòåêñû
class Logger {
public:
	void log(const std::string& massage) {
		std::lock_guard<std::mutex> lock(_mutex);
		std::cout << "[" << _massageCounter << "]" << massage << '\n';
		_massageCounter++;
	}
private:
	std::mutex _mutex;
	int _massageCounter=0;
};

int main() {
	Logger logger;
	logger.log("hello");
	logger.log("info massage");

	std::thread t1 = std::thread([&logger]() {
		std::string threadName = "t1";
		for (size_t i = 0; i < 100; i++) {
			logger.log(threadName + " going " + std::to_string(i) + " iteration of work\n");
		}
	});
	  
	std::thread t2 = std::thread([&logger]() {
		std::string threadName = "t2";
		for (size_t i = 0; i < 100; i++) {
			logger.log(threadName + " going " + std::to_string(i) + " iteration of work\n");
		}
		});
	t1.join();
	t2.join();
	return 0;
}