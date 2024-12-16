/**
 * @file main.cpp
 * @author wenshuyu (wsy2161826815@163.com)
 * @brief 简单工厂案例
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
 * 简单工厂模式的用途：
 * 简单工厂模式(Simple Factory Pattern)是一种创建型设计模式, 
 * 用于根据不同的条件创建不同的实例. 它将实例化对象的逻辑集中在工厂类中, 
 * 客户端只需要传入参数而无需关心具体的实例化过程, 从而降低代码耦合性. 
 *
 * 用途：
 * 1. 封装对象的创建逻辑：将对象的实例化操作集中管理, 客户端无需了解对象的具体实现. 
 * 2. 提高代码的可维护性：当需要新增对象时, 只需修改工厂类即可, 而无需改动客户端代码. 
 * 3. 简化客户端代码：客户端只需传入参数, 工厂负责返回对应的实例. 
 * 4. 避免重复代码：将相似的实例化逻辑集中在工厂类中, 减少冗余代码. 
 *
 * 示例：
 * 在本代码中：
 * - `Operation`是抽象基类, 定义了基本操作的接口. 
 * - `OperationAdd`、`OperationSub`、`OperationMul`和`OperationDiv`是具体实现类, 分别表示加、减、乘、除操作. 
 * - `OperationFactory`是简单工厂类, 根据传入的运算符`op`创建对应的操作对象. 
 * 客户端代码通过工厂创建操作对象并设置操作数, 而无需直接实例化具体的操作类. 
 * 这种设计使得代码更加清晰、易于扩展和维护. 
 */


// 操作基类
class Operation {
public:
    double number_1 = 0;
    double number_2 = 0;

    virtual double get_result() const = 0; // 纯虚函数

    virtual ~Operation() = default;
};

// 加法类
class OperationAdd : public Operation {
public:
    double get_result() const override {
        return number_1 + number_2;
    }
};

// 减法类
class OperationSub : public Operation {
public:
    double get_result() const override {
        return number_1 - number_2;
    }
};

// 乘法类
class OperationMul : public Operation {
public:
    double get_result() const override {
        return number_1 * number_2;
    }
};

// 除法类
class OperationDiv : public Operation {
public:
    double get_result() const override {
        return number_1 / number_2;
    }
};

class OperationFactory {
public:
    static Operation* CreateOperation(char op) {
        switch (op) {
            case '+':
                return new OperationAdd();
            case '-':
                return new OperationSub();
            case '*':
                return new OperationMul();
            case '/':
                return new OperationDiv();
            default:
                return nullptr;
        }
    }
};

int main(int argc, char* argv[]) {
    // 加法
    char op = '+';
    Operation* operation = OperationFactory::CreateOperation(op);
    operation->number_1 = 10;
    operation->number_2 = 5;
    std::cout << "Result: " << operation->get_result() << std::endl;

    // 减法
    op = '-';
    operation = OperationFactory::CreateOperation(op);
    operation->number_1 = 10;
    operation->number_2 = 5;
    std::cout << "Result: " << operation->get_result() << std::endl;

    // 乘法
    op = '*';
    operation = OperationFactory::CreateOperation(op);
    operation->number_1 = 10;
    operation->number_2 = 5;
    std::cout << "Result: " << operation->get_result() << std::endl;

    // 除法
    op = '/';
    operation = OperationFactory::CreateOperation(op);
    operation->number_1 = 10;
    operation->number_2 = 5;
    std::cout << "Result: " << operation->get_result() << std::endl;

    return 0;
}