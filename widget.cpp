#include "widget.h"
#include "ui_widget.h"

Widget::Widget(QWidget *parent) :
      QWidget(parent),
      ui(new Ui::Widget)
{
   ui->setupUi(this);
   this->setWindowTitle("Genetic Algorithm, Travelling Salesman Problem");

   qRegisterMetaType<QImage>("QImage");
   connect(&thread, SIGNAL(renderedImage(QImage)),
           this, SLOT(updatePixmap(QImage)));

   pixmap = QPixmap(500, 500);
   pixmap.fill(Qt::transparent);

   ui->pushButton_2->setVisible(false);
   ui->pushButton_7->setVisible(false);

   connect(this, SIGNAL(thread_render(int,int,double,int)), &thread, SLOT(render(int,int,double,int)));
   connect(this, SIGNAL(thread_newPopulation(int,double)), &thread, SLOT(newPopulation(int,double)));
   connect(this, SIGNAL(thread_optimizeDirection(bool)), &thread, SLOT(setDirection(bool)));
   connect(this, SIGNAL(thread_setMutationRate(double)), &thread, SLOT(setMutationRate(double)));
   connect(this, SIGNAL(thread_setMultithreading(bool)), &thread, SLOT(setMultiThreading(bool)));
   connect(this, SIGNAL(thread_setPopulationSize(int)), &thread, SLOT(setPopulationSize(int)));

   connect(this, SIGNAL(thread_togglePause()), &thread, SLOT(togglePause()));
}

Widget::~Widget()
{
   delete ui;
}

void Widget::startThread()
{
   int maxLocations = ui->spinBoxLocations->value();
   int maxIndividuen = ui->spinBoxIndividuen->value();
   double maxMutationRate = ui->doubleSpinBoxMutationrate->value();
   int generationMethod = 0;

   if( ui->radioButtonZufall->isChecked() )
   {
      generationMethod = 0;
   }

   if( ui->radioButtonKreis->isChecked() )
   {
      generationMethod = 1;
   }

   if( ui->radioButtonRaster->isChecked() )
   {
      generationMethod = 2;
   }

   emit thread_render(maxLocations, maxIndividuen, maxMutationRate, generationMethod);
}

void Widget::updatePixmap(const QImage &image)
{
   pixmap = QPixmap::fromImage(image);
   update();
}

void Widget::changeEvent(QEvent *e)
{
   QWidget::changeEvent(e);
   switch (e->type()) {
   case QEvent::LanguageChange:
      ui->retranslateUi(this);
      break;
   default:
      break;
   }
}

void Widget::paintEvent(QPaintEvent *)
{
   QPainter painter(this);
   painter.drawPixmap(pixmap.rect(), pixmap);
}

void Widget::on_pushButton_clicked()
{
}

void Widget::on_pushButton_3_clicked()
{
   emit thread_newPopulation( ui->spinBoxIndividuen->value(), ui->doubleSpinBoxMutationrate->value() );
}

void Widget::on_pushButton_5_clicked()
{
   this->startThread();
}

void Widget::on_pushButton_6_clicked()
{
   emit thread_togglePause();
}

void Widget::on_checkBoxReverse_clicked()
{
   emit thread_optimizeDirection( ui->checkBoxReverse->checkState() );
}

void Widget::on_checkBoxMultiThreading_clicked()
{
   bool multiThreading = ui->checkBoxMultiThreading->isChecked();

   emit thread_setMultithreading(multiThreading);
}

void Widget::on_pushButton_2_clicked()
{
   ui->pushButton_2->setVisible(false);
   emit thread_setMutationRate( ui->doubleSpinBoxMutationrate->value() );
}

void Widget::on_doubleSpinBoxMutationrate_valueChanged(double )
{
   ui->pushButton_2->setVisible(true);
}

void Widget::on_spinBoxIndividuen_valueChanged(int )
{
   ui->pushButton_7->setVisible(true);
}

void Widget::on_pushButton_7_clicked()
{
   ui->pushButton_7->setVisible(false);
   emit thread_setPopulationSize( ui->spinBoxIndividuen->value() );
}
