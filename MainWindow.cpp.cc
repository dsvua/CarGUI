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

#include <qt4/QtGui/qpainterpath.h>

#include "MainWindow.h"

MainWindow::MainWindow() {
    widget.setupUi(this);
    port_ = 8080;
    host_ = "localhost";
    mouseGrabbed_ = false;
    mouseBorder_ = 1;
    mouseIgnoreMoveRadius_ = 30;
    //QFuture<void> gst_ = QtConcurrent::run(streamParser);
    setWindowTitle(tr("Robotic Car"));
    
    //-------------------------
    QGraphicsScene *scene = new QGraphicsScene;
    qDebug() << scene->sceneRect();
    //QGraphicsView *view = new QGraphicsView (scene);
    widget.testWidget->setScene(scene);
    widget.testWidget->setViewport(new QGLWidget);
    
    QGst::Ui::GraphicsVideoSurface *surface = new QGst::Ui::GraphicsVideoSurface(widget.testWidget);
    //... 
    //...
    QGst::Ui::GraphicsVideoWidget *videoWidget = new QGst::Ui::GraphicsVideoWidget;
    videoWidget->setSurface(surface);
    scene->addItem(videoWidget);

    QGst::ElementPtr rtpbin = QGst::ElementFactory::make("gstrtpbin");
    qDebug() << "created rtpbin";
    QGst::ElementPtr source = QGst::ElementFactory::make("udpsrc", "src");
    qDebug() << "created source";
    QGst::ElementPtr rtph264depay = QGst::ElementFactory::make("rtph264depay");
    qDebug() << "created rtph264depay";
    QGst::ElementPtr avdec_h264 = QGst::ElementFactory::make("avdec_h264");
    qDebug() << "created avdec_h264";
    QGst::ElementPtr videoconvert = QGst::ElementFactory::make("videoconvert");
    qDebug() << "created videoconvert";
    QGst::ElementPtr videoscale = QGst::ElementFactory::make("videoscale");
    qDebug() << "created videoscale";
    QGst::ElementPtr sink = surface->videoSink();
    qDebug() << "created sink";

    //pipeline_ = QGst::Parse::launch(pipeDescr_).dynamicCast<QGst::Pipeline>();
    //pipeline_ = QGst::Parse::launch(&argv[]);;
    
    pipeline_ = QGst::Pipeline::create();
    qDebug() << "QGst::Pipeline::create()";
    //pipeline_->add(rtpbin);

    source->setProperty("port", 9000);
    source->setProperty("caps", QGst::Caps::fromString("application/x-rtp,"
            " media=(string)video, "
            "clock-rate=(int)90000, encoding-name=(string)H264"));
    pipeline_->add(source);
    //if(rtpbin->link(source) == false)
    //    qDebug("Link source failed");
    pipeline_->add(rtph264depay);
    if(source->link(rtph264depay) == false)
        qDebug("Link rtph264depay failed");
    pipeline_->add(avdec_h264);
    if(rtph264depay->link(avdec_h264) == false)
        qDebug("Link avdec_h264 failed");
    pipeline_->add(videoconvert);
    if(avdec_h264->link(videoconvert) == false)
        qDebug("Link videoconvert failed");
    pipeline_->add(videoscale);
    if(videoconvert->link(videoscale) == false)
        qDebug("Link videoscale failed");
    pipeline_->add(sink);
    if(videoscale->link(sink) == false)
        qDebug("Link sink failed");
           
    pipeline_->setState(QGst::StatePlaying);
    
    qDebug() <<  "videoWidget->rect()" << videoWidget->rect();

    
    //setCentralWidget(view);

    //-------------------------
    
    
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