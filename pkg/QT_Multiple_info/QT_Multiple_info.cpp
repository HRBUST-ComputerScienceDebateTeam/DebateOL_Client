#include "./QT_Multiple_info.h"

My_Multiple_Info::My_Multiple_Info(QWidget * base ,std::string s , std::string titleinfo){
    mydialog = new QDialog(base);
    myform = new QFormLayout(mydialog);

    myform->addRow(new QLabel(QString::fromStdString(titleinfo)));
    std::map<std::string , std::string> infomp =  JsonstringToMap(s);


    int i = 0;
    for(auto &it: infomp){
        QLineEdit_list.push_back(new(QLineEdit));
        qs_list.push_back(new QString(QString::fromStdString(it.first)));
        myform->addRow(*qs_list[i], QLineEdit_list[i]);
        i++;
    }
    buttonBox = new QDialogButtonBox(QDialogButtonBox::Ok | QDialogButtonBox::Cancel,
                               Qt::Horizontal, mydialog);
    myform->addRow(buttonBox);
    QObject::connect(buttonBox, SIGNAL(accepted()), mydialog, SLOT(accept()));
    QObject::connect(buttonBox, SIGNAL(rejected()), mydialog, SLOT(reject()));
}
My_Multiple_Info::~My_Multiple_Info(){
    //回收
    if(buttonBox)
        delete buttonBox;
    for(int i = 0 ; i<QLineEdit_list.size();i++){
        if(QLineEdit_list[i]) delete (QLineEdit_list[i]);
    }
    for(int i = 0 ; i<qs_list.size();i++){
        if(qs_list[i]) delete (qs_list[i]);
    }
    if(myform)
        delete myform;
    if(mydialog)
        delete mydialog;
}
std::string My_Multiple_Info::run(){
    if (mydialog->exec() == QDialog::Accepted) {
        // Do something here
        std::map<std::string , std::string>mp;
        for(int i = 0;i<qs_list.size();i++){
            mp[(*qs_list[i]).toStdString()] = QLineEdit_list[i]->text().toStdString();
        }
        return MapToJsonstring(mp);
    }else{
        // 取消返回空
        return "";
    }
    return "";
}
