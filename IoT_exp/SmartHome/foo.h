#ifndef FOO_H
#define FOO_H

#include <QWidget>

namespace Ui {
class Foo;
}

class Foo : public QWidget
{
    Q_OBJECT

public:
    explicit Foo(QWidget *parent = 0);
    ~Foo();

private:
    Ui::Foo *ui;
};

#endif // FOO_H
