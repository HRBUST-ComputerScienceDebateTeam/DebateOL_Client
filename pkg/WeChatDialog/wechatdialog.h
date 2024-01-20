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
public:
    explicit WeChatDialog(QWidget *parent = nullptr);
    ~WeChatDialog();

    void closeEvent(QCloseEvent *event);
private:
    Ui::WeChatDialog *ui;
};

#endif // WECHATDIALOG_H
