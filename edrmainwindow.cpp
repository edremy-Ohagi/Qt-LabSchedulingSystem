#include "edrmainwindow.h"
#include "qdatetime.h"
#include "ui_edrmainwindow.h"
#include "chartdialog.h"
#include "roomdialog.h"
#include "statdialog.h"

edrMainWindow::edrMainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::edrMainWindow)
{
    ui->setupUi(this);
    initUI();
    initSignal();
}

edrMainWindow::~edrMainWindow()
{
    delete ui;
}

void edrMainWindow::initUI()
{
    ui->dockWidget_2->setVisible(false);//初始化不可见
    ui->tableView->setSpan(0,0,2,1);//合并单元格
    ui->tableView->setSpan(0,1,2,1);//合并单元格
    ui->tableView->setSpan(0,2,1,3);//合并单元格
    ui->tableView->setSpan(0,5,1,3);//合并单元格
    ui->tableView->setSpan(0,8,1,3);//合并单元格
    ui->tableView->setSpan(0,11,1,3);//合并单元格
    ui->tableView->setSpan(0,14,1,3);//合并单元格
    initModel(&mo_310);//初始化模型
    initModel(&mo_311);
    initModel(&mo_312);
    initModel(&mo_417);
    initModel(&mo_418);
    initModel(&mo_R1);
    initModel(&mo_R2);
    initModel(&mo_R3);
    initModel(&mo_RA);
    initModel(&mo_RB);
    initModel(&mo_RC);
    initModel(&mo_RD);
    initModel(&mo_RE);
    ui->statusbar->addWidget(&lb_room);//状态栏
    ui->statusbar->addWidget(&lb_ppl);
    ui->statusbar->addWidget(&lb_arr);
    lb_arr.setText("当前排课编号：");
    ui->statusbar->addWidget(&lb_class);
    lb_class.setText("当前课程名：");
    ui->statusbar->addWidget(&lb_teacher);
    lb_teacher.setText("当前教师名：");
}

void edrMainWindow::initModel(QStandardItemModel *new_model)//初始化所有新模型的函数
{
    new_model->clear();
    new_model->setRowCount(22);//行列设置
    new_model->setColumnCount(17);
    QModelIndex indexDef = new_model->index(0,0,QModelIndex());//把00用来存储人数
    QStandardItem * tItem = new QStandardItem;//表头设置
    tItem->setSelectable(false);
    tItem->setEditable(false);
    tItem->setText("周次");
    tItem->setBackground(QBrush(Qt::magenta));
    new_model->setItem(0,0,tItem);
    new_model->setItem(1,0,tItem);
    tItem = new QStandardItem;//每一个不同的item都要new一下，不然会覆盖
    tItem->setSelectable(false);
    tItem->setEditable(false);
    tItem->setBackground(QBrush(Qt::magenta));
    tItem->setText("起止日期");
    new_model->setItem(0,1,tItem);
    new_model->setItem(1,1,tItem);
    tItem = new QStandardItem;
    tItem->setSelectable(false);
    tItem->setEditable(false);
    tItem->setText("周一");
    tItem->setBackground(QBrush(Qt::green));
    new_model->setItem(0,2,tItem);
    new_model->setItem(0,3,tItem);
    new_model->setItem(0,4,tItem);
    tItem = new QStandardItem;
    tItem->setSelectable(false);
    tItem->setEditable(false);
    tItem->setBackground(QBrush(Qt::green));
    tItem->setText("周二");
    new_model->setItem(0,5,tItem);
    new_model->setItem(0,6,tItem);
    new_model->setItem(0,7,tItem);
    tItem = new QStandardItem;
    tItem->setSelectable(false);
    tItem->setEditable(false);
    tItem->setBackground(QBrush(Qt::green));
    tItem->setText("周三");
    new_model->setItem(0,8,tItem);
    new_model->setItem(0,9,tItem);
    new_model->setItem(0,10,tItem);
    tItem = new QStandardItem;
    tItem->setSelectable(false);
    tItem->setEditable(false);
    tItem->setBackground(QBrush(Qt::green));
    tItem->setText("周四");
    new_model->setItem(0,11,tItem);
    new_model->setItem(0,12,tItem);
    new_model->setItem(0,13,tItem);
    tItem = new QStandardItem;
    tItem->setSelectable(false);
    tItem->setEditable(false);
    tItem->setBackground(QBrush(Qt::green));
    tItem->setText("周五");
    new_model->setItem(0,14,tItem);
    new_model->setItem(0,15,tItem);
    new_model->setItem(0,16,tItem);
    for(int i=0;i<5;i++){
        tItem = new QStandardItem;
        tItem->setSelectable(false);
        tItem->setEditable(false);
        tItem->setBackground(QBrush(Qt::cyan));
        tItem->setText("上午");
        new_model->setItem(1,2+3*i,tItem);
    }
    for(int i=0;i<5;i++){
        tItem = new QStandardItem;
        tItem->setSelectable(false);
        tItem->setEditable(false);
        tItem->setBackground(QBrush(Qt::cyan));
        tItem->setText("下午");
        new_model->setItem(1,3+3*i,tItem);
    }
    for(int i=0;i<5;i++){
        tItem = new QStandardItem;
        tItem->setSelectable(false);
        tItem->setEditable(false);
        tItem->setBackground(QBrush(Qt::cyan));
        tItem->setText("晚上");
        new_model->setItem(1,4+3*i,tItem);
    }
    for(int i=0;i<20;i++){
        tItem = new QStandardItem;
        tItem->setSelectable(false);
        tItem->setEditable(false);
        tItem->setBackground(QBrush(Qt::lightGray));
        tItem->setText(QString::number(i+1));
        new_model->setItem(2+i,0,tItem);
        QString str = iniDate.addDays(7*i).toString("MM.dd");//转化为日期
        str+="-";
        str+=iniDate.addDays(7+7*i).toString("MM.dd");
        tItem = new QStandardItem;
        tItem->setSelectable(false);
        tItem->setEditable(false);
        tItem->setBackground(QBrush(Qt::lightGray));
        tItem->setText(str);
        new_model->setItem(2+i,1,tItem);
    }
    new_model->setData(indexDef,120,Qt::UserRole);//默认120人
}

