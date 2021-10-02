
// IonFuryEditorView.h: CIonFuryEditorView 클래스의 인터페이스
//

#pragma once


class CIonFuryEditorView : public CView
{
private:
	





protected: // serialization에서만 만들어집니다.
	CIonFuryEditorView() noexcept;
	DECLARE_DYNCREATE(CIonFuryEditorView)

// 특성입니다.
public:
	CIonFuryEditorDoc* GetDocument() const;

// 작업입니다.
public:

// 재정의입니다.
public:
	virtual void OnDraw(CDC* pDC);  // 이 뷰를 그리기 위해 재정의되었습니다.
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);
protected:
	virtual BOOL OnPreparePrinting(CPrintInfo* pInfo);
	virtual void OnBeginPrinting(CDC* pDC, CPrintInfo* pInfo);
	virtual void OnEndPrinting(CDC* pDC, CPrintInfo* pInfo);

// 구현입니다.
public:
	virtual ~CIonFuryEditorView();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// 생성된 메시지 맵 함수
protected:
	DECLARE_MESSAGE_MAP()
public:
	virtual void OnInitialUpdate();
	afx_msg void OnSize(UINT nType, int cx, int cy);
	afx_msg void OnTimer(UINT_PTR nIDEvent);
	virtual BOOL DestroyWindow();
	afx_msg void OnObject();
};

#ifndef _DEBUG  // IonFuryEditorView.cpp의 디버그 버전
inline CIonFuryEditorDoc* CIonFuryEditorView::GetDocument() const
   { return reinterpret_cast<CIonFuryEditorDoc*>(m_pDocument); }
#endif

