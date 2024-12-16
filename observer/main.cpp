/**
 * @file main.cpp
 * @author wenshuyu (wsy2161826815@163.com)
 * @brief 观察者模式
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
#include <vector>
#include <memory>
#include <string>
#include <algorithm>

/**
 * 观察者模式的用途：
 * 观察者模式(Observer
 * Pattern)是一种行为型设计模式, 定义了一种一对多的依赖关系, 
 * 当一个对象(主题)发生变化时, 所有依赖它的对象(观察者)都会自动收到通知并更新. 
 * 观察者模式可以松耦合地实现对象间的通信. 
 *
 * 用途：
 * 1. 当对象间存在一对多依赖关系时, 使用观察者模式. 
 * 2. 当一个对象的改变需要通知其他对象, 但不知道具体有多少对象需要被通知. 
 * 3. 用于事件监听机制, 例如 GUI 系统中的事件驱动设计. 
 *
 * 关键角色：
 * - **Subject(主题)**：
 *   - 定义了观察者的管理接口, 如
 * `attach`(添加观察者)、`detach`(移除观察者)、`notify`(通知观察者). 
 * - **Observer(观察者)**：
 *   - 定义了更新接口, 具体观察者需要实现此接口. 
 * - **ConcreteSubject(具体主题)**：
 *   - 维护主题的状态, 并在状态改变时通知所有观察者. 
 * - **ConcreteObserver(具体观察者)**：
 *   - 实现更新接口, 获取主题的状态并同步到观察者. 
 *
 *
 * 优势：
 * 1. 解耦了主题和观察者：主题只依赖于观察者接口, 不需要了解观察者的具体实现. 
 * 2. 支持广播通信：主题通过 `notify` 方法通知所有注册的观察者. 
 * 3. 动态扩展性：可以在运行时添加或移除观察者. 
 *
 * 缺点：
 * 1. 如果观察者过多, 可能导致通知开销较大. 
 * 2. 观察者的更新顺序无法保证, 可能出现不一致的状态. 
 * 3. 如果主题和观察者之间存在循环依赖, 可能引发内存泄漏或栈溢出. 
 *
 * 适用场景：
 * - GUI 事件驱动(如按钮点击、窗口更新). 
 * - 发布-订阅系统(如新闻订阅、消息队列). 
 * - 数据模型和视图之间的同步更新. 
 */

// 抽象观察者
class Observer {
public:
    virtual ~Observer() = default;
    virtual void update(const std::string& state) = 0; // 接收状态更新
};

// 抽象主题
class Subject {
protected:
    std::vector<std::shared_ptr<Observer>> observers_; // 观察者列表

public:
    virtual ~Subject() = default;

    // 添加观察者
    void attach(const std::shared_ptr<Observer>& observer) {
        observers_.emplace_back(observer);
    }

    // 移除观察者
    void detach(const std::shared_ptr<Observer>& observer) {
        observers_.erase(
            std::remove_if(observers_.begin(), observers_.end(),
                           [&observer](const std::shared_ptr<Observer>& o) {
                               return o.get() == observer.get(); // 比较指针地址
                           }),
            observers_.end());
    }

    // 通知所有观察者
    void notify(const std::string& state) const {
        for (const auto& observer: observers_) {
            try {
                observer->update(state); // 调用每个观察者的更新方法
            } catch (const std::exception& e) {
                std::cerr << "Error notifying observer: " << e.what()
                          << std::endl;
            }
        }
    }
};

// 具体主题
class SubjectA : public Subject {
private:
    std::string subject_state; // 状态

public:
    // 获取状态
    const std::string& get_state() const {
        return subject_state;
    }

    // 设置状态并通知观察者
    void set_state(const std::string& state) {
        subject_state = state;
        notify(subject_state); // 通知观察者
    }
};

// 具体观察者
class ObserverA : public Observer {
private:
    std::string name;
    std::string state;

public:
    explicit ObserverA(const std::string& name) : name(name) {
    }

    void update(const std::string& state) override {
        this->state = state; // 更新观察者的状态
        std::cout << "ObserverA [" << name << "] updated state to: " << state
                  << std::endl;
    }

    const std::string& get_name() const {
        return name;
    }

    void set_name(const std::string& new_name) {
        name = new_name;
    }
};

// 主函数
int main(int argc, char* argv[]) {
    // 创建具体主题
    auto subject_a = std::make_shared<SubjectA>();

    // 创建观察者并注册到主题
    auto observer_a1 = std::make_shared<ObserverA>("observer_a1");
    auto observer_a2 = std::make_shared<ObserverA>("observer_a2");

    subject_a->attach(observer_a1);
    subject_a->attach(observer_a2);

    // 设置状态并自动通知观察者
    subject_a->set_state("state_a");

    // 修改观察者名称
    observer_a1->set_name("observer_a1_new");
    observer_a2->set_name("observer_a2_new");

    // 再次更新状态
    subject_a->set_state("state_b");

    // 移除观察者并测试
    subject_a->detach(observer_a1);
    subject_a->set_state("state_c");

    return 0;
}
