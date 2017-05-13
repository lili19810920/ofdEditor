#include "PassageMainWindow.h"

#include <QDesktopWidget>
#include <QApplication>
#include <QAction>
#include <QToolBar>
#include <QMenu>
#include <QWidget>
#include <QMenuBar>
#include <QStatusBar>
#include <QMessageBox>
#include <QColorDialog>
#include <QFileDialog>
#include <QDebug>
#include <QMdiSubWindow>
#include <QMdiArea>
#include <QPalette>


#include "Doc/DocPassage.h"

PassageMainWindow::PassageMainWindow(QWidget *parent)
    :QMainWindow(parent)
{
    init();
}

PassageMainWindow::~PassageMainWindow()
{

}

/**
 * @Author Chaoqun
 * @brief  摘要
 * @param  参数
 * @return 返回值
 * @date   2017/05/13
 */
DocPassage *PassageMainWindow::createMdiChild()
{
    DocPassage * child = new DocPassage;
    this->area->addSubWindow(child);
    child->setVisible(true);            // 设置可见
    return NULL;
}

/**
 * @Author Chaoqun
 * @brief  初始化窗口
 * @param  void
 * @return void
 * @date   2017/05/13
 */
void PassageMainWindow::init()
{
    this->area = new QMdiArea();
    this->setCentralWidget(this->area);

    initAction();
    connectAction();

    QLabel * status = new QLabel();
    this->statusBar()->addWidget(status);

    this->setMinimumSize(960,720);
    this->setBackgroundRole(QPalette::Text);

}

/**
 * @Author Chaoqun
 * @brief  初始化动作
 * @param  参数
 * @return 返回值
 * @date   2017/05/13
 */
