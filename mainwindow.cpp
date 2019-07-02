#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "QPixmap"
#include "QDebug"
#include "QPainter"
#include "QMenu"
#include "QAction"
#include "QComboBox"
#include "QString"
#include "QStack"
#include "QMessageBox"
#include "QLabel"
#include "QtMath"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    ditu_width=ui->label->width()*1.331;
        ditu_height=ui->label->height()*1.331;

        ditu_x=0;
        ditu_y=0;

        QPixmap temp(":/ditu/ditu.png");
        temp.save("temp.png");
        yuantu=temp;
        yuantu=yuantu.scaled(ui->label->width()*1.331, ui->label->height()*1.331, Qt::IgnoreAspectRatio, Qt::SmoothTransformation);
        ui->label->setGeometry(0,0,ditu_width,ditu_height);
        ui->label->setPixmap(yuantu);

        huitu_button_cnt=51;


       didianzuobiao();
        guanjiandianzuobiao();
        biandejianli();
       julijuzheng(); //距离矩阵建立
        xinxijianli(); //信息建立
        ////  ui->label_4->setPalette(Qt::red);
        ////  ui->label_4->setBackgroundRole();
}

MainWindow::~MainWindow()
{
    delete ui;
}
void MainWindow::mousePressEvent(QMouseEvent *e){
     last=e->globalPos();
    if(xinxi_flag==0){
         xinxi_flag=1;
         qDebug()<<"xinxi_weizhi["<<xinxi_cnt<<"].x1="<<e->x()<<",xinxi_weizhi["<<xinxi_cnt<<"].y1="<<e->y()<<";";
         huitu_button[xinxi_cnt]=new QPushButton(this);
         huitu_button[xinxi_cnt]->setObjectName(QString::number(xinxi_cnt));
         huitu_button[xinxi_cnt]->setText(QString::number(xinxi_cnt));
         huitu_button[xinxi_cnt]->setGeometry(e->x(),e->y(),20,20);


    }
    else if(xinxi_flag==1){
        xinxi_flag=0;
        qDebug()<<"xinxi_weizhi["<<xinxi_cnt<<"].x2="<<e->x()<<",xinxi_weizhi["<<xinxi_cnt<<"].y2="<<e->y()<<";";
        xinxi_cnt++;
    }
}
void MainWindow::mouseMoveEvent(QMouseEvent *e){

    qDebug()<<"move";
      ditu_x=ui->label->x();
      ditu_y=ui->label->y();
      int dx=e->globalX()-last.x();
      int dy=e->globalY()-last.y();
      last=e->globalPos();
      ditu_x+=dx;
      ditu_y+=dy;
      ui->label->setGeometry(ditu_x,ditu_y,ui->label->width(),ui->label->height());
}
void MainWindow::mouseReleaseEvent(QMouseEvent *e){
    mouse_flag=0;
}
void MainWindow::paintEvent(QPaintEvent *e){
//    qDebug()<<"paint";
//    QPainter painter(ui->label);
//    QPixmap pix(":/ditu/ditu.png");
//    painter.drawPixmap(0,0,ditu_width,ditu_height,pix);
//    update();
}
void MainWindow::wheelEvent(QWheelEvent *e){//针对鼠标滑轮进行Wheel事件判定，以进行缩小或放大
    if(e->delta()>0){ //
//        ditu_width*=1.1;
//        ditu_height*=1.1;
//        beishu*=1.1;
//        yuantu.load("temp.png");
//        yuantu=yuantu.scaled(ditu_width, ditu_height, Qt::IgnoreAspectRatio, Qt::SmoothTransformation);
//        ui->label->setPixmap(yuantu);
//        ui->label->setGeometry(ui->label->x(),ui->label->y(),ditu_width,ditu_height);
        if(suofang_flag==0){
            ditu_width*=1.1;
            ditu_height*=1.1;
            beishu=beishu*1.1;
            yuantu.load("temp.png");
            yuantu=yuantu.scaled(ditu_width, ditu_height, Qt::IgnoreAspectRatio, Qt::SmoothTransformation);
            ui->label->setPixmap(yuantu);
            ui->label->setGeometry(ui->label->x(),ui->label->y(),ditu_width,ditu_height);
            for(int i=0;i<XinxiNumber;i++){
               xinxi[i]->setGeometry(xinxi_weizhi[i].x1*beishu,xinxi_weizhi[i].y1*beishu,(xinxi_weizhi[i].x2-xinxi_weizhi[i].x1)*beishu,(xinxi_weizhi[i].y2-xinxi_weizhi[i].y1)*beishu);
            }

         }
        else if(suofang_flag==1){
            QMessageBox *suofang_jinggao=new QMessageBox(this);
            suofang_jinggao->setText("正在进行路径规划，无法缩放，请稍候");
            suofang_jinggao->setWindowTitle("警告信息");
            suofang_jinggao->show();
        }

    }
    else if (e->delta()<0){

        if(suofang_flag==0){
            ditu_width*=0.9;
            ditu_height*=0.9;
            beishu=beishu*0.9;
            yuantu.load("temp.png");
            yuantu=yuantu.scaled(ditu_width, ditu_height, Qt::IgnoreAspectRatio, Qt::SmoothTransformation);
            ui->label->setPixmap(yuantu);
            ui->label->setGeometry(ui->label->x(),ui->label->y(),ditu_width,ditu_height);
            for(int i=0;i<XinxiNumber;i++){
               xinxi[i]->setGeometry(xinxi_weizhi[i].x1*beishu,xinxi_weizhi[i].y1*beishu,(xinxi_weizhi[i].x2-xinxi_weizhi[i].x1)*beishu,(xinxi_weizhi[i].y2-xinxi_weizhi[i].y1)*beishu);
            }
         }
        else if(suofang_flag==1){
            QMessageBox *suofang_jinggao=new QMessageBox(this);
            suofang_jinggao->setText("正在进行路径规划，无法缩放，请稍候");
            suofang_jinggao->setWindowTitle("警告信息");
            suofang_jinggao->show();
        }
    }
}
void MainWindow::onMenu_1_Triggered(QAction *action)
{
    //起点
    if (action == action_s_chongqing)
    {
        qDebug()<<"chongqing qi dian";
    }
    else if (action == action_s_jiangjin)
    {
        qDebug()<<"jiangjin zhong dian";
    }
    //终点
    if (action == action_e_chongqing)
    {
        qDebug()<<"chongqing zhong dian";
    }
    else if (action == action_e_jiangjin)
    {
        qDebug()<<"jiangjin zhong dian";
    }
}

