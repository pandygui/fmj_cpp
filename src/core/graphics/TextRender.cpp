
#include "TextRender.h"


void TextRender::init()
{
    long size = 0;
    std::ifstream in;
    std::streampos pos;

    if (mHZKBuf == NULL)
    {
    in.open(std::string("./dat/HZK16"), std::ios::in | std::ios::binary);
    if (!in.is_open())
    {
        std::cout << "Error opening file";
        exit(1);
    }

    pos = in.tellg();
    in.seekg(0, std::ios::end);
    size = (long)in.tellg();
    in.seekg(pos);

    mHZKBuf = new char[size];
    in.read(mHZKBuf, size);
    in.close();
    }


    if (mASCBuf == NULL)
    {
    in.open(std::string("./dat/ASC16"), std::ios::in | std::ios::binary);
    if (!in.is_open())
    {
        std::cout << "Error opening file";
        exit(1);
    }

    pos = in.tellg();
    in.seekg(0, std::ios::end);
    size = (long)in.tellg();
    in.seekg(pos);

    mASCBuf = new char[size];
    in.read(mASCBuf, size);
    in.close();
    }


    //工厂模式
    mBmpHzk = Bitmap::createBitmap(16, 16, ARGB_8888);
    mBmpAsc = Bitmap::createBitmap(8, 16, ARGB_8888);
    mPixels = new int[16 * 16];
}

void TextRender::drawText(Canvas *canvas, std::string &text, int x, int y, bool bInverse /*= false*/)
{
    drawText(canvas, text.c_str(), x, y, bInverse);
}

void TextRender::drawSelText(Canvas *canvas, std::string &text, int x, int y)
{
    drawText(canvas, text, x, y, true);
}

void TextRender::drawSelText(Canvas *canvas, const char *text, int x, int y)
{
    drawText(canvas, text, x, y, true);
}

void TextRender::drawText(Canvas *canvas, const char *text, int x, int y, bool bInverse /*= false*/)
{
    int textlen = strlen(text);

    for (int i = 0; i < textlen && text[i] != 0; i++)
    {
        int t = (int)text[i] & 0xFF;
        if (t >= 0xa1)
        {
            ++i;
            int offset = (94 * (t - 0xa1) + ((int)text[i] & 0xFF) - 0xa1) * 32;
            canvas->drawBitmap(getHzk(offset, bInverse), x, y);
            x += 16;
        }
        else if (t < 128)
        {
            int offset = t * 16;
            canvas->drawBitmap(getAsc(offset, bInverse), x, y);
            x += 8;
        }
        else
        {
            x += 8;
        }
    }
}

/**
 *
 * @param canvas
 * @param text
 * @param r
 * @param y
 * @return 0,文字都在r->top上方
 * 1,文字在r中
 * 2,文字都在r->bottom下方
 * -1,出错
 */
int TextRender::drawText(Canvas *canvas, std::string & text, Rect *r, int y)
{
    const char *buf = text.c_str();
    int length = (int)(text.length());
    int i = 0;
    // 比r->top高的不画
    for (; y <= r->top - 16 && i < length; y += 16)
    {
        for (int x = 0; x < 160 && i < length;)
        {
            int t = (int)buf[i] & 0xFF;
            if (t >= 0xa1)
            {
                i += 2;
                x += 16;
            }
            else
            {
                ++i;
                x += 8;
            }
        }
    }

    if (i >= length)
    {
        return 0;
    }

    // 比r->bottom低的不画
    for (; y < r->bottom && i < length; y += 16)
    {
        for (int x = 0; x < 160 && i < length;)
        {
            int t = (int)buf[i] & 0xFF;
            if (t >= 0xa1)
            {
                ++i;
                int offset = (94 * (t - 0xa1) + ((int)buf[i] & 0xFF) - 0xa1) * 32;
                canvas->drawBitmap(getHzk(offset), x, y);
                x += 16;
            }
            else if (t < 128)
            {
                int offset = t * 16;
                canvas->drawBitmap(getAsc(offset), x, y);
                x += 8;
            }
            else
            {
                x += 8;
            }
            ++i;
        }
    } 

    if (i == 0 && length > 0)
    {
        return 2;
    }

    return 1;
}

/**
 * call drawText(Canvas, char *, int, Rect)
 */
int TextRender::drawText(Canvas *canvas, std::string & text, int start, Rect *r)
{
    const char *buf = text.c_str();
    return drawText(canvas, buf, start, r);
}

/**
 *
 * @param canvas
 * @param buf
 * @param start buf中第一个要画的字节
 * @param r
 * @return 下一个要画的字节
 */
