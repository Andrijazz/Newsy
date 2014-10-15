#include "CorpusHandler.h"

#include <QFile>
#include <QTextStream>
#include <QVector>

#include <iostream>

#include "configservice.h"

CorpusHandler::CorpusHandler(QString purpose)
{
    m_corpusName = ConfigService::getConfig("CORPUS");

    QString path = CORPUS_PATH;
    path.append("/");
    path.append(m_corpusName);
    path.append("/");
    path.append("training");

    QDir dir(path);
    QFileInfoList content;
    if (dir.exists())
    {
        content = dir.entryInfoList(QDir::Dirs);
    }

    foreach (QFileInfo f, content)
    {
        if (f.baseName() != "")
        {
            m_categories.push_back(f.baseName());
        }
    }

    initializeFor(purpose);
}

CorpusHandler::~CorpusHandler()
{
}

void CorpusHandler::initializeFor(QString purpose)
{
    m_corpus.reset(new std::vector< boost::tuple<QString, QFileInfoList, int> >());

    for(std::vector<QString>::const_iterator i = m_categories.begin(); i != m_categories.end(); i++)
    {
        QFileInfoList list = getCategoryFileInfoList(*i, purpose);
        m_corpus->push_back(boost::make_tuple(*i, list, list.size()));
    }

    m_iter = 0;
}

QFileInfoList CorpusHandler::getCategoryFileInfoList(QString category, QString purpose)
{
    QString path = CORPUS_PATH;

    path.append("/"); path.append(m_corpusName); path.append("/"); path.append(purpose); path.append("/"); path.append(category);

    QDir dir(path);
    if (dir.exists())
    {
        return dir.entryInfoList(QDir::Files | QDir::NoSymLinks);
    }
    return QFileInfoList();
}

QString CorpusHandler::getArticle()
{
    if (boost::get<1>((*m_corpus)[m_iter]).empty())
    {
        // move to the next category
        m_iter++;
    }

    if (end())
    {
        return "";
    }

    // read the first file
    QString text = readFile(boost::get<1>((*m_corpus)[m_iter]).front());

    // delete it from the list of unread files
    boost::get<1>((*m_corpus)[m_iter]).removeFirst();

    return text;
}

QString CorpusHandler::readFile(QFileInfo fileInfo)
{
    // TODO: Fix corpus by removing links file

    if (fileInfo.isFile() && fileInfo.baseName() != "links")
    {
        QFile file(fileInfo.filePath());
        if (file.exists())
        {
            if (file.open(QIODevice::ReadOnly | QIODevice::Text))
            {
                QTextStream in(&file);
                QString text = in.readAll();
                std::cout << file.fileName().toStdString() << std::endl;

                return text;
            }
        }

    }
    return "";
}

bool CorpusHandler::end()
{
    return m_iter == m_corpus->size();
}


std::vector<QString> CorpusHandler::getCategories()
{
    return m_categories;
}

unsigned int CorpusHandler::getNumberOfCategories()
{
    return m_categories.size();
}

int CorpusHandler::getCategoryIndex(QString category)
{
    for (unsigned int i = 0; i < m_categories.size(); i++)
    {
        if (m_categories[i] == category)
            return i;
    }
    return -1;
}

QString CorpusHandler::getCorpusName()
{
    return m_corpusName;
}

std::vector<int> CorpusHandler::numberOfArticlesPerCategory()
{
    std::vector<int> categories_sizes;
    for (unsigned int i = 0; i < m_corpus->size(); i++)
    {
        categories_sizes.push_back(boost::get<2>(m_corpus->at(i)));
    }
    return categories_sizes;
}
