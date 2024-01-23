#include <bits/stdc++.h>
#include <QDialog>
#include <QFormLayout>
#include <QLineEdit>
#include <QObject>
#include <QDialogButtonBox>
#include <qlabel.h>

#include "../JsonChange/jsonchange.h"

//传入一个map构成的需要信息序列 弹出弹窗 处理并且回收

class My_Multiple_Info{
public:
    QDialog *mydialog;
    QFormLayout * myform;
    QDialogButtonBox * buttonBox;
    std::vector<QLineEdit * >QLineEdit_list;
    std::vector<QString * > qs_list;
public:
    std::string run();
public:
    My_Multiple_Info(QWidget * base, std::string s , std::string titleinfo="请输入:");
    ~My_Multiple_Info();
};