void PassageMainWindow::initAction()
{
    this->newFileAction = new QAction(tr("New File"));      // 新建文件
    this->newFileAction->setStatusTip(tr("Create a new ofd file"));
    this->newFileAction->setShortcut(QKeySequence::New);

    this->openFileAtcion = new QAction(tr("Open File"));    // 打开文件
    this->openFileAtcion->setStatusTip(tr("Open an existing ofd file"));
    this->openFileAtcion->setShortcut(QKeySequence::Open);

    this->saveAction = new QAction(tr("Save"));             // 保存
    this->saveAction->setStatusTip(tr("Save file"));
    this->saveAction->setShortcut(QKeySequence::Save);

    this->saveAsAction = new QAction(tr("Save as"));        // 另存为
    this->saveAsAction->setStatusTip(tr("Save as"));
    this->saveAsAction->setShortcut(QKeySequence::SaveAs);

    this->printAction = new QAction(tr("Print"));       // 打印
    this->printAction->setStatusTip(tr("Print your document"));

    this->undoAction = new QAction(tr("Undo"));             // 撤销操作
    this->undoAction->setStatusTip(tr("Undo your last action"));
    this->undoAction->setShortcut(QKeySequence::Undo);

    this->redoAction = new QAction(tr("Redo"));             // 重新操作
    this->redoAction->setStatusTip(tr("Redo the action you undo"));
    this->redoAction->setShortcut(QKeySequence::Redo);

    this->copyAction = new QAction(tr("Copy"));             // 复制文本
    this->copyAction->setStatusTip(tr("Copy the content you selected"));
    this->copyAction->setShortcut(QKeySequence::Copy);

    this->cutAction = new QAction(tr("Cut"));             // 剪切
    this->cutAction->setStatusTip(tr("Cut the content you selected"));
    this->cutAction->setShortcut(QKeySequence::Cut);

    this->pasteAction = new QAction(tr("Paste"));           // 粘贴
    this->pasteAction->setStatusTip(tr("Paste your pasteboard content"));
    this->pasteAction->setShortcut(QKeySequence::Paste);

    this->insertTextBlockAction = new QAction("Insert TextBlock");  // 插入文本框
    this->insertTextBlockAction->setStatusTip(tr("Insert a new TextBlock"));

    this->insertImageAction = new QAction("Insert Image");           // 插入图片
    this->insertImageAction->setStatusTip(tr("Insert a image"));

    this->insertTableAction = new QAction("Insert Table");          // 插入一个表格
    this->insertTableAction->setStatusTip(tr("Insert a table"));

    this->textFormat = new QAction(tr("Text Format"));      // 文字格式
    this->textFormat->setStatusTip(tr("Set the selected texts' Format"));

    this->paragraphFormat = new QAction(tr("Paragraph Format"));    // 段落格式
    this->paragraphFormat->setStatusTip(tr("Set this paragarph format"));

    this->imageFormat = new QAction(tr("Image Format"));        // 图片格式
    this->imageFormat->setStatusTip(tr("Set the Selected image's format"));

    this->tableFormat = new QAction(tr("Table Format"));    // 表格格式
    this->tableFormat->setStatusTip(tr("Set the selected table's format"));

    this->aboutQtAction = new QAction(tr("about Qt"));      // 关于QT

    this->aboutAppAction = new QAction(tr("About App"));    // 关于本应用
    this->aboutAppAction->setStatusTip(tr("About this Application"));

    this->helpAciton = new QAction(tr("Help"));
    this->helpAciton->setStatusTip(tr("Show the help Window"));

    this->filesMenu = this->menuBar()->addMenu(tr("Files"));
    this->editMenu = this->menuBar()->addMenu(tr("Edit"));
    this->formatMenu = this->menuBar()->addMenu(tr("Format"));
    this->insertMenu = this->menuBar()->addMenu(tr("Insert"));
    this->aboutMenu = this->menuBar()->addMenu(tr("About"));

    this->filesMenu->addAction(this->newFileAction);
    this->filesMenu->addAction(this->openFileAtcion);
    this->filesMenu->addAction(this->saveAction);
    this->filesMenu->addAction(this->saveAsAction);
    this->filesMenu->addAction(this->printAction);

    this->editMenu->addAction(this->undoAction);
    this->editMenu->addAction(this->redoAction);
    this->editMenu->addSeparator();     // 分割线
    this->editMenu->addAction(this->copyAction);
    this->editMenu->addAction(this->cutAction);
    this->editMenu->addAction(this->pasteAction);

    this->formatMenu->addAction(this->textFormat);
    this->formatMenu->addAction(this->paragraphFormat);
    this->formatMenu->addAction(this->imageFormat);
    this->formatMenu->addAction(this->tableFormat);

    this->insertMenu->addAction(this->insertTextBlockAction);
    this->insertMenu->addAction(this->insertImageAction);
    this->insertMenu->addAction(this->insertTableAction);

    this->aboutMenu->addAction(this->aboutQtAction);
    this->aboutMenu->addAction(this->aboutAppAction);
    this->aboutMenu->addAction(this->helpAciton);
/*---------------------------------------------------------------------*/
    this->file_toolBar = this->addToolBar(tr("File"));
    this->edit_toolBar = this->addToolBar(tr("Edit"));
    this->format_toolBar = this->addToolBar(tr("Format"));
    this->insert_toolBar = this->addToolBar(tr("Insert"));

    this->file_toolBar->addAction(this->newFileAction);
    this->file_toolBar->addAction(this->openFileAtcion);
    this->file_toolBar->addAction(this->saveAction);

    this->edit_toolBar->addAction(this->undoAction);
    this->edit_toolBar->addAction(this->redoAction);

    this->format_toolBar->addAction(this->textFormat);
    this->format_toolBar->addAction(this->paragraphFormat);
    this->format_toolBar->addAction(this->imageFormat);
    this->format_toolBar->addAction(this->tableFormat);

    this->insert_toolBar->addAction(this->insertTextBlockAction);
    this->insert_toolBar->addAction(this->insertImageAction);
    this->insert_toolBar->addAction(this->insertTableAction);

}

/**
 * @Author Chaoqun
 * @brief  为QActions链接响应事件
 * @param  参数
 * @return 返回值
 * @date   2017/05/13
 */
void PassageMainWindow::connectAction()
{
    connect(this->newFileAction, &QAction::triggered,
            this,&PassageMainWindow::createMdiChild);   // 新建窗口
}

/**
 * @Author Chaoqun
 * @brief  解除QAction的所有事件响应
 * @param  void
 * @return 返回值
 * @date   2017/05/13
 */
void PassageMainWindow::disconnectAction()
{

}

/**
 * @Author Chaoqun
 * @brief  获取激活的窗口
 * @param  void
 * @return DocPassage *
 * @date   2017/05/13
 */
DocPassage *PassageMainWindow::activeMdiChild()
{
    if (QMdiSubWindow *activeSubWindow = this->area->activeSubWindow())
        return qobject_cast<DocPassage *>(activeSubWindow->widget());
    return 0;
}
