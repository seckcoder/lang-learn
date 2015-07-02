


class SpinLock {
  public:
    void lock();
    void unlock();
};

class ThreadQueue {
  public:
    // atomic sleep.
    // unlock the spin lock and sleep the current thread into queue atomically
    void sleep(SpinLock *spin) {
    }
    void wakeup_front() {
    }
};

class Mutex {
  public:
    bool flag;
    ThreadQueue tque;
    SpinLock spin;
    void acquire() {
      while (true) {
        spin.lock();
        if (flag) {
          tque.sleep(&spin);
        } else {
          flag = true;
          spin.unlock();
        }
      }
    }
    void release() {
      spin.lock();
      flag = false;
      tque.wakeup_front();
      spin.unlock();
    }
};