void edrMainWindow::initSignal()
{
    connect(ui->tableView,SIGNAL(mouseLeftClicked(const QModelIndex &)),this,SLOT(do_mouseLeftClicked(const QModelIndex &)));
    connect(ui->tableView,SIGNAL(mouseRightClicked(const QModelIndex &)),this,SLOT(do_mouseRightClicked(const QModelIndex &)));
}

void edrMainWindow::on_stackedWidget_currentChanged(int arg1)//控制禁止手动切换页面
{
    Q_UNUSED(arg1);
    if(ui->bttn_Chart->isChecked()){
        ui->stackedWidget->setCurrentIndex(1);
    }
    if(ui->btn_Arr->isChecked()){
        ui->stackedWidget->setCurrentIndex(0);
    }
}

void edrMainWindow::do_mouseLeftClicked(const QModelIndex index)//左键更新左下角状态栏
{
    QStandardItemModel * cModel = dynamic_cast<QStandardItemModel*>(ui->tableView->model());//downcast获取当前model
    QStandardItem * cItem = cModel->itemFromIndex(index);//获取当前item
    if(!cItem->text().isEmpty()&&cItem->isSelectable()){//忽略空表格和表头
        lb_arr.setText(QString("当前排课编号："+cItem->text()));
        lb_class.setText(QString("当前课程名："+data[cItem->text().toInt()-1].mName));//访问data获取
        lb_teacher.setText(QString("当前教师名："+data[cItem->text().toInt()-1].mTeacher));
    }
    else{//空的则全部置空
        lb_arr.setText(QString("当前排课编号："));
        lb_class.setText(QString("当前课程名："));
        lb_teacher.setText(QString("当前教师名："));
    }
}

void edrMainWindow::do_mouseRightClicked(const QModelIndex index)//排课模式下右键取消
{
    QStandardItemModel * cModel = dynamic_cast<QStandardItemModel*>(ui->tableView->model());
    QStandardItem * cItem = cModel->itemFromIndex(index);
    if(ui->pushButton_arr->isChecked()&&ui->lineEdit_arrN->text()==cItem->text()&&cItem->isSelectable()){
        //判断是否在排课模式，是否是当前排课的课程，是否可选择（禁止擦除表头数据）
        cItem->setText(QString());
        data[ui->lineEdit_arrN->text().toInt()-1].mRemaining++;//剩余次数++
        //标签同步更改
        ui->lineEdit_arrNleft->setText(QString::number(data[ui->lineEdit_arrN->text().toInt()-1].mRemaining));
        //清除背景色
        cItem->setBackground(QBrush());
        //删除对应的ChartList，不影响报表
        int transferSlot = cItem->row()*cModel->columnCount()+cItem->column();
        ChartList[ui->lineEdit_arrN->text().toInt()-1]->remove(transferSlot*100+ui->lineEdit_arrN->text().toInt());
    }
}

void edrMainWindow::on_btn_310_clicked()//初始化所有初始房间，其实设计的不是特别好
{
    //写完这些这么多单独的btn clicked 才想到其实可以绑定到一个槽函数上，而且后续添加机房也使用了这种想法。
    ui->tableView->setModel(&mo_310);
    lb_room.setText("当前教室：北区310");
    index = mo_310.index(0,0);
    lb_ppl.setText(QString("当前教室人数：%1").arg(mo_310.data(index,Qt::UserRole).toString()));
    //qDebug()<<mo_310.data(index,Qt::UserRole);测试人数
}

void edrMainWindow::on_btn_311_clicked()
{
    ui->tableView->setModel(&mo_311);
    lb_room.setText("当前教室：北区311");
    // mo_311.setData(mo_311.index(0,0),30,Qt::UserRole);//测试不同index是否通用
    // qDebug()<<mo_311.data(index,Qt::UserRole);
    index = mo_311.index(0,0);
    lb_ppl.setText(QString("当前教室人数：%1").arg(mo_311.data(index,Qt::UserRole).toString()));

}

void edrMainWindow::on_btn_312_clicked()
{
    ui->tableView->setModel(&mo_312);
    lb_room.setText("当前教室：北区312");
    index = mo_312.index(0,0);
    lb_ppl.setText(QString("当前教室人数：%1").arg(mo_312.data(index,Qt::UserRole).toString()));
}

void edrMainWindow::on_btn_417_clicked()
{
    ui->tableView->setModel(&mo_417);
    lb_room.setText("当前教室：北区417");
    index = mo_417.index(0,0);
    lb_ppl.setText(QString("当前教室人数：%1").arg(mo_417.data(index,Qt::UserRole).toString()));
}

