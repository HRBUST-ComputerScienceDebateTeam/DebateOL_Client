#include "dialog.h"
#include "./ui_dialog.h"

Dialog::Dialog(QWidget *parent)
    : QDialog(parent)
    , ui(new Ui::Dialog)
{
    ui->setupUi(this);

    m_pAudioRead = new AudioRead;

    m_pAudioWrite = new AudioWrite;

    connect(m_pAudioRead,SIGNAL(SIG_audioFrame(QByteArray))
            ,m_pAudioWrite,SLOT(slot_playAudio(QByteArray)));
}

Dialog::~Dialog()
{
    delete ui;
}


void Dialog::on_pb_start_clicked()
{
    m_pAudioRead->start();
}


void Dialog::on_pb_pause_clicked()
{
    m_pAudioRead->pause();
}

