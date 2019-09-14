#include <Windows.h>

HINSTANCE _hInstance;
HWND _hWnd;
LPTSTR _IpszClass = TEXT("�簢���ű��");
LRESULT CALLBACK WndProc(HWND, UINT, WPARAM, LPARAM);
bool userControl = true;
RECT userRc = { 100, 100, 200, 200 };
RECT computerRC = { 300, 300, 400, 400 };
RECT smallRc = { 130,130,170,170 };
int APIENTRY WinMain(HINSTANCE hInstance,
	HINSTANCE hPrevInstance,
	LPSTR IpszCmdParam, int nCmdShow)
{
	_hInstance = hInstance;

	WNDCLASS WndClass;
	WndClass.cbClsExtra = 0;
	WndClass.cbWndExtra = 0;
	WndClass.hbrBackground = (HBRUSH)GetStockObject(WHITE_BRUSH);
	WndClass.hCursor = LoadCursor(NULL, IDC_ARROW);
	WndClass.hIcon = LoadIcon(NULL, IDI_APPLICATION);
	WndClass.hInstance = hInstance;
	WndClass.lpfnWndProc = (WNDPROC)WndProc;
	WndClass.lpszClassName = _IpszClass;
	WndClass.lpszMenuName = NULL;
	WndClass.style = CS_HREDRAW | CS_VREDRAW;

	RegisterClass(&WndClass);

	_hWnd = CreateWindow(
		_IpszClass,
		_IpszClass,
		WS_OVERLAPPEDWINDOW,
		100,
		100,
		800,
		800,
		NULL,
		(HMENU)NULL,
		hInstance,
		NULL
	);

	ShowWindow(_hWnd, nCmdShow);

	MSG message;
	while (GetMessage(&message, 0, 0, 0))
	{
		TranslateMessage(&message);
		DispatchMessage(&message);
	}
	return message.wParam;
}

