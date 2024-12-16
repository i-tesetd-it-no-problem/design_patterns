/**
 * @file main.cpp
 * @author wenshuyu (wsy2161826815@163.com)
 * @brief 状态模式
 * @version 1.0
 * @date 2024-12-13
 *
 * @copyright Copyright (c) 2024
 *
 * Permission is hereby granted, free of charge, to any person obtaining a copy
 * of this software and associated documentation files (the "Software"), to deal
 * in the Software without restriction, including without limitation the rights
 * to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
 * copies of the Software, and to permit persons to whom the Software is
 * furnished to do so, subject to the following conditions:
 *
 * The above copyright notice and this permission notice shall be included in
 * all copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 * AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 * LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 * OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
 * SOFTWARE.
 *
 */

#include <iostream>
#include <memory>

// 向前声明
class Context;
class StateA;
class StateB;

class State {
public:
    virtual ~State() = default;
    virtual void handle(class Context* context) = 0;
};

class Context {
private:
    std::shared_ptr<State> _state;

public:
    Context(std::shared_ptr<State> state) : _state(state) {
    }

    std::shared_ptr<State> get_state() const {
        return _state;
    }

    void set_state(std::shared_ptr<State> state) {
        _state = state;
    }

    void request() {
        _state->handle(this);
    }
};

class StateA : public State {

public:
    void handle(Context* context) override {
        std::cout << "StateA handle" << std::endl;
        context->set_state(
            std::static_pointer_cast<State>(std::make_shared<StateB>()));
    }
};

class StateB : public State {

public:
    void handle(Context* context) override {
        std::cout << "StateB handle" << std::endl;
        context->set_state(
            std::static_pointer_cast<State>(std::make_shared<StateA>()));
    }
};

// 客户端代码
int main(int argc, char* argv[]) {

    auto context = std::make_shared<Context>(std::make_shared<StateA>());

    context->request();
    context->request();
    context->request();

    return 0;
}
