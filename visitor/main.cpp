/**
 * @file main.cpp
 * @author wenshuyu (wsy2161826815@163.com)
 * @brief 访问者模式
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
#include <vector>
#include <memory>
#include <algorithm>

/**
 * 访问者模式的用途：
 * 访问者模式(Visitor
 * Pattern)是一种行为型设计模式, 用于将操作(行为)与对象的结构分离. 
 * 它允许在不修改对象结构的情况下, 定义作用于这些对象的新操作. 
 * 访问者模式特别适用于对象结构稳定但行为扩展性要求高的场景. 
 *
 * 用途：
 * 1. 需要对对象结构中的元素定义多种操作, 而又不希望修改其类定义. 
 * 2. 对象结构稳定, 但操作多变, 需要灵活扩展行为. 
 * 3. 在运行时需要根据对象类型执行不同的操作. 
 *
 * 关键角色：
 * - **Element(元素接口)**：
 *   定义一个 `accept` 方法, 接收访问者对象. 
 * - **ConcreteElement(具体元素类)**：
 *   实现元素接口, 定义自己特定的操作, 并允许访问者访问. 
 * - **Vistor(访问者接口)**：
 *   定义访问元素的接口, 如 `visitElementA` 和 `visitElementB`. 
 * - **ConcreteVistor(具体访问者类)**：
 *   实现访问者接口, 为不同元素定义具体操作. 
 * - **ObjectStructure(对象结构)**：
 *   管理元素集合, 提供方法让访问者遍历所有元素. 
 *
 * 示例中的实现：
 * 1. `Element`：
 *    - 定义了元素的抽象接口. 
 * 2. `ElementA` 和 `ElementB`：
 *    - 具体元素类, 分别实现了 `accept` 方法. 
 * 3. `Vistor`：
 *    - 定义了访问者的抽象接口. 
 * 4. `VistorA` 和 `VistorB`：
 *    - 具体访问者类, 实现了访问不同元素的逻辑. 
 * 5. `ObjectStructure`：
 *    - 管理元素集合, 提供了添加、删除元素及遍历元素的功能. 
 * 6. 主函数：
 *    - 创建对象结构并添加元素. 
 *    - 创建访问者并应用于对象结构, 展示不同访问者对相同元素的不同操作. 
 *
 * 优势：
 * 1. 遵循开闭原则：可以在不修改对象结构的情况下, 新增访问者以定义新的操作. 
 * 2. 灵活扩展：便于添加新的行为(访问者)或应用逻辑. 
 * 3. 易于分离：将数据结构和行为分离, 操作逻辑集中在访问者中. 
 *
 * 缺点：
 * 1. 对象结构的元素修改困难：如果需要新增元素, 必须同时修改所有访问者. 
 * 2.
 * 双重分派增加复杂性：访问者模式依赖于两次分派(对象接受访问者, 访问者识别对象类型). 
 * 3. 元素集合过大时可能导致访问者实现冗长. 
 *
 * 适用场景：
 * - 对象结构稳定, 但需要经常新增行为. 
 * - 需要对不同类型的对象执行多种不同操作. 
 * - 希望将数据结构与操作解耦. 
 */

// 访问者基类
class Vistor;

// 元素基类
class Element {
public:
    virtual ~Element() = default; // 确保派生类正确析构
    virtual void accept(Vistor& vistor) = 0;
    virtual std::string get_name() = 0;
};

// 前向声明具体元素类
class ElementA;
class ElementB;

// 访问者基类
class Vistor {
public:
    virtual ~Vistor() = default;

    virtual void visitElementA(ElementA* elementA) = 0;
    virtual void visitElementB(ElementB* elementB) = 0;
};

// 具体元素A
class ElementA : public Element {
public:
    void accept(Vistor& vistor) override {
        vistor.visitElementA(this);
    }
    std::string get_name() override {
        return "ElementA";
    }
};

// 具体元素B
class ElementB : public Element {
public:
    void accept(Vistor& vistor) override {
        vistor.visitElementB(this);
    }
    std::string get_name() override {
        return "ElementB";
    }
};

// 具体访问者A
class VistorA : public Vistor {
public:
    void visitElementA(ElementA* elementA) override {
        std::cout << "VistorA visits " << elementA->get_name() << std::endl;
    }
    void visitElementB(ElementB* elementB) override {
        std::cout << "VistorA visits " << elementB->get_name() << std::endl;
    }

    std::string get_name() {
        return "VistorA";
    }
};

// 具体访问者B
class VistorB : public Vistor {
public:
    void visitElementA(ElementA* elementA) override {
        std::cout << "VistorB visits " << elementA->get_name() << std::endl;
    }
    void visitElementB(ElementB* elementB) override {
        std::cout << "VistorB visits " << elementB->get_name() << std::endl;
    }

    std::string get_name() {
        return "VistorB";
    }
};

// 对象结构
class ObjectStructure {
private:
    std::vector<std::shared_ptr<Element>> elements;

public:
    void attach(std::shared_ptr<Element> element) {
        elements.push_back(std::move(element));
    }

    void detach(std::shared_ptr<Element> element) {
        elements.erase(std::remove(elements.begin(), elements.end(), element),
                       elements.end());
    }

    void accept(Vistor& vistor) {
        for (auto& element: elements) {
            element->accept(vistor);
        }
    }
};

// 客户端代码
int main() {
    ObjectStructure objectStructure;

    objectStructure.attach(std::make_shared<ElementA>());
    objectStructure.attach(std::make_shared<ElementB>());

    VistorA vistorA;
    VistorB vistorB;

    std::cout << "Applying VistorA:" << std::endl;
    objectStructure.accept(vistorA);

    std::cout << "\nApplying VistorB:" << std::endl;
    objectStructure.accept(vistorB);

    return 0;
}
