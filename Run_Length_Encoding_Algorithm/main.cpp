#include <QCoreApplication>
#include <QDebug>

QString compress(QString s)
{
   QString sb;
   int count = 1;
   QChar current = s[0];

   for(int i = 1; i < s.length();i++)
   {
       if (current == s[i])
       {
           count++;
       }
       else
       {

           sb.append(QString::number(count));
           sb.append(current);
           count = 1;
           current = s[i];
       }
   }//for end
   sb.append(QString::number(count));
   sb.append(current);
   return sb;
}

QString decompress(QString s)
{
    QString a = "";
    int count = 0;
    QString sb;
    QChar current;
    for(int i = 0; i < s.length(); i++)
    {
        current = s[i];
        if (current.isDigit())
            a += current;
        else
        {
            count = a.toInt();
            a = "";
            for (int j = 0; j < count; j++)
                sb.append(current);
        }
    }//for end
    return sb;
}


int main(int argc, char *argv[])
{
    QCoreApplication a(argc, argv);
    auto ans =compress("This is a test string, TXXTTTVVTMMMMVFFFDD");
    qDebug()<<"Compressed string:" <<ans<<endl;

    auto dcmp = decompress(ans);
    qDebug()<<"Decompressed string is: " << dcmp;
    return a.exec();
}
