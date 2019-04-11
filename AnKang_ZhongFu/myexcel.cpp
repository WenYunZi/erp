#include "myexcel.h"

myExcel::myExcel(QWidget *parent) :
    QDialog(parent)
{
}

//第一个参数是页面上的表格，第二个是导出文件的表头数据
void myExcel::Table2ExcelByHtml(QTableView *table,QString title)
{
    QString fileName = QFileDialog::getSaveFileName(table,"保存",QStandardPaths::writableLocation(QStandardPaths::DocumentsLocation),"Excel 文件(*.xls *.xlsx)");
    if (fileName!="")
    {
        QAxObject *excel = new QAxObject;
        if (excel->setControl("Excel.Application")){ //连接Excel控件
            excel->dynamicCall("SetVisible (bool Visible)","false");//不显示窗体
            excel->setProperty("DisplayAlerts", false);//不显示任何警告信息。如果为true那么在关闭是会出现类似“文件已修改，是否保存”的提示
            QAxObject *workbooks = excel->querySubObject("WorkBooks");//获取工作簿集合
            workbooks->dynamicCall("Add");//新建一个工作簿
            QAxObject *workbook = excel->querySubObject("ActiveWorkBook");//获取当前工作簿
            QAxObject *worksheet = workbook->querySubObject("Worksheets(int)", 1);

            int i,j;
            //QTablewidget 获取数据的列数
            //int colcount=table->columnCount();
            //QTablewidget 获取数据的行数
            //int rowcount=table->rowCount();

            //QTableView 获取列数
            int colcount=table->model()->columnCount();
            //QTableView 获取行数
            int rowcount=table->model()->rowCount();

            QAxObject *cell,*col;

            QProgressDialog *progressDialog = new QProgressDialog(this);
            progressDialog->setFixedSize(500,100);
            progressDialog->setWindowModality(Qt::WindowModal);//采用模拟的方式进行显示，即显示进度的同时，其他窗口将不响应输入信号
            progressDialog->setWindowTitle(tr("请等待"));//设置标题的显示时间
            progressDialog->setLabelText(tr("正在构建Excel表头..."));
            progressDialog->setCancelButtonText(tr("取消"));//退出按钮名字
            progressDialog->setRange(0,colcount+1);//设置显示的范围


            //标题行
            cell=worksheet->querySubObject("Cells(int,int)", 1, 1);
            cell->dynamicCall("SetValue(const QString&)", title);
            cell->querySubObject("Font")->setProperty("Size", 18);
            //调整行高
            worksheet->querySubObject("Range(const QString&)", "1:1")->setProperty("RowHeight", 30);
            //合并标题行
            QString cellTitle;
            cellTitle.append("A1:");
            cellTitle.append(QChar(colcount - 1 + 'A'));
            cellTitle.append(QString::number(1));
            QAxObject *range = worksheet->querySubObject("Range(const QString&)", cellTitle);
            range->setProperty("WrapText", true);
            range->setProperty("MergeCells", true);
            range->setProperty("HorizontalAlignment", -4108);//xlCenter
            range->setProperty("VerticalAlignment", -4108);//xlCenter

            //设置当前的标题进度
            progressDialog->setValue(1);
            //如果检测到按钮取消被激活，就跳出去
            if(progressDialog->wasCanceled()){
              return;
            }

            //列标题
            int columnCount = 1;
            for(i=0;i<colcount;i++)
            {
                QString columnName;
                columnName.append(QChar(i  + 'A'));
                columnName.append(":");
                columnName.append(QChar(i + 'A'));
                col = worksheet->querySubObject("Columns(const QString&)", columnName);
                col->setProperty("ColumnWidth", table->columnWidth(i)/6);
                cell=worksheet->querySubObject("Cells(int,int)", 2, i+1);
                //QTableWidget 获取表格头部文字信息
                //columnName=table->horizontalHeaderItem(i)->text();
                //QTableView 获取表格头部文字信息
                columnName=table->model()->headerData(i,Qt::Horizontal,Qt::DisplayRole).toString();
                cell->dynamicCall("SetValue(const QString&)", columnName);
                cell->querySubObject("Font")->setProperty("Bold", true);
                cell->querySubObject("Interior")->setProperty("Color",QColor(191, 191, 191));
                cell->setProperty("HorizontalAlignment", -4108);//xlCenter
                cell->setProperty("VerticalAlignment", -4108);//xlCenter

                //设置当前的标题进度
                progressDialog->setValue(++columnCount);
                //如果检测到按钮取消被激活，就跳出去
                if(progressDialog->wasCanceled()){
                  return;
                }
            }

            //数据区

            //QTableWidget 获取表格数据部分
            //for(i=0;i<rowcount;i++){
            //    for (j=0;j<colcount;j++)
            //    {
            //        worksheet->querySubObject("Cells(int,int)", i+3, j+1)->dynamicCall("SetValue(const QString&)", table->item(i,j)?table->item(i,j)->text():"");
            //    }
            //}


            //设置当前的标题进度
            progressDialog->setRange(0,colcount*rowcount);//设置显示的范围
            progressDialog->setLabelText(tr("正在生成Excel数据..."));
            progressDialog->setValue(0);

            //QTableView 获取表格数据部分
            int count = 0;
            for(i=0;i<rowcount;i++) //行数
            {
                for (j=0;j<colcount;j++)//列数
                {
                    QModelIndex index = table->model()->index(i, j);
                    QString strdata=table->model()->data(index).toString();
                    worksheet->querySubObject("Cells(int,int)", i+3, j+1)->dynamicCall("SetValue(const QString&)", strdata);
                    progressDialog->setValue(++count);   //设置当前的值
                    //如果检测到按钮取消被激活，就跳出去
                    if(progressDialog->wasCanceled()){
                      return;
                    }
                }
            }


            //画框线
            QString lrange;
            lrange.append("A2:");
            lrange.append(colcount - 1 + 'A');
            lrange.append(QString::number(table->model()->rowCount() + 2));
            range = worksheet->querySubObject("Range(const QString&)", lrange);
            range->querySubObject("Borders")->setProperty("LineStyle", QString::number(1));
            range->querySubObject("Borders")->setProperty("Color", QColor(0, 0, 0));
            //调整数据区行高
            QString rowsName;
            rowsName.append("2:");
            rowsName.append(QString::number(table->model()->rowCount() + 2));
            range = worksheet->querySubObject("Range(const QString&)", rowsName);
            range->setProperty("RowHeight", 20);
            workbook->dynamicCall("SaveAs(const QString&)",QDir::toNativeSeparators(fileName));//保存至fileName
            workbook->dynamicCall("Close()");//关闭工作簿
            excel->dynamicCall("Quit()");//关闭excel
            delete excel;
            excel=NULL;
            if (QMessageBox::question(NULL,"完成","文件已经导出，是否现在打开？",QMessageBox::Yes|QMessageBox::No)==QMessageBox::Yes){
                QDesktopServices::openUrl(QUrl("file:///" + QDir::toNativeSeparators(fileName)));
            }
        }
        else{
            QMessageBox::warning(NULL,"错误","未能创建 Excel 对象，请安装 Microsoft Excel。",QMessageBox::Apply);
        }
    }
}
