#include "loggeragent.h"
#include "ui_loggeragent.h"

LoggerAgent::LoggerAgent( QWidget *parent ) :
    QDialog( parent ),
    ui( new Ui::LoggerAgent )
{
    ui->setupUi( this );
}

LoggerAgent::~LoggerAgent( )
{
    delete ui;
}

void LoggerAgent::on_pushButton_lms_readon_2_clicked( )
{
    Logger::log( BCD::UR::DISCONNECT, ui->lineEdit_urmsg->text().simplified() );
}

void LoggerAgent::on_pushButton_sp_start_clicked( )
{
    Logger::log( BCD::SP20000C::TURN_ON );
}

void LoggerAgent::on_pushButton_sp_stop_clicked( )
{
    Logger::log( BCD::SP20000C::TURN_OFF );
}

void LoggerAgent::on_pushButton_lms_readon_clicked( )
{
    Logger::log( BCD::LMS::TURN_ON_READING );
}

void LoggerAgent::on_pushButton_lms_readoff_clicked( )
{
    Logger::log( BCD::LMS::TURN_OFF_READING );
}

void LoggerAgent::on_pushButton_savelog_clicked( )
{
    Logger::save( );
}

void LoggerAgent::on_pushButton_savelog3_clicked( )
{
    Logger::save( BCD::ActionInfo::LEVEL3 );
}

void LoggerAgent::on_pushButton_test_clicked( )
{
    // works
    Logger::log( BCD::LMS::TURN_ON_READING, "turn on reading" );
    Logger::log( BCD::LMS::TURN_OFF_READING );

    for ( int i = 0; i < 20; ++i ) {
        Logger::log( i ) << i;
    }
    Logger::log( ) << "default";
}

void batchLogging( bool turnOn, const QString &message )
{
    int i = 0;
    while (++i < 10000) {
        Logger::log( turnOn
                     ? BCD::LMS::TURN_ON_READING
                     : BCD::LMS::TURN_OFF_READING,
                     QString().sprintf( "%s-%05d",
                                        qPrintable( message ), i) );
    }
}

void LoggerAgent::on_pushButton_thread1_clicked( )
{
    static int i = 0;
    boost::thread log( batchLogging,
                       true,
                       QString().sprintf( "thread1-%02d", ++i ) );
    log.detach();
}

void LoggerAgent::on_pushButton_thread2_clicked( )
{
    static int i = 0;
    boost::thread log( batchLogging,
                       false,
                       QString().sprintf( "thread2-%02d", ++i ));
    log.detach();
}

void LoggerAgent::on_pushButton_refresh_clicked( )
{
    Logger::save();
}