void MainWindow::on_comboBox_activated(const QString &arg1)
{
        if(arg1=="重庆")s=0;
            else if(arg1=="江津")s=1;
            else if(arg1=="永川")s=2;
            else if(arg1=="合川")s=3;
            else if(arg1=="长寿")s=4;
            else if(arg1=="南川")s=5;
            else if(arg1=="巴南")s=6;
            else if(arg1=="綦江")s=7;
            else if(arg1=="万盛")s=8;
            else if(arg1=="荣昌")s=9;
            else if(arg1=="铜梁")s=10;
            else if(arg1=="潼南")s=11;
            else if(arg1=="武隆")s=12;
            else if(arg1=="彭水")s=13;
            else if(arg1=="黔江")s=14;//
            else if(arg1=="酉阳")s=15;//
            else if(arg1=="秀山")s=16;//
            else if(arg1=="涪陵")s=17;//

          else if(arg1=="垫江")s=18;//
          else if(arg1=="梁平")s=19;//
          else if(arg1=="忠县")s=20;//
          else if(arg1=="万州")s=21;//
          else if(arg1=="开县")s=22;//
          else if(arg1=="云阳")s=23;//
          else if(arg1=="奉节")s=24;//
          else if(arg1=="巫溪")s=25;//
          else if(arg1=="巫山")s=26;//


}
void MainWindow::on_comboBox_4_activated(const QString &arg1)
{
    if(arg1=="重庆")e=0;
        else if(arg1=="江津")e=1;
        else if(arg1=="永川")e=2;
        else if(arg1=="合川")e=3;
        else if(arg1=="长寿")e=4;
        else if(arg1=="南川")e=5;
        else if(arg1=="巴南")e=6;
        else if(arg1=="綦江")e=7;
        else if(arg1=="万盛")e=8;
        else if(arg1=="荣昌")e=9;
        else if(arg1=="铜梁")e=10;
        else if(arg1=="潼南")e=11;
        else if(arg1=="武隆")e=12;
        else if(arg1=="彭水")e=13;
        else if(arg1=="黔江")e=14;//
        else if(arg1=="酉阳")e=15;//
        else if(arg1=="秀山")e=16;//
        else if(arg1=="涪陵")e=17;//

      else if(arg1=="垫江")e=18;//
      else if(arg1=="梁平")e=19;//
      else if(arg1=="忠县")e=20;//
      else if(arg1=="万州")e=21;//
      else if(arg1=="开县")e=22;//
      else if(arg1=="云阳")e=23;//
      else if(arg1=="奉节")e=24;//
      else if(arg1=="巫溪")e=25;//
      else if(arg1=="巫山")e=26;//
}
void MainWindow::huituClicked(){
    huitu_button_cnt--;
    delete huitu_button[huitu_button_cnt];
}


void MainWindow::on_lujing_button_clicked()
{
    if(suofang_flag==0){
            if(s==e){
               QMessageBox *message=new QMessageBox(this);
               message->setText("起点和终点不能相同！");
               message->setWindowTitle("警告信息");
               message->show();
            }
            else {

                jisuanZuiduanLujing(s);
                lujingjisuan(e,s);
                huaxian();


                }


        }
        else if(suofang_flag==1){
            QMessageBox *message=new QMessageBox(this);
            message->setText("请等待本次路径规划完毕再进行下次路径规划！");
            message->setWindowTitle("警告信息");
            message->show();
        }
}

void MainWindow::on_pushButton_clicked()//放大地图
{
    if(suofang_flag==0){
            ditu_width*=1.1;
            ditu_height*=1.1;
            beishu=beishu*1.1;
            yuantu.load("temp.png");
            yuantu=yuantu.scaled(ditu_width, ditu_height, Qt::IgnoreAspectRatio, Qt::SmoothTransformation);
            ui->label->setPixmap(yuantu);
            ui->label->setGeometry(ui->label->x(),ui->label->y(),ditu_width,ditu_height);
            for(int i=0;i<XinxiNumber;i++){
               xinxi[i]->setGeometry(xinxi_weizhi[i].x1*beishu,xinxi_weizhi[i].y1*beishu,(xinxi_weizhi[i].x2-xinxi_weizhi[i].x1)*beishu,(xinxi_weizhi[i].y2-xinxi_weizhi[i].y1)*beishu);
            }
         }
        else if(suofang_flag==1){
            QMessageBox *suofang_jinggao=new QMessageBox(this);
            suofang_jinggao->setText("正在进行路径规划，无法缩放，请稍候");
            suofang_jinggao->setWindowTitle("警告信息");
            suofang_jinggao->show();
        }

        for(int i=0;i<XinxiNumber;i++){
           xinxi[i]->setGeometry(xinxi_weizhi[i].x1*beishu,xinxi_weizhi[i].y1*beishu,(xinxi_weizhi[i].x2-xinxi_weizhi[i].x1)*beishu,(xinxi_weizhi[i].y2-xinxi_weizhi[i].y1)*beishu);
        }
}

void MainWindow::on_pushButton_2_clicked()//缩小地图
{
    if(suofang_flag==0){
            ditu_width*=0.9;
            ditu_height*=0.9;
            beishu=beishu*0.9;
            yuantu.load("temp.png");
            yuantu=yuantu.scaled(ditu_width, ditu_height, Qt::IgnoreAspectRatio, Qt::SmoothTransformation);
            ui->label->setPixmap(yuantu);
            ui->label->setGeometry(ui->label->x(),ui->label->y(),ditu_width,ditu_height);
            for(int i=0;i<XinxiNumber;i++){
               xinxi[i]->setGeometry(xinxi_weizhi[i].x1*beishu,xinxi_weizhi[i].y1*beishu,(xinxi_weizhi[i].x2-xinxi_weizhi[i].x1)*beishu,(xinxi_weizhi[i].y2-xinxi_weizhi[i].y1)*beishu);
            }
         }
        else if(suofang_flag==1){
            QMessageBox *suofang_jinggao=new QMessageBox(this);
            suofang_jinggao->setText("正在进行路径规划，无法缩放，请稍候");
            suofang_jinggao->setWindowTitle("警告信息");
            suofang_jinggao->show();
        }

}


