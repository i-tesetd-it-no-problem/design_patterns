/**
 * @file main.cpp
 * @author wenshuyu (wsy2161826815@163.com)
 * @brief 备忘录模式
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
#include <string>

/**
 * 备忘录模式的用途：
 * 备忘录模式(Memento
 * Pattern)是一种行为型设计模式, 用于保存对象的状态, 以便在未来可以恢复到之前的状态. 
 * 它通过在不暴露对象实现细节的前提下, 捕获并保存其内部状态, 从而实现状态的快照与恢复. 
 *
 * 用途：
 * 1.
 * 状态快照：需要对某些关键时刻的对象状态进行保存和回滚, 例如游戏存档、文档撤销功能等. 
 * 2. 数据恢复：系统崩溃或发生错误时, 通过备忘录恢复到安全状态. 
 * 3. 状态对比：保存多个状态快照, 用于比较或分析对象状态的变化. 
 *
 * 关键角色：
 * - **Originator(发起者)**：需要保存其状态的对象, 并能够创建和恢复备忘录. 
 * - **Memento(备忘录)**：存储发起者的内部状态, 供发起者在需要时恢复. 
 * - **CareTaker(管理者)**：负责存储和管理备忘录, 但不操作其内容. 
 *
 * 示例中的实现：
 * 1. `Originator` 类：
 *    - 内部包含当前状态的表示(`std::string state`). 
 *    -
 * 提供了创建备忘录(`create_memento`)和恢复备忘录(`restore_memento`)的方法. 
 * 2. `Memento` 类：
 *    - 嵌套在 `Originator` 中, 用于存储 `Originator` 的状态. 
 *    - 提供了获取状态(`getState`)的接口. 
 * 3. `CareTaker` 类：
 *    - 存储 `Memento` 的实例. 
 *    - 提供了保存和获取备忘录的接口. 
 * 4. 主函数演示：
 *    - 保存发起者的状态到备忘录, 改变状态后通过管理者恢复之前的状态. 
 *
 * 优势：
 * 1. 状态封装：将状态的存储和操作隔离, 发起者状态的私有信息不会暴露给外界. 
 * 2. 简化撤销功能：通过存储状态快照, 轻松实现状态回滚. 
 * 3. 便于多版本管理：可以保存对象的多个状态快照. 
 *
 * 缺点：
 * 1. 内存开销：保存多个状态时, 可能占用较多内存资源. 
 * 2. 实现复杂：需要管理状态存储和恢复逻辑, 并防止备忘录被外界修改. 
 *
 * 适用场景：
 * - 需要支持撤销操作的系统(如文本编辑器). 
 * - 需要恢复历史状态的应用(如游戏存档、事务处理). 
 * - 需要对状态变化进行跟踪和管理. 
 */

// 发起者类
class Originator {
private:
    std::string state;

public:
    // 备忘录类
    class Memento {
    private:
        std::string state;

    public:
        Memento(std::string state) : state(state) {
        }

        std::string getState() {
            return state;
        }
    };

    // 创建备忘录
    std::shared_ptr<Memento> create_memento() {
        return std::make_shared<Memento>(this->state);
    }

    // 恢复备忘录
    void restore_memento(std::shared_ptr<Memento> memento) {
        this->state = memento->getState();
    }

    // 显示当前状态
    void show_state() {
        std::cout << "Current state: " << this->state << std::endl;
    }

    // 设置状态
    void set_state(std::string state) {
        this->state = state;
    }

    // 获取状态
    std::string get_state() {
        return this->state;
    }
};

// 管理者类
class CareTaker {
private:
    std::shared_ptr<Originator::Memento> memento;

public:
    // 获取备忘录
    std::shared_ptr<Originator::Memento> get_memento() const {
        return memento;
    }

    // 设置备忘录
    void set_memento(std::shared_ptr<Originator::Memento> memento) {
        this->memento = memento;
    }
};

int main(int argc, char* argv[]) {

    // 设置初始状态
    Originator originator;
    originator.set_state("On");
    originator.show_state();

    // 管理者通过备忘录记录当前状态
    CareTaker care_taker;
    care_taker.set_memento(originator.create_memento());

    // 状态发生变化
    originator.set_state("Off");
    originator.show_state();

    // 管理者恢复之前的状态
    originator.restore_memento(care_taker.get_memento());
    originator.show_state();

    return 0;
}
