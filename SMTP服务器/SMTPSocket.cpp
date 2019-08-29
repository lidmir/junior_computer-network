// SMTPSocket.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "SMTP.h"
#include "SMTPSocket.h"
#include "MakingPicture.h"
#include "SMTPDlg.h"


// SMTPSocket

SMTPSocket::SMTPSocket()
{
	IsData = false;
	Quit = false;
}

SMTPSocket::~SMTPSocket()
{
}


// SMTPSocket ��Ա����


void SMTPSocket::OnAccept(int nErrorCode)
{
	// TODO: �ڴ����ר�ô����/����û���

	CString PreLog, Log;
	AfxGetMainWnd()->GetDlgItemText(IDC_EDIT1, PreLog);
	Log += PreLog;
	SMTPSocket *NewSock = new SMTPSocket();

	int IsConnect = Accept(*NewSock);
	if (IsConnect != 0)
	{
		char* send = "220 SMTP is ready \r\n";
		NewSock->Send(send, strlen(send), 0);
		NewSock->AsyncSelect(FD_READ);//���ý��ܺ������в�����
		Log += "TCP�����ɹ�\r\n";
		Log += "S:220 Simple Mail Server Ready for Mail\r\n";
	}
	else
	{
		Log += "TCP����ʧ��\r\n";

	}
	AfxGetMainWnd()->SetDlgItemText(IDC_EDIT1, Log);
	CAsyncSocket::OnAccept(nErrorCode);
}
void SMTPSocket::OnReceive(int nErrorCode)
{
	// TODO: �ڴ����ר�ô����/����û���
	int length = Receive(data, sizeof(data), 0);//���յ������ݴ浽data
	CString receive;
	receive += data;
	CString PreLog, Log;
	AfxGetMainWnd()->GetDlgItemText(IDC_EDIT1, PreLog);
	if (!IsData)//д������־
	{
		Log = PreLog + L"C:" + receive.Left(length) + L"\r\n";
	}
	else
	{
		Log = PreLog + L"C:" + L"data" + L"\r\n";
	}

	if (length != 0)//������յ�����
	{
		if (!IsData)//������յ���������
		{
			//�ֱ�Բ�ͬ�������Ӧ��
			if (receive.Left(4) == "EHLO")
			{
				char* send = "250 OK 127.0.0.1\r\n";//Ӧ��

				Send(send, strlen(send), 0);//����Ӧ��
				Log = Log + L"S:" + L"127.0.0.1\r\n";
				AsyncSelect(FD_READ);//�������պ���
				AfxGetMainWnd()->SetDlgItemText(IDC_EDIT1, Log);//д������־
				return;
			}
			if (receive.Left(10) == "MAIL FROM:")
			{
				char *send = "250 Sender OK\r\n";

				Send(send, strlen(send), 0);
				Log = Log + L"S:" + L"250 Sender OK\r\n";
				AsyncSelect(FD_READ);
				AfxGetMainWnd()->SetDlgItemText(IDC_EDIT1, Log);
				return;
			}
			if (receive.Left(8) == "RCPT TO:")
			{
				char* send = "250 Receiver OK\r\n";

				Send(send, strlen(send), 0);
				Log = Log + L"S:" + L"250 Receiver OK\r\n";
				AsyncSelect(FD_READ);
				AfxGetMainWnd()->SetDlgItemText(IDC_EDIT1, Log);
				return;
			}
			if (receive.Left(4) == "DATA")
			{
				IsData = true;//����յ�DATA���˵���������Ľ��յ���������
				char* send = "354 Go ahead\r\n";

				Send(send, strlen(send), 0);

				Log = Log + "S:" + (CString)send;
				AsyncSelect(FD_READ);
				AfxGetMainWnd()->SetDlgItemText(IDC_EDIT1, Log);
				return;
			}
			if (receive.Left(4) == "QUIT" || receive.Left(4) == "RSET")
			{
				char* send = "221 Quit,Goodbye\r\n";

				Send(send, strlen(send), 0);
				Log = Log + "S:" + (CString)send;
				Quit = true;//�ͻ����˳������ֹ����
				AsyncSelect(FD_READ);
				Log = Log + L"\r\n\r\n";
				AfxGetMainWnd()->SetDlgItemText(IDC_EDIT1, Log);
				return;
			}
			char* send = "500 order is wrong\r\n";

			Send(send, strlen(send), 0);
			Log = Log + "S:" + (CString)send;
			Quit = true;
			AfxGetMainWnd()->SetDlgItemText(IDC_EDIT1, Log);
			return;
		}
		else//���յ������ݣ�������δ������ȫʱ��������Ӧ��
		{
			CString str1, str2;		
			AfxGetMainWnd()->GetDlgItemText(IDC_EDIT2, str1);
			str2 = str1 + receive.Left(length);
			AfxGetMainWnd()->SetDlgItemText(IDC_EDIT2, str2);
			if (receive.Find(L"\r\n.\r\n") != -1)//���ݽ������
			{
				IsData = false;
				char* send;
				send = "250 Message accepted for delivery\r\n";//����Ӧ��

				Send(send, strlen(send), 0);
				Log = Log + "S:" + (CString)send;
				AfxGetMainWnd()->SetDlgItemText(IDC_EDIT1, Log);

				AfxGetMainWnd()->GetDlgItemText(IDC_EDIT2, pic);
				//��������bmp/jpg/pngͼƬ
				if ((pic.Find(L"Content-Type: image/bmp") != -1)||(pic.Find(L"Content-Type: image/jpeg") != -1)||(pic.Find(L"Content-Type: image/png") != -1))
				{
					//��ȡbmpͼƬ��base64����
					int Attachment_Start = pic.Find(L"Content-Disposition: attachment", 0);
					int Bmp_Start = pic.Find(L"\r\n\r\n", Attachment_Start);
					CString Start = pic.Mid(Bmp_Start + 4, pic.GetLength() - Bmp_Start - 4);
					int length = Start.Find(L"\r\n\r\n", 0);
					pic = Start.Left(length);
					CImage picture;
					//����
					DeCode(pic);
					//�ļ����bmpͼ��
					picture.Load(_T("1.bmp"));
					//���뵽�Ի���
				    CSMTPDlg *CurrentApp = (CSMTPDlg *)AfxGetApp();
					CSMTPDlg *CurrentDlg = (CSMTPDlg *)CurrentApp->m_hWnd;
					CurrentDlg->m_pic.SetBitmap((HBITMAP)picture);
				}
				//��������gifͼƬ
				if (pic.Find(L"Content-Type: image/gif") != -1)
				{
					//��ȡgifͼƬ��base64����
					int Attachment_Start = pic.Find(L"Content-Disposition: attachment", 0);
					int Bmp_Start = pic.Find(L"\r\n\r\n", Attachment_Start);
					CString Start = pic.Mid(Bmp_Start + 4, pic.GetLength() - Bmp_Start - 4);
					int length = Start.Find(L"\r\n\r\n", 0);
					pic = Start.Left(length);
					CImage picture;
					//����
					DeCode1(pic);
					//�ļ����gifͼ��
					picture.Load(_T("2.gif"));
					//���뵽�Ի���
				    CSMTPDlg *CurrentApp = (CSMTPDlg *)AfxGetApp();
					CSMTPDlg *CurrentDlg = (CSMTPDlg *)CurrentApp->m_hWnd;
					CurrentDlg->m_pic.SetBitmap((HBITMAP)picture);					
				}
			}
			AsyncSelect(FD_READ);

			return;
		}
	}
	if (Quit)//�˳�
	{
		//Close();//�ر��׽���
		Quit = false;
		return;
	}
	CAsyncSocket::OnReceive(nErrorCode);
}
