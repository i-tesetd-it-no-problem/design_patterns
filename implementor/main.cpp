/**
 * @file main.cpp
 * @author wenshuyu (wsy2161826815@163.com)
 * @brief 桥接模式
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
#include <string>

/**
 * 桥接模式的用途：
 * 桥接模式(Bridge
 * Pattern)是一种结构型设计模式, 用于将抽象部分与其实现部分分离, 使它们可以独立变化. 
 * 通过桥接模式, 可以在抽象和实现之间构建一个桥梁, 从而实现解耦, 适用于系统需要同时扩展多个维度的场景. 
 *
 * 用途：
 * 1. 避免类层次过于庞大, 将类的功能层次与实现层次分离. 
 * 2. 需要在抽象和实现之间动态切换时, 可以通过桥接模式实现灵活的扩展. 
 * 3. 提供一种实现多维度扩展的结构, 而不增加系统的复杂性. 
 *
 * 关键角色：
 * - **Abstraction(抽象类)**：
 *   定义抽象层的接口, 维护对实现部分(Implementor)的引用, 并通过实现部分完成具体操作. 
 * - **RefinedAbstraction(扩展抽象类)**：
 *   扩展抽象类的功能, 通常通过调用 `Abstraction` 中的操作实现具体功能. 
 * - **Implementor(实现接口)**：
 *   定义实现层的接口, 供具体实现类扩展. 
 * - **ConcreteImplementor(具体实现类)**：
 *   实现 `Implementor` 接口, 提供具体操作的实现. 
 *
 * 示例中的实现：
 * 1. `Implementor`：
 *    - 定义了实现部分的抽象接口, 包含纯虚方法 `operation`. 
 * 2. `ConcreteImplementorA` 和 `ConcreteImplementorB`：
 *    - 提供了实现部分的具体操作, 实现了不同的行为. 
 * 3. `Abstraction`：
 *    - 定义了抽象部分的接口, 持有 `Implementor`
 * 的引用, 并通过调用其方法完成具体操作. 
 * 4. `AbstractionA` 和 `AbstractionB`：
 *    - 扩展了 `Abstraction`, 增加了与具体实现类交互的逻辑. 
 * 5. 主函数：
 *    - 创建扩展抽象类(如 `AbstractionA` 和
 * `AbstractionB`), 并动态切换具体实现类(如 `ConcreteImplementorA` 和
 * `ConcreteImplementorB`), 展示桥接模式的灵活性. 
 *
 * 优势：
 * 1. 抽象和实现分离：两者可以独立变化, 互不影响. 
 * 2. 遵循单一职责原则：抽象和实现的职责明确, 易于扩展和维护. 
 * 3. 动态切换实现：可以在运行时动态切换实现部分. 
 * 4. 提高代码的灵活性和可扩展性：适用于多维度变化的场景. 
 *
 * 缺点：
 * 1. 增加系统复杂性：需要引入抽象层和实现层, 可能导致代码结构复杂. 
 * 2. 开发成本提高：需要设计和维护抽象接口和实现类. 
 *
 * 适用场景：
 * - 一个类需要在多个维度上扩展, 而这些维度需要独立变化. 
 * - 系统需要动态切换不同的实现部分. 
 * - 希望通过组合方式替代多层次的继承结构, 以减少类的数量和耦合度. 
 */

// 实现接口
class Implementor {
public:
    virtual ~Implementor() = default;
    virtual void operation() = 0;
};

// 具体实现A
class ConcreteImplementorA : public Implementor {
public:
    void operation() override {
        std::cout << "ConcreteImplementorA operation" << std::endl;
    }
};

// 具体实现B
class ConcreteImplementorB : public Implementor {
public:
    void operation() override {
        std::cout << "ConcreteImplementorB operation" << std::endl;
    }
};

// 抽象类
class Abstraction {
protected:
    std::shared_ptr<Implementor> implementor;
    std::string name;

public:
    Abstraction(std::string name) : name(name) {
    }

    void set_implementor(std::shared_ptr<Implementor> implementor) {
        this->implementor = implementor;
    }

    virtual void operation() {
        if (implementor) {
            implementor->operation();
        }
    }

    virtual ~Abstraction() = default;
};

// 扩展部分A
class AbstractionA : public Abstraction {
public:
    AbstractionA(std::string name) : Abstraction(name) {
    }

    void operation() override {
        std::cout << "AbstractionA operation" << std::endl;
        Abstraction::operation();
    }
};

// 扩展部分B
class AbstractionB : public Abstraction {
public:
    AbstractionB(std::string name) : Abstraction(name) {
    }

    void operation() override {
        std::cout << "AbstractionB operation" << std::endl;
        Abstraction::operation();
    }
};

// 客户端代码
int main(int argc, char* argv[]) {

    std::shared_ptr<Abstraction> abstractionA =
        std::make_shared<AbstractionA>("AbstractionA");
    abstractionA->set_implementor(std::make_shared<ConcreteImplementorA>());
    abstractionA->operation();
    abstractionA->set_implementor(std::make_shared<ConcreteImplementorB>());
    abstractionA->operation();

    std::shared_ptr<Abstraction> abstractionB =
        std::make_shared<AbstractionB>("AbstractionB");
    abstractionB->set_implementor(std::make_shared<ConcreteImplementorA>());
    abstractionB->operation();
    abstractionB->set_implementor(std::make_shared<ConcreteImplementorB>());
    abstractionB->operation();

    return 0;
}
