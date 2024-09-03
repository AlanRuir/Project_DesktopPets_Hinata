#include <hinata.h>
#include <QGuiApplication>
#include <QRandomGenerator>

Hinata::Hinata(QWidget *parent)
    : QWidget(parent)
    , hinata_label_(new QLabel(this))
{
    setFixedSize(128, 128);

    //设置窗口的控制栏隐藏
    setWindowFlags(Qt::FramelessWindowHint | windowFlags());
    setAttribute(Qt::WA_TranslucentBackground);

    hinata_current_img_url_ = "://img/shime1.png";

    walk_timeout_id_  = startTimer(250);        //每300毫秒走一步
    move_timeout_id_  = startTimer(30);
    down_timeout_id_  = startTimer(7);
    model_timeout_id_ = startTimer(10000);      //每10秒切换一次走路模式
    move_left_        = false;
    old_pos_x_        = frameGeometry().x();
    walk_flag_        = false;
    sit_flag_         = true;
    can_be_walk_      = false;

    //获取当前设备屏幕可用大小
    screen_available_x_ = QGuiApplication::primaryScreen()->availableGeometry().width();
    screen_available_y_ = QGuiApplication::primaryScreen()->availableGeometry().height();

    can_be_down_ = frameGeometry().y() < screen_available_y_ - height();
}

Hinata::~Hinata()
{
    delete hinata_label_;
}

void Hinata::paintEvent(QPaintEvent *ev)
{
    QPainter painter;
    painter.begin(this);
    painter.drawPixmap(0, 0, QPixmap(hinata_current_img_url_));
    painter.end();
}

void Hinata::timerEvent(QTimerEvent *ev)
{
    if(ev->timerId() == model_timeout_id_)
    {
        walk_model_ = QRandomGenerator::global()->bounded(0, 7);
    }

    if(ev->timerId() == walk_timeout_id_)
    {
        if((0 == walk_model_ % 4) && can_be_walk_)
        {
            if(walk_flag_)
            {
                hinata_current_img_url_ = "://img/shime2.png";
                if(frameGeometry().left() > 0)        //保证宠物在可用屏幕内走动
                {
                    move(frameGeometry().topLeft() + QPoint(-5, 0));
                    walk_flag_ = !walk_flag_;
                }
                else
                {
                    hinata_current_img_url_ = "://img/shime1.png";
                }
            }
            else
            {
                hinata_current_img_url_ = "://img/shime3.png";
                if(frameGeometry().left() > 0)
                {
                    move(frameGeometry().topLeft() + QPoint(-5, 0));
                    walk_flag_ = !walk_flag_;
                }
                else
                {
                    hinata_current_img_url_ = "://img/shime1.png";
                }
            }
        }
        else if((0 == walk_model_ % 5) && can_be_walk_)
        {
            if(walk_flag_)
            {
                hinata_current_img_url_ = "://img/shime47.png";
                if(frameGeometry().left() + width() < screen_available_x_)       //保证宠物在可用屏幕内走动
                {
                    move(frameGeometry().topLeft() + QPoint(5, 0));
                }
                walk_flag_ = !walk_flag_;
            }
            else
            {
                hinata_current_img_url_ = "://img/shime48.png";
                if(frameGeometry().left() + width() < screen_available_x_)
                {
                    move(frameGeometry().topLeft() + QPoint(5, 0));
                }
                walk_flag_ = !walk_flag_;
            }
        }
        else if((0 == walk_model_ % 6) && can_be_walk_)
        {
            if(sit_flag_)
            {
                hinata_current_img_url_ = "://img/shime16.png";
                sit_flag_ = !sit_flag_;
            }
        }
        else if((0 == walk_model_ % 7) && can_be_walk_)
        {
            if(sit_flag_)
            {
                hinata_current_img_url_ = "://img/shime1.png";
                sit_flag_ = !sit_flag_;
            }
        }
        else
        {
            hinata_current_img_url_ = "://img/shime1.png";
        }

        update();
    }

    if(ev->timerId() == move_timeout_id_)
    {
        move_left_ = (frameGeometry().x() - old_pos_x_) < 0;
        old_pos_x_ = frameGeometry().x();
    }

    if(ev->timerId() == down_timeout_id_)
    {
        if(can_be_down_)
        {
            if(frameGeometry().y() < screen_available_y_ - height())
            {
                hinata_current_img_url_ = "://img/shime22.png";
                move(frameGeometry().topLeft() + QPoint(0, 3));
            }
            else
            {
                hinata_current_img_url_ = "://img/shime1.png";
                can_be_down_ = false;
                can_be_walk_ = true;
            }

            update();
        }
    }
}

void Hinata::mousePressEvent(QMouseEvent *ev)
{
    can_be_walk_ = false;

    if(Qt::RightButton == ev->button())
    {
        close();
    }
    else if(Qt::LeftButton == ev->button())
    {
        hinata_current_img_url_ = "://img/shime1.png";
        //求出按下点与窗口坐标差值
        pos_deviation_ = ev->globalPos() - frameGeometry().topLeft();
    }

    update();
}

void Hinata::mouseReleaseEvent(QMouseEvent *ev)
{
    can_be_walk_ = false;

    if(frameGeometry().y() < screen_available_y_ - height())
    {
        can_be_down_ = true;
    }
}

void Hinata::mouseMoveEvent(QMouseEvent *ev)
{
    can_be_walk_ = false;

    if(ev->buttons() & Qt::LeftButton)
    {
        move(ev->globalPos() - pos_deviation_);
    }

    if(move_left_)
    {
        hinata_current_img_url_ = "://img/shime8.png";
    }
    else
    {
        hinata_current_img_url_ = "://img/shime7.png";
    }

    update();
}
