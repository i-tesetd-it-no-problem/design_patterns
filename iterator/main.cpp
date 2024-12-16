/**
 * @file main.cpp
 * @author 
 * @brief 迭代器模式
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
 */

#include <iostream>
#include <memory>
#include <string>
#include <vector>

/**
 * 迭代器模式的用途：
 * 迭代器模式(Iterator Pattern)是一种行为型设计模式, 用于顺序访问聚合对象中的元素, 而不暴露其内部表示. 
 * 该模式将遍历逻辑与聚合对象的实现分离, 通过提供统一的接口, 使得不同类型的聚合对象可以使用相同的迭代方式. 
 *
 * 用途：
 * 1. 提供统一的遍历接口：不需要了解对象的内部结构即可顺序访问其元素. 
 * 2. 支持多种遍历策略：通过不同的迭代器实现, 可以灵活定义遍历规则. 
 * 3. 简化代码逻辑：将遍历操作封装到迭代器中, 减少重复代码. 
 *
 * 关键角色：
 * - **Iterator(迭代器接口)**：定义用于遍历聚合对象的方法(如 `first`、`next`、`isDone`、`currentItem`). 
 * - **ConcreteIterator(具体迭代器)**：实现迭代器接口, 维护遍历状态. 
 * - **Aggregate(聚合接口)**：定义创建迭代器的接口. 
 * - **ConcreteAggregate(具体聚合类)**：实现聚合接口, 并存储集合数据. 
 *
 * 
 * 优势：
 * 1. 统一遍历接口：适用于各种聚合结构(如数组、链表、树等). 
 * 2. 遍历与实现分离：聚合类只负责数据管理, 迭代器负责遍历. 
 * 3. 灵活扩展：可以通过不同的迭代器实现多种遍历逻辑(如正序、逆序、过滤等). 
 *
 * 缺点：
 * 1. 类数量增加：每种聚合结构都需要一个对应的迭代器. 
 * 2. 性能开销：迭代器的状态管理可能增加额外的开销. 
 *
 * 适用场景：
 * - 需要访问聚合对象的内容, 而不希望暴露其内部结构. 
 * - 需要支持多种遍历方式. 
 * - 聚合对象的结构可能变化, 但遍历逻辑需要保持一致. 
 */


// 迭代器接口
template <typename T>
class Iterator {
public:
    virtual ~Iterator() = default;
    virtual T first() = 0;
    virtual T next() = 0;
    virtual bool isDone() const = 0;
    virtual T currentItem() const = 0;
};

// 聚集接口
template <typename T>
class Aggregate {
public:
    virtual ~Aggregate() = default;
    virtual std::unique_ptr<Iterator<T>> create_iterator() = 0;
};

// 具体聚集类
template <typename T>
class ConcreteAggregate : public Aggregate<T> {
private:
    std::vector<T> items;

public:
    // 创建迭代器
    std::unique_ptr<Iterator<T>> create_iterator() override;

    int count() const {
        return items.size();
    }

    T get_item(int index) const {
        if (index >= 0 && index < count()) {
            return items[index];
        }
        throw std::out_of_range("Index out of bounds");
    }

    void set_item(const T& item) {
        items.push_back(item);
    }
};

// 具体迭代器类
template <typename T>
class ConcreteIterator : public Iterator<T> {
private:
    ConcreteAggregate<T>* aggregate;
    int current = 0;

public:
    explicit ConcreteIterator(ConcreteAggregate<T>* concreteAggregate) :
        aggregate(concreteAggregate) {};

    T first() override {
        current = 0;
        if (!isDone()) {
            return aggregate->get_item(current);
        }
        throw std::out_of_range("No items in aggregate");
    }

    T next() override {
        current++;
        if (!isDone()) {
            return aggregate->get_item(current);
        }
        throw std::out_of_range("Iterator out of range");
    }

    bool isDone() const override {
        return current >= aggregate->count();
    }

    T currentItem() const override {
        if (!isDone()) {
            return aggregate->get_item(current);
        }
        throw std::out_of_range("Iterator out of range");
    }
};

template <typename T>
std::unique_ptr<Iterator<T>> ConcreteAggregate<T>::create_iterator() {
    return std::make_unique<ConcreteIterator<T>>(this);
}

int main(int argc, char* argv[]) {

    ConcreteAggregate<std::string> bus;

    bus.set_item("Big Bird");
    bus.set_item("Small Dish");
    bus.set_item("Luggage");
    bus.set_item("Foreigner");

    auto iterator = bus.create_iterator();
    try {
        while (!iterator->isDone()) {
            std::cout << iterator->currentItem() << std::endl;
            iterator->next();
        }
    } catch (const std::exception& e) {
        std::cerr << "Error: " << e.what() << std::endl;
    }

    return 0;
}
