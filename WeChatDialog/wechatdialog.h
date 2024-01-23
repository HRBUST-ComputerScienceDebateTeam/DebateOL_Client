#ifndef WECHATDIALOG_H
#define WECHATDIALOG_H

#include <QDialog>

namespace Ui {
class WeChatDialog;
}

class WeChatDialog : public QDialog
{
    Q_OBJECT
signals:
    void SIG_closechat();
    void SIG_createRoom(std::string s);
    void SIG_joinRoom(std::string s);
public:
    explicit WeChatDialog(QWidget *parent = nullptr);
    ~WeChatDialog();

    void closeEvent(QCloseEvent *event);

    void setInfo(QString name,QString name_style,int icon =1);
private slots:
    void on_pb_create_clicked();

    void on_pb_join_clicked();

private:
    Ui::WeChatDialog *ui;
};

#endif // WECHATDIALOG_H