void edrMainWindow::on_btn_418_clicked()
{
    ui->tableView->setModel(&mo_418);
    lb_room.setText("当前教室：北区418");
    index = mo_418.index(0,0);
    lb_ppl.setText(QString("当前教室人数：%1").arg(mo_418.data(index,Qt::UserRole).toString()));
}

void edrMainWindow::on_btn_R1_clicked()
{
    ui->tableView->setModel(&mo_R1);
    lb_room.setText("当前教室：未来城R1");
    index = mo_R1.index(0,0);
    lb_ppl.setText(QString("当前教室人数：%1").arg(mo_R1.data(index,Qt::UserRole).toString()));
}

void edrMainWindow::on_btn_R2_clicked()
{
    ui->tableView->setModel(&mo_R2);
    lb_room.setText("当前教室：未来城R2");
    index = mo_R2.index(0,0);
    lb_ppl.setText(QString("当前教室人数：%1").arg(mo_R2.data(index,Qt::UserRole).toString()));
}

void edrMainWindow::on_btn_R3_clicked()
{
    ui->tableView->setModel(&mo_R3);
    lb_room.setText("当前教室：未来城R3");
    index = mo_R3.index(0,0);
    lb_ppl.setText(QString("当前教室人数：%1").arg(mo_R3.data(index,Qt::UserRole).toString()));
}

void edrMainWindow::on_btn_RA_clicked()
{
    ui->tableView->setModel(&mo_RA);
    lb_room.setText("当前教室：西区RA");
    index = mo_RA.index(0,0);
    lb_ppl.setText(QString("当前教室人数：%1").arg(mo_RA.data(index,Qt::UserRole).toString()));
}

void edrMainWindow::on_btn_RB_clicked()
{
    ui->tableView->setModel(&mo_RB);
    lb_room.setText("当前教室：西区RB");
    index = mo_RB.index(0,0);
    lb_ppl.setText(QString("当前教室人数：%1").arg(mo_RB.data(index,Qt::UserRole).toString()));
}

void edrMainWindow::on_btn_RC_clicked()
{
    ui->tableView->setModel(&mo_RC);
    lb_room.setText("当前教室：西区RC");
    index = mo_RC.index(0,0);
    lb_ppl.setText(QString("当前教室人数：%1").arg(mo_RC.data(index,Qt::UserRole).toString()));
}

void edrMainWindow::on_btn_RD_clicked()
{
    ui->tableView->setModel(&mo_RD);
    lb_room.setText("当前教室：西区RD");
    index = mo_RD.index(0,0);
    lb_ppl.setText(QString("当前教室人数：%1").arg(mo_RD.data(index,Qt::UserRole).toString()));
}

void edrMainWindow::on_btn_RE_clicked()
{
    ui->tableView->setModel(&mo_RE);
    lb_room.setText("当前教室：西区RE");
    index = mo_RE.index(0,0);
    lb_ppl.setText(QString("当前教室人数：%1").arg(mo_RE.data(index,Qt::UserRole).toString()));
}

void edrMainWindow::on_btn_Exp_toggled(bool checked)//选择浏览模式时
{
    if(checked)ui->dockWidget_2->setVisible(false);//隐藏底部工具栏
}


void edrMainWindow::on_btn_Arr_toggled(bool checked)//进入排课模式时
{
    if(checked){
        ui->dockWidget_2->setVisible(true);
    }
    ui->stackedWidget->setCurrentIndex(0);
    if(!checked){
        ui->pushButton_arr->setChecked(false);//切到其他模式时，将开始排课按钮取消选择，关闭排课模式
    }
}

void edrMainWindow::on_bttn_Chart_toggled(bool checked)//进入报表模式
{
    if(checked){
        ui->dockWidget_2->setVisible(true);
    }
    ui->stackedWidget->setCurrentIndex(1);
}

void edrMainWindow::on_btn_Stat_clicked()//统计按钮
{
    statDialog * dlg = new statDialog(this,data.size());
    dlg->setWindowFlag(Qt::MSWindowsFixedSizeDialogHint);
    QStandardItem * tItem = nullptr;
    for(int i = 0;i<data.size();i++){
        tItem = new QStandardItem;
        tItem->setSelectable(false);
        tItem->setEditable(false);
        tItem->setText(data[i].mStuDepar);
        dlg->m_chart->setItem(2+i,0,tItem);
        tItem = new QStandardItem;
        tItem->setSelectable(false);
        tItem->setEditable(false);
        tItem->setText(data[i].mTeacher);
        dlg->m_chart->setItem(2+i,1,tItem);
        tItem = new QStandardItem;
        tItem->setSelectable(false);
        tItem->setEditable(false);
        tItem->setText(data[i].mClass);
        dlg->m_chart->setItem(2+i,2,tItem);
        tItem = new QStandardItem;
        tItem->setSelectable(false);
        tItem->setEditable(false);
        tItem->setText(data[i].mName);
        dlg->m_chart->setItem(2+i,3,tItem);
        tItem = new QStandardItem;
        tItem->setSelectable(false);
        tItem->setEditable(false);
        tItem->setText(QString::number(data[i].mNum));
        dlg->m_chart->setItem(2+i,4,tItem);
    }
    dlg->resize();
    dlg->exec();
    delete dlg;
}


