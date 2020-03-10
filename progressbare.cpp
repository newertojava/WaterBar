#include "progressbare.h"
#include<QPainter>
#include<QTimer>
#include<QDebug>
#include<qmath.h>

ProgressBarE::ProgressBarE(QWidget *parent) :
    QWidget(parent)
{
    QTimer *timer = new QTimer;
    connect(timer,QTimer::timeout,this,[=](){
        this->offset += 0.6;
        update();
    });
    timer->start(100);
}

ProgressBarE::~ProgressBarE()
{
}

void ProgressBarE::paintEvent(QPaintEvent *event){
    int width = this->width();
    int height = this->height();
    int side = qMin(width, height);

    QPainter painter(this);

    painter.save();
    painter.setPen(Qt::NoPen);
    painter.setBrush(QBrush(bgColor));
    painter.drawRect(rect());
    painter.restore();

    painter.setRenderHints(QPainter::Antialiasing | QPainter::TextAntialiasing);
    painter.translate(width / 2, height / 2);
    painter.scale(side / 200.0, side / 200.0);


    drawBg(&painter);
    if(moreVison){
        drawE(&painter);
    }
    drawWater(&painter);
    drawText(&painter);

}

void ProgressBarE::updateValue(float va){
    this->value = va;
    update();
}

void ProgressBarE::setSinA(float sinA){
    this->sinA = sinA;
    update();
}

void ProgressBarE::setSinAlph(float alph){
    this->sinAlph = alph;
    update();
}

void ProgressBarE::setOffset(float set){
    this->offset = set;
    update();
}

void ProgressBarE::setWaterColor(QColor color){
    waterColor = color;
    update();
}

void ProgressBarE::setBGColor(QColor c){
    this->bgColor = c;
    update();
}

QColor ProgressBarE::getBGColor(){
    return this->bgColor;
}

float ProgressBarE::getSinA(){
    return this->sinA;
}

float ProgressBarE::getSinAlph(){
    return this->sinAlph;
}

QColor ProgressBarE::getWaterColor(){
    return this->waterColor;
}

float ProgressBarE::getValue(){
    return this->value;
}

float ProgressBarE::setMoreVision(bool flag){
    this->moreVison = flag;
    update();
}

void ProgressBarE::drawWater(QPainter* painter){
    QRect rect(-radius,-radius,2*radius,2*radius);
    int startX = -radius;
    int startY = -radius;
    int endX = radius;
    int endY = radius;
    float height = radius-((value*radius)/50);

    QPainterPath waterPath1;
    waterPath1.moveTo(startX,endY);
    QPainterPath waterPath2;
    waterPath2.moveTo(startX,endY);

    for(int i = startX;i<=endX;i++){
        float y1,y2;

        y1 = sinA*qSin(sinAlph*i+offset)+height;
        y2 = sinA*qSin(sinAlph*i+30+offset)+height;
        if(value == 0){
            y1 = y2 = endY;
        }
        if(value == 100){
            y1 = y2 = -endY;
        }
        waterPath1.lineTo(i,y1);
        waterPath2.lineTo(i,y2);
    }
    waterPath1.lineTo(endX,endY);
    waterPath2.lineTo(endX,endY);

    QPainterPath bigPath;
    bigPath.addEllipse(rect);
    waterPath1 = bigPath.intersected(waterPath1);
    waterPath2 = bigPath.intersected(waterPath2);
    painter->save();
    painter->setPen(Qt::NoPen);
    waterColor.setAlpha(180);
    painter->setBrush(waterColor);
    painter->drawPath(waterPath2);
    waterColor.setAlpha(100);
    painter->setBrush(waterColor);
    painter->drawPath(waterPath1);


    painter->restore();
}

void ProgressBarE::drawText(QPainter* painter){
    painter->save();
    QString text = QString("%1%").arg(value);
    QFont font = painter->font();
    font.setPixelSize(40);
    painter->setFont(font);
    QPen pen = painter->pen();
    pen.setColor(Qt::white);
    pen.setWidth(4);
    painter->setPen(pen);
    QRect rect(-radius,-radius,radius*2,radius*2);
    painter->drawText(rect,Qt::AlignCenter,text);
    painter->restore();
}

void ProgressBarE::drawBg(QPainter* painter){
    painter->save();
    painter->setBrush(bgEColor);
    QRect rect;
    if(moreVison){
        rect = QRect(-outRadius,-outRadius,outRadius*2,outRadius*2);
    }else{
        rect = QRect(-radius,-radius,radius*2,radius*2);
    }

    painter->drawEllipse(rect);
    painter->restore();
}

void ProgressBarE::drawE(QPainter* painter){
    painter->save();

    QPainterPath path;
    QPainterPath subpath;

    QRect out(-outERadius,-outERadius,2*outERadius,2*outERadius);
    QRect inn(-innERadius,-innERadius,2*innERadius,2*innERadius);
    float range = (value*1.0/100)*360;

    path.arcTo(out,-range,range);
    subpath.addEllipse(inn);
    path -= subpath;
    painter->setPen(Qt::NoPen);
    painter->setBrush(waterColor);

    painter->drawPath(path);

    painter->restore();
}
