#include "map_read.h"
#include <cmath>
#include <QFile>
#include <QDebug>
#include <QPainter>
#include <QJsonObject>
#include <QJsonArray>
#include <QJsonDocument>
#include <QJsonValue>
#include <QJsonParseError>
#include "map_read.h"
#define FILENAME "D:\\qt5.9file\\luojia\\map-picture\\1.smap"
map_read::map_read()
{
    size_x=0;
    size_y=0;
    origin_x=0;
    origin_y=0;
    cJSON* m_jsonStr=NULL;
}
void map_read::get_size()
{


        cJSON* item = NULL;
        double v_double_x = 0.0;
        double v_double_y = 0.0;

       const char* arrStr[] = { "minpos", "maxpos" };		// 可以提前定义需要解析的对象键，这样就可以使用for循环进行解析了

        item = cJSON_GetObjectItem(this->m_jsonStr, "header");
        if (item != NULL) {
            cJSON* val = NULL;
            int size = sizeof(arrStr) / sizeof(char*);
            // 通过遍历指针数组，获得每个对象的键，在进行解析操作（如果不使用for循环解析，那就老老实实的写代码将全部个数解析完毕）
            for (int i = 0; i < size; i++) {
                cJSON* obj1 = cJSON_GetObjectItem(item, arrStr[i]);
                if (obj1 != NULL && obj1->type == cJSON_Object) {

                    val = cJSON_GetObjectItem(obj1, "x");
                    if (val != NULL && val->type == cJSON_Number) {
                        v_double_x = val->valuedouble - v_double_x  ;
                        if (i == 0)
                        {
                            this->origin_x = val->valuedouble;
                            printf("origin_x = %f\n", this->origin_x);

                        }
                    }
                    val = cJSON_GetObjectItem(obj1, "y");
                    if (val != NULL && val->type == cJSON_Number) {
                        v_double_y = val->valuedouble - v_double_y;
                        if (i == 0)
                        {
                            this->origin_y = val->valuedouble;
                            printf("origin_y = %f\n", this->origin_y);
                        }
                    }

                }
            }
        }
        this->size_x = abs(v_double_x)*1000;
        this->size_y = abs(v_double_y)*1000;
        printf("size_x = %d\n",this->size_x);
        printf("size_y = %d\n", this->size_y);
}
void map_read::get_json()
{
    QFile jsonFile(FILENAME);
    if(! jsonFile.open(QIODevice::ReadOnly | QIODevice::Text))
        return;
    QByteArray jsonInfo = jsonFile.readAll();
    cJSON *root = cJSON_Parse(jsonInfo.data());
    if (!root) {
        printf("Error before: [%s]\n", cJSON_GetErrorPtr());
        free(this->m_jsonStr);
        return;
    }
    this->m_jsonStr = root;
}
void map_read::map_draw()
{
    double v_double_x = 0.0;
    double v_double_y = 0.0;
    int x, y = 0;
    MyPoint mypoint;
    QFile file(FILENAME);
    if (!file.open(QFile::ReadOnly | QFile::Text)) {
        qDebug() << "can't open error!";
        return;
    }
    QTextStream stream(&file);
    stream.setCodec("UTF-8");
    QString str = stream.readAll();
    file.close();
    QJsonParseError jsonError;
    QJsonDocument doc = QJsonDocument::fromJson(str.toUtf8(), &jsonError);
    if (jsonError.error != QJsonParseError::NoError && !doc.isNull()) {
        qDebug() << "Json格式错误！" << jsonError.error;
        return;
    }
    QJsonObject rootObj = doc.object();
    QJsonValue xyValue = rootObj.value("normalPosList");
    if (xyValue.type() == QJsonValue::Array) {
        // 转换成数组类型
        QJsonArray xyArray = xyValue.toArray();
        // 遍历数组
        for (int i = 0; i < xyArray.count(); i++) {
            // 获取数组的第一个元素，类型是QJsonValue
            QJsonValue xyValueChild = xyArray.at(i);
            // 判断是不是对象类型
            if (xyValueChild.type() == QJsonValue::Object) {
                // 转换成对象类型
                QJsonObject xyObj = xyValueChild.toObject();
                // 最后通过value函数就可以获取到值了，解析成功
                QJsonValue xValue = xyObj.value("x");
                QJsonValue yValue = xyObj.value("y");
                v_double_x = xValue.toDouble();
                x = (v_double_x - this->origin_x)*1000;
                v_double_y = yValue.toDouble();
                y = (v_double_y - this->origin_y)*1000;
                if(this->Mypoints.empty())
                {
                    mypoint.x=x;
                    mypoint.y=y;
                    Mypoints.push_back(mypoint);
                }
               else{
                    if(this->Mypoints.back().x!=x||this->Mypoints.back().y!=y)
                    {
                       mypoint.x=x;
                       mypoint.y=y;
                       Mypoints.push_back(mypoint);
                    }
               }
            }

        }
        int size=Mypoints.size();
        this->sum_plot=size;
        printf("sum_size = %d\n", size);
    }
}
