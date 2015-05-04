#include <algorithm>


struct Node {
    int v;
    int min_v;
    Node() {}
    Node(int hv, int h_min_v) :v(hv), min_v(h_min_v) {}
};

#define M 20000

template <class T>
class Stack {
    public:
        T data[M];
        int num_elems;
        Stack() {
            num_elems = 0;
        }
        void push(T x) {
            data[num_elems] = x;
            num_elems += 1;
        }
        void pop() {
            num_elems -= 1;
        }
        T top() const {
            return data[num_elems-1];
        }
        bool empty() const {
            return num_elems == 0;
        }
};
class MinStack {
public:
    // vector<Node> nodes;
    Stack<Node> nodes;
    void push(int x) {
        if (nodes.empty()) {
            nodes.push(Node(x, x));
        } else {
            nodes.push(Node(x, std::min(x, nodes.top().min_v)));
        }
    }

    void pop() {
        nodes.pop();
    }

    int top() {
        return nodes.top().v;
    }

    int getMin() {
        return nodes.top().min_v;
    }
};

int main() {
  MinStack min_stack;
  return 0;
}
