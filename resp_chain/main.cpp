/**
 * @file main.cpp
 * @author wenshuyu (wsy2161826815@163.com)
 * @brief 责任链模式
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
#include <vector>

/**
 * 责任链模式的用途：
 * 责任链模式(Chain of Responsibility Pattern)是一种行为型设计模式, 
 * 它允许多个对象以链式方式处理请求, 每个对象可以选择处理请求或者将其传递给下一个对象. 
 * 这种模式通过解耦请求发送者和处理者, 使得请求处理更加灵活. 
 *
 * 用途：
 * 1. 需要将多个处理者串联起来处理请求时(如事件处理、审批流程等). 
 * 2. 请求的处理逻辑动态变化时, 可以通过修改链条结构来调整处理逻辑. 
 * 3. 避免发送者直接与多个处理者耦合. 
 *
 * 关键角色：
 * - **Handler(处理者)**：
 *   定义了处理请求的接口, 并保存对下一个处理者的引用. 
 * - **ConcreteHandler(具体处理者)**：
 *   实现了处理请求的具体逻辑, 如果无法处理请求, 则将其传递给下一个处理者. 
 * - **Client(客户端)**：
 *   创建请求并将其提交给责任链的第一个处理者. 
 *
 * 示例中的实现：
 * 1. `Handler`：
 *    - 抽象处理者, 定义了 `set_successor` 和 `handle_request` 方法. 
 * 2. `HandlerA`、`HandlerB`、`HandlerC`：
 *    - 分别实现了具体处理逻辑, 并在无法处理时, 将请求传递给下一个处理者. 
 * 3. `HandlerDefault`：
 *    - 默认处理者, 处理责任链未能处理的请求. 
 * 4. 主函数：
 *    - 创建处理者并设置责任链. 
 *    - 处理多个请求, 展示责任链的动态传递过程. 
 *
 * 优势：
 * 1. 解耦请求发送者和处理者：请求发送者无需知道具体的处理逻辑. 
 * 2. 灵活调整责任链：可以动态改变处理者的链条顺序或数量. 
 * 3. 增强可扩展性：添加新的处理者不会影响现有代码. 
 *
 * 缺点：
 * 1. 请求处理效率可能较低：请求需要沿链条逐步传递. 
 * 2. 调试难度增加：链条较长时, 可能难以定位问题. 
 *
 * 适用场景：
 * - 多个对象可能处理同一请求, 具体由哪个对象处理在运行时确定. 
 * - 需要动态指定请求处理者或调整请求处理顺序. 
 * - 需要对请求的处理进行灵活的扩展和修改. 
 */


// 抽象处理者
class Handler {
protected:
    std::shared_ptr<Handler> successor; // 下一个处理者

public:
    virtual ~Handler() = default;

    // 设置下一个处理者
    void set_successor(std::shared_ptr<Handler> successor) {
        this->successor = successor;
    }

    // 处理请求的接口
    virtual void handle_request(int request) {
        if (successor) {
            successor->handle_request(request);
        } else {
            std::cout << "Request " << request
                      << " was not handled by any handler." << std::endl;
        }
    }
};

// 具体处理者 A
class HandlerA : public Handler {
public:
    void handle_request(int request) override {
        if (request >= 0 && request <= 10) {
            std::cout << "HandlerA handled request: " << request << std::endl;
        } else {
            std::cout << "HandlerA passing request: " << request
                      << " to next handler." << std::endl;
            Handler::handle_request(request);
        }
    }
};

// 具体处理者 B
class HandlerB : public Handler {
public:
    void handle_request(int request) override {
        if (request >= 11 && request <= 20) {
            std::cout << "HandlerB handled request: " << request << std::endl;
        } else {
            std::cout << "HandlerB passing request: " << request
                      << " to next handler." << std::endl;
            Handler::handle_request(request);
        }
    }
};

// 具体处理者 C
class HandlerC : public Handler {
public:
    void handle_request(int request) override {
        if (request >= 21 && request <= 30) {
            std::cout << "HandlerC handled request: " << request << std::endl;
        } else {
            std::cout << "HandlerC passing request: " << request
                      << " to next handler." << std::endl;
            Handler::handle_request(request);
        }
    }
};

// 默认处理者(处理未被其他处理者处理的请求)
class HandlerDefault : public Handler {
public:
    void handle_request(int request) override {
        std::cout << "HandlerDefault handled request: " << request << std::endl;
    }
};

int main() {
    // 创建处理者
    std::shared_ptr<Handler> handlerA = std::make_shared<HandlerA>();
    std::shared_ptr<Handler> handlerB = std::make_shared<HandlerB>();
    std::shared_ptr<Handler> handlerC = std::make_shared<HandlerC>();
    std::shared_ptr<Handler> handlerDefault =
        std::make_shared<HandlerDefault>();

    // 设置责任链
    handlerA->set_successor(handlerB);
    handlerB->set_successor(handlerC);
    handlerC->set_successor(handlerDefault);

    // 请求列表
    std::vector<int> requests = { 1, 5, 15, 25, 35, 45 };

    // 处理请求
    for (int request: requests) {
        std::cout << "\nProcessing request: " << request << std::endl;
        handlerA->handle_request(request);
    }

    return 0;
}
