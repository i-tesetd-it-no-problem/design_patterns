/**
 * @file main.cpp
 * @author wenshuyu (wsy2161826815@163.com)
 * @brief 单例模式
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

/**
 * 单例模式的用途：
 * 单例模式(Singleton Pattern)是一种创建型设计模式, 确保一个类只有一个实例, 并提供一个全局访问点. 
 * 单例模式通过限制实例化的方式, 保证系统中只存在一个共享实例. 
 *
 * 用途：
 * 1. 确保某些全局状态(如日志管理器、线程池)在整个系统中只有一个实例. 
 * 2. 避免重复创建对象, 节省资源. 
 * 3. 提供一种访问共享资源的全局接口. 
 *
 * 示例中的实现：
 * 1. 构造函数私有化：防止外部通过 `new` 或其他方式创建实例. 
 * 2. 删除拷贝构造函数和赋值运算符：防止通过拷贝或赋值创建额外的实例. 
 * 3. 使用静态局部变量：实现线程安全的懒加载, 只有在第一次访问时才会创建实例. 
 * 4. 提供 `get_instance` 方法：返回单例的全局唯一实例. 
 *
 * 优势：
 * 1. 控制实例数量：确保系统中只有一个实例. 
 * 2. 延迟初始化：实例只有在需要时才会创建, 节省资源. 
 * 3. 全局访问：通过静态方法提供全局访问点, 便于使用. 
 *
 * 缺点：
 * 1. 全局状态的潜在问题：滥用单例模式可能导致系统依赖全局状态, 降低代码的可测试性. 
 * 2. 多线程复杂性：在多线程环境下, 确保单例的线程安全需要额外处理. 
 * 3. 隐式依赖：可能导致代码耦合, 违背单一职责原则. 
 *
 * 适用场景：
 * - 需要确保某个类在系统中仅有一个实例. 
 * - 需要全局访问某个共享资源(如配置管理器、日志管理器). 
 * - 希望通过控制实例数量优化资源管理. 
 */


class Singleton {
private:
    Singleton() {
        std::cout << "Singleton instance created." << std::endl;
    }
    ~Singleton() {
        std::cout << "Singleton instance destroyed." << std::endl;
    }

public:
    // 禁止拷贝和赋值
    Singleton(const Singleton&) = delete;
    Singleton& operator=(const Singleton&) = delete;

    static Singleton& get_instance() {
        static Singleton instance;
        return instance;
    }

    void do_something() const {
        std::cout << "Singleton is working." << std::endl;
    }
};

int main() {
    Singleton& s1 = Singleton::get_instance();
    Singleton& s2 = Singleton::get_instance();

    if (&s1 == &s2) {
        std::cout << "s1 and s2 are the same instance" << std::endl;
    } else {
        std::cout << "s1 and s2 are different instances" << std::endl;
    }

    s1.do_something();

    return 0;
}
