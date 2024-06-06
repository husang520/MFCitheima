// CUserDlg.cpp: 实现文件
//

#include "pch.h"
#include "MFCSaleSystem.h"
#include "CUserDlg.h"

#include "InfoFile.h"

// CUserDlg

IMPLEMENT_DYNCREATE(CUserDlg, CFormView)

CUserDlg::CUserDlg()
	: CFormView(DIALOG_USER)
	, m_user(_T(""))
	, m_newPwd(_T(""))
	, m_surePwd(_T(""))
	, m_name(_T(""))
{

}

CUserDlg::~CUserDlg()
{
}

void CUserDlg::DoDataExchange(CDataExchange* pDX)
{
	CFormView::DoDataExchange(pDX);
	DDX_Text(pDX, IDC_EDIT1, m_user);
	//  DDX_Control(pDX, IDC_EDIT2, m_name);
	DDX_Text(pDX, IDC_EDIT3, m_newPwd);
	DDX_Text(pDX, IDC_EDIT4, m_surePwd);
	DDX_Text(pDX, IDC_EDIT2, m_name);
}

BEGIN_MESSAGE_MAP(CUserDlg, CFormView)
	ON_BN_CLICKED(IDC_BUTTON3, &CUserDlg::OnBnClickedButton3)
	ON_BN_CLICKED(IDC_BUTTON4, &CUserDlg::OnBnClickedButton4)
END_MESSAGE_MAP()


// CUserDlg 诊断

#ifdef _DEBUG
void CUserDlg::AssertValid() const
{
	CFormView::AssertValid();
}

#ifndef _WIN32_WCE
void CUserDlg::Dump(CDumpContext& dc) const
{
	CFormView::Dump(dc);
}
#endif
#endif //_DEBUG


// CUserDlg 消息处理程序


void CUserDlg::OnInitialUpdate()
{
	CFormView::OnInitialUpdate();

	// TODO: 在此添加专用代码和/或调用基类

	// 初始化
	m_user = TEXT("销售员");

	CInfoFile file;
	CString name, pwd;
	file.ReadLogin(name, pwd);

	m_name = name;
	UpdateData(FALSE);
}


void CUserDlg::OnBnClickedButton3()
{
	// TODO: 在此添加控件通知处理程序代码

	// 修改密码
	UpdateData(TRUE);	// 拿到最新值

	if (m_newPwd.IsEmpty() || m_surePwd.IsEmpty()) {
		MessageBox(TEXT("输入内容不能为空！"));
		return;
	}
	else {

	}

	if (m_newPwd != m_surePwd) {
		MessageBox(TEXT("新密码和确认密码要一致！"));
		return;
	}

	// 新密码和旧密码不要一致！
	CInfoFile file;
	CString name, pwd;
	file.ReadLogin(name, pwd);
	if (pwd == m_newPwd) {
		MessageBox(TEXT("新密码和旧密码不要一致！"));
		return;
	}
	
	// CString 转 char *
	CStringA tmp;
	CStringA tmp2;
	tmp = name;
	tmp2 = m_newPwd;
	file.WritePwd(tmp.GetBuffer(), tmp2.GetBuffer());
	MessageBox(TEXT("修改成功！"));

	// 情空内容
	m_newPwd.Empty();
	m_surePwd.Empty();
	UpdateData(FALSE);
}


void CUserDlg::OnBnClickedButton4()
{
	// TODO: 在此添加控件通知处理程序代码

	// 取消修改密码

	// 情空内容
	m_newPwd.Empty();
	m_surePwd.Empty();
	UpdateData(FALSE);

}
