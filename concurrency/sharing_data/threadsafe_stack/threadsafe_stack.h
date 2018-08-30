/*
 *  Author  :   Gu-hwan Bae
 *  Date    :   30 August, 2018
 *  Summary :   thread-safe stack(wrapper of std::stack)

    Concurrency in action 1st edition,
    (3.2.3) Spotting race conditions inherent in interfaces.
 */

#include <exception>
#include <memory>
#include <mutex>
#include <stack>

struct empty_stack : std::exception
{
    const char* what() const noexcept {
        return "stack is empty.";
    }
};

template <typename T>
class threadsafe_stack
{
public :
    threadsafe_stack() {};
    explicit threadsafe_stack(const threadsafe_stack&);

    threadsafe_stack& operator=(const threadsafe_stack&) = delete;

    void push(T&& new_value);
    std::shared_ptr<T> pop();
    void pop(T& value);
    bool empty() const;
private :
    std::stack<T> data;
    mutable std::mutex m;

    using lock = std::lock_guard<std::mutex>;
};

template <typename T>
threadsafe_stack<T>::threadsafe_stack(const threadsafe_stack& other)
{
    lock g{m};
    data = other.data;
}

template <typename T>
void threadsafe_stack<T>::push(T&& new_value)
{
    lock g{m};
    data.push(std::forward<T>(new_value));
}

// threadsafe_stack::pop() is ensure that avoid race condition
// by conbining std::stack top() and pop() interface.
// And threadsafe_stack overloads pop interface that return a shared pointer
// or assign to reference passing by parameter.
template <typename T>
std::shared_ptr<T> threadsafe_stack<T>::pop()
{
    lock g{m};
    if(data.empty())    // Check for empty before trying to pop value.
    {
        throw empty_stack();
    }
    // Allocate return value before modifying stack.
    auto res = std::make_shared<T>(data.top());
    return res;
}

template <typename T>
void threadsafe_stack<T>::pop(T& value)
{
    lock g{m};
    if(data.empty())
    {
        throw empty_stack();
    }
    value = data.top();
    data.pop();
}

template <typename T>
bool threadsafe_stack<T>::empty() const
{
    lock g{m};
    return data.empty();
}