void MainWindow::didianzuobiao(){
    didian[ 0 ].x= 362 ,didian[ 0 ].y= 352 ;//重庆市
    didian[ 1 ].x= 318 ,didian[ 1 ].y= 497 ;//江津
    didian[ 2 ].x= 258 ,didian[ 2 ].y= 404 ;//永川
    didian[ 3 ].x= 307 ,didian[ 3 ].y= 198 ;
    didian[ 4 ].x= 482 ,didian[ 4 ].y= 397 ;
    didian[ 5 ].x= 505 ,didian[ 5 ].y= 378 ;
    didian[ 6 ].x= 398 ,didian[ 6 ].y= 490 ;
    didian[ 7 ].x= 418 ,didian[ 7 ].y= 610 ;
    didian[ 8 ].x= 535 ,didian[ 8 ].y= 505 ;
    didian[ 9 ].x= 108 ,didian[ 9 ].y= 394 ;
    didian[ 10 ].x= 209 ,didian[ 10 ].y= 286 ;
    didian[ 11 ].x= 133 ,didian[ 11 ].y= 200 ;
    didian[ 12 ].x= 660 ,didian[ 12 ].y= 412 ;
    didian[ 13 ].x= 803 ,didian[ 13 ].y= 446 ;
    didian[ 14 ].x= 1003 ,didian[ 14 ].y= 403 ;
    didian[ 15 ].x= 958 ,didian[ 15 ].y= 535 ;
    didian[ 16 ].x= 1042 ,didian[ 16 ].y= 609 ;
    didian[ 17 ].x= 520 ,didian[ 17 ].y= 305 ;
    didian[ 18 ].x= 573 ,didian[ 18 ].y= 156 ;
    didian[ 19 ].x= 661 ,didian[ 19 ].y= 97 ;
    didian[ 20 ].x= 773 ,didian[ 20 ].y= 69 ;
    didian[ 21 ].x= 773 ,didian[ 21 ].y= 62 ;
    didian[ 22 ].x= 853 ,didian[ 22 ].y= 84 ;
    didian[ 23 ].x= 921 ,didian[ 23 ].y= 89 ;
    didian[ 24 ].x= 1023 ,didian[ 24 ].y= 97 ;
    didian[ 25 ].x= 1044 ,didian[ 25 ].y= 31 ;
    didian[ 26 ].x= 1113 ,didian[ 26 ].y= 85 ;

}
void MainWindow::guanjiandianzuobiao(){

    guanjiandian[ 0 ].x= 272 ,guanjiandian[ 0 ].y= 327,guanjiandian[ 0 ].duiyingjianzhu= 0 ;
    guanjiandian[ 1 ].x= 229,guanjiandian[ 1 ].y= 458 ,guanjiandian[ 1 ].duiyingjianzhu= 1 ;
    guanjiandian[ 2 ].x= 177 ,guanjiandian[ 2 ].y= 388 ,guanjiandian[ 2 ].duiyingjianzhu= 2 ;
    guanjiandian[ 3 ].x= 226 ,guanjiandian[ 3 ].y= 214 ,guanjiandian[ 3 ].duiyingjianzhu= 3 ;
    guanjiandian[ 4 ].x= 373 ,guanjiandian[ 4 ].y= 201 ,guanjiandian[ 4 ].duiyingjianzhu= 4 ;
    guanjiandian[ 5 ].x= 397 ,guanjiandian[ 5 ].y= 363 ,guanjiandian[ 5 ].duiyingjianzhu= 5 ;

    guanjiandian[ 6 ].x= 308 ,guanjiandian[ 6 ].y= 456 ,guanjiandian[ 6 ].duiyingjianzhu= 6 ;
    guanjiandian[ 7 ].x= 319 ,guanjiandian[ 7 ].y= 565 ,guanjiandian[ 7 ].duiyingjianzhu= 7 ;

    guanjiandian[ 8 ].x= 419 ,guanjiandian[ 8 ].y= 525,guanjiandian[ 8 ].duiyingjianzhu= 8 ;
    guanjiandian[ 9 ].x= 76 ,guanjiandian[ 9 ].y= 385 ,guanjiandian[ 9 ].duiyingjianzhu= 9 ;

    guanjiandian[ 10 ].x= 162 ,guanjiandian[ 10 ].y= 289 ,guanjiandian[ 10 ].duiyingjianzhu= 10 ;

    guanjiandian[ 11 ].x= 95 ,guanjiandian[ 11 ].y= 210 ,guanjiandian[ 11 ].duiyingjianzhu= 11 ;

    guanjiandian[ 12 ].x= 522,guanjiandian[ 12 ].y= 396 ,guanjiandian[ 12 ].duiyingjianzhu= 12 ;

    guanjiandian[ 13 ].x= 648 ,guanjiandian[ 13 ].y= 422,guanjiandian[ 13 ].duiyingjianzhu= 13 ;

    guanjiandian[ 14 ].x= 802 ,guanjiandian[ 14 ].y= 391 ,guanjiandian[ 14 ].duiyingjianzhu= 14 ;
    guanjiandian[ 15 ].x= 773 ,guanjiandian[ 15 ].y= 489 ,guanjiandian[ 15 ].duiyingjianzhu= 15 ;
    guanjiandian[ 16 ].x= 847 ,guanjiandian[ 16 ].y= 573 ,guanjiandian[ 16 ].duiyingjianzhu= 16 ;

    guanjiandian[ 17 ].x= 432 ,guanjiandian[ 17 ].y= 260 ,guanjiandian[ 17 ].duiyingjianzhu= 17 ;

//出问题
    guanjiandian[ 18 ].x=476 ,guanjiandian[ 18 ].y= 138,guanjiandian[ 18 ].duiyingjianzhu= 18 ;
    guanjiandian[ 19 ].x= 544 ,guanjiandian[ 19 ].y= 88 ,guanjiandian[ 19 ].duiyingjianzhu= 19 ;
    guanjiandian[ 20 ].x= 604 ,guanjiandian[ 20 ].y= 168 ,guanjiandian[ 20 ].duiyingjianzhu= 20 ;
    guanjiandian[ 21 ].x= 643 ,guanjiandian[ 21 ].y= 54 ,guanjiandian[ 21 ].duiyingjianzhu= 21 ;
    guanjiandian[ 22 ].x= 851 ,guanjiandian[ 22 ].y= 43 ,guanjiandian[ 22 ].duiyingjianzhu= 22;
    guanjiandian[ 23 ].x= 932 ,guanjiandian[ 23 ].y= 101 ,guanjiandian[ 23 ].duiyingjianzhu= 23 ;
    guanjiandian[ 24 ].x= 855 ,guanjiandian[ 24 ].y= 84 ,guanjiandian[ 24 ].duiyingjianzhu= 24 ;
    guanjiandian[ 25 ].x= 866 ,guanjiandian[ 25 ].y= 29 ,guanjiandian[ 25 ].duiyingjianzhu= 25;
    guanjiandian[ 26 ].x= 917,guanjiandian[ 26 ].y= 76 ,guanjiandian[ 26 ].duiyingjianzhu= 26 ;


  /*  guanjiandian[ 17 ].x=  80   ,guanjiandian[ 17 ].y= 254;
    guanjiandian[ 18 ].x=  90  ,guanjiandian[ 18 ].y=  253;
    guanjiandian[ 19 ].x=   666  ,guanjiandian[ 19 ].y= 752;
    guanjiandian[ 20 ].x=   32  ,guanjiandian[ 20 ].y=354 ;
    guanjiandian[ 21 ].x=    435 ,guanjiandian[ 21 ].y= 65;
    guanjiandian[ 22 ].x=    534 ,guanjiandian[ 22 ].y= 234;
    guanjiandian[ 23 ].x=    564 ,guanjiandian[ 23 ].y= 234;
    guanjiandian[ 24 ].x=    432 ,guanjiandian[ 24 ].y= 457;
    guanjiandian[ 25 ].x=    435 ,guanjiandian[ 25 ].y=645 ;
    guanjiandian[ 26 ].x=    67 ,guanjiandian[ 26 ].y= 132;
    guanjiandian[ 27 ].x=    45 ,guanjiandian[ 27 ].y= 436;
    guanjiandian[ 28 ].x=    43 ,guanjiandian[ 28 ].y= 886;
    guanjiandian[ 29 ].x=    777 ,guanjiandian[ 29 ].y= 434;
    guanjiandian[ 30 ].x=   354  ,guanjiandian[ 30 ].y= 533;

    guanjiandian[ 0 ].x= 387 ,guanjiandian[ 0 ].y= 365 ,guanjiandian[ 0 ].duiyingjianzhu= 0 ;
    guanjiandian[ 1 ].x= 408 ,guanjiandian[ 1 ].y= 510 ,guanjiandian[ 1 ].duiyingjianzhu= 1 ;
    guanjiandian[ 2 ].x= 860 ,guanjiandian[ 2 ].y= 244 ,guanjiandian[ 2 ].duiyingjianzhu= 2 ;
    guanjiandian[ 3 ].x= 996 ,guanjiandian[ 3 ].y= 294 ,guanjiandian[ 3 ].duiyingjianzhu= 3 ;
    guanjiandian[ 4 ].x= 741 ,guanjiandian[ 4 ].y= 320 ,guanjiandian[ 4 ].duiyingjianzhu= 4 ;
    guanjiandian[ 5 ].x= 217 ,guanjiandian[ 5 ].y= 366 ,guanjiandian[ 5 ].duiyingjianzhu= 5 ;
    guanjiandian[ 6 ].x= 522 ,guanjiandian[ 6 ].y= 203 ,guanjiandian[ 6 ].duiyingjianzhu= 6 ;
    guanjiandian[ 7 ].x= 790 ,guanjiandian[ 7 ].y= 434 ,guanjiandian[ 7 ].duiyingjianzhu= 7 ;
    guanjiandian[ 8 ].x= 584 ,guanjiandian[ 8 ].y= 507 ,guanjiandian[ 8 ].duiyingjianzhu= 8 ;
    guanjiandian[ 9 ].x= 348 ,guanjiandian[ 9 ].y= 414 ,guanjiandian[ 9 ].duiyingjianzhu= 9 ;
    guanjiandian[ 10 ].x= 389 ,guanjiandian[ 10 ].y= 279 ,guanjiandian[ 10 ].duiyingjianzhu= 10 ;
    guanjiandian[ 11 ].x= 725 ,guanjiandian[ 11 ].y= 543 ,guanjiandian[ 11 ].duiyingjianzhu= 11 ;
    guanjiandian[ 12 ].x= 606 ,guanjiandian[ 12 ].y= 613 ,guanjiandian[ 12 ].duiyingjianzhu= 12 ;
    guanjiandian[ 13 ].x= 1050 ,guanjiandian[ 13 ].y= 164 ,guanjiandian[ 13 ].duiyingjianzhu= 13 ;
    guanjiandian[ 14 ].x= 250 ,guanjiandian[ 14 ].y= 169 ,guanjiandian[ 14 ].duiyingjianzhu= 14 ;
    guanjiandian[ 15 ].x= 1005 ,guanjiandian[ 15 ].y= 70 ,guanjiandian[ 15 ].duiyingjianzhu= 15 ;
    guanjiandian[ 16 ].x= 131 ,guanjiandian[ 16 ].y= 421 ,guanjiandian[ 16 ].duiyingjianzhu= 16 ;




*/
}
void MainWindow::edgeClicked(){
    QPushButton *clickedButton = qobject_cast<QPushButton *>(sender());
    int i=clickedButton->text().toInt();
    if(edge_huitu_flag==0){
        e_s=i;
        edge_huitu_flag=1;
    }
    else if(edge_huitu_flag==1){
        e_e=i;
        edge_huitu_flag=0;
        qDebug()<<"edge["<<edge_cnt<<"].start="<<e_s<<",edge["<<edge_cnt<<"].end="<<e_e<<";";
        edge_cnt++;
        //      edge[0].start=0,edge[0].end=1;
    }
}

