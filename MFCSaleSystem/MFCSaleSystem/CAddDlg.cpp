// CAddDlg.cpp: 实现文件
//

#include "pch.h"
#include "MFCSaleSystem.h"
#include "CAddDlg.h"

#include "InfoFile.h"


// CAddDlg

IMPLEMENT_DYNCREATE(CAddDlg, CFormView)

CAddDlg::CAddDlg()
	: CFormView(DIALOG_ADD)
	, m_price1(0)
	, m_num1(0)
	, m_name2(_T(""))

	, m_num2(0)
	, m_price2(0)
{

}

CAddDlg::~CAddDlg()
{
}

void CAddDlg::DoDataExchange(CDataExchange* pDX)
{
	CFormView::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_COMBO1, m_combo);
	DDX_Text(pDX, IDC_EDIT1, m_price1);
	DDX_Text(pDX, IDC_EDIT2, m_num1);
	DDX_Text(pDX, IDC_EDIT3, m_name2);
	//  DDX_Text(pDX, IDC_EDIT4, m_price2);
	DDX_Text(pDX, IDC_EDIT5, m_num2);
	DDX_Text(pDX, IDC_EDIT4, m_price2);
}

BEGIN_MESSAGE_MAP(CAddDlg, CFormView)
	ON_CBN_SELCHANGE(IDC_COMBO1, &CAddDlg::OnCbnSelchangeCombo1)
	ON_BN_CLICKED(IDC_BUTTON5, &CAddDlg::OnBnClickedButton5)
	ON_BN_CLICKED(IDC_BUTTON6, &CAddDlg::OnBnClickedButton6)
	ON_BN_CLICKED(IDC_BUTTON7, &CAddDlg::OnBnClickedButton7)
	ON_BN_CLICKED(IDC_BUTTON8, &CAddDlg::OnBnClickedButton8)
END_MESSAGE_MAP()


// CAddDlg 诊断

#ifdef _DEBUG
void CAddDlg::AssertValid() const
{
	CFormView::AssertValid();
}

#ifndef _WIN32_WCE
void CAddDlg::Dump(CDumpContext& dc) const
{
	CFormView::Dump(dc);
}
#endif
#endif //_DEBUG


// CAddDlg 消息处理程序


void CAddDlg::OnInitialUpdate()
{
	CFormView::OnInitialUpdate();

	// TODO: 在此添加专用代码和/或调用基类

	//读取文件，获取商品名，给组合框添加字符串
	//需要包含#include "InfoFile.h"
	CInfoFile file;
	file.ReadDocline(); //读取商品信息
	for (list<msg>::iterator it = file.ls.begin(); it != file.ls.end(); it++)
	{
		m_combo.AddString((CString)it->name.c_str());
	}

	file.ls.clear(); //清空list的内容

	//将第一个商品名设为默认选中项
	m_combo.SetCurSel(0);

}


void CAddDlg::OnCbnSelchangeCombo1()
{
	// TODO: 在此添加控件通知处理程序代码
	CString text;
	//获取当前选中项
	int index = m_combo.GetCurSel();
	//获取当前内容
	m_combo.GetLBText(index, text);

	//需要包含#include "InfoFile.h"
	CInfoFile file;
	file.ReadDocline(); //读取商品信息
	for (list<msg>::iterator it = file.ls.begin(); it != file.ls.end(); it++)
	{
		if (text == it->name.c_str())
		{
			m_price1 = it->price;
			m_num1 = 0;
			UpdateData(FALSE); //内容更新到对应的控件
		}
	}

	file.ls.clear(); //清空list的内容

}


void CAddDlg::OnBnClickedButton5()
{
	// TODO: 在此添加控件通知处理程序代码
	//获取控件上的内容，更新到对应关联的变量中
	UpdateData(TRUE);

	if (m_num1 == 0)
	{
		MessageBox(TEXT("个数不能为0"));
		return;
	}

	CString type;
	//获取当前选中项
	int index = m_combo.GetCurSel();
	//获取组合框当前内容
	m_combo.GetLBText(index, type);

	CString str;
	str.Format(_T("添加了 商品：%s \r\n单价：%d \r\n个数：%d"), type, m_price1, m_num1);
	MessageBox(str);


	//需要包含#include "InfoFile.h"
	CInfoFile file;
	file.ReadDocline(); //读取商品信息
	for (list<msg>::iterator it = file.ls.begin(); it != file.ls.end(); it++)
	{
		if (type == it->name.c_str())
		{
			it->num += m_num1;
		}
	}
	file.WirteDocline(); //更新文件内容

	file.ls.clear(); //清空list的内容

	m_num1 = 0;
	UpdateData(FALSE); //更新到对应的控件

}


void CAddDlg::OnBnClickedButton6()
{
	// TODO: 在此添加控件通知处理程序代码
	m_combo.SetCurSel(0);
	m_num1 = 0;
	OnCbnSelchangeCombo1();

}


void CAddDlg::OnBnClickedButton7()
{
	// TODO: 在此添加控件通知处理程序代码
	UpdateData(TRUE); //获取控件内容

	if (m_num2 <= 0 || m_price2 <= 0 || m_name2.IsEmpty())
	{
		MessageBox(TEXT("输入信息有误"));
		return;
	}

	//需要包含#include "InfoFile.h"
	CInfoFile file;
	file.ReadDocline(); //读取商品信息
	file.Addline(m_name2, m_num2, m_price2); //添加商品
	file.WirteDocline(); //写文件
	file.ls.clear(); //清空list的内容
	MessageBox(_T("添加成功"));

	m_name2.Empty();
	m_num2 = 0;
	m_price2 = 0;
	UpdateData(FALSE);

}


void CAddDlg::OnBnClickedButton8()
{
	// TODO: 在此添加控件通知处理程序代码
	m_name2.Empty();
	m_num2 = 0;
	m_price2 = 0;
	UpdateData(FALSE);

}