int TextRender::drawText(Canvas *canvas, const char *buf, int start, Rect *r)
{
    int i = start;
    int y = r->top;
    int textlen = strlen(buf);
    // 比r->bottom低的不画
    for (; y <= r->bottom - 16 && i < textlen; y += 16)
    {
        for (int x = r->left; x <= r->right - 16 && i < textlen;)
        {
            int t = (int)buf[i] & 0xFF;
            if (t >= 0xa1)
            {
                ++i;
                int offset = (94 * (t - 0xa1) + ((int)buf[i] & 0xFF) - 0xa1) * 32;
                canvas->drawBitmap(getHzk(offset), x, y);
                x += 16;
            }
            else if (t < 128)
            {
                int offset = t * 16;
                canvas->drawBitmap(getAsc(offset), x, y);
                x += 8;
            }
            else
            {
                x += 8;
            }
            ++i;
        }
    }

    return i;
}

Bitmap *TextRender::getHzk(int offset, bool bInverse /*= false*/)
{
    int color_text = Manager::sCOLOR_BLACK;
    int color_front = Manager::sCOLOR_WHITE;

    if (true == bInverse)
    {
        color_text = Manager::sCOLOR_WHITE;
        color_front = Manager::sCOLOR_BLACK;
    }

    for (int i = 0; i < 32; i++)
    {
        int t = mHZKBuf[offset + i];
        int k = i << 3;
        mPixels[k]     = (t & 0x80) != 0 ? color_text : color_front;
        mPixels[k | 1] = (t & 0x40) != 0 ? color_text : color_front;
        mPixels[k | 2] = (t & 0x20) != 0 ? color_text : color_front;
        mPixels[k | 3] = (t & 0x10) != 0 ? color_text : color_front;
        mPixels[k | 4] = (t & 0x08) != 0 ? color_text : color_front;
        mPixels[k | 5] = (t & 0x04) != 0 ? color_text : color_front;
        mPixels[k | 6] = (t & 0x02) != 0 ? color_text : color_front;
        mPixels[k | 7] = (t & 0x01) != 0 ? color_text : color_front;
    }
    mBmpHzk->setPixels(mPixels, 0, 16, 0, 0, 16, 16);
    return mBmpHzk;
}

Bitmap *TextRender::getAsc(int offset, bool bInverse /*= false*/)
{
    int color_text = Manager::sCOLOR_BLACK;
    int color_front = Manager::sCOLOR_WHITE;

    if (true == bInverse)
    {
        color_text = Manager::sCOLOR_WHITE;
        color_front = Manager::sCOLOR_BLACK;
    }

    for (int i = 0; i < 16; i++)
    {
        int t = mASCBuf[offset + i];
        int k = i << 3;
        mPixels[k]     = (t & 0x80) != 0 ? color_text : color_front;
        mPixels[k | 1] = (t & 0x40) != 0 ? color_text : color_front;
        mPixels[k | 2] = (t & 0x20) != 0 ? color_text : color_front;
        mPixels[k | 3] = (t & 0x10) != 0 ? color_text : color_front;
        mPixels[k | 4] = (t & 0x08) != 0 ? color_text : color_front;
        mPixels[k | 5] = (t & 0x04) != 0 ? color_text : color_front;
        mPixels[k | 6] = (t & 0x02) != 0 ? color_text : color_front;
        mPixels[k | 7] = (t & 0x01) != 0 ? color_text : color_front;
    }
    mBmpAsc->setPixels(mPixels, 0, 8, 0, 0, 8, 16);
    return mBmpAsc;
}

TextRender::TextRender()
{
    mHZKBuf = NULL;
    mASCBuf = NULL;
    mPixels = NULL;
    mBmpHzk = NULL;
    mBmpAsc = NULL;

    init();
}

TextRender::~TextRender()
{
    delete mHZKBuf;
    delete mASCBuf;
    delete mBmpAsc;
    delete mBmpHzk;
    delete mPixels;
}

TextRender * TextRender::getInstance()
{
    if (NULL == mTextRenderInstance)
    {
        mTextRenderInstance = new TextRender();
    }

    return mTextRenderInstance;
}

void TextRender::InitTextRender()
{
    mTextRenderInstance = new TextRender();
}

Bitmap * TextRender::mBmpAsc;
Bitmap * TextRender::mBmpHzk;

int * TextRender::mPixels;
char * TextRender::mASCBuf;
char * TextRender::mHZKBuf;
TextRender * TextRender::mTextRenderInstance = NULL;
