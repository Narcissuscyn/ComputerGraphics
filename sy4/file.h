#ifndef FILE_H
#define FILE_H
typedef int Boundary;
#endif

//void CTest4View::cutPoint(CPoint p, Boundary b, CPoint winMin, CPoint winMax, CPoint* pOut, int* cnt, CPoint* first[], CPoint* s)
//{
//	CPoint pTemp;
//	if (!first[b])
//	{
//		first[b] = &p;
//	}
//	else
//	{
//		if (isCross(p,s[b],b,winMin,winMax))
//		{
//			pTemp = interSect(p, s[b], b, winMin, winMax);
//			if (b<3)
//			{
//				cutPoint(pTemp, b+1, winMin, winMax, pOut, cnt, first, s);
//			}
//		else
//		{
//			pOut[*cnt] = pTemp;
//			(*cnt)++;
//		}
//		}
//		s[b] = p;
//		if (isPointInside(p,b+1,winMin,winMax))
//		{
//			if (b<3)
//			{
//				cutPoint(p, b + 1, winMin, winMax, pOut, cnt, first, s);
//			}
//			else
//			{
//				pOut[*cnt] = p;
//				(*cnt)++;
//			}
//		}
//	}
//}
//
//
//void CTest4View::closeCut(CPoint winMin, CPoint winMax, CPoint* pOut, int* cnt, CPoint* first[], CPoint* s)
//{
//	CPoint pTemp;
//	Boundary edge;
//	for (edge = 0; edge < 3;edge++)
//	{
//		if (isCross(s[edge],*first[edge],edge,winMin,winMax))
//		{
//			pTemp = interSect(s[edge], *first[edge], edge, winMin, winMax);
//			if (edge<3)
//			{
//				cutPoint(pTemp, edge + 1, winMin, winMax, pOut, cnt, first, s);
//
//			}
//			else
//			{
//				pOut[*cnt] = pTemp;
//				(*cnt)++;
//			}
//		}
//	}
//}
//
//
//int CTest4View::polygonPoint(CPoint winMin, CPoint winMax, int n, CPoint* pIn, CPoint* pOut)
//{
//	ClearScreen();
//	CPoint* first[clip_num] = { 0, 0, 0, 0 }, s[clip_num];
//	int k, cnt = 0;
//	for (k = 0; k < n;k++)
//	{
//		cutPoint(pIn[k], 0, winMin, winMax, pOut, &cnt, first, s);
//	}
//	closeCut(winMin, winMax, pOut, &cnt, first, s);
//	return cnt;
//}
