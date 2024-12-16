/**
 * @file main.cpp
 * @author wenshuyu (wsy2161826815@163.com)
 * @brief 装饰器模式
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
 * 装饰器模式的用途：
 * 装饰器模式(Decorator Pattern)是一种结构型设计模式, 用于在不修改现有对象结构的前提下, 动态地为对象添加新功能. 
 * 它通过将对象包装在装饰器类中, 达到扩展功能的目的, 同时可以保持原有对象的接口一致性. 
 *
 * 用途：
 * 1. 动态扩展对象功能：在运行时为对象添加新的行为, 而无需修改类定义. 
 * 2. 替代继承：通过组合而非继承, 实现更灵活的功能扩展. 
 * 3. 多层装饰：可以通过多次包装对象, 叠加多种功能. 
 *
 * 关键角色：
 * - **Component(抽象组件)**：定义对象的基本接口, 可以被装饰. 
 * - **ConcreteComponent(具体组件)**：实现基本功能的核心对象. 
 * - **Decorator(装饰器基类)**：持有一个 `Component` 对象的引用, 定义与 `Component` 一致的接口. 
 * - **ConcreteDecorator(具体装饰器)**：在基类功能的基础上, 添加具体的增强功能. 
 *
 * 示例中的实现：
 * 1. `Component`：
 *    - 抽象接口, 定义了 `operation` 方法. 
 * 2. `ConcreteComponent`：
 *    - 提供未装饰的基本实现, 如 `ConcreteComponent::operation`. 
 * 3. `Decorator`：
 *    - 持有一个 `std::shared_ptr<Component>` 对象, 并通过 `Decorator::operation` 调用被装饰对象的功能. 
 * 4. `ConcreteDecorator1` 和 `ConcreteDecorator2`：
 *    - 在调用基类功能的基础上, 添加自己的装饰逻辑(如增加状态或功能). 
 * 5. 主函数中：
 *    - 创建未装饰的 `ConcreteComponent` 对象. 
 *    - 用具体装饰器 `ConcreteDecorator1` 和 `ConcreteDecorator2` 包装这些对象, 并调用装饰后的功能. 
 *
 * 优势：
 * 1. 动态扩展功能：可以根据需求灵活地为对象添加不同的行为. 
 * 2. 开闭原则：无需修改已有代码即可扩展功能. 
 * 3. 组合功能：可以通过多个装饰器叠加, 实现多种功能组合. 
 *
 * 缺点：
 * 1. 对象复杂性增加：装饰器会增加系统的类数量和对象层次. 
 * 2. 性能开销：多层装饰会导致递归调用, 增加运行时开销. 
 *
 * 适用场景：
 * - 需要动态扩展对象的功能, 而不想修改对象的类定义. 
 * - 需要为对象提供多种功能组合, 而不希望使用大量的子类. 
 * - 想要保持类的接口一致性, 同时引入新的功能. 
 */


// 抽象接口
class Component {
public:
    virtual ~Component() = default; // 虚析构函数
    virtual void operation() = 0;
};

// 未装饰的基本实现
class ConcreteComponent : public Component {
public:
    void operation() override {
        std::cout << "ConcreteComponent operation" << std::endl;
    }
};

// 装饰器基类
class Decorator : public Component {
protected:
    std::shared_ptr<Component> component; // 被装饰的对象

public:
    explicit Decorator(std::shared_ptr<Component> c) : component(c) {
    }

    void operation() override {
        if (component) {
            component->operation(); // 调用被装饰组件的操作
        }
    }
};

// 具体装饰器1
class ConcreteDecorator1 : public Decorator {
private:
    std::string added_state_; // 增加的状态

public:
    explicit ConcreteDecorator1(std::shared_ptr<Component> component) :
        Decorator(component) {
    }

    void operation() override {
        Decorator::operation(); // 装饰前
        added_state_ = "added state 1";

        // 装饰后
        std::cout << "ConcreteDecorator1 added_state: " << added_state_
                  << std::endl;
    }
};

// 具体装饰器2
class ConcreteDecorator2 : public Decorator {
private:
    std::string added_state_; // 增加的状态

public:
    explicit ConcreteDecorator2(std::shared_ptr<Component> component) :
        Decorator(component) {
    }

    void operation() override {
        Decorator::operation(); // 装饰前
        added_state_ = "added state 2";

        // 装饰后
        std::cout << "ConcreteDecorator2 added_state: " << added_state_
                  << std::endl;
    }
};

int main(int argc, char* argv[]) {
    // 创被装饰的对象
    std::shared_ptr<Component> c1 = std::make_shared<ConcreteComponent>();
    std::shared_ptr<Component> c2 = std::make_shared<ConcreteComponent>();

    // d1 装饰 c1
    std::shared_ptr<Decorator> d1 = std::make_shared<ConcreteDecorator1>(c1);

    // d2 装饰 c2
    std::shared_ptr<Decorator> d2 = std::make_shared<ConcreteDecorator2>(c2);

    d1->operation();
    d2->operation();

    return 0;
}
