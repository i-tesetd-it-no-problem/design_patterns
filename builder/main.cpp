/**
 * @file main.cpp
 * @author wenshuyu (wsy2161826815@163.com)
 * @brief 建造者模式
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
 * 建造者模式的用途：
 * 建造者模式(Builder
 * Pattern)是一种创建型设计模式, 用于将复杂对象的构建过程与表示分离. 
 * 它允许使用相同的构建过程创建不同的产品, 并通过逐步构建的方式控制复杂对象的生成. 
 *
 * 用途：
 * 1. 需要构造复杂对象时, 将构造逻辑分步执行, 并将构造过程和产品表示分离. 
 * 2. 需要创建的产品具有多种类型或不同的组合形式时. 
 * 3. 希望通过控制构造过程, 提高代码的灵活性和可维护性. 
 *
 * 关键角色：
 * - **Product(产品类)**：
 *   定义了要构建的复杂对象的内部结构和接口. 
 * - **Builder(建造者接口)**：
 *   定义了构建产品的步骤. 
 * - **ConcreteBuilder(具体建造者)**：
 *   实现了具体的构造步骤, 负责创建产品的不同部分. 
 * - **Director(指挥者)**：
 *   调用建造者的方法, 按顺序执行构造逻辑. 
 *
 * 示例中的实现：
 * 1. `Product`：
 *    - 包含了产品的部分结构, 通过 `set_part_1` 和 `set_part_2` 设置产品部件. 
 *    - 提供 `show` 方法, 用于展示构建完成的产品. 
 * 2. `Builder`：
 *    - 抽象接口, 定义了构建产品和返回结果的接口. 
 * 3. `Builder_A`：
 *    - 具体建造者, 实现了 `build_part` 方法, 构建产品的部件. 
 *    - 提供 `get_result` 方法返回最终构造的产品. 
 * 4. `Director`：
 *    - 持有建造者的引用, 通过调用其方法控制产品的构建过程. 
 * 5. 主函数：
 *    - 创建建造者和指挥者, 通过指挥者调用建造者完成产品的构造. 
 *
 * 优势：
 * 1. 分离产品构建过程和表示：构建逻辑和产品表示分离, 提高灵活性. 
 * 2. 符合单一职责原则：建造者专注于构建过程, 指挥者负责构建逻辑顺序. 
 * 3. 易于扩展：可以通过添加新的建造者类, 支持构建不同类型的产品. 
 *
 * 缺点：
 * 1. 增加代码复杂性：需要引入多个建造者类和指挥者类. 
 * 2. 产品种类变化时, 可能需要修改建造者和指挥者. 
 *
 * 适用场景：
 * - 创建复杂对象的步骤较多且步骤顺序固定. 
 * - 需要为不同类型的产品提供统一的构建接口. 
 * - 希望通过分步构造的方式简化代码逻辑. 
 */

// 产品类
class Product {
private:
    std::string part_1;
    std::string part_2;

public:
    void set_part_1(const std::string& part_1) {
        this->part_1 = part_1;
    }
    void set_part_2(const std::string& part_2) {
        this->part_2 = part_2;
    }
    void show() const {
        std::cout << "Product: " << part_1 << " " << part_2 << std::endl;
    }
};

// 建造者抽象类
class Builder {
public:
    virtual void build_part() = 0;
    virtual std::unique_ptr<Product> get_result() = 0;
    virtual ~Builder() = default;
};

// 具体建造者类
class Builder_A : public Builder {
private:
    std::unique_ptr<Product> product_;

public:
    Builder_A() : product_(std::make_unique<Product>()) {
    }

    void build_part() override {
        product_->set_part_1("part_1_A");
        product_->set_part_2("part_2_A");
    }

    std::unique_ptr<Product> get_result() override {
        return std::move(product_);
    }
};

// 指挥者类
class Director {
private:
    Builder& builder_;

public:
    explicit Director(Builder& builder) : builder_(builder) {
    }

    void construct() {
        builder_.build_part();
    }
};

int main(int argc, char* argv[]) {
    // 创建建造者和指挥者
    Builder_A builder_a;
    Director director(builder_a);

    // 构造产品
    director.construct();

    // 获取产品结果并展示
    std::unique_ptr<Product> product = builder_a.get_result();
    product->show();

    return 0;
}