void MainWindow::biandejianli(){
    //重庆周边地区
    edge[ 0 ].start= 0 ,edge[ 0 ].end= 1 ;
    edge[ 1 ].start= 0 ,edge[ 1 ].end= 2 ;
     edge[ 2 ].start= 0 ,edge[ 2 ].end=  3;
     edge[ 3 ].start= 0 ,edge[ 3 ].end= 4;
       edge[ 4 ].start= 0 ,edge[ 4 ].end= 5 ;
       edge[ 5 ].start= 0 ,edge[ 5 ].end=  6;
       edge[ 6 ].start= 0 ,edge[ 6 ].end=  10;
    edge[ 7 ].start= 0,edge[ 7 ].end= 17;
    edge[ 8 ].start= 3 ,edge[ 8 ].end= 0;
    edge[ 9 ].start=4 ,edge[ 9 ].end=0 ;
    edge[ 10 ].start= 5,edge[ 10 ].end=0 ;
    edge[ 11 ].start= 1 ,edge[ 11 ].end=0  ;
    edge[ 12 ].start= 2,edge[ 12 ].end= 0 ;
    edge[ 13 ].start= 6,edge[ 13 ].end= 0;
    edge[ 14 ].start=17,edge[ 14 ].end= 0;
    edge[ 15 ].start= 10,edge[ 15 ].end= 0;

    //永川
    edge[ 16 ].start= 2,edge[ 16 ].end=9  ;
    edge[ 17 ].start= 2,edge[ 17 ].end= 1 ;
    edge[ 18 ].start= 9 ,edge[ 18 ].end= 2 ;
    edge[ 19 ].start= 1 ,edge[ 19 ].end= 2 ;

    //铜梁
     edge[ 20 ].start= 10 ,edge[ 20 ].end= 11 ;
     edge[ 21 ].start= 11 ,edge[ 21 ].end=10 ;

     //巴南
       edge[ 22 ].start= 6 ,edge[ 22 ].end= 7 ;
       edge[ 23 ].start= 7,edge[ 23 ].end= 6;
       edge[24].start=   13,edge[24].end=  14  ;
    edge[ 25 ].start= 6 ,edge[ 25 ].end= 12;
    edge[ 26 ].start= 12,edge[ 26 ].end= 6 ;


    //綦江
    edge[ 27 ].start= 7 ,edge[ 27 ].end= 8 ;
    edge[ 28 ].start= 8 ,edge[ 28 ].end=7 ;

    //武隆
    edge[ 29 ].start= 12 ,edge[ 29 ].end=13 ;
    edge[ 30 ].start= 12,edge[ 30 ].end= 5 ;
    edge[ 31 ].start= 13 ,edge[ 31 ].end= 12;
    edge[ 32 ].start= 5 ,edge[ 32 ].end= 12 ;
    //彭水
    edge[ 33 ].start= 14 ,edge[ 33 ].end= 13;
   //黔江
    edge[ 34 ].start=14 ,edge[ 34 ].end=15 ;
    edge[ 35 ].start= 15,edge[ 35 ].end= 14 ;

   //酉阳
    edge[ 36 ].start= 15,edge[ 36 ].end=16;
    edge[ 37 ].start= 16,edge[ 37 ].end= 15 ;
    //长寿到涪陵
    edge[ 38].start= 4,edge[ 38].end=17 ;
    edge[ 39 ].start= 17,edge[ 39 ].end= 4 ;

    //长寿到垫江
    edge[ 40].start= 4,edge[ 40].end=17 ;
    edge[ 41 ].start= 17,edge[ 41].end=  4;

    //垫江到梁平
    edge[ 42].start= 18,edge[ 42].end=19 ;
    edge[ 43 ].start= 19,edge[ 43 ].end= 18 ;

    //垫江到忠县
    edge[ 44].start= 18,edge[ 44].end=20 ;
    edge[ 45 ].start= 20,edge[ 45 ].end=18  ;

    //忠县到万州
    edge[ 46].start= 20,edge[ 46].end=21 ;
    edge[ 47 ].start= 21,edge[ 47 ].end=20  ;
    //梁平到万州
    edge[ 48].start= 19,edge[ 48].end=21 ;
    edge[ 49 ].start= 21,edge[ 49 ].end=19  ;
    //万州到开县
    edge[ 50].start= 21,edge[ 50].end=22 ;
    edge[ 51 ].start= 22,edge[ 51 ].end=21 ;

    //万州到云阳
    edge[ 52].start= 21,edge[ 52].end=23 ;
    edge[ 53 ].start= 23,edge[ 53 ].end=21  ;

    //云阳到奉节
    edge[ 54].start= 23,edge[ 54].end=24 ;
    edge[ 55 ].start= 24,edge[ 55 ].end=23  ;


    //奉节到巫溪
    edge[ 56].start= 24,edge[ 56].end=25;
    edge[ 57 ].start= 25,edge[ 57 ].end=24 ;
    //奉节到巫山
    edge[ 58].start= 24,edge[ 58].end=26;
    edge[ 59 ].start= 26,edge[ 59 ].end=24  ;


}
void MainWindow::julijuzheng(){
    for(int i=0;i<GuanjiandianNumber;i++){
        for(int j=0;j<GuanjiandianNumber;j++){
            juli[i][j]=0;
        }
    }
    for(int i=0;i<EdgeNumber;i++){
       juli[edge[i].start][edge[i].end]=juli[edge[i].end][edge[i].start]=sqrt(
                   (guanjiandian[edge[i].start].x-guanjiandian[edge[i].end].x)*
               (guanjiandian[edge[i].start].x-guanjiandian[edge[i].end].x)+
               (guanjiandian[edge[i].start].y-guanjiandian[edge[i].end].y)*
               (guanjiandian[edge[i].start].y-guanjiandian[edge[i].end].y));
    }
}

