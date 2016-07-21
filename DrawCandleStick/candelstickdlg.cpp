#include "candelstickdlg.h"
#include <ctime>

CandleStickDlg::CandleStickDlg(QWidget *parent)
{
    m_candleStickWidth = 5;
    m_candleStickHeight = 5;
    setGeometry(100, 100, 400, 400);

    int width=size().width();
    int height=size().height();

    pix = new QPixmap(width,height);
    pix->fill(Qt::white);

    // loadMarketData("D:\QT_Learning\testDrawCandleStick\marketData.txt");
    loadMarketData("D:/QT_Learning/build-testConsole-Desktop_Qt_5_6_0_MSVC2013_64bit-Debug/marketData1.txt");
    // setCursor(Qt::CrossCursor);
    // setCursorPosition();

//    scrollArea = new QScrollArea;
//    scrollArea->setWidget(this);
//    scrollArea->viewport()->setBackgroundRole(QPalette::Dark);
//    scrollArea->viewport()->setAutoFillBackground(true);
//    scrollArea->setWindowTitle("Candle Stick Drawer");
}

CandleStickDlg::~CandleStickDlg()
{
}

void CandleStickDlg::loadMarketData(QString fileName)
{
    QFile f(fileName);
    if(!f.open(QIODevice::ReadOnly | QIODevice::Text))
    {
        qDebug() << "Open market data failed.";
        return;
    }

    QTextStream txtInput(&f);
    QString lineStr;

    while(!txtInput.atEnd())
    {
        lineStr = txtInput.readLine();
        QStringList strList = lineStr.split(" ");
        QString dateTime = strList[0];
        double open, highest, lowest, close;
        open = strList[1].toDouble();
        highest = strList[2].toDouble();
        lowest = strList[3].toDouble();
        close = strList[4].toDouble();
        m_vecMarketDatas.push_back(MarketPrice(dateTime, open, highest, lowest, close));
    }

    f.close();
}

void CandleStickDlg::showCandleStick(QPainter& painter, int index, double open,
                                     double high, double low, double close)
{
    double up_side, down_side;

    QBrush qBrush;

    if(open < close)
    {
        up_side = close;
        down_side = open;
        painter.setPen(Qt::red);
        qBrush = QBrush(Qt::red);
    }
    else
    {
        up_side = open;
        down_side = close;
        painter.setPen(Qt::green);
        qBrush = QBrush(Qt::green);
    }

    int width = this->width()/13;
    m_candleStickWidth = width*0.4;

    int move_downward = (this->height()/2)*0.55;
    int move_rightward = this->width()/10;

    painter.drawLine(this->x() + move_rightward + index*width + 0.5*m_candleStickWidth, this->y() + move_downward,
                     this->x() + move_rightward + index*width + 0.5*m_candleStickWidth, this->y() + move_downward - high + up_side);
    painter.drawLine(this->x() + move_rightward + index*width + 0.5*m_candleStickWidth,
                     this->y() + move_downward + (up_side - down_side),
                     this->x() + move_rightward + index*width + 0.5*m_candleStickWidth,
                     this->y() + + move_downward + (up_side - down_side) + (down_side - low));
    painter.drawRect(this->x() + move_rightward + index*width, this->y() + move_downward,
                     m_candleStickWidth, up_side-down_side);
    painter.fillRect(this->x() + move_rightward + index*width, this->y() + move_downward,
                     m_candleStickWidth, up_side-down_side, qBrush);
    //painter.fillRect(this->x()+index*width, this->y()+move_downward, m_candleStickWidth, up_side-down_side, qBrush);
    //painter.drawRect(150, 150, 50, 50);
    // m_painter.fillRect(0, 0, 128, 128, Qt::green);

    // load the market data price
    QVector<MarketPrice> m_vecMarketDatas;
}


void CandleStickDlg::paintEvent(QPaintEvent *)
{
//    m_painter->drawRect(150, 150, 50, 50);

    QPainter painter(this);
    //QPainter painter(pix);
    // painter.setPen(Qt::blue);
    // painter.setFont(QFont("Arial", 30));
    // painter.drawText(rect(), Qt::AlignCenter, "Qt");


//    int prices[5][4] = {{100, 175, 75, 87},
//                        {75, 100, 70, 90},
//                        {92, 108, 85, 99},
//                        {100, 124, 75, 110},
//                        {115, 138, 78, 95}};

//    qsrand((unsigned)time(0));

//    for(int i = 0; i<50; i++)
//    {
//        int index =qrand()%5;
//        showCandleStick(painter, i, prices[index][0], prices[index][1],
//                prices[index][2], prices[index][3]);
//    }


    for(int i = 0; i<m_vecMarketDatas.size(); i++)
    {
        // int index =qrand()%5;
        showCandleStick(painter, i, m_vecMarketDatas[i].open, m_vecMarketDatas[i].highest,
                m_vecMarketDatas[i].lowest, m_vecMarketDatas[i].close);
    }

    drawGrid(&painter);
    setBackgroundColor();

}

void CandleStickDlg::keyPressEvent(QKeyEvent *event)
{
    int x = this->x();
    int y = this->y();
    int width = this->width();
    int height = this->height();

    if(event->key()==Qt::Key_Up)
    {
        resize(width+3, height+3);
        // setGeometry(x, y, width+3, height+3);
    }
    if(event->key()==Qt::Key_Down)
    {
        resize(width-3, height-3);
        // setGeometry(x, y, width-3, height-3);
    }
    if(event->key()==Qt::Key_Left)
    {
        move(x-3, y);
    }
    if(event->key()==Qt::Key_Right)
    {
        move(x+3, y);
    }
    repaint();
}


void CandleStickDlg::drawGrid(QPainter *painter)
{
    int width = size().width();
    int height = size().height();

    int step = 20;

    QPen pen(Qt::DotLine);
    // QPen pen(Qt::DashLine);
    // QPen pen(Qt::DashDotLine);
    // QPen pen(Qt::DashDotDotLine);
    for(int i=step;i<width;i=i+step)
    {
        painter->setPen(pen);
        painter->drawLine(QPoint(i,0),QPoint(i,height));
    }
    for(int j=step;j<height;j=j+step)
    {
        painter->setPen(pen);
        painter->drawLine(QPoint(0,j),QPoint(width,j));
    }
}

void CandleStickDlg::setBackgroundColor()
{
    // setStyleSheet("background-color: yellow");
    // setStyleSheet("background-color: gray");
    // setStyleSheet("background-color: white");
}

