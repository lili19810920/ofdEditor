#ifndef DOCPAGE_H
#define DOCPAGE_H

#include "model_global.h"       // 导出lib使用

#include <QVector>
#include <QWidget>
#include <QGraphicsView>
#include <QGraphicsScene>
#include <QGraphicsProxyWidget>

// 类声明
class DocLayer;
//class CT_PageArea;
class DocBlock;
class DocTextBlock;
class InsertBlockInfo;
class DocPageScene;
class DocPassage;

/**
 * @Author Chaoqun
 * @brief  用来表示文章中的某一页
 * @date   2017/04/30
 */
class MODELSHARED_EXPORT DocPage
        :public QGraphicsView
{
    Q_OBJECT
public:

    enum Layer{Body,Foreground,Background};              // 分为三层
    enum BlockFlag{none,draw,drawMove,blockMove, blockResize};        // 插入时的绘制状态
    enum BlockType{text,image,table};                    // 插入时的类型
    explicit DocPage(QWidget * parent = 0);
    DocPage(double width,
            double height, double scaleFactor,QWidget * parent = 0);
    ~DocPage();

    DocPassage *getPassage();                     // 获得文章
    QSize getSize();                              // 获得页面像素大小
    double getWidth(){return width_mm;}           // 返回毫米单位宽度
    double getHeight(){return height_mm;}         // 返回毫米单位高度

    BlockFlag getBlockFlag(){return this->newBlockFlag;}

    DocLayer *getForegroundLayer();                 // 获得前景层
    DocLayer* getBodyLayer();                       // 获得正文层
    DocLayer* getBackgroundLayer();                 // 获得背景层

    //Pan
    void addImage();                                //添加图片

    bool isUsingWorkArea(){return this->has_working_area;}
    double getContentWidth(){return this->working_area_width;}
    double getContentHeight(){return this->working_area_height;}
    double getContentX(){return this->working_area_x;}
    double getContentY(){return this->working_area_y;}

public slots:
    void setSize(double width, double height);             // 设置页面大小
    void setPassage(DocPassage * passage);        // 设置文章
    void addBlock(DocBlock* block, DocPage::Layer layer);  // 为页面添加一个新元素
//    void addBlock(DocTextBlock* textBlock, DocPage::Layer layer);  // 为页面添加一个新元素
    void addItem(QGraphicsItem *item);      // 拓展接口
    QGraphicsProxyWidget *addWidget(QWidget *widget,
                          Qt::WindowFlags wFlags = Qt::WindowFlags());

    void setBlockFlag(BlockFlag flag){this->newBlockFlag = flag;}

    void setInsertBlockType(InsertBlockInfo& blockInfo);    // 设置下一个要插入的block的信息
    void remove();          // 移除本页
    void setScale(double scale);    // 设置页面的显示大小
    void setWorkingArea(
            bool isUsingWorkingArea,
            double contentWidth,
            double contentHeight,
            double contentX,
            double contentY);          // 设置工作区域

protected:
    void paintEvent(QPaintEvent *event);
    void mouseDoubleClickEvent(QMouseEvent *event);
    void mousePressEvent(QMouseEvent *event);
    void mouseMoveEvent(QMouseEvent *event);
    void mouseReleaseEvent(QMouseEvent *event);
    void focusInEvent(QFocusEvent *event);

private:

    void init();                         // 初始化UI
    DocPassage * passage;                // 页所属文章
    DocPageScene* docScene;              // 场景数据

    DocLayer* foregroundLayer;           // 前景层
    DocLayer* bodyLayer;                 // 正文层
    DocLayer* backgroundLayer;           // 背景层

    InsertBlockInfo * insertBlockInfo;    // 下一个插入的Block的类型

    // 还应该有模板页
    //CT_PageArea* area;                  // 页面大小描述

    double width_mm;                      // 页面的宽      --单位 mm
    double height_mm;                     // 页面的高
    double scaleFactor;                   // 表示缩放倍数

    QPointF oldPos;                     // 用来移动时使用，计算距离
    QPointF newPos;                     // 新点

    BlockFlag newBlockFlag;             // 是否画块
    DocBlock * activeBlock;             // 正在活跃的那个DocBlock

    bool has_working_area;
    double working_area_width;
    double working_area_height;
    double working_area_x;
    double working_area_y;


signals:        // 信号

    void signals_insertTextBlock(DocTextBlock* textBlock );  // 插入文本框信号
    void signals_removeTextBlock(DocTextBlock* textBlock );  // 移除文本框信号
    void has_focused_page();
    void has_no_focused_page();
    void signals_page_actived(DocPage* page);   // 本页面被激活信号
};


/**
 * @Author Chaoqun
 * @brief  希望用它来传递插入block的具体信息，包含层、类型等概念
 *         因为，获取鼠标信息的函数是继承于那些特定函数的，不方便
 *         传参数
 * @date   2017/05/16
 */
class MODELSHARED_EXPORT InsertBlockInfo
{
public:
    DocPage::Layer layer;
    DocPage::BlockType type;

    InsertBlockInfo(DocPage::Layer layers,
                    DocPage::BlockType types)
    {
        this->layer = layers;
        this->type = types;
    }
};


#endif // DOCPAGE_H
