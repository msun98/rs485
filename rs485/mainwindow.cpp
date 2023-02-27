#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
//    , m_serialPort(new QSerialPort(this))
{
    ui->setupUi(this);

    m_serialPort = new QSerialPort(this);

//    fillPortsInfo();

    connect(m_serialPort, &QSerialPort::readyRead, this, &MainWindow::readData);
    connect(m_serialPort, &QSerialPort::errorOccurred, this, &MainWindow::handleError);

}

MainWindow::~MainWindow()
{
    delete ui;
}

//void MainWindow::fillPortsInfo()
//{
//    ui->comboBox->clear();

//    const auto infos = QSerialPortInfo::availablePorts(); // 시리얼 포트 정보 이용가능하도록
//    for(const QSerialPortInfo &info : infos) {
//        ui->comboBox->addItem(info.portName()); // 콤보박스에 시리얼포트 정보 받아온 이름을 붙여넣는다.
//    }
//}

void MainWindow::on_btnConnect_clicked()
{
    // 시리얼 설정 코드
    std::cout<<"workindlnd"<<std::endl;
    m_serialPort->setPortName("/dev/ttyUSB0"); // 포트 이름 지정
    m_serialPort->setBaudRate(QSerialPort::Baud9600); // baud: 초당 신호(siganl) 요소의 수 , 예) 하나의 버드에 2bit 있다면 1Baud 동안 2bit 전송 됨
    m_serialPort->setDataBits(QSerialPort::Data8); // dataBits
    m_serialPort->setParity(QSerialPort::NoParity); // 정보 전달 과정에 오류가 생겼는지 검사하기 위한 것
    m_serialPort->setStopBits(QSerialPort::OneStop); // 포트를 열기전에 set 또는 success 하면 return true로 반환된다.
    m_serialPort->setFlowControl(QSerialPort::NoFlowControl); // 흐름제어
    if (m_serialPort->open(QIODevice::ReadWrite)) { //시리얼 장치 연 후 작업들


        ui->btnConnect->setEnabled(false);
        std::cout<<"open"<<std::endl;
        ui->btnDisConnect->setEnabled(true);
    }
    else {
        std::cout<<"ERROR"<<std::endl;
//        QMessageBox::critical(this, tr("Error"), m_serialPort->errorString());
    }
}

void MainWindow::on_btnDisConnect_clicked()
{
    if (m_serialPort->isOpen()) // 시리얼 포트 열렸으면
        m_serialPort->close(); // 시리얼 닫아라
    ui->btnConnect->setEnabled(true);
    ui->btnDisConnect->setEnabled(false);
}

QString str;
float distance;

uchar stringUltra;

void MainWindow::readData()
{

    QByteArray serialData = m_serialPort->readAll();
    uchar *_buf = (uchar*)serialData.data();

//    std::cout<<(int)_buf[0]<<std::endl;
//    std::cout<<(int)_buf[1]<<std::endl;
//    std::cout<<(int)_buf[2]<<std::endl;
//    std::cout<<(int)_buf[3]<<std::endl;

    uchar data[10];

    if(_buf[0] == 0xFF)
    {
        for(int i=0;i<4;i++)
        {
            qDebug() << serialData;
            data[i]=(int)_buf[i];
            std::cout<<(int)data[i]<<std::endl;
        }
    }

    if(data[0]==0xff)
      {
        int sum;
        sum = (data[0]+data[1]+data[2])&0x00FF;
        if(sum==data[3])
        {
          distance=(data[1]<<8)+data[2];
          if(distance>30)
            {
             qDebug()<<"distance="<<distance/10<<"cm";
             ui->le_value->setText(QString::number(distance/10));
            }
          else
           {
             qDebug()<<"Below the lower limit";
           }
        }
        else
        {
            qDebug()<<"ERROR";
       }
       usleep(100);
    }


//     int i = 1;
//     std::cout<<"..............."<<std::endl;
//     for(auto & elem : _buf)
//     {
//         std::cout<<i<<":"<<int(elem)<<std::endl;
//         i++;
//     }
//     std::cout<<"..............."<<std::endl;

//     std::cout<<send_byte.size()<<std::endl;


//    qDebug() << serialData;
//    uchar sedata;
//    memcpy(&sedata, serialData,5);
//    qDebug()<<sedata;


//    QString string(serialData);

//    for(int i=0; i < serialData.length(); i++)
//    {
//        uchar sedata;
//        memcpy(&sedata, serialData, 3);

//        std::cout<<sedata<<std::endl;

////        printf("%d\n", (int)serialData[i]);// qbytearray 로 불러온 데이터 printf 로 받기 위함.￣
//    }

//    std::cout<<serialData.toHex()<<std::endl;
//    std::string serialData_string = std::string(serialData);

//     memcpy(&stringUltra, serialData, 4);



//    if (stringUltra == 0xff)
//    {
//        for(int i=0;i<4;i++)
//         {
//           ultraData[i]=stringUltra;
////           std::cout<< std::hex << stringUltra<<std::endl;
//           printf("%.2X", stringUltra);

//         }

//    }

//    qDebug() << serialData;


}


void MainWindow::handleError(QSerialPort::SerialPortError error)
{
    if (error == QSerialPort::ResourceError) {
        std::cout<<"Error"<<std::endl;
        on_btnDisConnect_clicked();
    }
}

void MainWindow::on_write_clicked()
{
    m_serialPort->write("ddddddddd");
}
