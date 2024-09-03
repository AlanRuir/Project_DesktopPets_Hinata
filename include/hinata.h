#ifndef  __HINATA_H__
#define  __HINATA_H__

#include <QWidget>
#include <QPaintEvent>
#include <QPainter>
#include <QTimerEvent>
#include <QPixmap>
#include <QMouseEvent>
#include <QPoint>
#include <QScreen>
#include <QTime>
#include <QPixmap>
#include <QLabel>

class Hinata : public QWidget
{
    Q_OBJECT

public:
    explicit Hinata(QWidget *parent = nullptr);
    ~Hinata();

protected:
    void paintEvent(QPaintEvent *ev) override;
    void timerEvent(QTimerEvent *ev) override;
    void mousePressEvent(QMouseEvent *ev) override;
    void mouseReleaseEvent(QMouseEvent *ev) override;
    void mouseMoveEvent(QMouseEvent *ev) override;

private:
    QLabel* hinata_label_;
    QString hinata_current_img_url_;
    QPoint  pos_deviation_;             //鼠标按下点与窗口左上角的位置差
    int     walk_timeout_id_;
    int     move_timeout_id_;
    int     down_timeout_id_;
    int     model_timeout_id_;
    bool    move_left_;                 //左走标志位
    int     old_pos_x_;
    double  screen_available_x_;        //当前屏幕可用窗口大小
    double  screen_available_y_;
    bool    can_be_down_;         //下落标志位
    bool    can_be_walk_;         //走路标志位
    bool    walk_flag_;           //走路标志位
    bool    sit_flag_;            //坐站标志位
    int     walk_model_;          //走路模式
};

#endif  // __HINATA_H__