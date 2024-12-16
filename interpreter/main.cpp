/**
 * @file main.cpp
 * @author wenshuyu (wsy2161826815@163.com)
 * @brief 解释器模式
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
#include <vector>
#include <string>

/**
 * 解释器模式的用途：
 * 解释器模式(Interpreter Pattern)是一种行为型设计模式
 * 它为特定语言的文法定义了一种表示, 并提供一个解释器来解释这些文法的句子. 
 * 解释器模式将复杂的语法解析任务分解为更小的表达式对象, 每个对象负责解释语法的一部分. 
 *
 * 用途：
 * 1. 用于语法解析：编译器、解释器、SQL解析器、数学表达式计算等. 
 * 2. 适用于频繁变更的复杂业务规则：将规则抽象为可复用的表达式. 
 * 3. 表达式计算：如正则表达式、公式计算等. 
 *
 * 关键角色：
 * - **Context(上下文)**：存储全局信息(输入和输出), 供表达式对象使用. 
 * - **AbstractExpression(抽象表达式)**：定义解释操作的抽象接口. 
 * - **TerminalExpression(终结符表达式)**：处理语法中的基本元素. 
 * -
 * **NonterminalExpression(非终结符表达式)**：表示语法规则或复杂结构, 通常组合终结符和其他非终结符表达式. 
 *
 * 示例：
 * - `TerminalExpression` 对输入进行终结符处理. 
 * - `NonterminalExpression` 表示更复杂的规则, 组合或扩展基础表达式. 
 *
 * 优势：
 * 1. 语法与逻辑分离, 便于扩展. 
 * 2. 通过组合表达式, 可以表示复杂规则. 
 *
 * 缺点：
 * 1. 表达式数量增加时, 会导致类膨胀. 
 * 2. 性能可能会因为递归调用解释而降低. 
 *
 * 适用场景：
 * - 需要对输入进行规则化解析. 
 * - 规则较为固定, 但需要灵活扩展. 
 */

// 上下文类, 存储输入和输出
class Context {
private:
    std::string input;
    std::string output;

public:
    const std::string& get_input() const {
        return input;
    }

    void set_input(const std::string& input) {
        this->input = input;
    }

    const std::string& get_output() const {
        return output;
    }

    void set_output(const std::string& output) {
        this->output = output;
    }
};

// 抽象表达式类
class AbstractExpression {
public:
    virtual ~AbstractExpression() = default;
    virtual void interpret(Context& context) const = 0; // 解释方法
};

// 终结符表达式类
class TerminalExpression : public AbstractExpression {
public:
    void interpret(Context& context) const override {
        std::string input = context.get_input();
        std::string output = "Terminal processed: " + input;
        context.set_output(output);
        std::cout << "TerminalExpression: " << output << std::endl;
    }
};

// 非终结符表达式类
class NonterminalExpression : public AbstractExpression {
public:
    void interpret(Context& context) const override {
        std::string input = context.get_input();
        std::string output = "Nonterminal processed: " + input;
        context.set_output(output);
        std::cout << "NonterminalExpression: " << output << std::endl;
    }
};

// 客户端代码
int main(int argc, char* argv[]) {
    Context context;

    // 设置初始输入
    context.set_input("Initial Input");

    // 创建表达式列表
    std::vector<std::shared_ptr<AbstractExpression>> expressions;

    expressions.push_back(std::make_shared<TerminalExpression>());
    expressions.push_back(std::make_shared<NonterminalExpression>());
    expressions.push_back(std::make_shared<TerminalExpression>());

    // 解释表达式
    for (const auto& expression: expressions) {
        expression->interpret(context);
    }

    return 0;
}
