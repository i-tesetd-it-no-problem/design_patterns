/**
 * @file main.cpp
 * @author wenshuyu (wsy2161826815@163.com)
 * @brief 适配器模式
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
 * 适配器模式的用途：
 * 适配器模式(Adapter
 * Pattern)是一种结构型设计模式, 用于将一个类的接口转换为客户期望的另一种接口. 
 * 它通过引入适配器类, 使得原本由于接口不兼容而无法工作的类能够协同工作. 
 * 适配器模式通常被用来解决现有代码无法直接复用的问题. 
 *
 * 用途：
 * 1. 使现有类能够适配新的接口要求, 避免修改原有代码. 
 * 2. 实现不兼容接口之间的协作. 
 * 3. 对现有接口进行封装, 为客户提供更灵活的使用方式. 
 *
 * 关键角色：
 * - **Target(目标接口)**：
 *   定义客户所期待的接口, 通常是抽象类或接口. 
 * - **Adaptee(被适配者)**：
 *   定义了客户不兼容的接口, 通常是已有的类. 
 * - **Adapter(适配器)**：
 *   实现目标接口, 并通过组合或继承的方式将被适配者的接口转换为目标接口. 
 *
 * 示例中的实现：
 * 1. `Adaptee`：
 *    - 定义了现有的接口 `specific_request`. 
 * 2. `Target`：
 *    - 定义了客户所期待的标准接口 `request`. 
 * 3. `Adapter`：
 *    - 继承 `Target`, 实现了客户期望的接口 `request`. 
 *    - 通过组合的方式, 将 `Adaptee` 的接口 `specific_request` 适配为 `Target`
 * 的接口. 
 * 4. 主函数：
 *    - 客户代码通过 `Target` 指针调用 `request` 方法, 实际操作由 `Adapter`
 * 转发给 `Adaptee`. 
 *
 * 优势：
 * 1. 增强代码复用性：能够复用现有类, 而无需修改其代码. 
 * 2.
 * 提高代码灵活性：客户代码无需知道被适配者的存在, 只需通过目标接口与适配器交互. 
 * 3. 符合开闭原则：通过新增适配器类, 扩展了现有代码的功能, 而无需修改原有类. 
 *
 * 缺点：
 * 1. 系统复杂性增加：需要引入额外的适配器类. 
 * 2. 性能开销：可能由于接口转换增加一些间接调用的开销. 
 *
 * 适用场景：
 * - 想要使用一个现有的类, 但其接口与当前系统要求不兼容. 
 * - 需要创建一个可以复用的类库, 而又不希望修改现有代码. 
 * - 需要适配多个不同的接口, 实现统一的调用方式. 
 */

// 需要适配的类
class Adaptee {
public:
    void specific_request() {
        std::cout << "Adaptee::specific_request()" << std::endl;
    }
};

// 客户所期待的接口
class Target {
public:
    virtual void request() {
        std::cout << "Regular request" << std::endl;
    }

    virtual ~Target() = default;
};

// 适配器类
class Adapter : public Target {
private:
    std::unique_ptr<Adaptee> adaptee_;

public:
    Adapter() : adaptee_(std::make_unique<Adaptee>()) {
    }

    void request() override {
        std::cout << "Adapter::request()" << std::endl;
        adaptee_->specific_request();
    }
};

int main(int argc, char* argv[]) {
    std::unique_ptr<Target> TargetPtr = std::make_unique<Adapter>();
    TargetPtr->request();

    return 0;
}