void edrMainWindow::on_btn_ppl_clicked()//设置人数按钮
{
    if(ui->tableView->model()){
        bool isEdit=0;
        int inputValue = QInputDialog::getInt(this,"输入人数","输入该教室人数",120,30,120,1,&isEdit);
        if(isEdit){
            QAbstractItemModel * tmodel = ui->tableView->model();
            tmodel->setData(tmodel->index(0,0),inputValue,Qt::UserRole);//在0,0设置用户数据存储人数
            lb_ppl.setText(QString("当前教室人数：%1").arg(inputValue));//更新标签
        }
    }
}
//以下为第二个功能——排课功能实现
void edrMainWindow::on_pushButton_arrN_clicked()//生成排课码 按钮
{
    QString strCourseN = ui->line_courseN->text();//先获取框中输入的内容
    QString strteacher = ui->comboBox_tch->currentText();
    QString strstu = ui->comboBox_stuy->currentText();
    QString strstudepar = ui->line_stuDepar->text();
    QString strtchdepar = ui->line_tchDepar->text();
    bool isfind =0;
    bool isempty =0;
    for(int i = 0;i<data.size();i++){//提供在只填写课程名与教师名的情况下自动补全，同样需要点一下按钮排课码，后续信息直接无视
        if(strCourseN==data[i].mName&&data[i].mTeacher==strteacher&&strstu==data[i].mClass){
            isfind =1;
            ui->line_tchDepar->setText(data[i].mTeacherDepar);
            ui->line_stuDepar->setText(data[i].mStuDepar);
            ui->spinBox_arr->setValue(data[i].mNum);
            ui->lineEdit_arrN->setText(QString::number(i+1));
            ui->lineEdit_arrNleft->setText(QString::number(data[i].mRemaining));
            break;
        }
    }
    if(!isfind){//判断数据是否都填写完毕
        if(strCourseN.isEmpty()||strteacher.isEmpty()||strstu.isEmpty()||strstudepar.isEmpty()||strtchdepar.isEmpty()||ui->spinBox_arr->value()<=0){
            isempty = 1;
            QMessageBox::information(this,"无法生成排课码","有数据为空！",QMessageBox::Ok);
        }
    }
    if(!isfind&&!isempty){//新建一个排课码
        CourseInfo newInfo;
        newInfo.mClass=strstu;
        newInfo.mName=strCourseN;
        newInfo.mTeacher=strteacher;
        newInfo.mStuDepar=strstudepar;
        newInfo.mTeacherDepar=strtchdepar;
        newInfo.mNum=ui->spinBox_arr->value();
        newInfo.mRemaining=newInfo.mNum;
        data.append(newInfo);
        ui->lineEdit_arrN->setText(QString::number(data.size()));//排课码
        ui->lineEdit_arrNleft->setText(QString::number(ui->spinBox_arr->value()));//剩余次数
        //Chartlist增加数据便于后续处理
        ChartList.append(new QMap<int,ChartInfo>);
        //这里的下拉框和后面报表功能的下拉框增加选项
        ui->comboBox_Acourse->addItem(strCourseN);
        ui->comboBox_stuy->addItem(strstu);
        ui->comboBox_tch->addItem(strteacher);
        ui->comboBox_Ateacher->addItem(strteacher);
    }
}

void edrMainWindow::on_pushButton_arr_toggled(bool checked)//开启排课模式按钮自检
{
    if(checked){
        if(ui->lineEdit_arrN->text().isEmpty()){//判断是否有排课码，没有不允许进入排课模式
            QMessageBox::information(this,"无法开始排课","尚未生成排课码！",QMessageBox::Ok);
            ui->pushButton_arr->setChecked(false);
        }
    }
}


void edrMainWindow::on_tableView_doubleClicked(const QModelIndex &index)//双击添加排课
{
    QStandardItemModel * cModel = dynamic_cast<QStandardItemModel*>(ui->tableView->model());
    QStandardItem * cItem = cModel->itemFromIndex(index);
    // qDebug()<<ui->pushButton_arr->isChecked();//一开始排课没反应，测试
    // qDebug()<<cItem->isSelectable();//测试禁止对表头修改
    if(ui->pushButton_arr->isChecked()&&cItem->isSelectable()){//排课模式且非标题格子
        int tRemaining = ui->lineEdit_arrNleft->text().toInt();//一开始排课不掉数字，后来发现是自己起名起混淆了，获取了arrn的text
        int arrN=ui->lineEdit_arrN->text().toInt();
        //qDebug()<<tRemaining;
        if(!cItem->text().isEmpty()){//两个条件不允许排课
            QMessageBox::information(this,"无法进行排课操作","该时间段已排课！",QMessageBox::Ok);
        }
        else if(!tRemaining){
            QMessageBox::information(this,"无法进行排课操作","排课次数已用尽！",QMessageBox::Ok);
        }
        else {//某一时段重复添加
            int transferSlot = cItem->row()*cModel->columnCount()+cItem->column();
            //ChartList[arrN-1]->find(transferSlot)!=ChartList[arrN-1]->end()无效，寻找原因
            // qDebug()<<transferSlot;
            // qDebug()<<transferSlot*100+arrN;
            // qDebug()<<ChartList[arrN-1]->find(transferSlot*100+arrN).key();
            // qDebug()<<ChartList[arrN-1]->end().key();
            //原因是因为应该find(transferSlot*100+arrN)
            if(ChartList[arrN-1]->find(transferSlot*100+arrN)!=ChartList[arrN-1]->end()){
                QMessageBox::information(this,"无法进行排课操作","该时段已在其他地方排课！",QMessageBox::Ok);
            }
            else{//成功排课
                cItem->setText(ui->lineEdit_arrN->text());//item文字设置为排课码
                data[arrN-1].mRemaining--;//剩余次数-1
                ui->lineEdit_arrNleft->setText(QString::number(data[arrN-1].mRemaining));
                cItem->setTextAlignment(Qt::AlignCenter);
                cItem->setBackground(QBrush(Qt::yellow));
                //Chartlist增加数据便于后续报表处理
                ChartInfo tCInfo;
                tCInfo.JiFang=lb_room.text().remove(0,5);
                tCInfo.row=cItem->row();
                tCInfo.line=cItem->column();
                // qDebug()<<cItem->column();
                // qDebug()<<cModel->item(0,cItem->column())->text();
                tCInfo.Week=cModel->item(0,((cItem->column()-2)/3)*3+2)->text();
                //只能提取合并的那个主item的数据
                tCInfo.WuBie=cModel->item(1,cItem->column())->text();
                int transferDays = 7*(cItem->row()-2)+(cItem->column()-2)/3;
                //行起始为0，所以不能-3，列同理
                tCInfo.date=iniDate.addDays(transferDays);
                ChartList[arrN-1]->insert(transferSlot*100+arrN,tCInfo);//键值为第几格*100+排课码
            }
        }
    }
}

