/**
 * @file main.cpp
 * @author wenshuyu (wsy2161826815@163.com)
 * @brief 抽象工厂案例
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
 * 抽象工厂模式的用途：
 * 抽象工厂模式(Abstract Factory Pattern)是一种创建型设计模式, 用于提供一个接口, 
 * 用于创建一系列相关或相互依赖的对象, 而无需指定它们具体的类. 它适用于需要创建多个产品族的场景, 
 * 并且每个产品族中的产品相互关联, 但客户端不需要了解具体实现细节. 
 *
 * 用途：
 * 1. 实现产品族之间的约束关系：确保同一工厂生成的产品是相互兼容的. 
 * 2. 提高代码可扩展性：通过增加新的具体工厂和产品, 可以轻松扩展产品族. 
 * 3. 隐藏产品具体实现：客户端代码仅依赖于抽象接口, 完全与具体产品实现解耦. 
 * 4. 提供一致性：确保创建的一组对象具有统一的风格或接口, 避免产品之间的兼容性问题. 
 *
 * 示例：
 * 在本代码中：
 * - `AbstractFatory`是抽象工厂, 定义了创建产品A和产品B的方法接口. 
 * - `ConcreteFatory1`和`ConcreteFatory2`是具体工厂, 分别实现了产品A1、B1和产品A2、B2的创建. 
 * - `AbstractProductA`和`AbstractProductB`分别定义了产品A和产品B的抽象接口. 
 * - `ProdunctA1`、`ProdunctA2`、`ProdunctB1`、`ProdunctB2`是具体的产品类. 
 * 客户端代码通过工厂对象创建产品, 而不关心具体的产品类, 从而实现了对产品族的解耦和扩展. 
 */


// 抽象产品A
class AbstractProductA {
public:
    virtual void methodA() const = 0;
    virtual ~AbstractProductA() = default;
};

// 产品A1
class ProdunctA1 : public AbstractProductA {
public:
    void methodA() const override {
        std::cout << "ProdunctA1::methodA()" << std::endl;
    }
};

// 产品A2
class ProdunctA2 : public AbstractProductA {
public:
    void methodA() const override {
        std::cout << "ProdunctA2::methodA()" << std::endl;
    }
};

// 抽象产品B
class AbstractProductB {
public:
    virtual void methodB() const = 0;
    virtual ~AbstractProductB() = default;
};

// 产品B1
class ProdunctB1 : public AbstractProductB {
public:
    void methodB() const override {
        std::cout << "ProdunctB1::methodB()" << std::endl;
    }
};

// 产品B2
class ProdunctB2 : public AbstractProductB {
public:
    void methodB() const override {
        std::cout << "ProdunctB2::methodB()" << std::endl;
    }
};

// 抽象工厂
class AbstractFatory {
public:
    virtual std::unique_ptr<AbstractProductA> create_productA() const = 0;
    virtual std::unique_ptr<AbstractProductB> create_productB() const = 0;
    virtual ~AbstractFatory() = default;
};

// 具体工厂1
class ConcreteFatory1 : public AbstractFatory {
public:
    std::unique_ptr<AbstractProductA> create_productA() const override {
        return std::make_unique<ProdunctA1>();
    }
    std::unique_ptr<AbstractProductB> create_productB() const override {
        return std::make_unique<ProdunctB1>();
    }
};

// 具体工厂2
class ConcreteFatory2 : public AbstractFatory {
public:
    std::unique_ptr<AbstractProductA> create_productA() const override {
        return std::make_unique<ProdunctA2>();
    }
    std::unique_ptr<AbstractProductB> create_productB() const override {
        return std::make_unique<ProdunctB2>();
    }
};

int main(int argc, char* argv[]) {
    // 具体工厂1
    std::unique_ptr<AbstractFatory> factory1 =
        std::make_unique<ConcreteFatory1>();

    // 调用工厂方法
    std::unique_ptr<AbstractProductA> productA1 = factory1->create_productA();
    productA1->methodA();
    std::unique_ptr<AbstractProductB> productB1 = factory1->create_productB();
    productB1->methodB();

    // 具体工厂2
    std::unique_ptr<AbstractFatory> factory2 =
        std::make_unique<ConcreteFatory2>();

    std::unique_ptr<AbstractProductA> productA2 = factory2->create_productA();
    productA2->methodA();
    std::unique_ptr<AbstractProductB> productB2 = factory2->create_productB();
    productB2->methodB();

    return 0;
}