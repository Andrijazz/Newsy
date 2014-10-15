#include "Tokenizer.h"

#include "tokens.h"
#include "lexer.h"

extern int yylex(void);
extern char* yyget_text(void);
// extern int yywrap(void);

std::map<QString, int> Tokenizer::parse(QString text)
{
    YY_BUFFER_STATE bufferState = yy_scan_string(text.toUtf8().constData());

    std::map<QString, int> words;

    // Parse the string.
    int token = yylex();
    while (token)
    {
        if (token == WORD)
        {
            QString w(yyget_text());
            w = w.toLower();
            if (words[w])
            {
                words[w]++;
            }
            else
            {
                words[w] = 1;
            }
            token = yylex();
            continue;
        }
        token = yylex();
    }

    // and release the buffer.
    yy_delete_buffer(bufferState);

    return words;
}

QString Tokenizer::getCategory(QString text)
{
    YY_BUFFER_STATE bufferState = yy_scan_string(text.toUtf8().constData());

    QString category = "Unknown";

    int token = yylex();
    while (token)
    {
        if (token == HEADER_NEWS_GROUP)
        {
            category = yyget_text();
            return category;
        }
        token = yylex();
    }

    // and release the buffer.
    yy_delete_buffer(bufferState);

    return category;
}
// STRINGS IN CPP ARE BULLSHIT
//char* Tokenizer::toLowerCase(char* str)
//{
//    int differ = 'A'-'a';
//    char ch;
//    int ii = strlen(str);
//    for (int i = 0; i < ii; i++)
//    {
//        strncpy(&ch, str + i, 1);
//        if (ch >= 'A' && ch <= 'Z')
//        {
//            ch = ch - differ;
//            memcpy(str + i, &ch, 1);
//        }
//    }
//    return str;
//}

//QString Tokenizer::tokenToString(const int token)
//{
//    QString token_string = "UNKNOWN_TOKEN";
//    switch (token)
//    {
//        case HEADER:
//            token_string = "HEADER";
//            break;
//        case WORD:
//            token_string = "WORD";
//            break;
//        case NUMBER:
//            token_string = "NUMBER";
//            break;
//        case SPACES:
//            token_string = "SPACES";
//            break;
//        case PUNCT:
//            token_string = "PUNCT";
//            break;
//        case HEADER_SOURCE:
//            token_string = "HEADER_SOURCE";
//            break;
//        case HEADER_DATE:
//            token_string = "HEADER_DATE";
//            break;
//        case HEADER_NEWS_GROUP:
//            token_string = "HEADER_NEWS_GROUP";
//            break;
//        case HEADER_CAPTION:
//            token_string = "HEADER_CAPTION";
//            break;
//        case HEADER_ARTICLE_BEGINNING:
//            token_string = "HEADER_ARTICLE_BEGINNING";
//            break;
//        case SPECIAL_CHAR:
//            token_string = "SPECIAL_CHAR";
//            break;

//    }
//    return token_string;
//}