//以下为报表功能实现
void edrMainWindow::on_btn_generateChart_clicked()//生成报表按钮
{
    bool isFind =0;
    int arrN0=0;//初始为0的排课码
    if(ui->comboBox_Ateacher->currentText().isEmpty()||ui->comboBox_Acourse->currentText().isEmpty()){
        QMessageBox::information(this,"无法生成报表","请填写课程名称与课程教师！",QMessageBox::Ok);
    }
    else{
        for(int i =0;i<data.size();i++){
            if(data[i].mName==ui->comboBox_Acourse->currentText()&&data[i].mTeacher==ui->comboBox_Ateacher->currentText()){
                isFind=1;
                arrN0=i;
                break;
            }
        }
        if(!isFind){
            QMessageBox::information(this,"无法生成报表","未找到对应的课程！\n请检查输入是否有误。",QMessageBox::Ok);
        }
        // else if(!data[arrN0].mRemaining){
        //     QMessageBox::information(this,"无法生成报表","尚未排完全部课程！",QMessageBox::Ok);
        // }//未排完课程不允许报表，不过还是废弃了，应该也允许的
        else{
            //补充其余框
            ui->lineEdit_AClass->setText(data[arrN0].mClass);
            ui->lineEdit_ANum->setText(QString::number(data[arrN0].mNum));
            ui->lineEdit_ASD->setText(data[arrN0].mStuDepar);
            ui->lineEdit_ATD->setText(data[arrN0].mTeacherDepar);
            chartDialog * dlg = new chartDialog(this,data[arrN0].mNum-data[arrN0].mRemaining);
            dlg->setWindowFlag(Qt::MSWindowsFixedSizeDialogHint);
            QStandardItem * tItem = new QStandardItem;
            tItem->setSelectable(false);
            tItem->setEditable(false);
            tItem->setText(data[arrN0].mName);
            dlg->m_chart->setItem(1,1,tItem);
            dlg->m_chart->setItem(1,2,tItem);
            tItem = new QStandardItem;
            tItem->setSelectable(false);
            tItem->setEditable(false);
            tItem->setText(data[arrN0].mTeacher);
            dlg->m_chart->setItem(1,4,tItem);
            tItem = new QStandardItem;
            tItem->setSelectable(false);
            tItem->setEditable(false);
            tItem->setText(data[arrN0].mClass);
            dlg->m_chart->setItem(2,1,tItem);
            dlg->m_chart->setItem(2,2,tItem);
            dlg->m_chart->setItem(2,3,tItem);
            dlg->m_chart->setItem(2,4,tItem);
            QMap<int,ChartInfo>::const_iterator j=ChartList[arrN0]->constBegin();//map的起始指针
            for(int i=0;i<ChartList[arrN0]->size();i++,j++){
                tItem = new QStandardItem;
                tItem->setSelectable(false);
                tItem->setEditable(false);
                tItem->setText(QString::number(i+1));
                dlg->m_chart->setItem(4+i,0,tItem);
                tItem = new QStandardItem;
                tItem->setSelectable(false);
                tItem->setEditable(false);
                tItem->setText(j->date.toString("M月dd日"));
                dlg->m_chart->setItem(4+i,1,tItem);
                tItem = new QStandardItem;
                tItem->setSelectable(false);
                tItem->setEditable(false);
                tItem->setText(j->Week);
                dlg->m_chart->setItem(4+i,2,tItem);
                tItem = new QStandardItem;
                tItem->setSelectable(false);
                tItem->setEditable(false);
                tItem->setText(j->WuBie);
                dlg->m_chart->setItem(4+i,3,tItem);
                tItem = new QStandardItem;
                tItem->setSelectable(false);
                tItem->setEditable(false);
                tItem->setText(j->JiFang);
                dlg->m_chart->setItem(4+i,4,tItem);
            }
            dlg->resize();
            dlg->exec();
            delete dlg;
        }
    }
}

