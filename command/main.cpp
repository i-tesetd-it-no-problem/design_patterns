/**
 * @file main.cpp
 * @author wenshuyu (wsy2161826815@163.com)
 * @brief 命令模式
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
 * 命令模式的用途：
 * 命令模式(Command
 * Pattern)是一种行为型设计模式, 用于将请求封装为对象, 从而使得不同的请求可以被参数化、记录、撤销或重做. 
 * 该模式将请求发送者与实际执行者解耦, 使得请求发送者无需了解请求的具体执行逻辑. 
 *
 * 用途：
 * 1. 参数化对象的行为：可以将不同的命令动态绑定到调用者, 实现不同的行为. 
 * 2. 支持撤销/重做操作：通过存储命令对象, 可以轻松实现操作回滚. 
 * 3. 请求记录与调度：将命令排队、记录日志或进行多次调用. 
 *
 * 关键角色：
 * - **Command(命令接口)**：定义执行请求的接口, 包含一个 `execute` 方法. 
 * - **ConcreteCommand(具体命令)**：实现命令接口, 并调用接收者的具体功能. 
 * - **Reciever(接收者)**：实际执行请求的对象, 包含具体的业务逻辑. 
 * - **Invoker(调用者)**：存储和调用命令对象, 触发命令的执行. 
 *
 * 示例中的实现：
 * 1. `Reciever`：抽象类, 定义了 `action` 接口. 
 *    - 子类 `RecieverA`、`RecieverB`、`RecieverC` 分别实现了具体的 `action`. 
 * 2. `Command`：定义了命令的抽象接口, 包含 `execute` 方法. 
 * 3. `CommandA`：具体命令类, 绑定多个接收者, 并通过 `execute` 方法调用它们的
 * `action`. 
 * 4. `Invoke`：调用者类, 负责存储命令对象, 并在合适的时机调用命令. 
 * 5. 主函数：
 *    - 创建多个接收者, 并将它们绑定到命令. 
 *    - 调用者设置命令对象, 并触发命令执行, 完成对多个接收者的操作. 
 *
 * 优势：
 * 1. 请求与执行逻辑解耦：调用者不需要了解接收者的具体实现. 
 * 2. 灵活扩展：可以轻松添加新的命令和接收者, 不影响现有代码. 
 * 3. 支持撤销/重做：通过记录命令对象状态, 可以实现复杂的操作回滚. 
 *
 * 缺点：
 * 1. 类数量增加：每个命令和接收者都需要对应的类, 可能导致系统复杂性增加. 
 * 2. 请求过多时, 可能导致内存开销增加. 
 *
 * 适用场景：
 * - 需要解耦请求发送者与执行者的场景. 
 * - 需要支持撤销/重做的操作(如编辑器的撤销功能). 
 * - 需要对请求进行记录或排队处理. 
 */

// 接收者
class Reciever {
public:
    virtual ~Reciever() = default;
    virtual void action() const = 0;
};

class RecieverA : public Reciever {
public:
    void action() const override {
        std::cout << "RecieverA::action()" << std::endl;
    }
};

class RecieverB : public Reciever {
public:
    void action() const override {
        std::cout << "RecieverB::action()" << std::endl;
    }
};

class RecieverC : public Reciever {
public:
    void action() const override {
        std::cout << "RecieverC::action()" << std::endl;
    }
};

// 命令
class Command {
protected:
    std::vector<std::shared_ptr<Reciever>> m_receivers;

public:
    virtual ~Command() = default;
    virtual void execute() const = 0;
};

// 命令A
class CommandA : public Command {
public:
    CommandA(const std::vector<std::shared_ptr<Reciever>>& recievers) {
        m_receivers = recievers;
    }

    void execute() const override {
        for (const auto& receiver: m_receivers) {
            receiver->action();
        }
    }
};

// 调用者
class Invoke {
private:
    std::shared_ptr<Command> m_command;

public:
    void set_command(const std::shared_ptr<Command>& command) {
        m_command = command;
    }

    void invoke() const {
        if (m_command) {
            m_command->execute();
        }
    }
};

int main(int argc, char* argv[]) {
    // 创建接收者
    std::vector<std::shared_ptr<Reciever>> receivers = {
        std::make_shared<RecieverA>(), std::make_shared<RecieverB>(),
        std::make_shared<RecieverC>()
    };

    // 创建命令并绑定接收者
    std::shared_ptr<Command> command = std::make_shared<CommandA>(receivers);

    // 设置命令并调用
    Invoke invoke;
    invoke.set_command(command);
    invoke.invoke();

    return 0;
}
