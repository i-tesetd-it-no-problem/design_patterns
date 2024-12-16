/**
 * @file main.cpp
 * @author wenshuyu (wsy2161826815@163.com)
 * @brief 组合模式
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
#include <algorithm>

/**
 * 组合模式的用途：
 * 组合模式(Composite
 * Pattern)是一种结构型设计模式, 用于将对象组合成树形结构以表示“部分-整体”的层次结构. 
 * 通过组合模式, 客户端可以一致地对待单个对象和对象的组合, 无需关注它们的具体实现细节. 
 *
 * 用途：
 * 1. 表示树形结构, 例如文件系统、组织结构、UI 元素等. 
 * 2. 需要统一处理单个对象和组合对象的场景. 
 * 3. 希望通过递归方式对对象结构进行操作. 
 *
 * 关键角色：
 * - **Component(抽象基类)**：
 *   定义叶子和组合对象的统一接口, 例如 `add`、`remove`、`display`. 
 * - **Leaf(叶子节点)**：
 *   实现 Component 接口, 表示树结构中的基本单元, 不支持添加或移除子节点. 
 * - **Composite(组合节点)**：
 *   实现 Component
 * 接口, 维护一个子组件的列表, 支持对子组件的操作(如添加、移除、显示). 
 *
 * 示例中的实现：
 * 1. `Component`：
 *    - 定义了树形结构的抽象接口. 
 *    - 提供了通用方法 `add`、`remove` 和纯虚方法 `display`. 
 * 2. `Leaf`：
 *    - 表示叶子节点, 不包含子节点. 
 *    - 实现了 `display` 方法, 用于显示当前节点信息. 
 * 3. `composite`：
 *    - 表示组合节点, 维护子节点的集合. 
 *    - 实现了 `add` 和 `remove` 方法, 用于管理子节点. 
 *    - 通过递归方式实现 `display`, 显示当前节点和其所有子节点. 
 * 4. 主函数：
 *    - 创建一个树形结构, 其中包含根节点、多个叶子节点和多个组合节点. 
 *    - 演示了 `add`、`remove` 和 `display` 方法的使用, 展示组合模式的灵活性. 
 *
 * 优势：
 * 1. 简化客户端代码：客户端无需区分单个对象和组合对象, 统一通过 Component
 * 接口操作. 
 * 2. 支持递归组合：可以轻松构建和操作复杂的树形结构. 
 * 3. 符合开闭原则：可以通过扩展 Component
 * 接口新增叶子或组合类型, 而无需修改现有代码. 
 *
 * 缺点：
 * 1. 可能导致系统复杂性增加：需要引入多个类来表示树形结构中的节点. 
 * 2. 对类型安全的支持有限：客户端需要自行确保对叶子节点和组合节点的正确操作. 
 *
 * 适用场景：
 * - 希望表示对象的部分-整体层次结构. 
 * - 希望客户端可以统一操作单个对象和组合对象. 
 * - 需要通过递归方式对对象进行操作. 
 */

// 抽象基类
class Component {
protected:
    std::string name;

    std::string repeatable_layer(int depth) const {
        return std::string(depth, '-');
    }

public:
    explicit Component(const std::string& name) : name(name) {
    }

    virtual ~Component() = default;

    virtual void add(std::shared_ptr<Component> component) {
        std::cout << "Can not add to this component" << std::endl;
    }

    virtual void remove(std::shared_ptr<Component> component) {
        std::cout << "Can not remove from this component" << std::endl;
    }

    virtual void display(int depth) const = 0;
};

// 叶子节点
class Leaf : public Component {
public:
    explicit Leaf(const std::string& name) : Component(name) {
    }

    void display(int depth) const override {
        std::cout << repeatable_layer(depth) << name << std::endl;
    }
};

// 组合节点
class composite : public Component {
private:
    std::vector<std::shared_ptr<Component>> children;

public:
    explicit composite(const std::string& name) : Component(name) {
    }

    void add(std::shared_ptr<Component> component) override {
        children.push_back(component);
    }

    void remove(std::shared_ptr<Component> component) override {
        auto it = std::find(children.begin(), children.end(), component);
        if (it != children.end()) {
            children.erase(it);
        } else {
            std::cout << "Component not found to remove" << std::endl;
        }
    }

    void display(int depth) const override {
        std::cout << repeatable_layer(depth) << name << std::endl;
        for (auto& child: children) {
            child->display(depth + 2);
        }
    }
};

int main(int argc, char* argv[]) {
    auto root = std::make_shared<composite>("root");
    root->add(std::make_shared<Leaf>("leafA"));
    root->add(std::make_shared<Leaf>("leafB"));

    auto compositeX = std::make_shared<composite>("compositeX");
    compositeX->add(std::make_shared<Leaf>("leafX1"));
    compositeX->add(std::make_shared<Leaf>("leafX2"));
    root->add(compositeX);

    auto compositeY = std::make_shared<composite>("compositeY");
    compositeY->add(std::make_shared<Leaf>("leafY1"));
    compositeY->add(std::make_shared<Leaf>("leafY2"));
    root->add(compositeY);

    root->display(0);

    std::cout << "Remove leafA" << std::endl;
    root->remove(std::make_shared<Leaf>("leafX1"));
    root->display(1);

    return 0;
}
