/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/*
 * File:   MainWindow.cpp
 * Author: serhiy
 *
 * Created on November 25, 2016, 11:19 AM
 */

#include "MainWindow.h"

MainWindow::MainWindow() {
    widget.setupUi(this);
    port_ = 8080;
    host_ = "localhost";
    mouseGrabbed_ = false;
    mouseBorder_ = 1;
    mouseIgnoreMoveRadius_ = 30;
    //QFuture<void> gst_ = QtConcurrent::run(streamParser);
    //setCentralWidget(openGLWidget);
    setWindowTitle(tr("Robotic Car"));
    connect(widget.actionConnect, SIGNAL(triggered()), this, SLOT(connectToHost()));
    connect(&socket_, SIGNAL(readyRead()), this, SLOT(readyRead()));
    connect(&socket_, SIGNAL(disconnected()), this, SLOT(disconnectedFromHost()));
}

MainWindow::~MainWindow() {
}

void MainWindow::keyPressEvent(QKeyEvent* event){
    //QWidget * tmpW = QWidget::mouseGrabber();
    //qDebug() << "mousegraber = " << tmpW;

   
    switch (event->key()){
        case Qt::Key_Right:
            this->sendMessage("Right");
            break;
        case Qt::Key_Left:
            this->sendMessage("Left");
            break;
        case Qt::Key_Up:
            this->sendMessage("respond");
            break;
        case Qt::Key_Enter:
        case Qt::Key_Return:
            this->sendMessage("exit");
            break;
        case Qt::Key_Escape:
            mouseGrabbed_ = false;
            setMouseTracking(false);
            releaseMouse();
            QCursor::setPos(originalMousePoint_);
            this->setCursor(originalMouseCursor_);
            break;
    }
}

void MainWindow::connectToHost(){
    
    qDebug() << "Connection state: " << socket_.state();
    
    if (socket_.state() != QAbstractSocket::ConnectedState){
        qDebug() << "Connecting to host";
        socket_.connectToHost(host_, port_);
        
        if (socket_.waitForConnected(3000)){
            if (socket_.state() == QAbstractSocket::ConnectedState)
                widget.actionConnect->setText("Disconnect");
            
        }
        else qDebug() << socket_.errorString();
        qDebug() << "Connected";
    }
    else {
        socket_.disconnectFromHost();
        widget.actionConnect->setText("Connect");
        qDebug() << "Disconnected";       
    } 
    this->setFocus();
}

void MainWindow::disconnectedFromHost(){
    widget.actionConnect->setText("Connect");
    qDebug() << "Disconnected";
}

bool MainWindow::sendMessage(QString message){
    char messageSize[5] = {0};
    sprintf(messageSize, "%d", message.length());   
    socket_.write(messageSize, 2);
    socket_.write(message.toStdString().c_str(), message.length());
}

QString MainWindow::receiveMessage(){
    char messageSize[5] = {0};
    socket_.read(messageSize, 2);
    int size = atoi(messageSize);
    QByteArray buff = socket_.read(size);
    return QString(buff);
}

void MainWindow::mousePressEvent(QMouseEvent* event){
    //qDebug() << "mouse grabber" << typeid(*(QWidget::mouseGrabber())).name();
    if (event->button() == Qt::LeftButton && widget.testWidget->underMouse()){
        if (!mouseGrabbed_){
            originalMouseCursor_ = this->cursor();
            originalMousePoint_ = QCursor::pos();
            widgetCenter_.setX(widget.testWidget->width() / 2);
            widgetCenter_.setY(widget.testWidget->height() / 2);
            QPoint tmpPoint = widget.testWidget->mapToGlobal(widgetCenter_);
            QCursor::setPos(tmpPoint);
            mouseGrabbed_ = true;
            grabMouse();
            setMouseTracking(true);
        }
    }
}

void MainWindow::mouseMoveEvent(QMouseEvent* event){
    //QWidget * tmpW = Qwidget.testWidget->mapFromParent(event->pos());
    QPoint local_xy = widget.testWidget->mapFromGlobal(event->globalPos());
    int x = local_xy.x();
    int y = local_xy.y();
    int height = widget.testWidget->height();
    int width = widget.testWidget->width();
    if (mouseGrabbed_){

        bool resetPos = false;
        if (x > (width - mouseBorder_)){
            x = width - mouseBorder_;
            resetPos = true;
        }
        
        if (x < mouseBorder_){
            x = mouseBorder_;
             resetPos = true;
        }
        
        if (y > (height - mouseBorder_)){
            y = height - mouseBorder_;
            resetPos = true;
        } 
        
        if (y < mouseBorder_){
            y = mouseBorder_;
            resetPos = true;
        }    
        
        if (resetPos){
            QPoint tmpPoint = widget.testWidget->mapToGlobal(QPoint(x,y));
            QCursor::setPos(tmpPoint);
        }

    }

    qDebug() << "height=" << height << " width=" << width << "dx=" << x << " dy=" << y << " local" << local_xy << widget.testWidget->mapToGlobal(QPoint(x,y)) << event->pos();
}

void MainWindow::readyRead(){
    qDebug() << "reading...";
    qDebug() << receiveMessage();
}