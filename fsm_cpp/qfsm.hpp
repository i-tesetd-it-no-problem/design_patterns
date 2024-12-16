/**
 * @file qfsm.hpp
 * @author wenshuyu (wsy2161826815@163.com)
 * @brief 状态机模板类
 * @version 1.0
 * @date 2024-12-16
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

#ifndef _QFSM_HPP_
#define _QFSM_HPP_

typedef int QState;
typedef int QSignal;

struct QEvent {
    QSignal sig;
};

enum QEventResult {
    Q_EVENT_HANDLED = 0,
    Q_EVENT_IGNORED,
    Q_EVENT_TRAN,
};

#define Q_HANDLED() (Q_EVENT_HANDLED)
#define Q_IGNORED() (Q_EVENT_IGNORED)
#define Q_TRAN(target_) (this->m_state = (target_), Q_EVENT_TRAN)

enum QReservedSignal {
    Q_EMPTY_SIG = 0, // 空信号
    Q_ENTRY_SIG,     // 进入信号
    Q_EXIT_SIG,      // 退出信号
    Q_INIT_SIG,      // 初始化信号
};

template <class F>
class QFsm {
public:
    typedef QState (F::*QStateHandler)(const QEvent &);

    QFsm() : m_state(nullptr) {
    }

    void init(QStateHandler init_state) {
        m_state = init_state;
        (static_cast<F *>(this)->*m_state)(m_reserved_ev[Q_INIT_SIG]);
        (static_cast<F *>(this)->*m_state)(m_reserved_ev[Q_ENTRY_SIG]);
    }

    void dispatch(const QEvent &e) {
        if (!m_state)
            return;
        QStateHandler s = m_state;
        QState r = (static_cast<F *>(this)->*s)(e);
        if (r == Q_EVENT_TRAN) {
            (static_cast<F *>(this)->*s)(m_reserved_ev[Q_EXIT_SIG]);
            (static_cast<F *>(this)->*m_state)(m_reserved_ev[Q_ENTRY_SIG]);
        }
    }

protected:
    QStateHandler m_state;
    static const QEvent m_reserved_ev[];
};

template <class F>
const QEvent QFsm<F>::m_reserved_ev[] = {
    { (QSignal)Q_EMPTY_SIG },
    { (QSignal)Q_ENTRY_SIG },
    { (QSignal)Q_EXIT_SIG },
    { (QSignal)Q_INIT_SIG },
};

#endif /* _QFSM_HPP_ */
