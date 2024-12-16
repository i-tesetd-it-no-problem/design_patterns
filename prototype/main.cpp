/**
 * @file main.cpp
 * @author wenshuyu (wsy2161826815@163.com)
 * @brief 原型模式
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
 * 原型模式的用途：
 * 原型模式(Prototype Pattern)是一种创建型设计模式, 用于通过复制现有对象来创建新对象, 
 * 而不是通过构造函数实例化. 它允许一个对象复制自身, 从而避免创建对象时的复杂初始化过程. 
 * 原型模式特别适用于需要大量相似对象或对象创建成本较高的场景. 
 *
 * 用途：
 * 1. 避免复杂对象的构造：对于构造过程较复杂或耗时的对象, 使用原型模式可以减少创建成本. 
 * 2. 动态创建对象：运行时无需知道具体类, 只需通过复制现有对象即可创建新的实例. 
 * 3. 提高性能：在需要频繁创建对象的场景下, 克隆现有对象比重新构造对象更高效. 
 * 4. 提供多样化的对象：原型模式可以让程序在运行时动态生成对象的不同变体. 
 *
 * 示例：
 * 在本代码中：
 * - `Prototype`是抽象基类, 定义了`clone()`方法用于克隆对象. 
 * - `PrototypeA`和`PrototypeB`是具体实现类, 实现了`clone()`方法. 
 * - 客户端通过调用`clone()`方法创建现有对象的副本, 而无需关心对象的创建细节. 
 * 
 * 优势：
 * - 使用`clone()`方法进行深拷贝, 确保克隆出的新对象与原始对象独立存储. 
 * - 确保不同的派生类可以在不暴露构造细节的情况下动态复制对象. 
 */


// 原型抽象基类
class Prototype {
public:
    virtual std::unique_ptr<Prototype> clone() const = 0; // 纯虚函数

    virtual ~Prototype() = default;
};

// 原型A
class PrototypeA : public Prototype {
public:
    std::unique_ptr<Prototype> clone() const override {
        return std::make_unique<PrototypeA>(*this); // 调用拷贝构造函数
    }
};

// 原型B
class PrototypeB : public Prototype {
public:
    std::unique_ptr<Prototype> clone() const override {
        return std::make_unique<PrototypeB>(*this); // 调用拷贝构造函数
    }
};

int main(int argc, char* argv[]) {
    // 创建原型A和原型B
    std::unique_ptr<PrototypeA> prototype_A = std::make_unique<PrototypeA>();
    std::unique_ptr<PrototypeB> prototype_B = std::make_unique<PrototypeB>();

    // 克隆原型A和原型B
    std::unique_ptr<Prototype> clone_A = prototype_A->clone(); // 克隆原型A
    std::unique_ptr<Prototype> clone_B = prototype_B->clone(); // 克隆原型B

    std::cout << "Clone A == Prototype A: "
              << (clone_A.get() != prototype_A.get()) << std::endl;
    std::cout << "Clone B == Prototype B: "
              << (clone_B.get() != prototype_B.get()) << std::endl;

    return 0;
}