void MainWindow::jisuanZuiduanLujing(int s)  //最短路径迪杰斯特拉算法
{
    //传入起点s,计算其到每一个点的最短路径
    //待插入其它代码
    bool fangwen_flag[GuanjiandianNumber]; //访问标记
    for(int i=0;i<GuanjiandianNumber;i++)
     {
        if(juli[s][i]>0&&i!=s)
        {
            gengxin[i]=juli[s][i];
            lujing[i]=s;
         }
        else
        {
            gengxin[i]=INT_MAX;
            lujing[i]=-1;
        }
        fangwen_flag[i]=false;
        lujing[s]=s;
        gengxin[s]=0;
    }
    fangwen_flag[s]=true;
    for(int i=1;i<GuanjiandianNumber;i++)
     {
        int min=INT_MAX;
        int temp;
        for(int j= 0;j<GuanjiandianNumber;j++)
         {
            if(fangwen_flag[j]==false&&gengxin[j]<min)
            {
                min=gengxin[j];
                temp=j;
            }
        }
        fangwen_flag[temp]=true;
        for(int k=0;k<GuanjiandianNumber;k++)
         {
            if(fangwen_flag[k]==false&&juli[temp][k]>0&&min+juli[temp][k]<gengxin[k])
            {
                gengxin[k]=min+juli[temp][k];
                lujing[k]=temp;
            }
        }
    }
}
void MainWindow::lujingjisuan(int e,int s)   //e是终点
{
    for(int i=0;i<GuanjiandianNumber;i++)
        zuiduan_lujing[i]=-1;
    int cnt=0;
    QTextStream cout(stdout,  QIODevice::WriteOnly);
    QStack<int> stack;
    //int u=e;
    while(e!=s)
    {
        stack.push(e);
        e=lujing[e];
    }
    stack.push(e);
    while(!stack.empty())
    {
        cout<<stack.top()<<" ";


        zuiduan_lujing[cnt++]=stack.top();
        stack.pop();
    }
}
void MainWindow::huaxian(){
        int s=this->s;//当前作为起点的地点代码
        int e=this->e;
        //画线
        suofang_flag=1;
        QPixmap pixmap_yuantu(":/ditu/ditu.png");
        pixmap_yuantu = pixmap_yuantu.scaled(ditu_width,ditu_height,Qt::IgnoreAspectRatio,Qt::SmoothTransformation);
         QPainter llpainter(&pixmap_yuantu);
         llpainter.setRenderHint(QPainter::Antialiasing);//平滑直线
         llpainter.setPen(QPen(Qt::red,5,Qt::DotLine,Qt::RoundCap,Qt::MiterJoin)); //设置虚线
         if(s==0)
             llpainter.drawLine(260*beishu, 317*beishu, guanjiandian[s].x*beishu, (guanjiandian[s].y)*beishu);
             //llpainter.drawLine(231*beishu, (191)*beishu, guanjiandian[s].x*beishu, (guanjiandian[s].y)*beishu);
       /*  else  if(s!=14&&s!=15&&s!=16)
             llpainter.drawLine(didian[s].x*beishu, (didian[s].y)*beishu, guanjiandian[s].x*beishu, (guanjiandian[s].y)*beishu);
   */
         for (int i=1;zuiduan_lujing[i]!=-1;i++)
            {
                llpainter.drawLine(guanjiandian[zuiduan_lujing[i-1]].x*beishu, (guanjiandian[zuiduan_lujing[i-1]].y)*beishu,
                                    guanjiandian[zuiduan_lujing[i]].x*beishu, (guanjiandian[zuiduan_lujing[i]].y)*beishu);
                //延时
                sleep(200);
                QPixmap pixmap = pixmap_yuantu.scaled(ditu_width,ditu_height);
                QPainter painter(this);
                yuantu=pixmap;
                ui->label->setPixmap(yuantu);
                yuantu.save("temp.png");
            }

            llpainter.setPen(QPen(Qt::red,5,Qt::DotLine,Qt::RoundCap,Qt::MiterJoin)); //设置虚线
            if(e==0)
                llpainter.drawLine(260*beishu, 317*beishu, guanjiandian[e].x*beishu, (guanjiandian[e].y-33)*beishu);
          /*  else if(e!=14&&e!=15&&e!=16)
            llpainter.drawLine(didian[e].x*beishu, (didian[e].y)*beishu, guanjiandian[e].x*beishu, (guanjiandian[e].y)*beishu);*/
            llpainter.end();

            QPixmap pixmap = pixmap_yuantu.scaled(ditu_width,ditu_height);
            QPainter painter(this);
            yuantu=pixmap;
            ui->label->setPixmap(yuantu);
            yuantu.save("temp.png");
            suofang_flag=0;
}
void MainWindow::on_pushButton_3_clicked()
{
    if(suofang_flag==0)
        {
            QPixmap temp(":/ditu/ditu.png");
            temp.save("temp.png");
            yuantu=temp;
            yuantu=yuantu.scaled(ui->label->width(), ui->label->height(), Qt::IgnoreAspectRatio, Qt::SmoothTransformation);
            ui->label->setPixmap(yuantu);
        }
        else if(suofang_flag==1){
            QMessageBox *qingchu_jinggao=new QMessageBox(this);
            qingchu_jinggao->setText("请等待路径规划完毕再清除!");
            qingchu_jinggao->setWindowTitle("警告信息");
            qingchu_jinggao->show();
        }
}
void MainWindow::xinxijianli(){
    //信息标签初始化祖先
    for (int i=0;i<XinxiNumber;i++){
        xinxi[i]=new QLabel(ui->label);
    }
    xinxizuobiao();
    xinxitooltip();
    //    信息位置与大小初始化
    for(int i=0;i<XinxiNumber;i++){
       xinxi[i]->setGeometry(xinxi_weizhi[i].x1,xinxi_weizhi[i].y1,xinxi_weizhi[i].x2-xinxi_weizhi[i].x1,xinxi_weizhi[i].y2-xinxi_weizhi[i].y1);

       xinxi[i]->show();
    }
}
void MainWindow::xinxizuobiao (){ //存储信息位置坐标x1，y1,x2,y2
    xinxi_weizhi[ 0 ].x1= 217 ,xinxi_weizhi[ 0 ].y1= 158 ;
    xinxi_weizhi[ 0 ].x2= 247 ,xinxi_weizhi[ 0 ].y2= 180 ;
    xinxi_weizhi[ 1 ].x1= 268 ,xinxi_weizhi[ 1 ].y1= 198 ;
    xinxi_weizhi[ 1 ].x2= 286 ,xinxi_weizhi[ 1 ].y2= 222 ;
    xinxi_weizhi[ 2 ].x1= 268 ,xinxi_weizhi[ 2 ].y1= 228 ;
    xinxi_weizhi[ 2 ].x2= 285 ,xinxi_weizhi[ 2 ].y2= 251 ;
    xinxi_weizhi[ 3 ].x1= 269 ,xinxi_weizhi[ 3 ].y1= 259 ;
    xinxi_weizhi[ 3 ].x2= 285 ,xinxi_weizhi[ 3 ].y2= 284 ;
    xinxi_weizhi[ 4 ].x1= 220 ,xinxi_weizhi[ 4 ].y1= 195 ;
    xinxi_weizhi[ 4 ].x2= 257 ,xinxi_weizhi[ 4 ].y2= 208 ;
    xinxi_weizhi[ 5 ].x1= 218 ,xinxi_weizhi[ 5 ].y1= 211 ;
    xinxi_weizhi[ 5 ].x2= 259 ,xinxi_weizhi[ 5 ].y2= 223 ;
    xinxi_weizhi[ 6 ].x1= 217 ,xinxi_weizhi[ 6 ].y1= 225 ;
    xinxi_weizhi[ 6 ].x2= 258 ,xinxi_weizhi[ 6 ].y2= 239 ;
    xinxi_weizhi[ 7 ].x1= 216 ,xinxi_weizhi[ 7 ].y1= 240 ;
    xinxi_weizhi[ 7 ].x2= 258 ,xinxi_weizhi[ 7 ].y2= 255 ;
    xinxi_weizhi[ 8 ].x1= 214 ,xinxi_weizhi[ 8 ].y1= 256 ;
    xinxi_weizhi[ 8 ].x2= 259 ,xinxi_weizhi[ 8 ].y2= 272 ;
    xinxi_weizhi[ 9 ].x1= 221 ,xinxi_weizhi[ 9 ].y1= 276 ;
    xinxi_weizhi[ 9 ].x2= 258 ,xinxi_weizhi[ 9 ].y2= 287 ;
    xinxi_weizhi[ 10 ].x1= 90 ,xinxi_weizhi[ 10 ].y1= 150 ;
    xinxi_weizhi[ 10 ].x2= 138 ,xinxi_weizhi[ 10 ].y2= 169 ;
    xinxi_weizhi[ 11 ].x1= 98 ,xinxi_weizhi[ 11 ].y1= 174 ;
    xinxi_weizhi[ 11 ].x2= 144 ,xinxi_weizhi[ 11 ].y2= 192 ;
    xinxi_weizhi[ 12 ].x1= 78 ,xinxi_weizhi[ 12 ].y1= 198 ;
    xinxi_weizhi[ 12 ].x2= 123 ,xinxi_weizhi[ 12 ].y2= 215 ;
    xinxi_weizhi[ 13 ].x1= 90 ,xinxi_weizhi[ 13 ].y1= 221 ;
    xinxi_weizhi[ 13 ].x2= 136 ,xinxi_weizhi[ 13 ].y2= 239 ;
    xinxi_weizhi[ 14 ].x1= 72 ,xinxi_weizhi[ 14 ].y1= 246 ;
    xinxi_weizhi[ 14 ].x2= 117 ,xinxi_weizhi[ 14 ].y2= 264 ;
    xinxi_weizhi[ 15 ].x1= 79 ,xinxi_weizhi[ 15 ].y1= 270 ;
    xinxi_weizhi[ 15 ].x2= 124 ,xinxi_weizhi[ 15 ].y2= 286 ;
    xinxi_weizhi[ 16 ].x1= 65 ,xinxi_weizhi[ 16 ].y1= 304 ;
    xinxi_weizhi[ 16 ].x2= 120 ,xinxi_weizhi[ 16 ].y2= 321 ;
    xinxi_weizhi[ 17 ].x1= 60 ,xinxi_weizhi[ 17 ].y1= 327 ;
    xinxi_weizhi[ 17 ].x2= 111 ,xinxi_weizhi[ 17 ].y2= 344 ;
    xinxi_weizhi[ 18 ].x1= 220 ,xinxi_weizhi[ 18 ].y1= 300 ;
    xinxi_weizhi[ 18 ].x2= 280 ,xinxi_weizhi[ 18 ].y2= 318 ;
    xinxi_weizhi[ 19 ].x1= 220 ,xinxi_weizhi[ 19 ].y1= 325 ;
    xinxi_weizhi[ 19 ].x2= 280 ,xinxi_weizhi[ 19 ].y2= 344 ;
    xinxi_weizhi[ 20 ].x1= 565 ,xinxi_weizhi[ 20 ].y1= 388 ;
    xinxi_weizhi[ 20 ].x2= 615 ,xinxi_weizhi[ 20 ].y2= 399 ;
    xinxi_weizhi[ 21 ].x1= 565 ,xinxi_weizhi[ 21 ].y1= 369 ;
    xinxi_weizhi[ 21 ].x2= 617 ,xinxi_weizhi[ 21 ].y2= 383 ;
    xinxi_weizhi[ 22 ].x1= 565 ,xinxi_weizhi[ 22 ].y1= 351 ;
    xinxi_weizhi[ 22 ].x2= 615 ,xinxi_weizhi[ 22 ].y2= 366 ;
    xinxi_weizhi[ 23 ].x1= 66 ,xinxi_weizhi[ 23 ].y1= 44 ;
    xinxi_weizhi[ 23 ].x2= 129 ,xinxi_weizhi[ 23 ].y2= 110 ;
    xinxi_weizhi[ 24 ].x1= 500 ,xinxi_weizhi[ 24 ].y1= 178 ;
    xinxi_weizhi[ 24 ].x2= 625 ,xinxi_weizhi[ 24 ].y2= 200 ;
    xinxi_weizhi[ 25 ].x1= 439 ,xinxi_weizhi[ 25 ].y1= 131 ;
    xinxi_weizhi[ 25 ].x2= 623 ,xinxi_weizhi[ 25 ].y2= 168 ;
    xinxi_weizhi[ 26 ].x1= 475 ,xinxi_weizhi[ 26 ].y1= 98 ;
    xinxi_weizhi[ 26 ].x2= 588 ,xinxi_weizhi[ 26 ].y2= 132 ;
    xinxi_weizhi[ 27 ].x1= 613 ,xinxi_weizhi[ 27 ].y1= 63 ;
    xinxi_weizhi[ 27 ].x2= 715 ,xinxi_weizhi[ 27 ].y2= 107 ;
    xinxi_weizhi[ 28 ].x1= 672 ,xinxi_weizhi[ 28 ].y1= 124 ;
    xinxi_weizhi[ 28 ].x2= 724 ,xinxi_weizhi[ 28 ].y2= 159 ;
    xinxi_weizhi[ 29 ].x1= 316 ,xinxi_weizhi[ 29 ].y1= 180 ;
    xinxi_weizhi[ 29 ].x2= 359 ,xinxi_weizhi[ 29 ].y2= 198 ;
    xinxi_weizhi[ 30 ].x1= 316 ,xinxi_weizhi[ 30 ].y1= 200 ;
    xinxi_weizhi[ 30 ].x2= 335 ,xinxi_weizhi[ 30 ].y2= 241 ;
    xinxi_weizhi[ 31 ].x1= 364 ,xinxi_weizhi[ 31 ].y1= 180 ;
    xinxi_weizhi[ 31 ].x2= 417 ,xinxi_weizhi[ 31 ].y2= 201 ;
    xinxi_weizhi[ 32 ].x1= 316 ,xinxi_weizhi[ 32 ].y1= 151 ;
    xinxi_weizhi[ 32 ].x2= 415 ,xinxi_weizhi[ 32 ].y2= 173 ;
    xinxi_weizhi[ 33 ].x1= 184 ,xinxi_weizhi[ 33 ].y1= 29 ;
    xinxi_weizhi[ 33 ].x2= 243 ,xinxi_weizhi[ 33 ].y2= 99 ;
    xinxi_weizhi[ 34 ].x1= 155 ,xinxi_weizhi[ 34 ].y1= 105 ;
    xinxi_weizhi[ 34 ].x2= 244 ,xinxi_weizhi[ 34 ].y2= 136 ;
    xinxi_weizhi[ 35 ].x1= 257 ,xinxi_weizhi[ 35 ].y1= 44 ;
    xinxi_weizhi[ 35 ].x2= 302 ,xinxi_weizhi[ 35 ].y2= 133 ;
    xinxi_weizhi[ 36 ].x1= 312 ,xinxi_weizhi[ 36 ].y1= 46 ;
    xinxi_weizhi[ 36 ].x2= 357 ,xinxi_weizhi[ 36 ].y2= 134 ;
    xinxi_weizhi[ 37 ].x1= 365 ,xinxi_weizhi[ 37 ].y1= 29 ;
    xinxi_weizhi[ 37 ].x2= 404 ,xinxi_weizhi[ 37 ].y2= 134 ;
    xinxi_weizhi[ 38 ].x1= 434 ,xinxi_weizhi[ 38 ].y1= 28 ;
    xinxi_weizhi[ 38 ].x2= 473 ,xinxi_weizhi[ 38 ].y2= 50 ;
    xinxi_weizhi[ 39 ].x1= 446 ,xinxi_weizhi[ 39 ].y1= 79 ;
    xinxi_weizhi[ 39 ].x2= 466 ,xinxi_weizhi[ 39 ].y2= 92 ;
    xinxi_weizhi[ 40 ].x1= 430 ,xinxi_weizhi[ 40 ].y1= 99 ;
    xinxi_weizhi[ 40 ].x2= 451 ,xinxi_weizhi[ 40 ].y2= 113 ;
    xinxi_weizhi[ 41 ].x1= 412 ,xinxi_weizhi[ 41 ].y1= 118 ;
    xinxi_weizhi[ 41 ].x2= 432 ,xinxi_weizhi[ 41 ].y2= 129 ;
    xinxi_weizhi[ 42 ].x1= 6 ,xinxi_weizhi[ 42 ].y1= 158 ;
    xinxi_weizhi[ 42 ].x2= 53 ,xinxi_weizhi[ 42 ].y2= 177 ;
    xinxi_weizhi[ 43 ].x1= 16 ,xinxi_weizhi[ 43 ].y1= 225 ;
    xinxi_weizhi[ 43 ].x2= 47 ,xinxi_weizhi[ 43 ].y2= 274 ;
    xinxi_weizhi[ 44 ].x1= 56 ,xinxi_weizhi[ 44 ].y1= 360 ;
    xinxi_weizhi[ 44 ].x2= 105 ,xinxi_weizhi[ 44 ].y2= 377 ;
    xinxi_weizhi[ 45 ].x1= 52 ,xinxi_weizhi[ 45 ].y1= 380 ;
    xinxi_weizhi[ 45 ].x2= 104 ,xinxi_weizhi[ 45 ].y2= 397 ;
    xinxi_weizhi[ 46 ].x1= 139 ,xinxi_weizhi[ 46 ].y1= 360 ;
    xinxi_weizhi[ 46 ].x2= 272 ,xinxi_weizhi[ 46 ].y2= 392 ;
    xinxi_weizhi[ 47 ].x1= 44 ,xinxi_weizhi[ 47 ].y1= 410 ;
    xinxi_weizhi[ 47 ].x2= 90 ,xinxi_weizhi[ 47 ].y2= 443 ;
    xinxi_weizhi[ 48 ].x1= 95 ,xinxi_weizhi[ 48 ].y1= 411 ;
    xinxi_weizhi[ 48 ].x2= 143 ,xinxi_weizhi[ 48 ].y2= 443 ;
    xinxi_weizhi[ 49 ].x1= 150 ,xinxi_weizhi[ 49 ].y1= 411 ;
    xinxi_weizhi[ 49 ].x2= 197 ,xinxi_weizhi[ 49 ].y2= 444 ;
    xinxi_weizhi[ 50 ].x1= 205 ,xinxi_weizhi[ 50 ].y1= 412 ;
    xinxi_weizhi[ 50 ].x2= 249 ,xinxi_weizhi[ 50 ].y2= 443 ;
    xinxi_weizhi[ 51 ].x1= 264 ,xinxi_weizhi[ 51 ].y1= 412 ;
    xinxi_weizhi[ 51 ].x2= 334 ,xinxi_weizhi[ 51 ].y2= 440 ;
    xinxi_weizhi[ 52 ].x1= 161 ,xinxi_weizhi[ 52 ].y1= 200 ;
    xinxi_weizhi[ 52 ].x2= 197 ,xinxi_weizhi[ 52 ].y2= 253 ;
    xinxi_weizhi[ 53 ].x1= 155 ,xinxi_weizhi[ 53 ].y1= 258 ;
    xinxi_weizhi[ 53 ].x2= 192 ,xinxi_weizhi[ 53 ].y2= 287 ;
    xinxi_weizhi[ 54 ].x1= 339 ,xinxi_weizhi[ 54 ].y1= 204 ;
    xinxi_weizhi[ 54 ].x2= 370 ,xinxi_weizhi[ 54 ].y2= 240 ;
    xinxi_weizhi[ 55 ].x1= 402 ,xinxi_weizhi[ 55 ].y1= 302 ;
    xinxi_weizhi[ 55 ].x2= 462 ,xinxi_weizhi[ 55 ].y2= 354 ;
    xinxi_weizhi[ 56 ].x1= 400 ,xinxi_weizhi[ 56 ].y1= 386 ;
    xinxi_weizhi[ 56 ].x2= 462 ,xinxi_weizhi[ 56 ].y2= 439 ;
    xinxi_weizhi[ 57 ].x1= 489 ,xinxi_weizhi[ 57 ].y1= 427 ;
    xinxi_weizhi[ 57 ].x2= 542 ,xinxi_weizhi[ 57 ].y2= 451 ;
    xinxi_weizhi[ 58 ].x1= 492 ,xinxi_weizhi[ 58 ].y1= 339 ;
    xinxi_weizhi[ 58 ].x2= 537 ,xinxi_weizhi[ 58 ].y2= 372 ;
    xinxi_weizhi[ 59 ].x1= 562 ,xinxi_weizhi[ 59 ].y1= 413 ;
    xinxi_weizhi[ 59 ].x2= 620 ,xinxi_weizhi[ 59 ].y2= 424 ;
    xinxi_weizhi[ 60 ].x1= 560 ,xinxi_weizhi[ 60 ].y1= 430 ;
    xinxi_weizhi[ 60 ].x2= 620 ,xinxi_weizhi[ 60 ].y2= 453 ;
    xinxi_weizhi[ 61 ].x1= 621 ,xinxi_weizhi[ 61 ].y1= 224 ;
    xinxi_weizhi[ 61 ].x2= 755 ,xinxi_weizhi[ 61 ].y2= 301 ;
    xinxi_weizhi[ 62 ].x1= 260 ,xinxi_weizhi[ 62 ].y1= 155 ;
    xinxi_weizhi[ 62 ].x2= 286 ,xinxi_weizhi[ 62 ].y2= 179 ;
    xinxi_weizhi[ 63 ].x1= 352 ,xinxi_weizhi[ 63 ].y1= 375 ;
    xinxi_weizhi[ 63 ].x2= 379 ,xinxi_weizhi[ 63 ].y2= 400 ;

    for(int i=0;i<XinxiNumber;i++)
        xinxi_weizhi[i].y1-=11,xinxi_weizhi[i].y2-=11;
}

