/**
 * @file main.cpp
 * @author wenshuyu (wsy2161826815@163.com)
 * @brief 外观模式
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
 * 外观模式的用途：
 * 外观模式(Facade Pattern)是一种结构型设计模式, 其主要目的是提供一个高层接口, 
 * 通过这个接口可以简化对复杂子系统的访问. 通过外观模式, 客户端无需直接与子系统的各个组件交互, 
 * 而是通过外观类统一管理, 降低系统复杂性, 提高代码的可维护性和扩展性. 
 *
 * 用途：
 * 1. 简化客户端与子系统的交互：隐藏子系统的细节, 提供简单易用的接口. 
 * 2. 提高模块化：将子系统与客户端代码解耦, 使子系统的变化不会直接影响客户端. 
 * 3. 统一子系统操作：将多组件的操作逻辑封装到一个方法中, 实现批量管理和协调. 
 * 4. 降低学习成本：使系统更容易理解和使用, 特别是对于复杂系统. 
 *
 * 示例：
 * 在本代码中, `Faced`类作为外观类, 统一封装了`SubSystem1`、`SubSystem2`、
 * `SubSystem3`和`SubSystem4`的功能. 
 * - `method_a()`提供了子系统功能组合1的访问. 
 * - `method_b()`提供了子系统功能组合2的访问. 
 * 客户端代码无需了解各个子系统的内部逻辑, 只需要通过`Faced`类调用对应的方法即可. 
 */


// 系统接口
class SystemInterface {
public:
    virtual ~SystemInterface() = default;
};

// 子系统1
class SubSystem1 : public SystemInterface {
public:
    void memthod1() {
        std::cout << "SubSystem1::memthod1()" << std::endl;
    }
};

// 子系统2
class SubSystem2 : public SystemInterface {
public:
    void memthod2() {
        std::cout << "SubSystem2::memthod2()" << std::endl;
    }
};

// 子系统3
class SubSystem3 : public SystemInterface {
public:
    void memthod3() {
        std::cout << "SubSystem3::memthod3()" << std::endl;
    }
};

// 子系统4
class SubSystem4 : public SystemInterface {
public:
    void memthod4() {
        std::cout << "SubSystem4::memthod4()" << std::endl;
    }
};

// 外观模式

class Faced {
private:
    std::shared_ptr<SubSystem1> sub_system1_;
    std::shared_ptr<SubSystem2> sub_system2_;
    std::shared_ptr<SubSystem3> sub_system3_;
    std::shared_ptr<SubSystem4> sub_system4_;

public:
    Faced() {
        sub_system1_ = std::make_shared<SubSystem1>();
        sub_system2_ = std::make_shared<SubSystem2>();
        sub_system3_ = std::make_shared<SubSystem3>();
        sub_system4_ = std::make_shared<SubSystem4>();
    }

    void method_a() {
        std::cout << "Method Group A" << std::endl;
        sub_system1_->memthod1();
        sub_system2_->memthod2();
        sub_system4_->memthod4();
    }

    void method_b() {
        std::cout << "Method Group B" << std::endl;
        sub_system3_->memthod3();
        sub_system4_->memthod4();
    }
};

int main(int argc, char* argv[]) {

    Faced facade;

    facade.method_a();
    facade.method_b();

    return 0;
}
