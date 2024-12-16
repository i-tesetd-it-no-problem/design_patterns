#include "qfsm.hpp"
#include <iostream>

class MyFSM : public QFsm<MyFSM> {
public:
    enum new_event {
        Q_TIMEOUT_SIG = Q_INIT_SIG + 1,
    };

    QState state_a(const QEvent& e) {
        switch (e.sig) {
            case Q_ENTRY_SIG:
                std::cout << "Entering A\n";
                break;
            case Q_EXIT_SIG:
                std::cout << "Exiting A\n";
                break;
            case Q_TIMEOUT_SIG:
                std::cout << "Timeout A\n";
                return Q_TRAN(&MyFSM::state_b);
            default:
                break;
        }
        return Q_HANDLED();
    }

    QState state_b(const QEvent& e) {
        switch (e.sig) {
            case Q_ENTRY_SIG:
                std::cout << "Entering B\n";
                break;
            case Q_EXIT_SIG:
                std::cout << "Exiting B\n";
                break;
            case Q_TIMEOUT_SIG:
                std::cout << "Timeout B\n";
                return Q_TRAN(&MyFSM::state_a);
            default:
                break;
        }
        return Q_HANDLED();
    }

    static const QEvent my_event[];
};

const QEvent MyFSM::my_event[] = {
    { (QSignal)Q_TIMEOUT_SIG },
};

int main(int argc, char* argv[]) {
    MyFSM fsm;
    fsm.init(&MyFSM::state_a);

    for (int i = 0; i < 10; i++) {
        fsm.dispatch(MyFSM::my_event[0]);
    }

    return 0;
}