LRESULT CALLBACK WndProc(HWND hWnd, UINT iMessage, WPARAM wParam, LPARAM lParam)
{
	HDC hdc;
	PAINTSTRUCT paint; //����Ʈ ����ü
	switch (iMessage)
	{
	case WM_CREATE:
		break;
	case WM_PAINT:
		hdc = BeginPaint(hWnd, &paint);
		Rectangle(hdc, userRc.left, userRc.top, userRc.right, userRc.bottom); //Ű����� �����̴� �簢��
		Rectangle(hdc, computerRC.left, computerRC.top, computerRC.right, computerRC.bottom); //�����̰� ������ �ϴ� �簢��
		Rectangle(hdc, smallRc.left, smallRc.top, smallRc.right, smallRc.bottom); //Ű����� �����̴� �簢��
		EndPaint(hWnd, &paint);
		break;
	case WM_KEYDOWN: //Ű���� Ű�� �������� �޼��� �߻�
		switch (wParam)
		{
		case VK_LEFT:	//���� ����Ű
			if (userRc.left > 0 && userControl == true) // ���� ������ �ƴҶ�
			{
				userRc.left -= 10;
				userRc.right -= 10;
				smallRc.left -= 5;
				smallRc.right -= 5;
				if (smallRc.right > userRc.right)
				{
					smallRc.left -= 5;
					smallRc.right -= 5;
				}
				//�÷��̾ �����̴� �簢���� ������ �����̰� �Ǵ� �簢���� �����ʺ��� �۾����� �Ǵ� ���
				//�÷��̾ �����̴� �簢���� ������ �����̰� �Ǵ� �簢���� ���ʺ��� ū ���
				//�����̰� �Ǵ� �簢���� ������ �� �𼭸����� �Ʒ� �𼭸����� ������ �������
				//�����̰� �Ǵ� �簢���� ���� ������ �ƴҋ�
				if ((userRc.left < computerRC.right && userRc.left > computerRC.left) && (userRc.top<computerRC.bottom && userRc.bottom>computerRC.top) && computerRC.left > 0)
				{
					computerRC.left -= 10;
					computerRC.right -= 10;
					smallRc.left = computerRC.left + 30;
					smallRc.right = computerRC.left + 70;
					smallRc.top = computerRC.top + 30;
					smallRc.bottom = computerRC.top + 70;
					userControl = false;
				}
				//�����̰� �Ǵ� �簢���� ���� ���� �ϋ�
				else if ((userRc.left < computerRC.right && userRc.left > computerRC.left) && (userRc.top<computerRC.bottom && userRc.bottom>computerRC.top) && computerRC.left <= 0)
				{
					userRc.left += 10;
					userRc.right += 10;
					userControl = false;
				}
				InvalidateRect(hWnd, NULL, true);
			}
			//��Ʈ���� �ٲ�
			else if (userControl == false)
			{
				computerRC.left -= 10;
				computerRC.right -= 10;
				smallRc.left -= 5;
				smallRc.right -= 5;
				if (smallRc.right > computerRC.right)
				{
					smallRc.left -= 5;
					smallRc.right -= 5;
				}
				//�÷��̾ �����̴� �簢���� ������ �����̰� �Ǵ� �簢���� �����ʺ��� �۾����� �Ǵ� ���
				//�÷��̾ �����̴� �簢���� ������ �����̰� �Ǵ� �簢���� ���ʺ��� ū ���
				//�����̰� �Ǵ� �簢���� ������ �� �𼭸����� �Ʒ� �𼭸����� ������ �������
				//�����̰� �Ǵ� �簢���� ���� ������ �ƴҋ�
				if ((computerRC.left < userRc.right && computerRC.left > userRc.left) && (computerRC.top<userRc.bottom && computerRC.bottom>userRc.top) && userRc.left > 0)
				{
					userRc.left -= 10;
					userRc.right -= 10;
					smallRc.left = userRc.left + 30; //�ε�ġ�� �簢�� �߾����� �̵�
					smallRc.right = userRc.left + 70;
					smallRc.top = userRc.top + 30;
					smallRc.bottom = userRc.top + 70;
					userControl = true;
				}
				//�����̰� �Ǵ� �簢���� ���� ���� �ϋ�
				else if ((computerRC.left < userRc.right && computerRC.left > userRc.left) && (computerRC.top<userRc.bottom && computerRC.bottom>userRc.top) && userRc.left <= 0)
				{
					computerRC.left += 10;
					computerRC.right += 10;
				}
				InvalidateRect(hWnd, NULL, true);
			}
			break;
		case VK_RIGHT:	//������ ����Ű
			if (userRc.right < 785 && userControl == true)// ���� �������� �ƴҶ�
			{
				userRc.left += 10;
				userRc.right += 10;
				smallRc.left += 5;
				smallRc.right += 5;
				if (smallRc.left < userRc.left)
				{
					smallRc.left += 5;
					smallRc.right += 5;
				}
				//�÷��̾ �����̴� �簢���� �������� �����̰� �Ǵ� �簢���� ���ʺ��� Ŀ���� �Ǵ� ���
				//�÷��̾ �����̴� �簢���� �������� �����̰� �Ǵ� �簢���� �����ʺ��� ���� ���
				//�����̰� �Ǵ� �簢���� ���� �� �𼭸����� �Ʒ� �𼭸����� ������ �������
				//�����̰� �Ǵ� �簢���� ���� �������� �ƴҋ�
				if ((userRc.right > computerRC.left && userRc.right < computerRC.right) && (userRc.top<computerRC.bottom && userRc.bottom>computerRC.top) && computerRC.right<785)
				{
					computerRC.left += 10;
					computerRC.right += 10;
					smallRc.left = computerRC.left + 30;//�ε�ġ�� �簢�� �߾����� �̵�
					smallRc.right = computerRC.left + 70;
					smallRc.top = computerRC.top + 30;
					smallRc.bottom = computerRC.top + 70;
					userControl = false;
				}
				//�����̰� �Ǵ� �簢���� ���� ������ �ϋ�
				else if ((userRc.right > computerRC.left && userRc.right < computerRC.right) && (userRc.top<computerRC.bottom && userRc.bottom>computerRC.top) && computerRC.right >= 785)
				{
					userRc.left -= 10;
					userRc.right -= 10;
					userControl = false;
				}
				InvalidateRect(hWnd, NULL, true);
			}
			//��Ʈ���� �ٲ�
			else if (computerRC.right < 785 && userControl == false)// ���� �������� �ƴҶ�
			{
				computerRC.left += 10;
				computerRC.right += 10;
				smallRc.left += 5;
				smallRc.right += 5;
				if (smallRc.left < computerRC.left)
				{
					smallRc.left += 5;
					smallRc.right += 5;
				}
				//�÷��̾ �����̴� �簢���� �������� �����̰� �Ǵ� �簢���� ���ʺ��� Ŀ���� �Ǵ� ���
				//�÷��̾ �����̴� �簢���� �������� �����̰� �Ǵ� �簢���� �����ʺ��� ���� ���
				//�����̰� �Ǵ� �簢���� ���� �� �𼭸����� �Ʒ� �𼭸����� ������ �������
				//�����̰� �Ǵ� �簢���� ���� �������� �ƴҋ�
				if ((computerRC.right > userRc.left && computerRC.right < userRc.right) && (computerRC.top<userRc.bottom && computerRC.bottom>userRc.top) && userRc.right<785)
				{
					userRc.left += 10;
					userRc.right += 10;
					smallRc.left = userRc.left + 30;//�ε�ġ�� �簢�� �߾����� �̵�
					smallRc.right = userRc.left + 70;
					smallRc.top = userRc.top + 30;
					smallRc.bottom = userRc.top + 70;
					userControl = true;
				}
				//�����̰� �Ǵ� �簢���� ���� ������ �ϋ�
				else if ((computerRC.right > userRc.left && computerRC.right < userRc.right) && (computerRC.top<userRc.bottom && computerRC.bottom>userRc.top) && userRc.right >= 785)
				{
					computerRC.left -= 10;
					computerRC.right -= 10;
					userControl = true;
				}
				InvalidateRect(hWnd, NULL, true);
			}
			break;
		case VK_UP: //���� ����Ű
			if (userRc.top > 0 && userControl == true)// ���� ������ �ƴҶ�
			{
				userRc.top -= 10;
				userRc.bottom -= 10;
				smallRc.top -= 5;
				smallRc.bottom -= 5;
				if (smallRc.bottom > userRc.bottom)
				{
					smallRc.top -= 5;
					smallRc.bottom -= 5;
				}
				//�÷��̾ �����̴� �簢���� ������ �����̰� �Ǵ� �簢���� �Ʒ��ʺ��� �۾����� �Ǵ� ���
				//�÷��̾ �����̴� �簢���� ������ �����̰� �Ǵ� �簢���� ���ʺ��� ū ���
				//�����̰� �Ǵ� �簢���� �Ʒ��� ���� �𼭸����� ������ �𼭸����� ������ �������
				//�����̰� �Ǵ� �簢���� ���� ������ �ƴҋ�
				if ((userRc.top < computerRC.bottom && userRc.top > computerRC.top) && (userRc.right > computerRC.left && userRc.left < computerRC.right) && computerRC.top >0)
				{

					computerRC.top -= 10;
					computerRC.bottom -= 10;
					smallRc.left = computerRC.left + 30;//�ε�ġ�� �簢�� �߾����� �̵�
					smallRc.right = computerRC.left + 70;
					smallRc.top = computerRC.top + 30;
					smallRc.bottom = computerRC.top + 70;
					userControl = false;
				}
				//�����̰� �Ǵ� �簢���� ���� ���� �ϋ�
				else if ((userRc.top < computerRC.bottom && userRc.top > computerRC.top) && (userRc.right > computerRC.left && userRc.left < computerRC.right) && computerRC.top <= 0)
				{
					userRc.top += 10;
					userRc.bottom += 10;
					userControl = false;
				}

				InvalidateRect(hWnd, NULL, true);
			}
			//��Ʈ���� �ٲ�
			else if (computerRC.top > 0 && userControl == false)// ���� ������ �ƴҶ�
			{
				computerRC.top -= 10;
				computerRC.bottom -= 10;
				smallRc.top -= 5;
				smallRc.bottom -= 5;
				if (smallRc.bottom > computerRC.bottom)
				{
					smallRc.top -= 5;
					smallRc.bottom -= 5;
				}
				//�÷��̾ �����̴� �簢���� ������ �����̰� �Ǵ� �簢���� �Ʒ��ʺ��� �۾����� �Ǵ� ���
				//�÷��̾ �����̴� �簢���� ������ �����̰� �Ǵ� �簢���� ���ʺ��� ū ���
				//�����̰� �Ǵ� �簢���� �Ʒ��� ���� �𼭸����� ������ �𼭸����� ������ �������
				//�����̰� �Ǵ� �簢���� ���� ������ �ƴҋ�
				if ((computerRC.top < userRc.bottom && computerRC.top > userRc.top) && (computerRC.right > userRc.left && computerRC.left < userRc.right) && userRc.top >0)
				{

					userRc.top -= 10;
					userRc.bottom -= 10;
					smallRc.left = userRc.left + 30;//�ε�ġ�� �簢�� �߾����� �̵�
					smallRc.right = userRc.left + 70;
					smallRc.top = userRc.top + 30;
					smallRc.bottom = userRc.top + 70;
					userControl = true;
				}
				//�����̰� �Ǵ� �簢���� ���� ���� �ϋ�
				else if ((computerRC.top < userRc.bottom && computerRC.top > userRc.top) && (computerRC.right > userRc.left && computerRC.left < userRc.right) && userRc.top <= 0)
				{
					computerRC.top += 10;
					computerRC.bottom += 10;
					userControl = true;
				}
				InvalidateRect(hWnd, NULL, true);
			}
			break;
		case VK_DOWN://�Ʒ��� ����Ű
			if (userRc.bottom < 760 && userControl == true)// ���� �Ʒ����� �ƴҶ�
			{
				userRc.top += 10;
				userRc.bottom += 10;
				smallRc.top += 5;
				smallRc.bottom += 5;
				if (smallRc.top < userRc.top)
				{
					smallRc.top += 5;
					smallRc.bottom += 5;
				}
				//�÷��̾ �����̴� �簢���� �Ʒ����� �����̰� �Ǵ� �簢���� ���ʺ��� Ŀ���� �Ǵ� ���
				//�÷��̾ �����̴� �簢���� �Ʒ����� �����̰� �Ǵ� �簢���� �Ʒ��ʺ��� ū ���
				//�����̰� �Ǵ� �簢���� ���� ���� �𼭸����� ������ �𼭸����� ������ �������
				//�����̰� �Ǵ� �簢���� ���� �Ʒ����� �ƴҋ�
				if ((userRc.bottom > computerRC.top && userRc.bottom < computerRC.bottom) && (userRc.right > computerRC.left && userRc.left < computerRC.right) && computerRC.bottom < 760)
				{
					computerRC.top += 10;
					computerRC.bottom += 10;
					smallRc.left = computerRC.left + 30;//�ε�ġ�� �簢�� �߾����� �̵�
					smallRc.right = computerRC.left + 70;
					smallRc.top = computerRC.top + 30;
					smallRc.bottom = computerRC.top + 70;
					userControl = false;
				}
				//�����̰� �Ǵ� �簢���� ���� �Ʒ��� �ϋ�
				else if ((userRc.bottom > computerRC.top && userRc.bottom < computerRC.bottom) && (userRc.right > computerRC.left && userRc.left < computerRC.right) && computerRC.bottom >= 760)
				{
					userRc.top -= 10;
					userRc.bottom -= 10;
					userControl = false;
				}
				InvalidateRect(hWnd, NULL, true);
			}
			//��Ʈ���� �ٲ�
			else if (computerRC.bottom < 760 && userControl == false)// ���� �Ʒ����� �ƴҶ�
			{
				computerRC.top += 10;
				computerRC.bottom += 10;
				smallRc.top += 5;
				smallRc.bottom += 5;
				if (smallRc.top < computerRC.top)
				{
					smallRc.top += 5;
					smallRc.bottom += 5;
				}
				//�÷��̾ �����̴� �簢���� �Ʒ����� �����̰� �Ǵ� �簢���� ���ʺ��� Ŀ���� �Ǵ� ���
				//�÷��̾ �����̴� �簢���� �Ʒ����� �����̰� �Ǵ� �簢���� �Ʒ��ʺ��� ū ���
				//�����̰� �Ǵ� �簢���� ���� ���� �𼭸����� ������ �𼭸����� ������ �������
				//�����̰� �Ǵ� �簢���� ���� �Ʒ����� �ƴҋ�
				if ((computerRC.bottom > userRc.top && computerRC.bottom < userRc.bottom) && (computerRC.right > userRc.left && computerRC.left < userRc.right) && userRc.bottom < 760)
				{
					userRc.top += 10;
					userRc.bottom += 10;
					smallRc.left = userRc.left + 30;//�ε�ġ�� �簢�� �߾����� �̵�
					smallRc.right = userRc.left + 70;
					smallRc.top = userRc.top + 30;
					smallRc.bottom = userRc.top + 70;
					userControl = true;
				}
				//�����̰� �Ǵ� �簢���� ���� �Ʒ��� �ϋ�
				else if ((computerRC.bottom > userRc.top && computerRC.bottom < userRc.bottom) && (computerRC.right > userRc.left && computerRC.left < userRc.right) && userRc.bottom >= 760)
				{
					computerRC.top -= 10;
					computerRC.bottom -= 10;
					userControl = true;
				}
				InvalidateRect(hWnd, NULL, true);
			}
			break;
		}
		break;
	case WM_DESTROY:
		PostQuitMessage(0);
		return 0;
	}

	return (DefWindowProc(hWnd, iMessage, wParam, lParam));
}