//以下为添加机房功能实现
void edrMainWindow::on_pushButton_addroom_clicked()
{
    roomDialog * dlg = new roomDialog;
    dlg->setWindowFlag(Qt::MSWindowsFixedSizeDialogHint);
    int ret = dlg->exec();

    if(ret == QDialog::Accepted){
        //拿到数据
        int rindex = dlg->AreaChoice();
        QString roomName = dlg->getName();
        int roomPpl = dlg->getppl();
        if(roomName.isEmpty()){
            QMessageBox::information(this,"无法添加机房操作","请输入机房名称！",QMessageBox::Ok);
            return;
        }
        //新建model，初始化
        QStandardItemModel * new_mdl = new QStandardItemModel;
        moList.append(new_mdl);
        initModel(new_mdl);
        //设置人数
        new_mdl->setData(new_mdl->index(0,0),roomPpl,Qt::UserRole);
        //设置按钮
        QPushButton * new_btn = new QPushButton(ui->page_1);
        new_btn->setProperty("number",moList.size()-1);//设置属性，辨识哪个序号
        new_btn->setProperty("index",rindex);
        new_btn->setText(roomName);
        qDebug()<<rindex;
        switch (rindex){//其实用不到←还是用到了，区分选择的区域添加到对应的区域
        case 0:
            ui->verticalLayout_NWSB->addWidget(new_btn);
            break;
        case 1:
            ui->verticalLayout_WLC->addWidget(new_btn);
            break;
        case 2:
            ui->verticalLayout_NWSX->addWidget(new_btn);
            break;
        default:break;
        }
        connect(new_btn,SIGNAL(clicked()),this,SLOT(do_btn_Other_Room_clicked()));
        btnList.append(new_btn);
    }
    delete dlg;
}

void edrMainWindow::do_btn_Other_Room_clicked()
{
    QStandardItemModel * cur_model = moList[sender()->property("number").toInt()];
    ui->tableView->setModel(cur_model);
    QString lbstring = "当前教室：";
    QPushButton * cur_btn = qobject_cast<QPushButton*>(sender());
    //qDebug()<<sender();
    //qDebug()<<cur_btn->text();
    //qDebug()<<cur_btn->property("number");
    switch (ui->toolBox->currentIndex()){
    case 0:
        lbstring +=QString("北区%1").arg(cur_btn->text());
        break;
    case 1:
        lbstring +=QString("未来城%1").arg(cur_btn->text());
        break;
    case 2:
        lbstring +=QString("西区%1").arg(cur_btn->text());
        break;
    default:break;
    }
    lb_room.setText(lbstring);
    index = cur_model->index(0,0);
    lb_ppl.setText(QString("当前教室人数：%1").arg(cur_model->data(index,Qt::UserRole).toString()));
}

//void edrMainWindow::init_buttons(QPushButton *newBtn){}//本来是打算初始化按钮的一些额外操作的，后来发现没有用上
//以下为存储功能
void edrMainWindow::on_act_save_triggered()
{
    QString curPath = QDir::currentPath();
    QString dlgTitle= "保存为";
    QString filter = "二进制数据流文件(*.stream);;所有文件(*.*)";
    QString sFileName= QFileDialog::getSaveFileName(this,dlgTitle,curPath,filter);
    if(sFileName.isEmpty())
    {
        qDebug()<<"File 404";
        return ;
    }
    QFileInfo fileInfo(sFileName);
    QDir::setCurrent(fileInfo.absoluteFilePath());
    //保存文件
    QFile fileDevice(sFileName);
    if(!fileDevice.open(QIODevice::WriteOnly))return;
    QDataStream fileStream(&fileDevice);
    fileStream.setVersion(QDataStream::Qt_6_7);
    //有以下内容要存储：1、模型item，2、排课码及对应排课信息，3、新增机房，4、报表内容暂存
    //排课码和对应排课信息存储
    int N = data.size();
    fileStream<<N;
    for (int i = 0; i < N; ++i) {
        fileStream<<data[i].mClass;
        fileStream<<data[i].mName;
        fileStream<<data[i].mNum;
        fileStream<<data[i].mRemaining;
        fileStream<<data[i].mStuDepar;
        fileStream<<data[i].mTeacher;
        fileStream<<data[i].mTeacherDepar;
    }
    //报表内容
    int M = ChartList.size();
    fileStream<<M;
    for (int i = 0; i < M; ++i){
        int total = ChartList[i]->size();
        fileStream<<total;
        QMap<int,ChartInfo>::const_iterator tit=ChartList[i]->constBegin();//map的起始指针
        for (int j = 0; j < total; ++j,++tit) {
            fileStream<<tit.key();
            fileStream<<tit->JiFang;
            fileStream<<tit->Week;
            fileStream<<tit->WuBie;
            fileStream<<tit->date;
            fileStream<<tit->line;
            fileStream<<tit->row;
        }
    }
    //内置模型
    saveModel(&mo_310,fileStream,N);
    saveModel(&mo_311,fileStream,N);
    saveModel(&mo_312,fileStream,N);
    saveModel(&mo_417,fileStream,N);
    saveModel(&mo_418,fileStream,N);
    saveModel(&mo_R1,fileStream,N);
    saveModel(&mo_R2,fileStream,N);
    saveModel(&mo_R3,fileStream,N);
    saveModel(&mo_RA,fileStream,N);
    saveModel(&mo_RB,fileStream,N);
    saveModel(&mo_RC,fileStream,N);
    saveModel(&mo_RD,fileStream,N);
    saveModel(&mo_RE,fileStream,N);
    //新增机房
    int roomN = moList.size();
    fileStream<<roomN;
    for (int i = 0; i < roomN; ++i) {
        saveModel(moList[i],fileStream,N);
    }
    for (int i = 0; i < roomN; ++i) {
        //没有toint，tolonglong导致后续出错
        fileStream<<btnList[i]->text()<<btnList[i]->property("index").toInt()<<btnList[i]->property("number").toLongLong();
        //qDebug()<<btnList[i]->property("index").toInt()<<btnList[i]->property("number").toLongLong();
    }
    fileDevice.close();
}