void MainWindow::sleep(unsigned int msec){
    QTime reachTime =QTime::currentTime().addMSecs(msec);
    while(QTime::currentTime()<reachTime){
        QCoreApplication::processEvents(QEventLoop::AllEvents,100);
    }
}
void MainWindow::xinxitooltip(){
    /*xinxi[0]->setToolTip("	重庆市\n"
                        );
    xinxi[1]->setToolTip("	重庆市\n"
                        );

    xinxi[2]->setToolTip("	重庆市\n"
                        );
    xinxi[3]->setToolTip("	重庆市\n"
                        );
    xinxi[4]->setToolTip("	重庆市\n"
                        );
    xinxi[5]->setToolTip("	重庆市\n"
                        );
    xinxi[6]->setToolTip("	重庆市\n"
                        );
    xinxi[7]->setToolTip(" 重庆市\n"
                       );
    xinxi[8]->setToolTip("	重庆市\n"
                        );
    xinxi[9]->setToolTip("	重庆市\n"
                        );
    xinxi[10]->setToolTip("	重庆市\n"
                        );
    xinxi[11]->setToolTip("	重庆市\n"
                        );
    xinxi[12]->setToolTip("	重庆市\n"
                        );
    xinxi[13]->setToolTip("	重庆市\n"
                        );
    xinxi[14]->setToolTip("	重庆市\n"
                        );
    xinxi[15]->setToolTip("重庆市\n"
                        );
    xinxi[16]->setToolTip("重庆市\n"
                        );
    xinxi[17]->setToolTip("	重庆市\n"
                        );*/



}
void MainWindow::on_label_linkActivated(const QString &link )
{

}



