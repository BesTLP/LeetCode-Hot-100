//#include <vector>
//
//class MinStack
//{
//public:
//    MinStack()
//    {
//        it = stack.begin();
//    }
//
//    void push(int val)
//    {
//        it = stack.emplace(it, val);
//        if (minStack.empty() || val <= minStack.back())
//        {
//            minStack.push_back(val);
//        }
//    }
//
//    void pop()
//    {
//        if (*it == minStack.back()) minStack.pop_back();
//        it = stack.erase(it);
//    }
//
//    int top()
//    {
//        return *it;
//    }
//
//    int getMin()
//    {
//        return minStack.back();
//    }
//private:
//    std::vector<int> stack;
//    std::vector<int> minStack;
//    std::vector<int>::iterator it;
//};

#include <vector>

class MinStack
{
public:
    MinStack()
    {
    }

    void push(int val)
    {
        stack.push_back(val);
        if (minStack.empty() || val <= minStack.back())
        {
            minStack.push_back(val);
        }
    }

    void pop()
    {
        if (stack.back() == minStack.back()) minStack.pop_back();
        stack.pop_back();
    }

    int top()
    {
        return stack.back();
    }

    int getMin()
    {
        return minStack.back();
    }
private:
    std::vector<int> stack;
    std::vector<int> minStack;
};