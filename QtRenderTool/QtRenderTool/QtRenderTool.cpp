#include "QtRenderTool.h"
QtRenderTool::QtRenderTool(QWidget *parent)
    : QMainWindow(parent)
{
    ui.setupUi(this);
}

QtRenderTool::~QtRenderTool()
{}

void QtRenderTool::paintEvent(QPaintEvent* event)
{
    auto paintArea = this->ui.imageArea;
    QPainter painter(paintArea);
    int w = 500;
    int h = 800;
    QImage image(w, h, QImage::Format::Format_RGB888);  // RGB888 ÿ�����ص��ÿ����ɫʹ��8λ��ʾ��һ�����ص�ռ��3���ֽ�
    unsigned char* data = image.bits();  // ͼ����ʹ�õ��ڴ�
    painter.begin(this);

    /* �ı�ÿ�����ص����ɫ */
    for (int i = 0; i < h; i++)
    {
        int begin = i * w * 3;  // ÿ�еĿ�ʼ��

        for (int j = 0; j < w * 3; j += 3)
        {
            data[begin + j] = 255;    // R
            data[begin + j + 1] = 0;  // G
            data[begin + j + 2] = 0;  // B
        }
    }

    auto area_width = paintArea->width();
    auto area_height= paintArea->height();
    image= image.scaled(area_width, area_height);
    painter.drawImage(0, 0, image);

    painter.end();
}
