/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/*
 * File:   main.cpp
 * Author: serhiy
 *
 * Created on November 24, 2016, 10:06 AM
 */

#include <QApplication>
#include "MainWindow.h"
#include <QGst/Init>

int main(int argc, char *argv[]) {
    // initialize resources, if needed
    // Q_INIT_RESOURCE(resfile);


    QApplication app(argc, argv);
    QGst::init(&argc, &argv);
    
    MainWindow window;
    // create and show your widgets here
    window.show();

    return app.exec();
}
