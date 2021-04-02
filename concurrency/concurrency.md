# Intro to C++ Concurrency

Let's start with the very basics before we work through a simple example in c++:

## Overview

When we want to perform multiple pieces of work simultaneously, we can either choose to run them in a synchronos or asynchronos manner:

**Synchronous**
```
                         time
main()      ---------        -------------------------> 
          func()    |        | return()
thread()            ------->
```

**Asynchronous**
```
                         time
main()      ------------------------------------------> 
          func()    |        
thread()            ------->
```

As you can see in the diagrams above, synchronous programs pause execution of the program that started them until completition while asynchronous programs run along side the calling thread.

Two very important concepts we need to define first are:

- **process**: Also called task = running computer program, controlled by the os
- **thread**: Also called "light-weight processes". Are concurrent execution units within a process

The os can set a process into one of several states:

- **Ready**: After creation the process is loaded into main memory and waiting in the CPU queue managed by the os to be executed
- **Running**: Os has given the process CPU time to run
- **Blocked**: Process is waiting for an event (e.g. i/o, resources)
- **Terminated**: Process completes or is killed
- **Ready suspended**: Process was moved out of main memory, but is ready as soon as it is moved to main memory again
- **Blocked suspended**: Process was moved out of main memory, but is blocked as soon as it is moved to main memory again

The os manages processes with a **scheduler** that can assign cpu time to different processes.

Managing processes is quite a lot of work for the os and a more light-weight and resource friendly way is to utilize threads:

As already stated, threads are concurrent execution units within a process. They are easier to create and destroy (like up to 100x).

Threads can share resources with processes such as files, network connections and memory while processes are isolated from each other. Quite similar to processes, threads also have states:

- **New**: When it is created a thread is in the new state - This state does not take cpu resources
- **Runnable**: Now the thread can be run if it is scheduled
- **Blocked**: Again, the threat does not consume cpu time and is waiting to resume execution

## C++ Implementation

Concurrency support was first included in the standard library in c++11. Before that you had to rely on third-party implementations or the native concurrency options provided by each os.

Simply include the `<thread>` header file and you are ready to go :)

Each running program has a "main thread" and potentially other threads as well. Each thread has a unique id:

```
#include <iostream>
#include <thread>

int main()
{
    unsigned int nCores = std::thread::hardware_concurrency();
    std::cout << "# Cores = " << nCores << std::endl;
    std::cout << "Thread id = " << std::this_thread::get_id() << std::endl;

    return 0;
}
```
On my machine I get:
```
# Cores = 12
Thread id = 9788
```

Now let's create a second thread:
```
#include <iostream>
#include <thread>

void foo()
{
    std::this_thread::sleep_for(std::chrono::milliseconds(100)); // simulate work
    std::cout << "Finished work in thread with id = " << std::this_thread::get_id() << std::endl; 
}

int main()
{
    // create thread
    std::thread t(foo);

    std::this_thread::sleep_for(std::chrono::milliseconds(50));
    std::cout << "Finished work in main thread with id = " << std::this_thread::get_id() << std::endl;

    // Threads are non-blocking!
    // Use join() to block execution of the parent until the child thread finishes
    t.join();

    return 0;
}
```
We get:
```
Finished work in main thread with id = 8560
Finished work in thread with id = 18548
```

> Note: If you use g++ do not forget to add the flag -pthread! The MSVC compiler works without a flag.

