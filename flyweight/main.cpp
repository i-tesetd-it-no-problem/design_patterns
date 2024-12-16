/**
 * @file main.cpp
 * @author wenshuyu (wsy2161826815@163.com)
 * @brief 享元模式
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
#include <unordered_map>

/**
 * 享元模式的用途：
 * 享元模式(Flyweight
 * Pattern)是一种结构型设计模式, 通过共享对象来减少内存使用并提高性能. 
 * 它适用于系统中存在大量相似对象, 且这些对象可以通过共享来减少内存消耗的场景. 
 * 享元模式将对象的状态分为**内部状态**(共享部分)和**外部状态**(不共享部分), 从而实现对象的复用. 
 *
 * 用途：
 * 1. 减少内存消耗：通过共享相同的对象实例来避免重复存储. 
 * 2. 提高系统性能：减少对象的创建和销毁操作, 优化资源使用. 
 * 3. 提高管理效率：将共享对象集中管理, 减少对象分散带来的复杂性. 
 *
 * 适用场景：
 * - 系统中有大量相似对象. 
 * - 对象中的状态可以分为内部状态和外部状态. 
 * - 需要节约内存并共享对象的场景. 
 *
 * 示例：
 * 在本代码中：
 * - `FlyWeight`是享元抽象基类, 定义了一个`operation`方法来接受外部状态. 
 * - `ConcreteFlyWeight`是具体享元类, 实现了抽象类的方法, 表示共享的具体对象. 
 * - `UnsharedConcreteFlyWeight`是非共享享元类, 表示需要独立存储的对象. 
 * - `FlyWeightFactory`是享元工厂类, 负责管理和提供共享对象. 
 *
 * 优势：
 * - 减少内存使用, 通过共享`ConcreteFlyWeight`对象来复用相同的状态. 
 * - 使用享元工厂`FlyWeightFactory`确保每个共享对象只有一份实例, 避免重复创建. 
 * - 客户端通过传递不同的外部状态动态调整共享对象的行为, 而无需创建新的对象. 
 */

class FlyWeight {
public:
    virtual ~FlyWeight() = default;

    // 接受一个外部状态
    virtual void operation(int extrinsicState) = 0;
};

class ConcreteFlyWeight : public FlyWeight {
    void operation(int extrinsicState) override {
        std::cout << "ConcreteFlyWeight: " << extrinsicState << std::endl;
    }
};

// 非共享
class UnsharedConcreteFlyWeight : public FlyWeight {
    void operation(int extrinsicState) override {
        std::cout << "UnsharedConcreteFlyWeight: " << extrinsicState
                  << std::endl;
    }
};

class FlyWeightFactory {
private:
    std::unordered_map<std::string, std::shared_ptr<FlyWeight>> flyweights;

public:
    std::shared_ptr<FlyWeight> get_flyweight(const std::string& key) {
        if (flyweights.find(key) == flyweights.end()) {
            flyweights[key] = std::make_shared<ConcreteFlyWeight>();
        }
        return flyweights[key];
    }
};

int main(int argc, char* argv[]) {
    int extrinsicState = 22;

    FlyWeightFactory factory;

    std::shared_ptr<FlyWeight> fx = factory.get_flyweight("x");
    fx->operation(--extrinsicState);

    std::shared_ptr<FlyWeight> fy = factory.get_flyweight("y");
    fy->operation(--extrinsicState);

    std::shared_ptr<FlyWeight> fz = factory.get_flyweight("z");
    fz->operation(--extrinsicState);

    std::shared_ptr<FlyWeight> uf =
        std::make_shared<UnsharedConcreteFlyWeight>();
    uf->operation(--extrinsicState);

    return 0;
}
