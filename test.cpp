#include <iostream>
#include <thread>

class Thread {
    private:
        int x_ = 0;
    public:
        Thread(int x) { x_ = x;}

        void operator()() {
            std::cout << "Thread object created" << std::endl;
        }
        void print(int p) {
            std::cout << "Member function printing: " << x_ + p << std::endl;
        }
};

int main()
{

    Thread T1(1);
    Thread T2(2);
    //By value
    std::thread t1{&Thread::print, T1, 1};
    //By reference
    std::thread t2{&Thread::print, &T2, 1};

    std::cout << "Finished work in main thread with id = " << std::this_thread::get_id() << std::endl;

    std::shared_ptr<Thread> T3(new Thread(1));
    std::thread t3{&Thread::print, T3, 1};

    t1.join();
    t2.join();
    t3.join();
    return 0;
}