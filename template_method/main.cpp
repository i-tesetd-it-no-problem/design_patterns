/**
 * @file main.cpp
 * @author wenshuyu (wsy2161826815@163.com)
 * @brief 模板方法
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
 * 模板方法模式的用途：
 * 模板方法模式(Template Method
 * Pattern)是一种行为型设计模式, 定义了一个算法的骨架, 并允许子类重写某些特定步骤而不改变算法的整体结构. 
 * 它通过在父类中定义模板方法(Template
 * Method), 将算法的通用逻辑封装起来, 而将具体的实现延迟到子类. 
 *
 * 用途：
 * 1. 定义算法的框架：将通用逻辑封装在父类中, 避免重复代码. 
 * 2. 提高代码复用性：子类只需实现特定步骤, 而无需关心算法整体结构. 
 * 3. 统一行为模式：通过模板方法, 确保所有子类遵循相同的执行顺序和逻辑规则. 
 *
 * 关键角色：
 * - **AbstractTemplate(抽象模板类)**：
 *   - 定义了算法骨架, 通过`template_method`实现通用逻辑. 
 *   -
 * 声明了抽象方法`primitive_operation1`和`primitive_operation2`, 由子类实现. 
 * - **ConcreteClass(具体实现类)**：
 *   - 实现了抽象方法, 定义了算法中具体步骤的行为. 
 *
 * 示例：
 * 在本代码中：
 * - `AbstractTemplate` 定义了模板方法 `template_method`, 其调用了
 * `primitive_operation1` 和 `primitive_operation2`. 
 * - `ConcreteClass1` 和 `ConcreteClass2` 是具体实现类, 分别提供了
 * `primitive_operation1` 和 `primitive_operation2` 的具体实现. 
 * - 客户端通过调用模板方法执行算法, 而不需要关心算法的具体实现细节. 
 *
 * 模板方法执行流程：
 * 1. 调用模板方法 `template_method`. 
 * 2. 模板方法依次调用 `primitive_operation1` 和
 * `primitive_operation2`(子类实现的方法). 
 * 3. 最后执行模板方法中定义的其他逻辑. 
 *
 *
 * 优势：
 * 1. 提高复用性：通用逻辑在父类中实现, 具体逻辑在子类中实现. 
 * 2. 易于维护：算法结构固定, 逻辑清晰, 修改不影响整体流程. 
 * 3. 符合开闭原则：新增子类不会修改父类代码, 且不会破坏已有的算法框架. 
 *
 * 缺点：
 * 1. 子类需要实现所有的抽象方法, 可能增加代码量. 
 * 2. 模板方法在父类中定义, 灵活性受到一定限制. 
 *
 * 适用场景：
 * - 有多个子类共享相同的算法结构, 但部分实现细节不同. 
 * - 需要统一流程并保证一致性, 同时允许特定步骤的自定义实现. 
 */

class AbstractTemplate {
public:
    virtual ~AbstractTemplate() = default;

    virtual void primitive_operation1() = 0;
    virtual void primitive_operation2() = 0;

    void template_method() {
        primitive_operation1();
        primitive_operation2();
        std::cout << "template_method" << std::endl;
    }
};

class ConcreteClass1 : public AbstractTemplate {
public:
    void primitive_operation1() override {
        std::cout << "ConcreteClass1::primitive_operation1" << std::endl;
    }
    void primitive_operation2() override {
        std::cout << "ConcreteClass1::primitive_operation2" << std::endl;
    }
};

class ConcreteClass2 : public AbstractTemplate {
public:
    void primitive_operation1() override {
        std::cout << "ConcreteClass2::primitive_operation1" << std::endl;
    }
    void primitive_operation2() override {
        std::cout << "ConcreteClass2::primitive_operation2" << std::endl;
    }
};

// 客户端代码
int main(int argc, char* argv[]) {

    std::unique_ptr<AbstractTemplate> abstract_template;

    abstract_template = std::make_unique<ConcreteClass1>();
    abstract_template->template_method();

    abstract_template = std::make_unique<ConcreteClass2>();
    abstract_template->template_method();

    return 0;
}