void edrMainWindow::saveModel(QStandardItemModel *tModel,QDataStream & fStream,int total)//模型item
{
    int ppl = tModel->data(tModel->index(0,0),Qt::UserRole).toInt();
    fStream<<ppl;
    //qDebug()<<"ppl:"<<ppl;
    //把表头暂时清空，防止存储无用item←因为find items只能指定列，所以不需要了
    //QList<QStandardItem *> C1,C2,R1,R2;
    // C1 = tModel->takeColumn(0);
    // C2 = tModel->takeColumn(0);
    // R1 = tModel->takeRow(0);
    // R2 = tModel->takeRow(0);
    // tModel->insertColumn(0);
    // tModel->insertColumn(0);
    // tModel->insertRow(0);
    // tModel->insertRow(0);
    // QList<QStandardItem *> dblist = tModel->findItems(QString::number(1),Qt::MatchRecursive,2);
    // fStream<<dblist.size();
    // qDebug()<<"dbsize:"<<dblist.size();
    // qDebug()<<"db:"<<tModel->item(2,2)->text();
    // qDebug()<<QString::number(1);
    // for (int var = 0; var < dblist.size(); ++var) {
    //     qDebug()<<"dbtext:"<<dblist[var]->text();
    //     qDebug()<<dblist[var]->row();
    //     qDebug()<<dblist[var]->column();
    // }
    for (int i = 1; i <= total; ++i) {
        //finditems只能一列一列找，其实很麻烦
        for (int var = 2; var < 17; ++var) {
            QList<QStandardItem *> tlist = tModel->findItems(QString::number(i),Qt::MatchFixedString,var);
            fStream<<tlist.size();
            //qDebug()<<"size:"<<tlist.size();
            for (int j = 0; j < tlist.size(); ++j) {
                //直接存储<<QStandarditem好像出问题，试试文字
                fStream<<tlist[j]->text();
                fStream<<tlist[j]->row();
                fStream<<tlist[j]->column();
                //qDebug()<<"text:"<<tlist[j]->text();
                //qDebug()<<tlist[j]->row();
                //qDebug()<<tlist[j]->column();
            }
        }
    }
    //恢复表格状态←因为find items只能指定列，所以不需要了
    // tModel->takeColumn(0);
    // tModel->takeColumn(0);
    // tModel->takeRow(0);
    // tModel->takeRow(0);
    // tModel->insertRow(0,R2);
    // tModel->insertRow(0,R1);
    // tModel->insertColumn(0,C2);
    // tModel->insertColumn(0,C1);
    // ui->tableView->setSpan(0,0,2,1);//合并单元格
    // ui->tableView->setSpan(0,1,2,1);//合并单元格
    // ui->tableView->setSpan(0,2,1,3);//合并单元格
    // ui->tableView->setSpan(0,5,1,3);//合并单元格
    // ui->tableView->setSpan(0,8,1,3);//合并单元格
    // ui->tableView->setSpan(0,11,1,3);//合并单元格
}

