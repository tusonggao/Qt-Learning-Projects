#ifndef CANDELSTICKDLG_H
#define CANDELSTICKDLG_H

#include "../commonHeaderFiles/commonwidgetheader.h"

class MarketPrice
{
public:
    MarketPrice() {}
    MarketPrice(QString date, double o, double h, double l, double c)
    {
        dateTime = date;
        open = o;
        highest = h;
        lowest = l;
        close = c;
    }

    QString dateTime;
    double open, highest, lowest, close;
};

class CandleStickDlg : public QDialog
{
    Q_OBJECT

public:
    explicit CandleStickDlg(QWidget *parent = 0);
    void loadMarketData(QString fileName);
    ~CandleStickDlg();

protected:
    void paintEvent(QPaintEvent *);
    void keyPressEvent(QKeyEvent *);

private:
    void drawGrid(QPainter *painter);
    void setBackgroundColor();

public:
    void showCandleStick(QPainter &painter, int index, double open,
                         double high, double low, double close);

private:
//    QLabel *label1;
//    QLabel *areaLabel;
//    QLineEdit *radiusEdit;
//    QPushButton *countButton;
    int m_candleStickWidth;
    int m_candleStickHeight;
    QVector<MarketPrice> m_vecMarketDatas;
    QPixmap *pix;
    QScrollArea *scrollArea;
};

#endif // CANDELSTICKDLG_H
