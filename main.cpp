#include <QByteArray>
#include <QFile>
#include <QMap>
#include <QByteArray>
#include <QString>
#include <QFile>
#include <QDir>
#include <QVector>
#include <QList>
#include <QMap>
#include <QPair>
#include <QArrayData>

struct cap
{
    int one;
    int two;
};

QByteArray headgood(const QByteArray & h = QByteArray())
{
    static QByteArray x;
   if (!h.isEmpty())
        x = h;

   return x;
}

QByteArray head();
int cut(const QByteArray &b, QByteArray &head, QByteArray &data);
void CREATE(const QByteArray& ba, const QString& name);
QByteArray chinhhinh(const QByteArray& ba, const QString& name = "",uint64_t pk = 150000)
{
    QByteArray ret;
    QVector<QByteArray> v;
    int s = ba.size();
    for(int i = 0; i < (s/1024); i++){
        if ((s - (i*1024)) >= 1024)
            v.push_back(ba.mid(i*1024,1024 ));
        else
            v.push_back(ba.mid(i*1024,(s - (i*1024))));
    }

lap:
    pk += 10000;
    bool a[v.size()];
    for(int i =0; i < v.size(); i++)
    {
        QByteArray sum = v.at(i);
        short *p = (short*)sum.data();
        uint64_t s = 0;
        for(int j = 0; j < 1024; j+=2)
        {
            if(*p>0)
                s += *p;
            p++;
        }
        if(s > pk)
            a[i] = false;
        else
            a[i] = true;
    }

    int st = 0,et = 0;
    int count = 0;
    QList<cap> bo;
    for(int i = 0; i < v.size(); i++)
    {
        if(a[i] == false)
        {
            count++;
        }
        else
        {
            if(count >= 1)
                bo.append({i-count,i});
            count = 0;
        }
        if(i == v.size()-1 && count!= 0)
        {
            bo.append({i-count,i});
        }
    }

    if(name == "rời")
    {
        int z =9;
        z++;
    }
    et = st = 0;
    for(int i = 0; i < bo.size() -2 ; i++)
    {
        if ((bo.at(i).two - bo.at(i).one) <=3)
        {
            if((bo.at(i+1).one - bo.at(i).two) <= 2)
            {
                int one = bo.at(i).one;
                bo.removeAt(i);
                bo[i].one = one;
                break;
            }
        }
    }
    for(int i = bo.size() -1; i > 0 ; i--)
    {
        if ((bo.at(i).two - bo.at(i).one) <= 3)
        {
            if((bo.at(i).one - bo.at(i-1).two) <= 2)
            {
                int two = bo.at(i).two;
                bo.removeAt(i);
                bo[i-1].two = two;
                break;
            }
        }
    }
    if(bo.size() <= 2)
        goto lap;
    for(int i = 1; i < bo.size() -1 ; i++)
    {
        if(i == 1)
            st = bo.at(i).one;
        if(i == bo.size() -2)
            et = bo.at(i).two;
    }
    st -= 1;
    et += 1;
    if(st > 0)
        ret = ba.mid(st*1024,(et-st)*1024);
    return ret;
}
QMap <uint, uint> chia(const QByteArray& b);
int main()
{
    QByteArray ba,h,d;

    QFile ft("D:\\audio data\\texts.txt");
    if(ft.open(QIODevice::ReadWrite))
    {
        ba = ft.readAll();
        ft.close();
    }
    QString l(ba);
    QStringList ll = l.split(' ', QString::SkipEmptyParts);
    QFile fs("D:\\audio data\\data.wav");
    if(fs.open(QIODevice::ReadWrite))
    {
        ba = fs.readAll();
        fs.close();
    }

    cut(ba,h,d);
    if(h.size() == 78)
        headgood(h);
    if(d.isEmpty())
        return 0;
    chia(d);

    QMap <uint, uint> v = chia(d);
    QList<uint> lkey = v.keys();

    QList<QByteArray> list;

    for(int i = 0; i < lkey.size(); i++)
    {
        if(i == 0)
        {
            list.append(d.mid(0,lkey[i]));
        }
        else
        {
            list.append(d.mid(lkey[i-1] + v.value(lkey[i-1]),lkey.at(i) - (lkey[i-1] + v.value(lkey[i-1]))));
        }
    }
    list.append(d.mid(lkey[lkey.size()-1] + v.value(lkey[lkey.size()-1]),d.size() - (lkey[lkey.size()-1] + v.value(lkey[lkey.size()-1]))));

    if(ll.size() == list.size())
    {
        for(int i = 0; i < ll.size(); i++)
        {
            CREATE(list.at(i),ll.at(i));
        }
    }

    return 0;
}
void CREATE(const QByteArray& ba, const QString& name)
{
    QByteArray sizew,banh, zba;

    if(name == "sáu")
    {
        int i = 0;
        i++;
    }

    zba = chinhhinh(ba,name);
//    if(zba.size() < 5)
//    {
//        zba = chinhhinh(ba,"", 200000);
//    }

    banh += headgood();
    int sizep = 74;
    if(banh.isEmpty()){
        banh += head();
        sizep = 40;
    }
    banh += zba;

    QFile fanh("D:\\audio gen\\" + name + ".wav");
    if(fanh.open(QIODevice::ReadWrite))
        fanh.write(banh);

    if(fanh.seek(4))
    {
        int size = banh.size() - 8;
        char* ptr =(char*)(&size);
        for(int i = 0; i < 3; i++){
            sizew.append(*ptr);
            ptr++;
        }
        fanh.write(sizew);
    }

    if(fanh.seek(sizep))
    {
        int size = banh.size() - (sizep+4);
        char* ptr =(char*)(&size);
        for(int i = 0; i < 3; i++){
            sizew.append(*ptr);
            ptr++;
        }
        fanh.write(sizew);
    }
}
QMap <uint, uint> chia(const QByteArray& b)
{
    QList<QByteArray> list;
    QByteArray tem;
    uint size =  b.size();
    int count = 0;
    QMap <uint, uint> v;
    for(uint i = 0; i < size-6; i+=2)
    {
        if(b[i] == 0 && b[i+1] == 0 && b[i+2] == 0 && b[i+3] == 0)
        {
            count++;
        }
        else
        {
            if(count > 5000){
                v[i-(count*2)]= count*2;
            }
            count = 0;
        }
    }
    return v;
}
QByteArray head()
{
    char h[44]= \
    {0x52, 0x49, 0x46, 0x46,
     0x00, 0x00, 0x00, 0x00,
     0x57, 0x41, 0x56, 0x45,
     0x66, 0x6d, 0x74, 0x20,
     0x10, 0x00, 0x00, 0x00,
     0x01, 0x00, 0x01, 0x00,
     0x44, (char)0xac, 0x00, 0x00,
     (char)0x88, 0x58, 0x01, 0x00,
     0x02, 0x00, 0x10, 0x00,
     0x64, 0x61, 0x74, 0x61,
     0x00, 0x00, 0x00, 0x00};

    QByteArray RET(h,44);

    return RET;
}
int cut(const QByteArray &b, QByteArray &head, QByteArray &data)
{
    int ret = 0;
    if(!b.isNull()){
        int n = b.size();
        for(int i = 0; i < b.length(); i++)
        {
            if( b[i]  == 'd' &&
                b[i+1]  == 'a' &&
                b[i+2]  == 't' &&
                b[i+3]  == 'a' )
            {
                ret = i;
            }

        }
        head = b.mid(0,ret+8);
        data = b.mid(ret+8,n-(ret+8));
    }
    return ret;
}

