#include"StdAfx.h"
//base.hʵ�ֽ����յ���ͼƬ���ݽ��벢ת�����µ�1.bmp��bmp/jpg/png)��2.gif(gif)�ļ�
//�����ڶԻ�������ʾ
char symbol[65] = { 'A', 'B', 'C', 'D', 'E', 'F', 'G', 'H', 'I', 'J',
'K', 'L', 'M', 'N', 'O', 'P', 'Q', 'R', 'S', 'T',
'U', 'V', 'W', 'X', 'Y', 'Z', 'a', 'b', 'c', 'd',
'e', 'f', 'g', 'h', 'i', 'j', 'k', 'l', 'm', 'n',
'o', 'p', 'q', 'r', 's', 't', 'u', 'v', 'w', 'x',
'y', 'z', '0', '1', '2', '3', '4', '5', '6', '7',
'8', '9', '+', '/' };
BOOL SwapCharToByte(BYTE& a, char& b)    //����
{
	for (int i = 0; i<65; i++)
	{
		if (b == symbol[i])
		{
			a = i & 0x00ff;//��ȡ���ֽ�
			return true;
		}
	}
	return false;
}
BOOL DeCode(CString &attachment)   //���벢ת�����µ�1.bmp��bmp/jpg/png)
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
					char t = attachment.GetAt(i);//����ַ������ÿһ���ַ�
					if (!SwapCharToByte(temp[k], t))
					{
						temp[k] = 255;
						k--;
					}
					i++;
				}
			}
			//base64���룬�ĸ���λ���������λ
			buf[0] = (temp[0] << 2) | (temp[1] >> 4);
			buf[1] = (temp[1] << 4) | (temp[2] >> 2);
			buf[2] = (temp[2] << 6) | (temp[3]);
			//д���ļ�
			file.Write(buf, 3);
			file.SeekToEnd();
		}
	}
	file.Close();
	return true;
}
BOOL DeCode1(CString &attachment)  //���벢ת�����µ�2.gif(gif)
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
					char t = attachment.GetAt(i);//����ַ������ÿһ���ַ�
					if (!SwapCharToByte(temp[k], t))
					{
						temp[k] = 255;
						k--;
					}
					i++;
				}
			}
			//base64���룬�ĸ���λ���������λ
			buf[0] = (temp[0] << 2) | (temp[1] >> 4);
			buf[1] = (temp[1] << 4) | (temp[2] >> 2);
			buf[2] = (temp[2] << 6) | (temp[3]);
			//д���ļ�
			file.Write(buf, 3);
			file.SeekToEnd();
		}
	}
	file.Close();
	return true;
}
