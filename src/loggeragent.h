#ifndef LOGGERAGENT_H
#define LOGGERAGENT_H

#include "logger.h"
#include <QDialog>
#include <QStandardItem>
#include <QTextCodec>
#include <boost/thread.hpp>
#include <boost/thread/mutex.hpp>
#include <boost/thread/condition.hpp>
#include <boost/chrono/chrono.hpp>

namespace Ui {
class LoggerAgent;
}

class LoggerAgent : public QDialog
{
    Q_OBJECT

public:
    explicit LoggerAgent( QWidget *parent = 0 );
    ~LoggerAgent( );

private slots:
    void on_pushButton_lms_readon_2_clicked( );
    void on_pushButton_sp_start_clicked( );
    void on_pushButton_sp_stop_clicked( );
    void on_pushButton_lms_readon_clicked( );
    void on_pushButton_lms_readoff_clicked( );
    void on_pushButton_savelog_clicked( );
    void on_pushButton_savelog3_clicked( );
    void on_pushButton_test_clicked( );
    void on_pushButton_thread1_clicked( );
    void on_pushButton_thread2_clicked( );
    void on_pushButton_refresh_clicked( );

private:
    Ui::LoggerAgent *ui;
};

#endif // LOGGERAGENT_H
