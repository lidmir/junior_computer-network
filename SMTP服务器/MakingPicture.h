#include"StdAfx.h"
//base.h实现将接收到的图片内容解码并转换成新的1.bmp（bmp/jpg/png)或2.gif(gif)文件
//用以在对话框中显示
char symbol[65] = { 'A', 'B', 'C', 'D', 'E', 'F', 'G', 'H', 'I', 'J',
'K', 'L', 'M', 'N', 'O', 'P', 'Q', 'R', 'S', 'T',
'U', 'V', 'W', 'X', 'Y', 'Z', 'a', 'b', 'c', 'd',
'e', 'f', 'g', 'h', 'i', 'j', 'k', 'l', 'm', 'n',
'o', 'p', 'q', 'r', 's', 't', 'u', 'v', 'w', 'x',
'y', 'z', '0', '1', '2', '3', '4', '5', '6', '7',
'8', '9', '+', '/' };
BOOL SwapCharToByte(BYTE& a, char& b)    //换码
{
	for (int i = 0; i<65; i++)
	{
		if (b == symbol[i])
		{
			a = i & 0x00ff;//截取低字节
			return true;
		}
	}
	return false;
}
BOOL DeCode(CString &attachment)   //解码并转换成新的1.bmp（bmp/jpg/png)
{
	BYTE buf[4];
	CFile file;
	if (file.Open(L"1.bmp", CFile::modeWrite | CFile::modeCreate))
	{
		int len = attachment.GetLength();
		BYTE temp[4];
		int i = 0;
		while (i<len)
		{
			for (int k = 0; k<4; k++)
			{
				if (i<len)
				{
					char t = attachment.GetAt(i);//获得字符串里的每一个字符
					if (!SwapCharToByte(temp[k], t))
					{
						temp[k] = 255;
						k--;
					}
					i++;
				}
			}
			//base64解码，四个六位变成三个八位
			buf[0] = (temp[0] << 2) | (temp[1] >> 4);
			buf[1] = (temp[1] << 4) | (temp[2] >> 2);
			buf[2] = (temp[2] << 6) | (temp[3]);
			//写入文件
			file.Write(buf, 3);
			file.SeekToEnd();
		}
	}
	file.Close();
	return true;
}
BOOL DeCode1(CString &attachment)  //解码并转换成新的2.gif(gif)
{
	BYTE buf[4];
	CFile file;
	if (file.Open(L"2.gif", CFile::modeWrite | CFile::modeCreate))
	{
		int len = attachment.GetLength();
		BYTE temp[4];
		int i = 0;
		while (i<len)
		{
			for (int k = 0; k<4; k++)
			{
				if (i<len)
				{
					char t = attachment.GetAt(i);//获得字符串里的每一个字符
					if (!SwapCharToByte(temp[k], t))
					{
						temp[k] = 255;
						k--;
					}
					i++;
				}
			}
			//base64解码，四个六位变成三个八位
			buf[0] = (temp[0] << 2) | (temp[1] >> 4);
			buf[1] = (temp[1] << 4) | (temp[2] >> 2);
			buf[2] = (temp[2] << 6) | (temp[3]);
			//写入文件
			file.Write(buf, 3);
			file.SeekToEnd();
		}
	}
	file.Close();
	return true;
}
