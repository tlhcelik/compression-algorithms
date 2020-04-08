#include <QCoreApplication>
#include <QList>
#include <QMap>
#include <QDebug>

QList<int> compress(QString text)
{
    QMap<QString, int> dictionary;
    for (int i = 0; i < 256; i++)
        dictionary.insert(QString(static_cast<char>(i)), i);

    QString w = QString::null;
    QList<int> compressed;

    foreach (QChar c, text)
    {
        QString wc = w+c;
        if(dictionary.contains(wc))
        {
            w =wc;
        }
        else
        {
            compressed.append(dictionary[w]);
            dictionary.insert(wc, dictionary.count());
            w = c;
        }

    }
    if(w.isEmpty() || w.isNull())
        compressed.append(dictionary[w]);

    return compressed;
}

QString decompress(QList<int> compressed)
{
    QMap<int, QString> dictionary;
    for (int i = 0; i < 256; i++)
        dictionary.insert(i, QString(static_cast<char>(i)));

    QString w = dictionary[compressed[0]];
    compressed.removeAt(0);

    QString decompressed;

    foreach (int k, compressed)
    {
        QString entry;
        if(dictionary.contains(k))
            entry =dictionary[k];
        else if(k == dictionary.count())
            entry = w + w[0];

        decompressed.append(entry);

        dictionary.insert(dictionary.count(), w + entry[0]);
        w=entry;

    }
    return  decompressed;
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

