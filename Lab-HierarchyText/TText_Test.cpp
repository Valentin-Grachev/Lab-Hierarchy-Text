#include "TText.h"
#include "Control.h"
#include <conio.h>

#define DOWN 80
#define NEXT 77
#define UP 72
#define ESC 27
#define INSERT 82
#define DELETE 83
#define ENTER 13

//TMemory mem;


int main()
{
	char filename[100];
	bool saved = false;
begin:

	while (true)
	{
		clrscr();
		cout << "Enter filename: ";
		cin >> filename;

		TText text;
		text.Load(filename);
		text.GoFirstLine();
		

		while (true)
		{
			clrscr();
			cout << "Navigation: |v|>|<| ; INSERT - Insert line; ENTER - Update line;" << endl;
			cout << "DELETE - Delete line; S - Save text; ESC - Close text." << endl;
			text.Print();

			if (saved) cout << "Text saved." << endl;
			saved = false;

			char control = _getch();
			switch (control)
			{
			case DOWN: try { text.GoNextLine(); } catch (...) {} break;
			case UP: try { text.GoBackLine(); } catch (...){} break;
			case NEXT: try { text.GoDownLine(); } catch (...) {} break;

			case INSERT:
			{
				char str[81];
				cout << "1 - Next line; 2 - Next section; 3 - Down line; 4 - Down section; 5 - Cancel" << endl;
				char a = _getch();
				if (a == '5') break;
				cout << "Enter line: ";
				cin >> str;
				switch (a)
				{
				case '1': text.InsertNextLine(str); break;
				case '2': text.InsertNextSection(str); break;
				case '3': text.InsertDownLine(str); break;
				case '4': text.InsertDownSection(str); break;
				}
				break;
			}
				
				
			case ENTER:
				char str[81];
				cout << "Enter new line: ";
				cin >> str;
				text.SetNavCurrent(str);
				break;

			case 's':
				text.Print(filename);
				saved = true;
				break;

			case ESC:
				goto begin;
				break;

			case DELETE:
			{
				cout << "1 - Next line; 2 - Down line; 3 - Cancel" << endl;
				char a = _getch();
				if (a == '3') break;
				switch (a)
				{
				case '1': text.DeleteNextLine(); break;
				case '2': text.DeleteDownLine(); break;
				case '3': break;
				}
				break;
			}
				
			}
		}
	}
}