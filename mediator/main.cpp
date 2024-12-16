/**
 * @file main.cpp
 * @author
 * @brief 中介者模式
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
 */

#include <iostream>
#include <memory>
#include <string>

/**
 * 中介者模式的用途：
 * 中介者模式(Mediator
 * Pattern)是一种行为型设计模式, 用于减少对象之间的直接依赖, 通过引入一个中介者对象, 
 * 让各个对象通过中介者进行交互, 而不是直接相互调用. 这种模式通过将对象之间的交互逻辑封装在中介者中, 
 * 实现了对象之间的松耦合, 并简化了系统的复杂性. 
 *
 * 用途：
 * 1. 消除对象之间复杂的网状依赖关系. 
 * 2. 统一交互逻辑, 便于维护和扩展. 
 * 3. 在需要协调多个对象的交互时, 使用中介者模式可简化设计. 
 *
 * 关键角色：
 * - **Mediator(中介者接口)**：
 *   定义了与同事类交互的方法, 通常提供 `send` 等接口, 用于传递消息或协调动作. 
 * - **ConcreteMediator(具体中介者)**：
 *   实现中介者接口, 维护对同事类的引用, 负责具体的交互协调逻辑. 
 * - **Colleague(抽象同事类)**：
 *   定义同事类的通用接口, 持有对中介者的引用, 通过中介者进行通信. 
 * - **ConcreteColleague(具体同事类)**：
 *   继承抽象同事类, 实现具体的功能逻辑, 通过中介者与其他同事类交互. 
 *
 * 示例中的实现：
 * 1. `Mediator`：
 *    - 抽象类, 定义了 `send` 方法, 用于发送消息. 
 * 2. `ConcreteMediator`：
 *    - 具体中介者, 持有 `ColleagueA` 和 `ColleagueB` 的引用. 
 *    - 实现了消息的路由逻辑, 将消息从一个同事类传递给另一个同事类. 
 * 3. `Colleague`：
 *    - 抽象类, 定义了 `send_msg` 和 `notify_msg` 接口. 
 *    - 持有对中介者的引用, 通过中介者进行消息传递. 
 * 4. `ColleagueA` 和 `ColleagueB`：
 *    - 具体同事类, 分别实现了发送和接收消息的逻辑. 
 * 5. 主函数：
 *    - 创建具体中介者和同事类对象, 设置同事类与中介者的关联关系. 
 *    - 同事类通过中介者发送消息, 演示中介者协调同事类之间的通信. 
 *
 * 优势：
 * 1. 减少对象之间的耦合：各个对象之间不再直接依赖, 通过中介者解耦. 
 * 2. 统一交互逻辑：交互逻辑集中在中介者中, 便于修改和扩展. 
 * 3. 提高系统灵活性：可以轻松增加新对象, 而无需修改现有类. 
 *
 * 缺点：
 * 1. 中介者可能过于复杂：当交互逻辑过多时, 中介者容易成为“上帝类”. 
 * 2. 降低性能：对象之间的直接交互被中介者替代, 可能增加一定的性能开销. 
 *
 * 适用场景：
 * - 多个对象之间存在复杂的网状交互, 且交互逻辑容易变化. 
 * - 系统需要动态增加或修改对象的交互逻辑. 
 * - 需要集中管理对象之间的交互, 减少对象之间的直接依赖. 
 */

// 同事类
class Colleague;

// 抽象中介类
class Mediator {
public:
    virtual ~Mediator() = default;
    virtual void send(const std::string& message, Colleague* colleague) = 0;
};

// 同事类
class Colleague {
protected:
    std::shared_ptr<Mediator> mediator_;

public:
    Colleague(std::shared_ptr<Mediator> mediator) : mediator_(mediator) {
    }
    virtual ~Colleague() = default;
    virtual void send_msg(const std::string& message) = 0;
    virtual void notify_msg(const std::string& message) = 0;
};

// 同事类A
class ColleagueA : public Colleague {
public:
    ColleagueA(std::shared_ptr<Mediator> mediator) : Colleague(mediator) {
    }

    void send_msg(const std::string& message) override {
        mediator_->send(message, this);
    }

    void notify_msg(const std::string& message) override {
        std::cout << "ColleagueA received message: " << message << std::endl;
    }
};

// 同事类B
class ColleagueB : public Colleague {
public:
    ColleagueB(std::shared_ptr<Mediator> mediator) : Colleague(mediator) {
    }

    void send_msg(const std::string& message) override {
        mediator_->send(message, this);
    }

    void notify_msg(const std::string& message) override {
        std::cout << "ColleagueB received message: " << message << std::endl;
    }
};

// 具体中介类
class ConcreteMediator : public Mediator {
private:
    std::shared_ptr<ColleagueA> colleagueA_;
    std::shared_ptr<ColleagueB> colleagueB_;

public:
    void set_colleagueA(std::shared_ptr<ColleagueA> colleagueA) {
        colleagueA_ = colleagueA;
    }

    void set_colleagueB(std::shared_ptr<ColleagueB> colleagueB) {
        colleagueB_ = colleagueB;
    }

    void send(const std::string& message, Colleague* colleague) override {
        if (colleague == colleagueA_.get()) {
            colleagueB_->notify_msg(message);
        } else if (colleague == colleagueB_.get()) {
            colleagueA_->notify_msg(message);
        }
    }
};

int main(int argc, char* argv[]) {

    std::shared_ptr<ConcreteMediator> mediator =
        std::make_shared<ConcreteMediator>();

    std::shared_ptr<ColleagueA> colleagueA =
        std::make_shared<ColleagueA>(mediator);
    std::shared_ptr<ColleagueB> colleagueB =
        std::make_shared<ColleagueB>(mediator);

    mediator->set_colleagueA(colleagueA);
    mediator->set_colleagueB(colleagueB);

    colleagueA->send_msg("Hello, I am ColleagueA");
    colleagueB->send_msg("Hello, I am ColleagueB");

    return 0;
}
