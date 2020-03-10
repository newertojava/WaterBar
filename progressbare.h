#ifndef PROGRESSBARE_H
#define PROGRESSBARE_H

#include <QWidget>
#include <QtUiPlugin/QDesignerExportWidget>

namespace Ui {
class ProgressBarE;
}

class /*QDESIGNER_WIDGET_EXPORT*/ ProgressBarE : public QWidget
{
    Q_OBJECT
    Q_PROPERTY(QColor waterColor READ getWaterColor WRITE setWaterColor)
    Q_PROPERTY(QColor bgColor READ getBGColor WRITE setBGColor)
    Q_PROPERTY(float value READ getValue WRITE updateValue)
    Q_PROPERTY(float sinA READ getSinA WRITE setSinA)
    Q_PROPERTY(float sinAlph READ getSinAlph WRITE setSinAlph)
    Q_PROPERTY(float offset WRITE setOffset)



public:
    explicit ProgressBarE(QWidget *parent = 0);
    ~ProgressBarE();
    void updateValue(float);
    void setSinA(float);
    void setSinAlph(float);
    void setOffset(float);
    void setWaterColor(QColor);
    void setBGColor(QColor);

    float getSinA();
    float getSinAlph();
    QColor getWaterColor();
    float getValue();
    QColor getBGColor();

    float setMoreVision(bool);
protected:
    void paintEvent(QPaintEvent*);

private:
    float offset = 0;
    float value = 0;
    float radius = 80.0;
    float sinA = 7.5;
    float sinAlph = 0.035;
    bool moreVison = false;

    float outRadius = 100;
    float outERadius = 95;
    float innERadius = 85;

    QColor bgEColor = "#2F2F32";
    QColor bgColor = Qt::white;
    QColor waterColor = QColor("#E36363");
    void drawBg(QPainter*);
    void drawWater(QPainter*);
    void drawText(QPainter*);
    void drawE(QPainter*);
};

#endif // PROGRESSBARE_H
