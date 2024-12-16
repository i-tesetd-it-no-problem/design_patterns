/**
 * @file main.cpp
 * @author wenshuyu (wsy2161826815@163.com)
 * @brief 代理模式
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
 * 代理模式的用途：
 * 代理模式(Proxy
 * Pattern)是一种结构型设计模式, 通过提供一个替代对象(代理对象)来控制对另一个对象的访问. 
 * 它可以为目标对象提供额外的功能, 例如延迟初始化、访问控制、日志记录等, 同时保持客户端与目标对象之间的接口一致. 
 *
 * 用途：
 * 1.
 * 控制访问：通过代理实现对真实对象的访问控制, 例如权限校验或对象生命周期管理. 
 * 2. 延迟加载：在需要时才创建真实对象, 从而提高系统性能和资源利用率. 
 * 3. 额外功能：在访问真实对象之前或之后, 添加额外的功能(如日志、统计等). 
 * 4. 网络代理：在分布式系统中, 通过代理访问远程对象. 
 *
 * 示例：
 * 在本代码中：
 * - `Subject`是抽象主题类, 定义了`request`接口. 
 * - `ReadSubject`是具体实现类, 表示需要代理的真实对象. 
 * -
 * `Proxy`是代理类, 通过内部持有`ReadSubject`对象的指针来实现对真实对象的访问. 
 *
 * 代理的作用：
 * -
 * 在`Proxy::request`方法中, 可以在调用真实对象的`request`方法之前或之后执行额外操作. 
 * -
 * 客户端通过代理对象调用接口, 而无需直接与真实对象交互, 从而实现对真实对象的保护和扩展. 
 *
 * 优势：
 * - 客户端代码无需修改即可通过代理增强功能, 增加了代码的灵活性. 
 * -
 * 实现了对象的分离和隔离, 避免客户端直接依赖真实对象, 提高了系统的可维护性和安全性. 
 */

// 抽象接口
class Image {
public:
    virtual ~Image() = default;
    virtual void display() = 0; // 显示图片
};

// 真实图片类
class RealImage : public Image {
private:
    std::string filename;

    void loadFromDisk() {
        std::cout << "Loading image from disk: " << filename << std::endl;
    }

public:
    explicit RealImage(const std::string& file) : filename(file) {
        loadFromDisk(); // 模拟图片从磁盘加载
    }

    void display() override {
        std::cout << "Displaying image: " << filename << std::endl;
    }
};

// 代理图片类
class ProxyImage : public Image {
private:
    std::shared_ptr<RealImage> realImage; // 实际图片对象
    std::string filename;

public:
    explicit ProxyImage(const std::string& file) : filename(file) {
    }

    void display() override {
        // 仅在需要时加载图片
        if (!realImage) {
            realImage = std::make_shared<RealImage>(filename);
        }
        realImage->display();
    }
};

// 客户端代码
int main(int argc, char* argv[]) {
    std::cout << "Creating ProxyImage (no actual image loaded yet)."
              << std::endl;
    ProxyImage proxyImage("example.jpg"); // 创建代理对象, 不加载图片

    std::cout << "\nDisplaying ProxyImage for the first time:" << std::endl;
    proxyImage.display(); // 第一次显示时加载图片

    std::cout << "\nDisplaying ProxyImage again:" << std::endl;
    proxyImage.display(); // 第二次显示直接复用已加载的图片

    return 0;
}
