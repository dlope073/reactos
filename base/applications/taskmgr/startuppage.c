/*
 *  ReactOS Task Manager
 *
 *  startuppage.cpp
 *
 *  Copyright (C) 2019  Daniel Lopez  <dlopez@fiu.edu>
 *
 * This library is free software; you can redistribute it and/or
 * modify it under the terms of the GNU Lesser General Public
 * License as published by the Free Software Foundation; either
 * version 2.1 of the License, or (at your option) any later version.
 *
 * This library is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
 * Lesser General Public License for more details.
 *
 * You should have received a copy of the GNU Lesser General Public
 * License along with this library; if not, write to the Free Software
 * Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston, MA  02110-1301  USA
 */
#include "precomp.h"
#include "startuppage.h"

HWND hStartupPageListCtrl; 
HWND hStartupPageHeaderCtrl; 

static int      nStartupPageWidth;
static int      nStartupPageHeight;

INT_PTR CALLBACK StartupPageWndProc(HWND hDlg, UINT message, WPARAM wParam, LPARAM lParam)
{
	int     nXDifference;
	int     nYDifference;
	int     cx, cy;
	RECT    rc;
	switch (message) {
		case WM_INITDIALOG:
		{
			/*
			* Save the width and height
			*/
			GetClientRect(hDlg, &rc);
			nStartupPageWidth = rc.right;
			nStartupPageHeight = rc.bottom;

			/* Update window position */
			SetWindowPos(hDlg, NULL, 15, 30, 0, 0, SWP_NOACTIVATE | SWP_NOOWNERZORDER | SWP_NOSIZE | SWP_NOZORDER);

			/*
			 * Get handles to the controls
			 */
			hStartupPageListCtrl = GetDlgItem(hDlg, IDC_STARTUP_LIST);
			hStartupPageHeaderCtrl = ListView_GetHeader(hStartupPageListCtrl);

			/*
			 * Set the title, and extended window styles for the list control
			 */
			SetWindowTextW(hProcessPageListCtrl, L"Startup");
			(void)ListView_SetExtendedListViewStyle(hStartupPageListCtrl, ListView_GetExtendedListViewStyle(hStartupPageListCtrl) | LVS_EX_FULLROWSELECT | LVS_EX_HEADERDRAGDROP);
			break;
		}
		case WM_SIZE: 
		{
			if (wParam == SIZE_MINIMIZED)
				return 0;

			cx = LOWORD(lParam);
			cy = HIWORD(lParam);
			nXDifference = cx - nStartupPageWidth;
			nYDifference = cy - nStartupPageHeight;
			nStartupPageWidth = cx;
			nStartupPageHeight = cy;

			/* Reposition the application page's controls */
			GetWindowRect(hApplicationPageListCtrl, &rc);
			cx = (rc.right - rc.left) + nXDifference;
			cy = (rc.bottom - rc.top) + nYDifference;
			SetWindowPos(hApplicationPageListCtrl, NULL, 0, 0, cx, cy, SWP_NOACTIVATE | SWP_NOOWNERZORDER | SWP_NOMOVE | SWP_NOZORDER);
			InvalidateRect(hApplicationPageListCtrl, NULL, TRUE);

			GetClientRect(hApplicationPageEndTaskButton, &rc);
			MapWindowPoints(hApplicationPageEndTaskButton, hDlg, (LPPOINT)(PRECT)(&rc), sizeof(RECT) / sizeof(POINT));
			cx = rc.left + nXDifference;
			cy = rc.top + nYDifference;
			SetWindowPos(hApplicationPageEndTaskButton, NULL, cx, cy, 0, 0, SWP_NOACTIVATE | SWP_NOOWNERZORDER | SWP_NOSIZE | SWP_NOZORDER);
			InvalidateRect(hApplicationPageEndTaskButton, NULL, TRUE);

			GetClientRect(hApplicationPageSwitchToButton, &rc);
			MapWindowPoints(hApplicationPageSwitchToButton, hDlg, (LPPOINT)(PRECT)(&rc), sizeof(RECT) / sizeof(POINT));
			cx = rc.left + nXDifference;
			cy = rc.top + nYDifference;
			SetWindowPos(hApplicationPageSwitchToButton, NULL, cx, cy, 0, 0, SWP_NOACTIVATE | SWP_NOOWNERZORDER | SWP_NOSIZE | SWP_NOZORDER);
			InvalidateRect(hApplicationPageSwitchToButton, NULL, TRUE);

			GetClientRect(hApplicationPageNewTaskButton, &rc);
			MapWindowPoints(hApplicationPageNewTaskButton, hDlg, (LPPOINT)(PRECT)(&rc), sizeof(RECT) / sizeof(POINT));
			cx = rc.left + nXDifference;
			cy = rc.top + nYDifference;
			SetWindowPos(hApplicationPageNewTaskButton, NULL, cx, cy, 0, 0, SWP_NOACTIVATE | SWP_NOOWNERZORDER | SWP_NOSIZE | SWP_NOZORDER);
			InvalidateRect(hApplicationPageNewTaskButton, NULL, TRUE);

			break;
		}
	}

	return 0;
}