void edrMainWindow::on_act_load_triggered()
{
    QString curPath = QDir::currentPath();
    QString dlgTitle= "打开文件";
    QString filter = "二进制数据流文件(*.stream);;所有文件(*.*)";
    QString oFileName= QFileDialog::getOpenFileName(this,dlgTitle,curPath,filter);
    if(oFileName.isEmpty())
    {
        qDebug()<<"File 404";
        return ;
    }
    QFileInfo fileInfo(oFileName);
    QDir::setCurrent(fileInfo.absoluteFilePath());
    //打开文件
    QFile fileDevice(oFileName);
    if(!fileDevice.open(QIODevice::ReadOnly))return;
    QDataStream fileStream(&fileDevice);
    fileStream.setVersion(QDataStream::Qt_6_7);
    //先初始化
    initModel(&mo_310);//初始化模型
    initModel(&mo_311);
    initModel(&mo_312);
    initModel(&mo_417);
    initModel(&mo_418);
    initModel(&mo_R1);
    initModel(&mo_R2);
    initModel(&mo_R3);
    initModel(&mo_RA);
    initModel(&mo_RB);
    initModel(&mo_RC);
    initModel(&mo_RD);
    initModel(&mo_RE);
    ui->tableView->setSpan(0,0,2,1);//合并单元格
    ui->tableView->setSpan(0,1,2,1);//合并单元格
    ui->tableView->setSpan(0,2,1,3);//合并单元格
    ui->tableView->setSpan(0,5,1,3);//合并单元格
    ui->tableView->setSpan(0,8,1,3);//合并单元格
    ui->tableView->setSpan(0,11,1,3);//合并单元格
    ui->tableView->setSpan(0,14,1,3);//合并单元格
    lb_room.setText("当前教室：");
    lb_ppl.setText("当前教室人数：");
    lb_arr.setText("当前排课编号：");
    lb_class.setText("当前课程名：");
    lb_teacher.setText("当前教师名：");
    ui->comboBox_Ateacher->clear();
    ui->comboBox_Acourse->clear();
    ui->comboBox_stuy->clear();
    ui->comboBox_tch->clear();
    ui->lineEdit_arrN->clear();
    ui->lineEdit_arrNleft->clear();
    ui->btn_Arr->setChecked(false);
    //删除所有用户存储数据
    data.clear();
    for (int i = 0; i < ChartList.size(); ++i) {
        ChartList[i]->clear();
        delete ChartList[i];
    }
    ChartList.clear();
    for (int i = 0; i < moList.size(); ++i) {
        moList[i]->clear();
        delete moList[i];
    }
    moList.clear();
    for (int i = 0; i < btnList.size(); ++i) {
        delete btnList[i];
    }
    btnList.clear();
    //排课码和对应排课信息存储
    int N = 0;
    fileStream>>N;
    CourseInfo tCI;
    for (int i = 0; i < N; ++i) {
        fileStream>>tCI.mClass;
        fileStream>>tCI.mName;
        fileStream>>tCI.mNum;
        fileStream>>tCI.mRemaining;
        fileStream>>tCI.mStuDepar;
        fileStream>>tCI.mTeacher;
        fileStream>>tCI.mTeacherDepar;
        data.append(tCI);
        ui->comboBox_Acourse->addItem(data[i].mName);//一开始不小心设置成了班级
        ui->comboBox_stuy->addItem(data[i].mClass);
        ui->comboBox_tch->addItem(data[i].mTeacher);
        ui->comboBox_Ateacher->addItem(data[i].mTeacher);
    }
    //报表内容
    int M = 0;
    fileStream>>M;
    int tkey = 0;
    for (int i = 0; i < M; ++i){
        int total = 0;
        fileStream>>total;
        //QMap<int,ChartInfo>::const_iterator tit=ChartList[i]->constBegin();//map的起始指针
        ChartList.append(new QMap<int,ChartInfo>);
        for (int j = 0; j < total; ++j) {
            fileStream>>tkey;
            ChartInfo tCI;
            fileStream>>tCI.JiFang;
            fileStream>>tCI.Week;
            fileStream>>tCI.WuBie;
            fileStream>>tCI.date;
            fileStream>>tCI.line;
            fileStream>>tCI.row;
            ChartList[i]->insert(tkey,tCI);
        }
    }
    //内置模型
    loadModel(&mo_310,fileStream,N);
    loadModel(&mo_311,fileStream,N);
    loadModel(&mo_312,fileStream,N);
    loadModel(&mo_417,fileStream,N);
    loadModel(&mo_418,fileStream,N);
    loadModel(&mo_R1,fileStream,N);
    loadModel(&mo_R2,fileStream,N);
    loadModel(&mo_R3,fileStream,N);
    loadModel(&mo_RA,fileStream,N);
    loadModel(&mo_RB,fileStream,N);
    loadModel(&mo_RC,fileStream,N);
    loadModel(&mo_RD,fileStream,N);
    loadModel(&mo_RE,fileStream,N);
    ui->tableView->setModel(new QStandardItemModel);
    //新增机房
    int roomN = 0;
    fileStream>>roomN;
    for (int i = 0; i < roomN; ++i) {
        moList.append(new QStandardItemModel);
        initModel(moList[i]);
        loadModel(moList[i],fileStream,N);
    }
    for (int i = 0; i < roomN; ++i) {
        QString tText;
        int tindex;
        qsizetype tnumber;
        fileStream>>tText>>tindex>>tnumber;
        QPushButton * new_btn = new QPushButton(ui->page_1);
        new_btn->setProperty("number",tnumber);//设置属性，辨识哪个序号
        new_btn->setProperty("index",tindex);
        //qDebug()<<tindex;
        //qDebug()<<tnumber;
        //不能忘
        new_btn->setText(tText);
        switch (tindex){//其实用不到←还是用到了，区分选择的区域添加到对应的区域
        case 0:
            ui->verticalLayout_NWSB->addWidget(new_btn);
            break;
        case 1:
            ui->verticalLayout_WLC->addWidget(new_btn);
            break;
        case 2:
            ui->verticalLayout_NWSX->addWidget(new_btn);
            break;
        default:break;
        }
        btnList.append(new_btn);
        connect(new_btn,SIGNAL(clicked()),this,SLOT(do_btn_Other_Room_clicked()));
    }
    fileDevice.close();
}

void edrMainWindow::loadModel(QStandardItemModel *tModel, QDataStream &fStream, int total)
{
    int ppl = 0;
    fStream>>ppl;
    //qDebug()<<"ppl:"<<ppl;
    tModel->setData(tModel->index(0,0),ppl,Qt::UserRole);
    int trow =0;
    int tcolumn =0;
    QString tText = 0;
    for (int i = 1; i <= total; ++i) {
        //这个qsizetype坑了我一下，在存储时没有转换成int
        for (int var = 2; var < 17; ++var) {
            qsizetype size= 0;
            fStream>>size;
            //qDebug()<<"size:"<<size;
            for (int j = 0; j < size; ++j) {
                fStream>>tText;
                fStream>>trow;
                fStream>>tcolumn;
                //qDebug()<<"text:"<<tText;
                //qDebug()<<trow;
                //qDebug()<<tcolumn;
                QStandardItem * tItem=new QStandardItem;
                tItem->setText(tText);
                tItem->setTextAlignment(Qt::AlignCenter);
                tItem->setBackground(QBrush(Qt::yellow));
                tModel->setItem(trow,tcolumn,tItem);
            }
        }
    }
}
