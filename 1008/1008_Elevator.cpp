#include <iostream>
using namespace std;  

int main()  
{  
	int N;
	cin >> N;
	int res = 0;
	int curr = 0, next = 0;
	while (N--)
	{
		cin >> next;
		if (next > curr)
		{
			res += (next - curr) * 6 + 5;
		}
		else
		{
			res += (curr - next) * 4 + 5;
		}
		curr = next;
	}
	cout << res << endl;

	return 0;  
}  