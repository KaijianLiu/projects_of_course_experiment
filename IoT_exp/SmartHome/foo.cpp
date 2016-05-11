#include "foo.h"
#include "ui_foo.h"

Foo::Foo(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Foo)
{
    ui->setupUi(this);
}

Foo::~Foo()
{
    delete ui;
}
