#include "mainwindow.h"
#include <QApplication>
#include <QtGui>
#include <QMouseEvent>
#include <QMessageBox>
#include <string>
#include <iostream>
typedef int ll;
using namespace std;
int i,j, clickedx = -1, clickedy = -1;
char a[10][10];
void time_to_move(int x1, int y1, int x2, int y2);
void make_click(int x, int y)
{
    if (clickedx == -1)
        clickedx = x, clickedy = y;
    else
    {
        time_to_move(x,y,clickedx,clickedy);
        clickedx = clickedy = -1;
    }
}
void check(ll x, ll y)
{
    /*if (y == 8 && a[x][y] == 'w')
       a[x][y] = 'W';
    if (y == 1 && a[x][y] == 'b')
       a[x][y] = 'B';*/
}

void Clear(ll x1, ll y1, ll x2, ll y2)
{
    ll signx = (x2-x1 > 0?1:-1);
    ll signy = (y2-y1 > 0?1:-1);
    for (int i = x1+signx, j = y1+signy; i != x2; i += signx, j += signy)
        a[i][j] = '.';
}

void make_hit(string s)
{
    ll sz = s.size();
    for (int i = 0; i < sz/3; i++)
    {
        a[s[(i+1)*3]-'a'+1][s[(i+1)*3+1]-'0'] = a[s[i*3]-'a'+1][s[i*3+1]-'0'];
        check(s[(i+1)*3]-'a'+1, s[(i+1)*3+1]-'0');
        Clear(s[i*3]-'a'+1, s[i*3+1]-'0', s[(i+1)*3]-'a'+1, s[(i+1)*3+1]-'0');
        a[s[i*3]-'a'+1][s[i*3+1]-'0'] = '.';
    }
}

void time_to_move(int x2, int y2, int x1, int y1)
{
    string s = "     ";
    s[0] = x1/40+'a';
    s[1] = '8'-y1/40;
    s[3] = x2/40+'a';
    s[4] = '8'-y2/40;
    cout << s << endl;
    make_hit(s);
}

class myWidget : public QWidget
{
    QMessageBox* msgBox;
    public:
        myWidget (QWidget *parent=0) : QWidget(parent)
        {
        }

        void mouseReleaseEvent ( QMouseEvent * event )
        {
          if(event->button() == Qt::LeftButton)
          {
            make_click(event->x(), event->y());
            this->repaint();
          }
        }

        void paintEvent(QPaintEvent *pe)
        {
             QPainter p(this);
             int i,j;
             for (int i = 8; i >= 1; i--)
             {
                 for (int j = 1; j <= 8; j++)
                     if (a[j][i] == 'b')
                     {
                         QRectF target((j-1)*40, (8-i)*40, 40.0, 40.0);
                         QRectF source(0.0, 0.0, 64.0, 64.0);
                         QImage image("c:/prog/qt/try2/images/black.png");
                         QPainter painter(this);
                         painter.drawImage(target, image, source);
                     } else
                     if (a[j][i] == 'w')
                     {
                         QRectF target((j-1)*40, (8-i)*40, 40.0, 40.0);
                         QRectF source(0.0, 0.0, 64.0, 64.0);
                         QImage image("c:/prog/qt/try2/images/white.png");
                         QPainter painter(this);
                         painter.drawImage(target, image, source);
                     }
             }
        }
};

void generate()
{
    for (i = 1; i <= 8; i++)
        for (j = 1; j <= 8; j++)
            if (j <= 3 && (i+j)%2 == 0)
               a[i][j] = 'w';
            else
            if (j >= 6 && (i+j)%2 == 0)
               a[i][j] = 'b';
            else
                a[i][j] = '.';
}

int main(int argc, char *argv[])
{
    generate();
    QApplication a(argc, argv);
    myWidget w;
    w.setFixedSize(320.0, 320.0);
    w.show();
    return a.exec();
}
