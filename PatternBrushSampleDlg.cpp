
// PatternBrushSampleDlg.cpp: 구현 파일
//

#include "pch.h"
#include "framework.h"
#include "PatternBrushSample.h"
#include "PatternBrushSampleDlg.h"
#include "afxdialogex.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CPatternBrushSampleDlg 대화 상자



CPatternBrushSampleDlg::CPatternBrushSampleDlg(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_PATTERNBRUSHSAMPLE_DIALOG, pParent)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CPatternBrushSampleDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CPatternBrushSampleDlg, CDialogEx)
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_WM_LBUTTONDOWN()
	ON_WM_MOUSEMOVE()
END_MESSAGE_MAP()


// CPatternBrushSampleDlg 메시지 처리기

BOOL CPatternBrushSampleDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// 이 대화 상자의 아이콘을 설정합니다.  응용 프로그램의 주 창이 대화 상자가 아닐 경우에는
	//  프레임워크가 이 작업을 자동으로 수행합니다.
	SetIcon(m_hIcon, TRUE);			// 큰 아이콘을 설정합니다.
	SetIcon(m_hIcon, FALSE);		// 작은 아이콘을 설정합니다.

	CBitmap my_bmp, num_bmp;
	my_bmp.LoadBitmap(IDB_TIPS_IMAGE);
	num_bmp.LoadBitmap(IDB_NUM);

	m_my_brush.CreatePatternBrush(&my_bmp);
	m_num_brush.CreatePatternBrush(&num_bmp);

	my_bmp.DeleteObject();
	
	/*
	CClientDC dc(this);
	CDC mem_dc;
	mem_dc.CreateCompatibleDC(&dc);
	mem_dc.SelectObject(&my_bmp);

	dc.BitBlt(0, 0, 48, 48, &mem_dc, 0, 0, SRCCOPY);
	*/

	return TRUE;  // 포커스를 컨트롤에 설정하지 않으면 TRUE를 반환합니다.
}

// 대화 상자에 최소화 단추를 추가할 경우 아이콘을 그리려면
//  아래 코드가 필요합니다.  문서/뷰 모델을 사용하는 MFC 애플리케이션의 경우에는
//  프레임워크에서 이 작업을 자동으로 수행합니다.

void CPatternBrushSampleDlg::OnPaint()
{
	CPaintDC dc(this); // 그리기를 위한 디바이스 컨텍스트입니다.
	if (IsIconic())
	{	

		SendMessage(WM_ICONERASEBKGND, reinterpret_cast<WPARAM>(dc.GetSafeHdc()), 0);

		// 클라이언트 사각형에서 아이콘을 가운데에 맞춥니다.
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// 아이콘을 그립니다.
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		//CBrush *p_old_brush = dc.SelectObject(&m_my_brush);
		dc.FillSolidRect(0, 0, 160, 48, RGB(218, 218, 218));
		//dc.SelectObject(p_old_brush);
		//CDialogEx::OnPaint();
	}
}

// 사용자가 최소화된 창을 끄는 동안에 커서가 표시되도록 시스템에서
//  이 함수를 호출합니다.
HCURSOR CPatternBrushSampleDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}



void CPatternBrushSampleDlg::OnLButtonDown(UINT nFlags, CPoint point)
{

	CClientDC dc(this);

	CBrush* p_old_brush = dc.SelectObject(&m_my_brush);
	dc.SetBrushOrg(point.x - 24, point.y - 24);
	dc.Ellipse(point.x-24, point.y-24, point.x+24, point.y+24);
	dc.SelectObject(p_old_brush);

	CDialogEx::OnLButtonDown(nFlags, point);
}


void CPatternBrushSampleDlg::OnMouseMove(UINT nFlags, CPoint point)
{
	if (nFlags & MK_LBUTTON)
	{
		if (point.x < 160 && point.y < 48)
		{
			CClientDC dc(this);

			CBrush* p_old_brush = dc.SelectObject(&m_num_brush);
			CGdiObject* p_old_pen = dc.SelectStockObject(NULL_PEN);
			//dc.SelectStockObject(NULL_PEN); // 펜을 쓰지 않겠다. StockObject는 시스템이 미리 갖고있는 GDIOBJ
			dc.Rectangle(point.x - 5, point.y - 5, point.x + 5, point.y + 5);
			dc.SelectObject(p_old_brush);
			dc.SelectObject(p_old_pen);
		}
	}

	CDialogEx::OnMouseMove(nFlags, point);
}
