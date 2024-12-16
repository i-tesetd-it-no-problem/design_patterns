/**
 * @file main.cpp
 * @author wenshuyu (wsy2161826815@163.com)
 * @brief 策略模式
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

/**
 * 策略模式的用途：
 * 策略模式(Strategy
 * Pattern)是一种行为型设计模式, 定义了一系列算法, 将每种算法封装到独立的策略类中, 并使它们可以互换. 
 * 策略模式通过将算法的使用与实现分离, 提高了代码的灵活性和扩展性. 
 *
 * 用途：
 * 1. 动态选择算法：根据需求或上下文动态选择不同的算法实现. 
 * 2. 提高代码复用性：将算法封装到独立的类中, 避免代码重复. 
 * 3. 遵循开闭原则：通过增加新策略扩展功能, 而无需修改已有代码. 
 *
 * 关键角色：
 * - **Strategy(策略接口)**：
 *   - 定义了算法的通用接口, 所有具体策略类必须实现此接口. 
 * - **ConcreteStrategy(具体策略类)**：
 *   - 实现了策略接口, 封装了具体的算法. 
 * - **Context(上下文类)**：
 *   - 持有一个策略对象的引用, 通过调用策略对象的接口执行具体算法. 
 *
 * 示例：
 * 在本代码中：
 * - `Strategy` 是策略接口, 定义了 `algorithm_interface` 方法. 
 * - `StrategyA` 和 `StrategyB` 是具体策略类, 分别提供了不同的算法实现. 
 * - `Context` 是上下文类, 持有一个策略对象并通过其接口调用算法. 
 *
 *
 * 优势：
 * 1. 动态切换算法：允许在运行时选择不同的策略. 
 * 2. 遵循单一职责原则：每个策略类只负责一个具体算法的实现. 
 * 3. 符合开闭原则：新增策略类无需修改已有代码. 
 *
 * 缺点：
 * 1. 增加了类的数量：每个策略需要独立的类. 
 * 2. 客户端需要了解所有策略类, 以便选择合适的策略. 
 *
 * 适用场景：
 * - 需要动态选择不同算法或行为. 
 * - 多个类只在行为上有细微差异, 通过策略模式避免代码重复. 
 * - 想要避免使用复杂的条件分支结构(如 `if-else` 或 `switch-case`). 
 */

class Strategy {
public:
    virtual ~Strategy() = default;
    virtual void algorithm_interface() = 0;
};

class StrategyA : public Strategy {
public:
    void algorithm_interface() override {
        std::cout << "StrategyA::algorithm_interface()" << std::endl;
    }
};

class StrategyB : public Strategy {
public:
    void algorithm_interface() override {
        std::cout << "StrategyB::algorithm_interface()" << std::endl;
    }
};

class Context {
private:
    std::shared_ptr<Strategy> m_strategy;

public:
    Context(std::shared_ptr<Strategy> strategy) : m_strategy(strategy){};

    void context_interface() const {
        m_strategy->algorithm_interface();
    }
};

int main(int argc, char* argv[]) {

    std::shared_ptr<Strategy> strategy_a = std::make_shared<StrategyA>();
    Context context_a(strategy_a);
    context_a.context_interface();

    std::shared_ptr<Strategy> strategy_b = std::make_shared<StrategyB>();
    Context context_b(strategy_b);
    context_b.context_interface();

    return 0;
}
